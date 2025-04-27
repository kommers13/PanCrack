#ifndef LISTCOMMANDS_H
#define LISTCOMMANDS_H

#include <vector>
#include <string>
#include <unordered_map>
#include <tuple>
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

namespace list_commands {

// name - key, description, options - value
unordered_map<string, pair<string, vector<string>>> get_all();

// возвращает данные команды по ее имени из JSON-файла
// name, description, options
tuple<string, string, vector<string>> get(const string& command_name);

}

#endif // LISTCOMMANDS_H
