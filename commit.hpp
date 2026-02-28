#include <iostream>
#include <filesystem>
#include <string>
using namespace std;

string get_formatted_time() {
    // 获取当前系统时间点
    time_t now = time(nullptr);
    tm* local_time = localtime(&now);
    char buffer[80];
    // 格式化时间为 "Wed Jun 01 12:00:00 2024 +0000" 的格式
    strftime(buffer, sizeof(buffer), "%a %b %d %H:%M:%S %Y %z", local_time);

    return string(buffer);
}

class Commit {
    public:
    bool is_sentinel = false;
        string log_massage = "";
        string timestamp = "";
        Commit* parent_commit = nullptr;
        Commit* next_commit = nullptr;
        // 哨兵节点
        Commit(bool is_sentinel, string log_massage) {
            this->is_sentinel = is_sentinel;
            this->log_massage = log_massage;
            this->timestamp = get_formatted_time();
        }
        // 普通commit节点
        Commit(string log_massage, Commit* parent_commit) {
            this->log_massage = log_massage;
            this->timestamp = get_formatted_time();
            this->parent_commit = parent_commit;
            // 防止空指针异常
            if (this->parent_commit != nullptr) {
                this->parent_commit->next_commit = this;
            }
        }
};


