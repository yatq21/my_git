#include <bits/stdc++.h>
using namespace std;



class Git {
    public:
        void help();
        void init();
        void add();
        void commit();
        void log();
        void status();
};



void Git::help() {
    string banner = R"(
                             _ __ 
   ____ ___  __  __   ____ _(_) /_
  / __ `__ \/ / / /  / __ `/ / __/
 / / / / / / /_/ /  / /_/ / / /_  
/_/ /_/ /_/\__, /   \__, /_/\__/  
          /____/   /____/         
    )";

    cout << banner << std::endl;
    cout << ">> Simple VCS | Author: yatq | Version: 1.0 <<" << std::endl;
}

void Git::init() {}
void Git::add() {}
void Git::commit() {}
void Git::log() {}
void Git::status() {}