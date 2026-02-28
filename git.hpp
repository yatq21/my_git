#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include "commit.hpp"
using namespace std;



class Git {
    public:
        Commit* sentinel_commit;
        void help();
        void init();
        void add(string filename);
        // 哨兵节点
        void commit(string id, bool is_sentinel, string log_massage);
        // 普通commit节点
        void commit(string id, string log_massage, Commit* parent_commit);
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
    filesystem::create_directory(".mygit");
    filesystem::create_directory(".mygit/staging_area");
    filesystem::create_directory(".mygit/commits");
    filesystem::create_directory(".mygit/HEAD");
    this->commit("111", true, "Initial commit");
}

void Git::add(string filename) {
    if (filesystem::is_regular_file(filename)) {
        filesystem::copy_file(filename, ".mygit/staging_area/" + filename, filesystem::copy_options::overwrite_existing);
    } else {
        cerr << "Error: " << filename << " does not exist." << endl;
    }
    
}
void Git::commit(string id, bool is_sentinel, string log_massage) {
    Commit *now_commit = new Commit(id, is_sentinel, log_massage);
    this->sentinel_commit = now_commit;
    this->sentinel_commit->save_commit(".mygit/commits");
}

void Git::commit(string id, string log_massage, Commit* parent_commit) {
    Commit *now_commit = new Commit(id, log_massage, parent_commit);
}


void Git::log() {}
void Git::status() {}