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


using namespace std;

class CommandParser : public QObject
{

    Q_OBJECT


    // список доступных команд
    vector<pair<string, string>> commands_and_help;
    // Команда, например, create, show, prufer
    string command;
    // Аргументы команды, например, GRAPH_NAME (for create), 11232122 (for prufer)
    vector<string> arguments;
    // Опции команды, например, --matrix_of_adjancency (-madj), --all (-a), --code (-c)
    vector<string> options;   // массив опций

public:

    /*
    Шаблон любой команды:
    <command> <arguments> [<options>]
    <command> - имя команды (одно слово)
    <arguments> - обязательные аргументы (может быть несколько, один или ни одного)
    <options> - опции команды (может быть несколько, одно или ни одного)
    Парсинг происходит следующим образом: первое слово - это команда, все слова после него без
    дефисов - это позиционные или непозиционные аргументы, все слова с двумя дефисами
    или одним - это непозиционные опции
    */

    // Конструктор парсера команд
    CommandParser(const vector<pair<string, string>>& coms_and_hlp);

    // преобразованная команды
    // string - команда
    // vector<string> - вектор аргументов
    // vector<string> - вектор опций
    tuple<string, vector<string>, vector<string>> process_command(const string& input);

public slots:
    // вставка результата команды в консоль
    // input - сырая строка от пользователя
    // output - компонент, в который будет вставлен ответ в виде текста
    void on_output_command(const QString& input, QObject* answer_field);

};

#endif // COMMANDPARSER_H
