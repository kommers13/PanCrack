#include "include/listcommands.h"
#include <iostream>

// получение информации о команде
tuple<string,       // имя команды
      string,       // описание команды
      unordered_map<string, string> // опции команды (длинная и короткая в паре)
      >
        ListCommands::get(const string& command_name) {

    ifstream in("cominf/" + command_name + ".json");
    json command_data = json::parse(in);
    unordered_map<string, string> options;

    for (auto option_pair: command_data["options"]) {
        for (auto [full_opt, shorthand_opt]: option_pair.items()) {
            options[shorthand_opt] = full_opt;
        }
    }

    return make_tuple(command_data["name"],
                       command_data["description"],
                       options);
}

// проверка существование команды
bool ListCommands::exist_command(const string& command) {
    const string path = "cominf";
    for (const auto& entry: fs::directory_iterator(path)) {
        if (entry.path() == (path + "\\" + command + ".json")) {
            return true;
        }
    }
    return false;
}
