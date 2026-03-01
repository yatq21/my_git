#include <iostream>
#include <filesystem>
#include <string>
#include <windows.h>
#include "git.hpp"
#include "hash_utils.hpp"
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
            // 此处add仅支持单文件的添加,无法递归.
            for (int i = 2; i < argc; i++) {
                git.add(argv[i]);
            }
        } else if (command == "commit") {
            // mygit commit -m "message"
            if (argc >= 4 && string(argv[2]) == "-m") {
                string log_message = argv[3];
                string commit_id = hash_utils::compute_commit_id_from_staging(".mygit/staging_area");
                if (commit_id.empty()) {
                    cout << "Staging area is empty, nothing to commit." << endl;
                    return 0;
                }
                git.load_head_commit();
                git.load_sentinel_commit();
                
                git.commit(commit_id, log_message, git.head_commit);
            } else {
                cout << "Usage: mygit commit -m \"message\"" << endl;
            }

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





