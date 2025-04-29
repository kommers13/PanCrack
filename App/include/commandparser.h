#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H

#include <string>
#include <unordered_set>
#include <vector>
#include <tuple>

#include <QObject>
#include <QString>
#include <QQuickView>
#include <QQuickItem>

#include "listcommands.h"


using namespace std;

class CommandParser : public QObject
{

    Q_OBJECT


    // класс, который предоставляет информацию о командах
    ListCommands* list_commands;


    /*
    Шаблон любой команды:
    <command> [<arguments>...] [<options>...]
    <command> - имя команды (одно слово)
    <arguments> - аргументы (может быть несколько, один или ни одного)
    <options> - опции команды (может быть несколько, одно или ни одного)
    Парсинг происходит следующим образом: первое слово - это команда, все слова после него без
    дефисов - это позиционные или непозиционные аргументы, все слова с двумя дефисами
    или одним - это непозиционные опции
    */


    // преобразованная команды
    // string -

    // vector<string> - вектор опций (они всегда полные, т. е. из -h будет --help,
    // а если --help, то опция изменятся не будет)
    tuple<string,    // имя команды
          vector<string>, // вектор аргументов
          vector<string>  // вектор опций (они всегда полные, т. е. из -h будет --help,
                          // а если --help, то опция изменятся не будет)
          > process_command(string input);

public:

    // Конструктор CommandParser, который принимает в качестве параметра объект ListCommands
    // эти объекты создаются в единственном экземпляре, и они не являются пространствами имен,
    // потому что их методы могут быть задействованы в качестве слотов
    CommandParser(ListCommands* _list_commands);

public slots:
    // вставка результата команды в консоль
    // input - сырая строка от пользователя
    // возвращается строка ответа команды
    QString on_output_command(const QString& input);

};

#endif // COMMANDPARSER_H
