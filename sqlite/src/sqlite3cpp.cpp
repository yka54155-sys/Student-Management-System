#include"sqlite3cpp.hpp"



//Sqlite3 Zone
sqlite3cpp::sqlite3cpp(const std::string& db_name)
{
    this->err_msg = "NULL";
     this->ok = !(sqlite3_open(db_name.c_str(),&this->db));
    if(this->ok == false)
    {
        this->err_msg = sqlite3_errmsg(this->db);
        this->throw_err_msg();
    }
}

sqlite3cpp::~sqlite3cpp()
{
    sqlite3_close(db);
    this->ok = false;
}

bool sqlite3cpp::is_open() const
{
    return this->ok;
}



const std::string& sqlite3cpp::get_errmsg()
{
    return this->err_msg;
}





bool sqlite3cpp::sqlite3cpp_exec(const std::string& sql)
{
    const char* str = sql.c_str();
    char* err_msg;
    int rc = sqlite3_exec
    (
        this->db,
        str,
        this->null_callback,
        0,
        &err_msg
    );

    if(rc == SQLITE_OK)
    {
        return true;
    }
    else
    {
        this->err_msg = err_msg;
        sqlite3_free(err_msg);
        this->throw_err_msg();
        return false;

    }

}






bool sqlite3cpp::sqlite3cpp_exec(const std::string& sql,std::function<int(std::any,int,const std::vector<std::string>&,const std::vector<std::string>&)> callback,std::any call_data)
{
    const char* str = sql.c_str();
    char* err_msg;

    auto wrapper = [](void* data,int col_num,char** col_value,char** col_name) -> int
    {
        struct callback_function
        {
            std::function<int(std::any,int,const std::vector<std::string>&,const std::vector<std::string>&)> user_callback;
            std::any call_data;
        };

        callback_function* cd_data = static_cast<callback_function*>(data);
        
        std::vector<std::string> value,name;
        for(int i = 0;i < col_num;++i)
        {
            value.emplace_back(col_value[i] ? col_value[i] : "NULL");
            name.emplace_back(col_name[i] ? col_name[i] : "NULL");
        }

        return cd_data->user_callback(cd_data->call_data,col_num,value,name);
    };

    struct callback_function
    {
        std::function<int(std::any,int,const std::vector<std::string>&,const std::vector<std::string>&)> user_callback;
        std::any call_data;
    } cb_data{callback,call_data};

    int rc = sqlite3_exec
    (
        this->db,
        str,
        wrapper,
        &cb_data,
        &err_msg
    );

    if(rc == SQLITE_OK)
    {
        return true;
    }
    else
    {
        this->err_msg = err_msg;
        sqlite3_free(err_msg);
        this->throw_err_msg();
        return false;
    }
    
    
}


//Exception Zone

sqlite3cpp::sqlite3_exception::sqlite3_exception(const std::string& msg)
{
    this->message = msg;
}

const std::string sqlite3cpp::sqlite3_exception::what() const
{
    return "Sqlite3 Exception:" + this->message;
}

void sqlite3cpp::throw_err_msg()
{
    if(this->err_msg != "NULL")
    {
        throw sqlite3_exception(this->err_msg);
    }
}