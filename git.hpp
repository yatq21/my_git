#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include "commit.hpp"
using namespace std;



class Git {
    public:
        // 哨兵节点，指向初始提交
        Commit* sentinel_commit = nullptr;
        // 当前HEAD指向的commit节点
        Commit* head_commit = nullptr;
        void help();
        void init();
        void add(string filename);
        // 哨兵节点
        void commit(string id, bool is_sentinel, string log_massage);
        // 普通commit节点
        void commit(string id, string log_massage, Commit* parent_commit);
        void log();
        void status();


        // 加载序列化的commit对象
        void load_head_commit() {
            ifstream head_file(".mygit/HEAD");
            if (!head_file.is_open()) {
                cerr << "Error: cannot open HEAD file: .mygit/HEAD" << endl;
                return;
            }

            string commit_id;
            getline(head_file, commit_id);
            head_file.close();

            if (commit_id.empty()) {
                this->head_commit = nullptr;
                return;
            }

            this->load_commit(commit_id);
        }

        void load_commit(string commit_id) {
            if (commit_id.empty()) {
                this->head_commit = nullptr;
                return;
            }

            Commit* restored = new Commit(commit_id, false, "");
            restored->load_commit(commit_id);
            this->head_commit = restored;
            if (restored->is_sentinel) {
                this->sentinel_commit = restored;
            }
        }
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
    cout << "\nUsage:" << std::endl;
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
    std::ofstream(".mygit/HEAD").close();
    this->commit("0", true, "Initial commit");
}

void Git::add(string filename) {
    if (!filesystem::is_regular_file(filename)) {
        cerr << "Error: " << filename << " does not exist." << endl;
        return;
    }

    string base_name = filesystem::path(filename).filename().string();
    filesystem::path dst = filesystem::path(".mygit/staging_area") / base_name;

    if (filesystem::exists(dst)) {
        filesystem::remove(dst);
    }

    filesystem::copy_file(filename, dst);
    
}
void Git::commit(string id, bool is_sentinel, string log_massage) {
    Commit *now_commit = new Commit(id, is_sentinel, log_massage);
    this->sentinel_commit = now_commit;
    this->head_commit = now_commit;
    ofstream head_file(".mygit/HEAD");
    if (head_file.is_open()) {
        head_file << this->head_commit->id << endl;
        head_file.close();
    }
    this->sentinel_commit->save_commit(".mygit/commits");
}

void Git::commit(string id, string log_massage, Commit* parent_commit) {
    Commit *now_commit = new Commit(id, log_massage, parent_commit);
    this->head_commit = now_commit;
    ofstream head_file(".mygit/HEAD");
    if (head_file.is_open()) {
        head_file << this->head_commit->id << endl;
        head_file.close();
    }
    this->head_commit->save_commit(".mygit/commits");
}


void Git::log() {

}
void Git::status() {}