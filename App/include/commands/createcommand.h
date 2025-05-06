#ifndef CREATECOMMAND_H
#define CREATECOMMAND_H

#include <QDebug>

#include "../signals.h"
#include "../listcommands.h"

#include <graph.h>

#include <string>
#include <vector>

using namespace std;

class CreateCommand
{
public:


    // cominf/create.json

    // функция возвращает строку результат команды
    // в данном случае, кроме основных имени команды, аргументов и опций, нам понадобился
    // указатель на Signals, так как будет вызываться реализация функция в JS
    static string execute(const string& command,
                          const vector<string>& args,
                          const vector<string>& opts,
                          Signals* my_signals);
};

#endif // CREATECOMMAND_H
