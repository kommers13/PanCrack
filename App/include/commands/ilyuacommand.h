#ifndef ILYUACOMMAND_H
#define ILYUACOMMAND_H

#include <vector>
#include <string>


using namespace std;

class ILYUACommand
{


    /* Команда ILYA */

public:


    static string execute(const string& command,
                          const vector<string>& args,
                          const vector<string>& opts);
};

#endif // ILYUACOMMAND_H
