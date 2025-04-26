#ifndef LISTCOMMANDS_H
#define LISTCOMMANDS_H

#include <vector>
#include <string>

using namespace std;

// вектор пар, где пара - это две строки: имя команды и ее описание
// (то описание, которое вызывается командой <command> --help)

const vector<pair<string, string>> commands_list = {

{"clear", "NAME\n"
          "\tCLEAR - clear the terminal screen\n"
          "SYNOPSIS\n"
          "\tCLEAR\n"
          "DESCRIPTION\n"
          "\tCLEAR just returns screen to original state. CLEAR doesn`t have any options\n"}

};

#endif // LISTCOMMANDS_H
