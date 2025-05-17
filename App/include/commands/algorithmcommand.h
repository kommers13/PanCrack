#ifndef ALGORITHMCOMMAND_H
#define ALGORITHMCOMMAND_H
#include <string>
#include <vector>
#include <unordered_map>
#include <graph.h>
#include <task1.h>
#include <task2.h>
#include <task3.h>
#include <task4.h>
#include <task7.h>
#include <task9.h>
#include "../listcommands.h"
#include "../dataconverse.h"
class AlgorithmCommand
{
public:
    static string execute(
        const string& command,      // имя команды
        const vector<string>& args, // вектор строк-аргументов
        const vector<string>& opts  // вектор опций
        );
};

#endif // ALGORITHMCOMMAND_H
