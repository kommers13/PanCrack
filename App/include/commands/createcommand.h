#ifndef CREATECOMMAND_H
#define CREATECOMMAND_H

#include <QDebug>

#include "../signals.h"
#include "../listcommands.h"
#include "../dataconverse.h"

#include <graph.h>

#include <string>
#include <vector>
#include <filesystem>

#include "macros/commacros.h"


using namespace std;
namespace fs = std::filesystem;


class CreateCommand
{
public:


    // cominf/create.json

    static string execute(const string& command,
                          const vector<string>& args,
                          const vector<string>& opts);
};

#endif // CREATECOMMAND_H
