#include <iostream>
#include <filesystem>
#include <string>
#include <windows.h>
#include "git.hpp"
using namespace std;

int main(int argc, char *argv[]) {
    SetConsoleOutputCP(65001);
    Git git;
    if (argc >= 2) {
        string command = string(argv[1]);
        if (command == "help") {
            // mygit help
            git.help();
        } else if (command == "init") {
            // mygit init
            if (filesystem::exists(".mygit")) {
                cout << "Repository already initialized." << endl;
            } else {
                git.init();
                cout << "Repository initialized successfully." << endl;
            }
            
        } else if (command == "add") {
            // mygit add <filename>
            git.add();
        } else if (command == "commit") {
            // mygit commit -m "message"
            //git.commit();
        } else if (command == "log") {
            // mygit log
            git.log();
        } else if (command == "status") {
            // mygit status
            git.status();
        } else {
            cout << "Unknown command: " << command << endl;
            cout << "Use 'help' to see available commands." << endl;
        }
    } else {
        git.help();
    }
    







    return 0;
}





