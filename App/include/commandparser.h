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

#include "signals.h"
#include "listcommands.h"

// заголовчные файлы для команд
#include "commands/clearcommand.h"
#include "commands/createcommand.h"
#include "commands/drawcommand.h"
#include "commands/showcommand.h"
#include "commands/viewcommand.h"
#include "commands/prufercommand.h"
#include "commands/algorithmcommand.h"
#include "commands/checkcommand.h"
#include "commands/helpcommand.h"


using namespace std;

class CommandParser : public QObject
{

    Q_OBJECT

    // класс, который предоставляет доступ к сигналам
    Signals* my_signals;


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
    // string - имя команды

    // vector<string> - вектор опций (они всегда полные, т. е. из -h будет --help,
    // а если --help, то опция изменятся не будет)
    tuple<string,    // имя команды
          vector<string>, // вектор аргументов
          vector<string>  // вектор опций (они всегда полные, т. е. из -h будет --help,
                          // а если --help, то опция изменятся не будет)
          > process_command(string input);

    // выбор команд
    // в качестве параметров передаем спаршенную команду для выполнения
    // возвращается результат выполнения команды
    string execute_command(const string& command,
                            const vector<string>& args,
                            const vector<string>& opts);

public:

    // Конструктор CommandParser принимает один параметр - это указатель на объект Signals,
    // который дает доступ с сигналам
    CommandParser(Signals* _my_signals);

public slots:
    // вставка результата команды в консоль
    // input - сырая строка от пользователя
    // возвращается строка ответа команды
    QString on_output_command(const QString& input);

};

#endif // COMMANDPARSER_H
