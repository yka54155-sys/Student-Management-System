#include"sqlite3cpp.hpp"
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#pragma execution_character_set("utf-8")



//完善封装
//研习sqlite3cpp_safe_exec


  int display(std::any call_data,int col_num,const std::vector<std::string>& col_v,const std::vector<std::string>& col_n)
   {
         for(int i = 0;i < col_num;++i)
         {
            std::cout << col_n[i] << ":" << col_v[i] << std::endl;
         }

         return 0;
   }

   
int main(int argc,char* argv[])
{
   SetConsoleOutputCP(65001);
   SetConsoleCP(65001);

   
   
   try
   {
      sqlite3cpp db("test.db");
      std::string sql;
      db.sqlite3cpp_exec("CREATE TABLE 'student'(ID INT PRIMARY KEY,NAME TEXT NOT NULL);");
      db.sqlite3cpp_exec("INSERT INTO 'student' VALUES(100,'cdsq');");
      std::string name;
      
      std::cin >> name;
      db.sqlite3cpp_safe_exec("SELECT * FROM 'student' WHERE NAME = ?",display,0,name);
      
      
      
      
      

   }
   catch(sqlite3cpp::sqlite3_exception& ex)
   {
      std::cout << ex.what() ;
   }
   catch(std::exception& e)
   {
      std::cout << e.what();
   }
   catch(...)
   {
      std::cout << "未知异常！";
   }
   

   getchar();
   return 0;
}