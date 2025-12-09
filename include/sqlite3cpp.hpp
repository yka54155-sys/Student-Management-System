#pragma once
#pragma execution_character_set("utf-8")
#include<iostream>
#include<stdio.h>
#include<string>
#include<sqlite3.h>
#include<functional>
#include<any>
#include<vector>
#include<variant>
#include<algorithm>
#include<type_traits>




class sqlite3cpp
{
    private:
        bool ok = false;
        sqlite3* db = NULL;
        std::string err_msg;
        static int ask_nums(const std::string& sql)
        {
            int count = 0;
            for(auto it = sql.cbegin();it != sql.cend();++it)
            {
                if(*it == '?') ++count;
            }
            return count;
        }
        static bool bind_param(sqlite3_stmt* stmt,int index,std::variant<int,double,std::string> args)
        {   
            int rc;
            if(index < 1)
            {
                throw(sqlite3cpp::sqlite3_exception("SQLite3cpp :'bind_param' index ERROR!"));
            }

            std::visit
            (
                [stmt,index,&rc](auto& value)
                {
                    using T = std::decay_t<decltype(value)>;
                    if constexpr(std::is_same_v<T,int>)
                    {
                        rc = sqlite3_bind_int(stmt,index,value);
                    }
                    else if constexpr(std::is_same_v<T,double>)
                    {
                        rc = sqlite3_bind_double(stmt,index,value);
                    }
                    else if constexpr(std::is_same_v<T,std::string>)
                    {
                        rc = sqlite3_bind_text(stmt,index,value.c_str(),-1,SQLITE_TRANSIENT);
                    }
                    else
                    {
                        rc = sqlite3_bind_null(stmt,index);
                    }

                }
                ,args
            );

            if(rc != SQLITE_OK)
            {
                throw sqlite3cpp::sqlite3_exception("SQLite3cpp : Bind ERROR!");
                return false;
            }
            else
            {
                return true;
            }
        }


    public:
        sqlite3cpp(const std::string&  db_name);
        ~sqlite3cpp();
        bool is_open()const;
        bool sqlite3cpp_exec(const std::string& sql);
        //void* data,int col_num,char** col_value,char** col_name
        bool sqlite3cpp_exec(const std::string& sql,std::function<int(std::any,int,const std::vector<std::string>&,const std::vector<std::string>&)> callback,std::any call_data);
        // bool init_table();
        const std::string& get_errmsg();
        
        
        template<typename...Args>
        bool sqlite3cpp_safe_exec(const std::string& sql,std::function<int(std::any,int,const std::vector<std::string>&,const std::vector<std::string>&)> callback,std::any call_data,const Args&...args)
        {
            int param_num = sizeof...(Args);
            
            if(ask_nums(sql) != param_num)
            {

                this->err_msg = "SQLite3cpp ERROR : Param num not Match.";
                this->throw_err_msg();
                return false;
            }

            sqlite3_stmt* stmt;
            if(sqlite3_prepare_v2(this->db,sql.c_str(),-1,&stmt,nullptr) != SQLITE_OK)
            {
                this->err_msg = "SQLite3cpp ERROR : sqlite3cpp_safe_exec.";
                this->throw_err_msg();
                return false;
            }

            int index = 1;
            ((this->bind_param(stmt,index,args),++index,args),...);

            int result = sqlite3_step(stmt);
            while(result == SQLITE_ROW)
            {
                int col_count = sqlite3_column_count(stmt);
                std::vector<std::string> values,names;

                for(int i = 0;i < col_count;i++)
                {
                    names.push_back(sqlite3_column_name(stmt,i));
                    const char* val = (const char*)sqlite3_column_text(stmt,i);
                    values.push_back(val ? val : "NULL");
                }

                callback(call_data,col_count,values,names);

                result = sqlite3_step(stmt);


            }


            sqlite3_finalize(stmt);

            return (result == SQLITE_DONE);


        }




        //Callback Zone
        static int null_callback(void* data,int argc,char** argv,char** col_name)
        {
            return 0;
        }

        static int display_all_student_callback(void* data,int argc,char** argv,char** col_name)
        {
            std::cout << "==================" << std::endl;
            for(int i = 0; i < argc ; ++i)
            {
                argv[i] ? argv[i] : "NULL";
                std::wcout << col_name[i] << ":" << argv[i] << std::endl;
            }
            std::cout << "==================" << std::endl;

            return 0;
        }


        //exception Zone
        class sqlite3_exception
        {
            private:
                std::string message;
            
            public:
                sqlite3_exception(const std::string& msg);
                ~sqlite3_exception() = default;

                const std::string what() const;
                bool operator!=(const std::string& str)const
                {
                    return message != str;
                }


        };

        void throw_err_msg();
};