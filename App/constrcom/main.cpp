#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>

#include "include/json.hpp"


using namespace std;
using json = nlohmann::json;
namespace fs = std::filesystem;


// запись содержимого help_file-а в поле description com_file-а
void write_help(const string& help_file, const string& com_file) {

    ifstream in_help(help_file);
    ifstream in_com(com_file);

    try {
        json j = json::parse(in_com);
        string buffer;
        string help_message = "";
        while (in_help >> buffer) {
            help_message += buffer + " ";
        }

        j["description"] = help_message;

        ofstream out_com(com_file);
        out_com << j;

        cout << help_file << " was INSERTED into " << com_file;
    }
    catch (const exception& e) {
        cout << help_file << " was NOT inserted into " << com_file;
    }
}

// вставляем help-ы внутрь json-файлов
void write_helps(const string& help_folder, const string& com_folder) {

    cout << "HELP_FOLDER: " << help_folder << '\n';
    cout << "COM_FOLDER: " << com_folder << '\n';
    cout << '\n';

    vector<string> commands_helps;
    for (auto entry: fs::directory_iterator(help_folder)) {
        commands_helps.push_back(entry.path().filename().u8string());
    }

    int count = 0;

    for (string commands_help: commands_helps) {
        write_help(help_folder + commands_help,
                   // ".html".size() is 5
                   com_folder + commands_help.substr(0, commands_help.size() - 5) + ".json");
        count++;
        cout << '\n';
    }

    cout << '\n';
    cout << count << "/" << commands_helps.size() << " help-files were inserted\n";
}

int main(int argc, char* argv[]) {

    string path = argv[1];

    write_helps(path + "/help/", path + "/");

    return 0;
}
