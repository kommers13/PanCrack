#ifndef CLEARCOMMAND_H
#define CLEARCOMMAND_H


#include <QDebug>

#include "../signals.h"
#include "../listcommands.h"

#include <string>
#include <vector>

// я никогда не умел нормально называть файлы и классы

using namespace std;


class ClearCommand
{

public:


    /*

    NAME

        CLEAR - clear the terminal screen

    SYNOPSIS

        CLEAR [-h]

    DESCRIPTION

        CLEAR just returns screen to original state.
        -h, --help - option that shows this text.

    */

    // функция возвращает строку результат команды
    // в данном случае, кроме основных имени команды, аргументов и опций, нам понадобился
    // указатель на Signals, так как будет вызываться реализация функция в JS
    static string execute(const string& command,
                          const vector<string>& args,
                          const vector<string>& opts,
                          Signals* my_signals);
};

#endif // CLEARCOMMAND_H
