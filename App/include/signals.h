#ifndef SIGNALS_H
#define SIGNALS_H

#include <QObject>
#include <graph.h>

class Signals : public QObject
{
    Q_OBJECT

    /*
    Класс для сигналов, которые будут испускаться из QML для C++
    И из C++ в QML (в компонент Signals)
    */

public:
    explicit Signals(QObject *parent = nullptr);

signals:
    QString output_command(const QString& input);
    // сигнал для рисования графа
    void graphDraw(const QVariantMap& graph);
    // сигналы для ВСЕХ команд
    void clearCommand();
};

#endif // SIGNALS_H
