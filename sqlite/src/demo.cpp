#include"sqlite3cpp.hpp"
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#pragma execution_character_set("utf-8")



//完善封装
//init_table
int main(int argc,char* argv[])
{
   SetConsoleOutputCP(65001);
   SetConsoleCP(65001);
  
   try
   {
        sqlite3cpp db("test.db");
        db.display_all();
   }
   catch(sqlite3cpp::sqlite3_exception& ex)
   {
        std::cout << ex.what();
   }
  

   getchar();
   return 0;
}