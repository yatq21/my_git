#include <iostream>
#include <fstream>
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
            git.help();
        } else if (command == "init") {
            git.init();
        } else if (command == "add") {
            git.add();
        } else if (command == "commit") {
            git.commit();
        } else if (command == "log") {
            git.log();
        } else if (command == "status") {
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





