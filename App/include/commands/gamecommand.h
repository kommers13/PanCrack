#ifndef GAMECOMMAND_H
#define GAMECOMMAND_H

#include <string>
#include <vector>


#include "../signals.h"
#include "../listcommands.h"

#include "macros/commacros.h"


using namespace std;


class GameCommand {
public:

    static string execute(const string& command,
                          const vector<string>& args,
                          const vector<string>& opts,
                          Signals* my_signals);

};

#endif // GAMECOMMAND_H
