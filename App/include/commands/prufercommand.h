#ifndef PRUFERCOMMAND_H
#define PRUFERCOMMAND_H
#include "../listcommands.h"
#include <string>
#include <vector>
using namespace std;
class prufercommand
{
public:
    static string execute(const string& command,
                          const vector<string>& args,
                          const vector<string>& opts);
};

#endif // PRUFERCOMMAND_H
