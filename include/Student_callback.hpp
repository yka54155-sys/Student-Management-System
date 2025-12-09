#pragma once
#include"sqlite3cpp.hpp"
#include"Head.hpp"
extern sqlite3cpp student_db;
//callback tmplate:
//std::function<int(std::any,int,const std::vector<std::string>&,const std::vector<std::string>&)> user_callback;
//void* data,int col_num,char** col_value,char** col_name
//std::any data,int col_num,const std::vector<std::string>& col_value,const std::vector<std::string>& col_name
namespace student_callback
{
    
    int null(std::any data,int col_num,const std::vector<std::string>& col_value,const std::vector<std::string>& col_name);
    int display(std::any,int col_num,const std::vector<std::string>& col_value,const std::vector<std::string>& col_name);
    int exist(std::any data,int col_num,const std::vector<std::string>& col_value,const std::vector<std::string>& col_name);
    int data_num(std::any data,int col_num,const std::vector<std::string>& col_value,const std::vector<std::string>& col_name);
    int modify_score(std::any data,int col_num,const std::vector<std::string>& col_value,const std::vector<std::string>& col_name);
    int total_score(std::any data,int col_num,const std::vector<std::string>& col_value,const std::vector<std::string>& col_name);
    int average_score(std::any data,int col_num,const std::vector<std::string>& col_value,const std::vector<std::string>& col_name);
    int add_total_score_to_table(std::any data,int col_num,const std::vector<std::string>& col_value,const std::vector<std::string>& col_name);
    int add_average_score_to_table(std::any data,int col_num,const std::vector<std::string>& col_value,const std::vector<std::string>& col_name);
}



