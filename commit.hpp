#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
using namespace std;

string get_formatted_time() {
    // 获取当前系统时间点
    time_t now = time(nullptr);
    tm* local_time = localtime(&now);
    char buffer[80];
    // 格式化时间为 "Wed Jun 01 12:00:00 2024 +0800" 的格式
    strftime(buffer, sizeof(buffer), "%a %b %d %H:%M:%S %Y", local_time);
    return string(buffer) + " +0800";
}

class Commit {
    public:
        string id;
        bool is_sentinel = false;
        string log_massage = "";
        string timestamp = "";
        Commit* parent_commit = nullptr;
        Commit* next_commit = nullptr;
        // 哨兵节点
        Commit(string id, bool is_sentinel, string log_massage) {
            this->id = id;
            this->is_sentinel = is_sentinel;
            this->log_massage = log_massage;
            this->timestamp = get_formatted_time();
        }
        // 普通commit节点
        Commit(string id, string log_massage, Commit* parent_commit) {
            this->id = id;
            this->log_massage = log_massage;
            this->timestamp = get_formatted_time();
            this->parent_commit = parent_commit;
            // 防止空指针异常
            if (this->parent_commit != nullptr) {
                this->parent_commit->next_commit = this;
            }
        }
        void save_commit(string path);
        void load_commit(string commit_id);

};

void Commit::save_commit(string path) {
    // 生成提交文件路径
    string commit_file_path = path + "/" + this->id + ".txt";
    ofstream commit_file(commit_file_path);
    if (commit_file.is_open()) {
        commit_file << "Commit ID: " << this->id << endl;
        commit_file << "Is Sentinel: " << (this->is_sentinel ? "Yes" : "No") << endl;
        commit_file << "Log Message: " << this->log_massage << endl;
        commit_file << "Timestamp: " << this->timestamp << endl;
        if (this->parent_commit != nullptr) {
            commit_file << "Parent Commit ID: " << this->parent_commit->id << endl;
        } else {
            commit_file << "Parent Commit ID: None" << endl;
        }
        commit_file.close();
    }
}

void Commit::load_commit(string commit_id) {
    string commit_file_path = ".mygit/commits/" + commit_id + ".txt";
    ifstream commit_file(commit_file_path);
    if (!commit_file.is_open()) {
        cerr << "Failed to open commit file: " << commit_file_path << endl;
        return;
    }

    this->id = commit_id;
    this->is_sentinel = false;
    this->log_massage = "";
    this->timestamp = "";
    this->parent_commit = nullptr;
    this->next_commit = nullptr;

    string line;
    while (getline(commit_file, line)) {
        if (line.rfind("Commit ID: ", 0) == 0) {
            this->id = line.substr(11);
        } else if (line.rfind("Is Sentinel: ", 0) == 0) {
            this->is_sentinel = (line.substr(13) == "Yes");
        } else if (line.rfind("Log Message: ", 0) == 0) {
            this->log_massage = line.substr(13);
        } else if (line.rfind("Timestamp: ", 0) == 0) {
            this->timestamp = line.substr(11);
        }
    }

    commit_file.close();
}




