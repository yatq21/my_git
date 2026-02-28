#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
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
    cout << "\n可用命令：" << std::endl;
    cout << "  init    初始化仓库（创建 .mygit 目录）" << std::endl;
    cout << "  add     将指定文件加入暂存区" << std::endl;
    cout << "  commit  提交暂存区并生成提交记录" << std::endl;
    cout << "  log     查看提交历史" << std::endl;
    cout << "  status  查看当前文件状态" << std::endl;
    cout << "\n示例：" << std::endl;
    cout << "  mygit init" << std::endl;
    cout << "  mygit add main.cpp" << std::endl;
    cout << "  mygit commit -m \"初始化提交\"" << std::endl;
    cout << "  mygit log" << std::endl;
    cout << "  mygit status" << std::endl;
    
}

void Git::init() {
    filesystem::create_directory(".git");
    filesystem::create_directory(".git/staging_area");
    filesystem::create_directory(".git/commits");
}
void Git::add() {}
void Git::commit() {}
void Git::log() {}
void Git::status() {}