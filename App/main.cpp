// Copyright (C) 2024 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "autogen/environment.h"

#include "include/signals.h"
#include "include/commandparser.h"
#include "include/listcommands.h"


int main(int argc, char *argv[])
{
    set_qt_environment();
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(mainQmlFile);
    QObject::connect(
                &engine, &QQmlApplicationEngine::objectCreated, &app,
                [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);


    // регистрация классов (ПЕРЕД ЗАГРУЗКОЙ QML-контента)
    qmlRegisterType<Signals>("signals", 1, 0, "Signals");

    engine.addImportPath(QCoreApplication::applicationDirPath() + "/qml");
    engine.addImportPath(":/");
    engine.load(url);

    if (engine.rootObjects().isEmpty())
        return -1;


    // связывание сигналов со слотами
    // берем объект из QML в C++
    Signals* all_signals = engine.rootObjects().first()->findChild<Signals*>("signals_id_");

    // класс CommandParser, предоставляющий функциональность парсера вводимых строк
    CommandParser* command_parser = new CommandParser(all_signals);

    // соединения сигнала, который вызывает обработчик строки ввода от пользователя
    QObject::connect(all_signals, &Signals::output_command,
                      command_parser, &CommandParser::on_output_command);

    // QObject::connect(all_signals, &Signals::get_command);

    return app.exec();
}
