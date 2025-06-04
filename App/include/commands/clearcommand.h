#ifndef CLEARCOMMAND_H
#define CLEARCOMMAND_H


#include <QDebug>

#include "../signals.h"
#include "../listcommands.h"

#include <string>
#include <vector>

#include "macros/commacros.h"

// я никогда не умел нормально называть файлы и классы - я знаю

using namespace std;


class ClearCommand
{

public:


    /* ../cominf/help/clear.html */

    // функция возвращает строку результат команды
    // в данном случае, кроме основных имени команды, аргументов и опций, нам понадобился
    // указатель на Signals, так как будет вызываться реализация функция в JS
    static string execute(const string& command,
                          const vector<string>& args,
                          const vector<string>& opts,
                          Signals* my_signals);
};

#endif // CLEARCOMMAND_H
