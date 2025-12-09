#include"Include.hpp"
#include"Head.hpp"
#include"Class.hpp"
#include"Menu.hpp"
#include"Student_callback.hpp"

//github

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

