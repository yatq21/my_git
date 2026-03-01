# mygit
这是一个C++实现的简易版本控制系统，模仿Git的基本功能。灵感来源于CS61B中的[Project 2: Gitlet | CS 61B Spring 2021](https://sp21.datastructur.es/materials/proj/proj2/proj2)项目.


实现了以写基础功能:
- init: 初始化版本库
- add: 将文件添加到暂存区
- commit: 提交更改
- log: 显示提交历史
- status: 显示当前状态

## 文件结构
- `mygit.cpp`: 包含主函数和命令行接口的实现
- `git.hpp`: 包含Git类的定义和实现，负责版本控制的核心逻辑
- `commit.hpp`: 定义Commit类，表示一次提交的基本信息
- `hash_utils.hpp`: 提供计算文件哈希值的工具函数
- `.mygit`: 存储版本控制信息的隐藏目录 (在工作目录init初始化之后生成)
  - `HEAD`: 存储当前分支的最新提交ID
  - `commits/`: 存储所有提交对象和历史文件的目录
  - `staging_area/`: 存储暂存区文件的目录


## 使用方法

  init    初始化仓库（创建 .mygit 目录）
  add     将指定文件加入暂存区
  commit  提交暂存区并生成提交记录
  log     查看提交历史
  status  查看当前文件状态

示例：
  mygit init
  mygit add main.cpp
  mygit commit -m "test"
  mygit log
  mygit status


## 不足

- 改项目没有实现分支切换合并等高级功能.
- 实现存档功能的方式比较简单，直接将提交信息保存在文件中，没有使用更高效的存储方式.

