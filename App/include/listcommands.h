#ifndef LISTCOMMANDS_H
#define LISTCOMMANDS_H

#include <QObject>

#include <vector>
#include <string>
#include <unordered_map>
#include <tuple>
#include <fstream>

#include "json.hpp"
#include <filesystem>


using json = nlohmann::json;
namespace fs = std::filesystem;
using namespace std;


namespace list_commands
{

/*
Эта область имен содержит функции, которые читают по запросу данные о команде <command> из файла
App/cominf/<command>.json
Формат добавление команды и ее описание ПОКА ЧТО такой, покажем на примере
команды clear.
Файл App/cominf/clear.json:

    {
      "name": "clear",
      "description": "NAME\n\tCLEAR - clear the terminal screen\nSYNOPSIS\n\tCLEAR\nDESCRIPTION\n\tCLEAR just returns screen to original state. CLEAR doesn`t have any options\n",
      "options": [
            {"-h": "--help"},
        ]
    }

Где "name" - имя команды, "description" - тот текст, который будет показываться при вводе
    <command> --help
или
    <command> -h
В данном случае
    clear --help
или
    clear -h

Замечание: у каждой команды есть как минимум ОДНА необязательная опция - это --help (-h),
которая выводит описание команды
*/

// Возвращает неупорядоченный словарь данных о команде,
// где команда является ключом, а остальные данные о ней - значением
// name - key, description, options - value
// DEPRECECATED
unordered_map<string,                               // имя команды
              pair<string,                          // описание (<command> --help)
                   unordered_map<string, string>    // опции команды (--help (-h), --show (-s))
                   >
                > get_all();

// возвращает данные команды по ее имени из JSON-файла
// JSON-файлы команд находятся в папке App/cominf
tuple<string,                       // имя команды
      string,                       // описание (<command> --help)
      // пары симетричны, т. е. если есть {a, b}, то есть и {b, a}
      unordered_map<string, string> // опции команды (--help (-h), --show (-s))
      > get(const string& command_name);

// проверяет, существует ли такая команда
bool exist_command(const string& command);

};

#endif // LISTCOMMANDS_H
