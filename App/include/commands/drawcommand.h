#ifndef DRAWGRAPH_H
#define DRAWGRAPH_H


#include <string>
#include <vector>
#include <filesystem>

#include <QVariantMap>

#include "../signals.h"
#include "../dataconverse.h"
#include "../listcommands.h"

#include "../graphdraw.h"


namespace fs = std::filesystem;
using namespace std;


class DrawCommand
{

    /*
      Команда принимает только один обязательный аргумент - имя графа
      Также есть необязательная опция -h (--help) для вывода описания


      Команда рисует граф с именем G
    */


public:


    static string execute(const string& command,
                          const vector<string>& args,
                          const vector<string>& opts,
                          Signals* my_signals);
};

#endif // DRAWGRAPH_H
