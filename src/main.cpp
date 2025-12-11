#include"Include.hpp"
#include"Head.hpp"
#include"Class.hpp"
#include"Menu.hpp"
#include"Student_callback.hpp"


/*
针对你非软件工程专业的背景，我建议按以下路径系统学习：

  🎯 第一阶段：基础知识补强（1-2个月）

  编程语言深化
   - C++核心概念：RAII、智能指针、移动语义、完美转发
   - STL深入：容器算法迭代器、函数对象、lambda表达式
   - 现代C++特性：C++11/14/17/20的重要特性

  计算机基础
   - 数据结构与算法：链表、树、图、排序、查找、时间复杂度分析
   - 操作系统：进程线程、内存管理、文件系统
   - 计算机网络：TCP/IP、HTTP、Socket编程

  🏗️ 第二阶段：软件工程核心（2-3个月）

  设计模式与架构
   - GoF设计模式：单例、工厂、观察者、策略、装饰器等
   - SOLID原则：单一职责、开闭原则、里氏替换、接口隔离、依赖倒置
   - 架构模式：MVC、三层架构、领域驱动设计(DDD)

  代码质量
   - 重构技巧：提取方法、提取类、消除重复代码
   - 代码规范：命名规范、注释规范、代码布局
   - 单元测试：Google Test框架、TDD开发模式

  💾 第三阶段：数据库与系统设计（1-2个月）

  数据库进阶
   - SQL优化：索引、查询优化、事务处理
   - 数据库设计：范式理论、ER图设计
   - ORM框架：了解现代数据库访问方式

  系统设计
   - 缓存策略：Redis、内存缓存
   - 并发编程：多线程、线程池、锁机制
   - 性能优化：性能分析工具、瓶颈识别

  🛠️ 第四阶段：工程实践（持续学习）

  开发工具与流程
   - 版本控制：Git进阶、分支策略
   - 构建系统：CMake高级用法、自动化构建
   - 调试技巧：GDB调试、内存泄漏检测

  项目管理
   - 敏捷开发：Scrum、看板方法
   - 需求分析：用例图、活动图
   - 软件测试：单元测试、集成测试、压力测试

  📚 推荐学习资源

  书籍
   - C++：《Effective C++》、《C++ Primer》、《Modern C++ Design》       
   - 设计模式：《设计模式：可复用面向对象软件的基础》、《重构》
   - 架构：《代码整洁之道》、《架构整洁之道》
   - 数据库：《高性能MySQL》、《SQLite权威指南》

  在线资源
   - Coursera：软件工程专项课程
   - 慕课网：C++进阶课程
   - GitHub：阅读优秀开源项目源码
   - LeetCode：算法练习

  🎯 针对你项目的具体改进计划

   1. 重构Student类：分离数据存储和显示逻辑
   2. 引入Service层：处理业务逻辑
   3. 优化数据库操作：使用事务、批量操作
   4. 添加单元测试：确保代码质量
   5. 改进错误处理：使用异常类层次结构

  ⏰ 学习时间规划

   - 每天1-2小时：理论学习
   - 每周1个小项目：实践应用
   - 每月1个中等项目：综合运用

  关键建议：不要贪多求快，每个概念都要动手实践。你的优势是有实际项目经   
  验，现在需要的是理论支撑和系统化知识。

✦ 预计6-8个月后，你的代码质量会有显著提升。坚持下去，非专业背景完全可以  
  超越科班出身！
*/
/*
基于你的项目现状，这是一份针对性的学习路线（非软件工程专业也能掌握）：

第一阶段：代码规范（1-2周）- 最紧迫
为什么重要： 这是进入职业圈的入场券，花小力气收益大

命名规范学习

读：Google C++ Style Guide 或 LLVM Coding Standards（中文版有）
练：把你项目中所有函数/变量重命名统一
工具：使用 VS Code 的重命名功能批量改
代码注释和文档

学：Doxygen 注释格式（5分钟学会）
做：给 Student 类的每个方法加注释说明参数和返回值
删除垃圾代码

就是删那些被注释掉的代码块 - 用 git 历史管理，别留在代码里
第二阶段：设计思维（2-3周）
为什么重要： 决定了代码是否易维护

单一职责原则（SRP）

你项目的问题：Student 类既管理学生数据，又管理成绩，又连接数据库
学习资源：《Clean Code》第10章 或 看这个视频讲解
改进方向：
内存管理和 RAII

现在的问题：SQLite 连接何时关闭？谁负责释放？
学习：构造函数/析构函数的配对使用
实战：写一个 DatabaseConnection 类，打开放在构造函数，关闭放在析构函数
错误处理

现在：几乎没有错误处理
学习：std::optional<T> 和 std::expected<T, E>（C++23）或自己用异常
改进例子：std::optional<Student> findStudentById(const std::string& id);
第三阶段：C++ 特性深化（3-4周）
为什么重要： 写出高效、安全的代码

模板和泛型编程

你已经用了 template<typename T> T get_right() - 很好！
深化：学习模板特化、SFINAE、概念（Concepts in C++20）
资源：《C++ Templates: The Complete Guide》或免费网课
现代 C++ 特性（C++17/20）

学会用：智能指针（unique_ptr、shared_ptr）替代原始指针
学会用：std::optional、std::variant、std::any
学会用：范围 for 循环、结构化绑定 auto [id, name] = ...
const 正确性

现在的问题：bool operator < (Student& other) 应该是 const Student& other
影响：const 对象无法使用你的运算符
第四阶段：工程实践（4-8周）
为什么重要： 这是职业和学生代码的分水岭

构建系统升级

当前：CMakeLists.txt 很基础
学习：CMake 的 target_link_libraries、find_package、FetchContent
目标：让别人 clone 你的代码，一句命令就能编译
包管理和依赖

现在：SQLite 手动管理，很容易出问题
学习：vcpkg 或 Conan（C++ 包管理工具）
改进：find_package(sqlite3 REQUIRED) 自动下载和链接
测试框架

学习：Google Test (gtest) 或 Catch2
写一些单元测试：测试 Student 类、测试数据库操作
意义：改代码时能快速知道有没有破坏功能
版本控制和协作

学会：.gitignore（不要把 build/ 目录提交）
学会：写规范的 commit message
学会：分支管理（feature branch）
第五阶段：数据库和系统设计（持续）
为什么重要： 这是大型项目的核心

数据库设计

现在的问题：你有 student 表和 score 表，但关系设计可能有问题
学习：数据库规范化（1NF、2NF、3NF）
优化：用 FOREIGN KEY 建立真正的表关系
ORM 或数据访问层

当前：直接写 SQL 字符串 + 回调，容易出 bug
学习：设计一个 Repository 模式的数据访问层
或用：现成的 ORM 库（C++ 的选项有 hiberate-cpp、sqlpp11 等）s
架构模式

学习：MVC、MVVM 或 Clean Architecture
对你的项目：分离 UI 层（菜单）、业务逻辑层、数据层
🎯 最短路径方案（如果时间紧）
第1周：

统一命名规范 → 删除注释代码 → 加代码注释
第2-3周：

重构：分离 Student、ScoreManager、DatabaseRepository 三个类
学习 RAII：管理 SQLite 连接的生命周期
第4周：

加错误处理（try-catch 或 optional）
写 3-5 个单元测试
后续： 按兴趣选择 - 数据库优化、GUI 界面、或学其他语言

学习资源总结
主题	推荐资源	预计时间
C++ 规范	Google Style Guide	2小时
设计原则	Clean Code 书 或 YouTube视频	10小时
现代C++	Effective Modern C++ 或官方文档	15小时
CMake	CMake 官方文档 + 示例项目	5小时
测试	Google Test 教程	4小时
总计		36小时
核心建议：不要全部学完再动手，而是学 1 个主题 → 立即应用到项目 → 迭代。 这样进度快，还能看到实际改进。

你的非软件工程背景反而是优势 - 你有其他领域的思维方式，更容易理解系统设计的本质。加油
*/
int main()
{
	

    
    try
    {

        int table_exist = 0;
        student_db.sqlite3cpp_exec
        (
            "SELECT COUNT(name) FROM sqlite_master WHERE type='table' AND name='student';",
            student_callback::exist,
            &table_exist
        );
        if(table_exist == 0)
        {
            student_db.sqlite3cpp_exec
            (
                "CREATE TABLE 'student'(ID TEXT PRIMARY KEY,NAME TEXT NOT NULL,AGE INT NOT NULL);"
            );
            student_db.sqlite3cpp_exec
            (
                "CREATE TABLE 'score'(ID TEXT ,SUBJECT TEXT,SCORE DOUBLE ,PRIMARY KEY(ID , SUBJECT));"
            );
        }


        bool key = 1;
        size_t select = menu.size() + 1;
        while (key)
        {
            system("cls");
            display_menu();
            std::cout << "select:";
            select = get_right<size_t>("select");

            if (select > menu.size() || select <= 0)
            {
                std::cout << "quit now?[Y/N]:";
                char s = ' ';
                std::cin >> s;
                if (s == 'Y' || s == 'y')
                {
                    key = 0;
                    
                }
            }
            else
            {
                
                //Select Function
                select_function(select);
            }

        }
       
    }

    catch (sqlite3cpp::sqlite3_exception& ex)
    {
      std::cout << ex.what() << std::endl;
      return 0;
    }
    catch (const std::exception& e)
    {
        std::cout << e.what()<< std::endl;
        return 0;
    }
    

    return 0;
        
	
	
}

