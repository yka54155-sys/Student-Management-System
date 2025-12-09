#include"Student_callback.hpp"

sqlite3cpp student_db("Student.db");

int display_score(std::any data,int col_num,const std::vector<std::string>& col_value,const std::vector<std::string>& col_name)
{
    int i = 1;
    std::cout << col_value[i] << ":" << col_value[i+1] << std::endl;
    return 0;
}
int student_callback::display(std::any data,int col_num,const std::vector<std::string>& col_value,const std::vector<std::string>& col_name)
{
    std::cout << "==================" << std::endl;
    for(int i = 0;i < col_num;++i)
    {
        std::cout << col_name[i] << ":" << col_value[i] << std::endl;
    }
    student_db.sqlite3cpp_safe_exec
    (
        "SELECT * FROM 'score' WHERE ID = ?",
        display_score,
        0,
        col_value[0]
    );
    std::cout << "==================" << std::endl;
    return 0;
}    
    
int student_callback::null(std::any data,int col_num,const std::vector<std::string>& col_value,const std::vector<std::string>& col_name)
{
    return 0;
}

int student_callback::exist(std::any data,int col_num,const std::vector<std::string>& col_value,const std::vector<std::string>& col_name)
{
    int* count = std::any_cast<int*>(data);
    *count = std::stoi(col_value[0]);
    return 0;
}

int student_callback::data_num(std::any data,int col_num,const std::vector<std::string>& col_value,const std::vector<std::string>& col_name)
{
    int* count = std::any_cast<int*>(data);
    *count = std::stoi(col_value[0]);
    return 0;
}

int student_callback::modify_score(std::any data,int col_num,const std::vector<std::string>& col_value,const std::vector<std::string>& col_name)
{
    double in_score = 0;

    std::string* id = std::any_cast<std::string*>(data);
    std::cout << col_value[0] << ":";
    in_score = get_right<double>(col_value[0] + ":");
    student_db.sqlite3cpp_safe_exec
    (
        "UPDATE 'score' SET SCORE = ? WHERE ID = ? AND SUBJECT = ?",
        student_callback::null,
        0,
        in_score,*id,col_value[0]
    );
    return 0;

}

int student_callback::total_score(std::any data,int col_num,const std::vector<std::string>& col_value,const std::vector<std::string>& col_name)
{
    //SELECT SCORE FROM 'score' WHERE ID = ?;
    double* total_score = std::any_cast<double*>(data);
    *total_score = *total_score + stod(col_value[0]);

    return 0;
}

int student_callback::average_score(std::any data,int col_num,const std::vector<std::string>& col_value,const std::vector<std::string>& col_name)
{
    //SELECT * FROM 'score' WHERE ID = ? LIMIT 1;
    double* average_score = std::any_cast<double*>(data);
    double total_score = 0;
    int score_num = 0;
    student_db.sqlite3cpp_safe_exec
    (
        "SELECT SCORE FROM 'score' WHERE ID = ?;",
        [&](std::any data,int col_num,const std::vector<std::string>& col_value,const std::vector<std::string>& col_name)
        {
            total_score = total_score + stod(col_value[0]);
            score_num++;
            return 0;
        },
        0,
        col_value[0]
    );
    *average_score  = score_num > 0 ? total_score / score_num : 0;
    
    
    return 0;
}

int student_callback::add_total_score_to_table(std::any data,int col_num,const std::vector<std::string>& col_value,const std::vector<std::string>& col_name)
{
    //SELECT * FROM 'student';
    double score = 0;
    student_db.sqlite3cpp_safe_exec
    (
        "SELECT SCORE FROM 'score' WHERE ID = ?;",
        student_callback::total_score,
        &score,
        col_value[0]
    );
    student_db.sqlite3cpp_safe_exec
    (
        "UPDATE 'student' SET TOTAL_SCORE = ? WHERE ID = ?;",
        student_callback::null,
        0,
        score,col_value[0]
    );
    return 0;
}


int student_callback::add_average_score_to_table(std::any data,int col_num,const std::vector<std::string>& col_value,const std::vector<std::string>& col_name)
{
    //SELECT * FROM 'student';
    double score = 0;
    student_db.sqlite3cpp_safe_exec
    (
        "SELECT * FROM 'score' WHERE ID = ? LIMIT 1;",
        student_callback::average_score,
        &score,
        col_value[0]
    );
    student_db.sqlite3cpp_safe_exec
    (
        "UPDATE 'student' SET AVERAGE_SCORE = ? WHERE ID = ?;",
        student_callback::null,
        0,
        score,col_value[0]
    );
    return 0;
}