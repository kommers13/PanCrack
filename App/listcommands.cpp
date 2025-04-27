#include "include/listcommands.h"
#include <iostream>

tuple<string, string, vector<string>> list_commands::get(const string& command_name) {
    ifstream in("data/" + command_name + ".json");
    json command_data = json::parse(in);
    vector<string> options = command_data["options"];
    return make_tuple(command_data["name"],
                      command_data["description"],
                      options);
}
