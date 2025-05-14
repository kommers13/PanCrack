#ifndef CHECKCOMMAND_H
#define CHECKCOMMAND_H
#include <string>
#include <vector>
#include <unordered_map>
#include <graph.h>
#include <task0.h>
#include <task5.h>
#include <task6.h>
#include "../listcommands.h"
#include "../dataconverse.h"
using namespace std;
class CheckCommand
{
public:
    static string execute(
        const string& command,      // имя команды
        const vector<string>& args, // вектор строк-аргументов
        const vector<string>& opts  // вектор опций
        );
};

#endif // CHECKCOMMAND_H
