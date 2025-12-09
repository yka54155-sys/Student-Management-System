#include"Head.hpp"
#include"Include.hpp"
#include"Class.hpp"
#include"Menu.hpp"
#include"Student_callback.hpp"

std::vector<std::string> menu =
{
	
	" 1.Add Student",
	" 2.Delete Student",
	" 3.Modify Student",
	" 4.Find Student(Name)",
	" 5.Find Student(Id)",
	" 6.Add Subject",
	" 7.Modify Score",
	" 8.Check Score in ID",
	" 9.Average Score All Student",
	" 10.Sort with Total Score",
	" 11.Max Score and Min Score",
	" 12.Failing Student", // score < 60
	" 13.Display All Students",
	
	
};

bool student_empty() 
{
	// if (students.empty())
	// {
	// 	cls_pause("Students is empty.", 1);
	// 	return true;
	// }
	// else
	// {
	// 	return false;
	// }
	int count = 0;
	student_db.sqlite3cpp_exec
	(
		"SELECT COUNT(*) FROM 'student';",
		student_callback::data_num,
		&count
	);
	if(count == 0)
	{
		return true;
	}
	else
	{
		return false;
	}

}

bool Id_exist(std::string in_id,std::string now_id)
{

	// //existed=true
	// using namespace std;

	// if (in_id == now_id)
	// {
	// 	return false;
	// }
	// for (auto it = students.cbegin(); it != students.cend(); ++it)
	// {
	// 	if (in_id == it->get_Id())
	// 	{
	// 		cout << "ID is existed!" << endl;
	// 		return true;
	// 	}


	// }

	// return false;

	int count = 0;
	student_db.sqlite3cpp_safe_exec
	(
		"SELECT COUNT(*) FROM 'student' WHERE ID = ?);",
		student_callback::exist,
		&count,
		in_id
	);
	if(count)
	{
		std::cout << std::endl << "ID is existed!";
		return true;
	}
	else
	{
		return false;
	}

}

bool Id_exist(std::string in_id)
{

	// //existed=true
	// using namespace std;

	
	// for (auto it = students.cbegin(); it != students.cend(); ++it)
	// {
	// 	if (in_id == it->get_Id())
	// 	{
	// 		cout << "ID is existed!" << endl;
	// 		return true;
	// 	}


	// }

	// return false;
	int count = 0;
	student_db.sqlite3cpp_safe_exec
	(
		"SELECT COUNT(*) FROM 'student' WHERE ID = ?;",
		student_callback::exist,
		&count,
		in_id
	);
	if(count)
	{
		
		return true;
	}
	else
	{
		return false;
	}
}

void display_menu()
{
	std::cout << "======================" << std::endl;
	for (size_t i = 0; i < menu.size(); i++)
	{
		std::cout << menu[i] << std::endl;
	}
	std::cout << "======================" << std::endl;
}
void add_total()
{	
	
	try
	{
		student_db.sqlite3cpp_exec
		(
			"ALTER TABLE 'student' ADD COLUMN TOTAL_SCORE REAL;",
			student_callback::null,
			0
		);
	}
	catch(...)
	{

	}

	student_db.sqlite3cpp_exec
	(
		"SELECT ID FROM 'student';",
		student_callback::add_total_score_to_table,
		0

	);
	
	return;
}
void add_average()
{
	
	try
	{
		student_db.sqlite3cpp_exec
		(
			"ALTER TABLE 'student' ADD COLUMN AVERAGE_SCORE REAL;",
			student_callback::null,
			0
		);
	}
	catch(...)
	{

	}

	student_db.sqlite3cpp_exec
	(
		"SELECT * FROM 'student';",
		student_callback::add_average_score_to_table,
		0

	);

	return;
}


//Select Function Zone


void add_student()
{
	// std::string in_name , in_id;
	// int in_age;
	// using namespace std;
	// system("cls");
	// cout << "Name:";
	// in_name = get_right<std::string>("Name");
	// cout << "Age:";
	// in_age = get_right<int>("Age");
	// cout << "Id:";
	// cin >> in_id;
	// while (Id_exist(in_id))
	// {
	// 	cout << "Id:";
	// 	cin >> in_id;
	// }
	// students.push_back(Student(in_name, in_age,in_id));
	// for (auto it = students.begin(); it != students.end(); ++it)
	// {
	// 	if (it->get_Id() == in_id)
	// 	{
	// 		cout << "Score:" << endl;
	// 		it->set_score();
	// 	}
		
	// }
	cls();
	std::string Id,Name;
	int Age;
	double Score;
	while(1)
	{
		cls();
		std::cout << "ID:";
		std::cin >> Id;
		if(Id_exist(Id))
		{
			std::cout << "ID is exised!"  << std::endl;
			pause();
		}
		else
		{
			break;
		}
	}
	
	
	std::cout << "Name:";
	std::cin >> Name; 
	std::cout << "Age:";
	Age = get_right<int>("Age:"); 
	std::cout << "Score:" << std::endl;
	std::cout << "  Chinese:";
	double chinese_score = get_right<double>("  Chinese:");
	std::cout << "  Math:";
	double math_score = get_right<double>("  Math:");
	std::cout << "  English:";
	double english_score = get_right<double>("  English:");

	student_db.sqlite3cpp_safe_exec
	(
		"INSERT INTO 'score' VALUES(?,?,?);",
		student_callback::null,
		0,
		Id,"chinese",chinese_score
	);
	student_db.sqlite3cpp_safe_exec
	(
		"INSERT INTO 'score' VALUES(?,?,?);",
		student_callback::null,
		0,
		Id,"math",math_score
	);
	student_db.sqlite3cpp_safe_exec
	(
		"INSERT INTO 'score' VALUES(?,?,?);",
		student_callback::null,
		0,
		Id,"english",english_score
	);

	
	bool rc = student_db.sqlite3cpp_safe_exec("INSERT INTO 'student' (ID,NAME,AGE) VALUES(?,?,?);",student_callback::null,0,Id.c_str(),Name.c_str(),Age);
	if(rc)
	{
		add_total();add_average();
		cls_pause("Add Successfully!",1);
	}
	else
	{
		cls_pause("Add Failed!",1);
	}
	

	
}
void delete_student()
{
	
	// using namespace std;
	// if (students.empty())
	// {
	// 	cls();
	// 	cout << "students is empty!" << endl;
		
	// 	system("pause");
	// 	return;
	// }
	// string in_id;
	// cls();
	// cout << "Which ID are you want delete:";
	// cin >> in_id;
	// for (auto it = students.begin(); it != students.end(); ++it)
	// {
	// 	if (it->get_Id() == in_id)
	// 	{
	// 		students.erase(it);
	// 		cls_pause("Student delete successfully!",1);
	// 		return;
	// 	}
	// }

	// cls_pause("ID not existed!",1);
	
	// return;
	if(student_empty())
	{
		cls_pause("Student is empty!",1);
		return;
	}
	cls();
	std::string in_id;
	std::cout << "Which ID are you want delete:";
	std::cin >> in_id;
	if(Id_exist(in_id))
	{
		student_db.sqlite3cpp_safe_exec
		(
			"DELETE FROM 'student' WHERE ID = ?",
			student_callback::null,
			0,
			in_id
		);
		student_db.sqlite3cpp_safe_exec
		(
			"DELETE FROM 'score' WHERE ID = ?",
			student_callback::null,
			0,
			in_id
		);
		add_total();add_average();
		cls_pause("Delete Successfully!",1);
	}
	else
	{
		cls_pause("ID not existed!",1);
		return;
	}
}

void modify_student()
{
	// using namespace std;
	// if (students.empty())
	// {
	// 	cls_pause("Student is empty",1);
	// 	return;
	// }
	// cls();
	// cout << "Which ID modify:";
	// string in_id;
	// cin >> in_id;
	// for (auto it = students.begin(); it != students.end(); ++it)
	// {
	// 	if (it->get_Id() == in_id)
	// 	{
	// 		cls();
	// 		cout << "Name:";
	// 		string in_name;
	// 		cin >> in_name;
	// 		it->set_name(in_name);

	// 		cout << "Age:";
	// 		int in_age;
	// 		cin >> in_age;
	// 		it->set_age(in_age);

	// 		cout << "Id:";
	// 		string in_id;
	// 		cin >> in_id;
	// 		it->set_id(in_id,*it);

	// 		cout << "Score:" << endl;
	// 		it->set_score();

	// 		cls_pause("Modify ok !", 1);

	// 		return;
	// 	}
	// }

	// cls_pause("No conform Id !", 1);
	// return;
	if(student_empty())
	{
		cls_pause("Student is empty!",1);
		return;
	}
	
	std::string in_id ,in_name;
	int in_age;
	double in_score;
	while(1)
	{
		cls();
		std::cout << "Which ID are you want modify:";
		std::cin >> in_id;
		if(Id_exist(in_id))
		{
			break;
		}
		else
		{
			cls_pause("ID not existed!",1);
			return;
		}
	}
	std::cout << "Name:";
	std::cin >> in_name;
	std::cout << "Age:";
	in_age = get_right<int>("Age:");
	
	student_db.sqlite3cpp_safe_exec
	(
		"SELECT SUBJECT FROM 'score' WHERE ID = ?",
		student_callback::modify_score,
		&in_id,
		in_id
	);

	student_db.sqlite3cpp_safe_exec
	(
		"UPDATE 'student' SET NAME = ? ,AGE = ? WHERE ID = ?;",
		student_callback::null,
		0,
		in_name,in_age,in_id
	);
	add_total();add_average();
	cls_pause("Modify Successfully!",1);
	

}

void find_name()
{
	// if (students.empty())
	// {
	// 	cls_pause("Student is empty", 1);
	// 	return;
	// }
	// cls();
	// std::cout << "Which name are you find:";
	// std::string in_name;
	// std::cin >> in_name;
	// for (std::vector<Student>::iterator it = students.begin(); it != students.end(); ++it)
	// {
	// 	if (it->get_Name() == in_name)
	// 	{
	// 		cls();
	// 		it->display_student();
	// 		pause();
	// 		return;
	// 	}
	// }
	// cls_pause("No match name.", 1);
	if(student_empty())
	{
		cls_pause("Student is empty!",1);
		return;
	}
	add_total();add_average();
	std::string in_name;
	cls();
	std::cout << "Which name are you want find:";
	std::cin >> in_name;
	int count = 0;
	student_db.sqlite3cpp_safe_exec
	(
		"SELECT COUNT(*) FROM 'student' WHERE NAME = ?;",
		student_callback::data_num,
		&count,
		in_name
	);
	if(count == 0)
	{
		cls_pause("No match name in student!",1);
		return;
	}
	else
	{
		student_db.sqlite3cpp_safe_exec
		(
			"SELECT * FROM 'student' WHERE NAME = ?;",
			student_callback::display,
			0,
			in_name
		);
		pause();
		
	}
}

void find_id()
{
	// if (students.empty())
	// {
	// 	cls_pause("Student is empty", 1);
	// 	return;
	// }
	// cls();
	// std::cout << "Which id are you find:";
	// std::string in_id;
	// std::cin >> in_id;
	// for (std::vector<Student>::iterator it = students.begin(); it != students.end(); ++it)
	// {
	// 	if (it->get_Id() == in_id)
	// 	{
	// 		cls();
	// 		it->display_student();
	// 		pause();
	// 		return;
	// 	}
	// }
	// cls_pause("No match id.", 1);
	if(student_empty())
	{
		cls_pause("Student is empty!",1);
		return;
	}
	add_total();add_average();
	std::string in_id;
	cls();
	std::cout << "Which name are you want find:";
	std::cin >> in_id;
	int count = 0;
	student_db.sqlite3cpp_safe_exec
	(
		"SELECT COUNT(*) FROM 'student' WHERE ID = ?;",
		student_callback::data_num,
		&count,
		in_id
	);
	if(count == 0)
	{
		cls_pause("No match ID in student!",1);
		return;
	}
	else
	{
		student_db.sqlite3cpp_safe_exec
		(
			"SELECT * FROM 'student' WHERE ID = ?;",
			student_callback::display,
			0,
			in_id
		);
		pause();
		
	}
}

void add_subject()
{
	// if (student_empty()) return;

	// cls();
	// std::cout << "What subject are you add:";
	// std::string sub;
	// std::cin >> sub;
	// cls();
	// std::cout << "Which mode are you want?" << std::endl;
	// std::cout << "1.All Student." << std::endl << "2.Someone Student." << std::endl << "select:";
	// size_t s = 3;
	// std::cin >> s;
	// while(s < 1 || s > 2)
	// {
		
	// 	cls_pause("input error try again!", 1);
	// 	std::cout << "Which mode are you want?" << std::endl;
	// 	std::cout << "1.All Student." << std::endl << "2.Someone Student." << std::endl << "select:";
	// 	std::cin >> s;
	// }

	// if (s == 1)
	// {
	// 	for (auto it = students.begin(); it != students.end(); ++it)
	// 	{
	// 		if (!it->subject_add(sub))
	// 		{
	// 			return;
	// 		}
	// 	}

	// 	cls_pause("Add subject successfully!", 1);
	// 	return;
	// }
	// if (s == 2)
	// {
	// 	cls();
	// 	std::cout << "Which ID are you want modify:";
	// 	std::string in_id;
	// 	std::cin >> in_id;
	// 	for (auto it = students.begin(); it != students.end(); ++it)
	// 	{
	// 		if (it->get_Id() == in_id)
	// 		{
	// 			if (!it->subject_add(sub))
	// 			{
	// 				return;
	// 			}
	// 		}
	// 	}
	// 	cls_pause("Add subject successfully!", 1);
	// 	return;
	// }
	if(student_empty())
	{
		cls_pause("Student is empty!",1);
		return;
	}
	add_total();add_average();
	std::string in_id;
	std::cout << "Which ID are you want add subject:";
	std::cin >> in_id;
	if(!Id_exist(in_id))
	{
		cls_pause("ID not existed!",1);
		return;
	}
	std::string add_sub;
	std::cout << "What is subject are you want add:";
	std::cin >> add_sub;
	std::cout << add_sub << " score:";
	double add_score = get_right<double>(add_sub + " score:");
	student_db.sqlite3cpp_safe_exec
	(
		"INSERT INTO 'score' VALUES(?,?,?);",
		student_callback::null,
		0,
		in_id,add_sub,add_score
	);

	cls_pause("Add Successfully!",1);
	return;

	

}

void modify_score()
{
	// if (student_empty())
	// {
	// 	return;
	// }
	// using namespace std;
	// cls();
	// cout << "Which ID's score are you want modify:";
	// string in_id;
	// cin >> in_id;
	// std::vector<Student>::iterator it = std::find_if
	// (
	// 	students.begin(), students.end(), 
	// 	[&in_id](const Student& s) {return s.get_Id() == in_id; }
	// );

	// if (it == students.end())
	// {
	// 	cls_pause("No match ID.", 1);
	// 	return;
	// }

	// cls();
	// it->display_student();
	// cout << "Which subject are you want modify?" << endl;
	// cout << "input subject name:";
	// string in_sub;
	// cin >> in_sub;
	// std::map<std::string, int>::iterator it_map = std::find_if
	// (
	// 	it->get_Score().begin(), it->get_Score().end(),
	// 	[&in_sub](const std::pair<std::string, int>& s) {return s.first == in_sub; }
	// );
	
	// if (it_map == it->get_Score().end())
	// {
	// 	cls_pause("No match subject.", 1);
	// 	return;
	// }

	// cout << "What score are you modify:";
	// int in_score;
	// cin >> in_score;
	// it->modify_score(in_sub, in_score);

	// return;
	if(student_empty())
	{
		cls_pause("Student is empty!",1);
		return;
	}
	
	std::cout << "Which ID are you want modify score:";
	std::string in_id;
	std::cin >> in_id;
	if(!Id_exist(in_id))
	{
		cls_pause("ID not existed!",1);
		return ;
	}
	cls();
	std::cout << in_id << " score:" << std::endl;
	student_db.sqlite3cpp_safe_exec
	(
		"SELECT SUBJECT FROM 'score' WHERE ID = ?;",
		student_callback::modify_score,
		&in_id,
		in_id
	);
	add_total();add_average();
	cls_pause("Modify score successfully!",1);
	return ;


}

void check_score()
{
	// if (student_empty())
	// {
	// 	return;
	// }

	// cls();
	// std::cout << "Which ID are you want check:";
	// std::string in_id;
	// std::cin >> in_id;
	// std::vector<Student>::iterator it = find_if
	// (
	// 	students.begin(), students.end(),
	// 	[&in_id](const Student& s) {return s.get_Id() == in_id; }
	// );

	// if (it == students.cend())
	// {
	// 	cls_pause("No match ID.", 1);
	// 	return;
	// }


	// it->display_score(it->get_Score());
	// std::cout << "    Total score:" << it->total_score() << std::endl;
	// std::cout << "    Average score:" << it->average_score() << std::endl;
	// pause();
	if(student_empty())
	{
		cls_pause("Student is empty!",1);
		return;
	}
	add_total();add_average();
	std::cout << "Which ID are you want check score:";
	std::string in_id;
	std::cin >> in_id;
	if(!Id_exist(in_id))
	{
		cls_pause("ID not existed!",1);
		return;
	}
	double total_score = 0;
	student_db.sqlite3cpp_safe_exec
	(
		"SELECT SCORE FROM 'score' WHERE ID = ?;",
		student_callback::total_score,
		&total_score,
		in_id
	);
	double average_score = 0;
	student_db.sqlite3cpp_safe_exec
	(
		"SELECT * FROM 'score' WHERE ID = ? LIMIT 1;",
		student_callback::average_score,
		&average_score,
		in_id
	);
	cls(); 
	std::cout << "===============" << std::endl;
	student_db.sqlite3cpp_safe_exec
	(
		"SELECT * FROM 'student' WHERE ID = ?",
		[&](std::any data,int col_num,const std::vector<std::string>& col_value,const std::vector<std::string>& col_name)
		{
			for(int i = 0;i < col_num;++i)
			{
				std::cout << col_name[i] << ":" << col_value[i] << std:: endl;

			}
			return 0;
		},
		0,
		in_id
	);
	student_db.sqlite3cpp_safe_exec
	(
		"SELECT SUBJECT , SCORE FROM 'score' WHERE ID = ?",
		[&](std::any data,int col_num,const std::vector<std::string>& col_value,const std::vector<std::string>& col_name)
		{
			int i = 0;
				std::cout << col_value[i] << ":" << col_value[i + 1] << std::endl;
			
			return 0;
		},
		0,
		in_id
	);
	std::cout << "Total Score:" << total_score << std::endl;
	std::cout << "Average Score:" << average_score << std::endl;
	
	std::cout << "===============" << std::endl;
	pause();
}

void average_score()
{
	// if (student_empty())
	// {
	// 	return;
	// }
	// cls();
	
	// double average_score = 0;
	// for (std::vector<Student>::iterator it = students.begin(); it != students.end(); ++it)
	// {
	// 	average_score = average_score + it->average_score();
	// }
	// std::cout << "All Student average score is:";
	// std::cout << average_score / students.size() << std::endl;
	// pause();
	if(student_empty())
	{
		cls_pause("Student is empty!",1);
		return;
	}
	add_total();add_average();
	std::cout << "The all student average score is : ";
	double average_score = 0;
	double total_score = 0;
	int student_num = 0;
	student_db.sqlite3cpp_exec
	(
		"SELECT SCORE FROM 'score';",
		[&](std::any data,int col_num,const std::vector<std::string>& col_value,const std::vector<std::string>& col_name)
		{
			total_score += stod(col_value[0]);
			return 0;
		},
		0
	);
	student_db.sqlite3cpp_exec
	(
		"SELECT COUNT(ID) FROM 'student';",
		student_callback::data_num,
		&student_num
	);
	average_score = (total_score / student_num);

	std::cout << average_score << std::endl;
	pause();
	return ;



}

void sort_score()
{
	// if (student_empty())
	// {
	// 	return;
	// }
	// size_t order = 0;
	// cls();
	// while (order < 1 || order > 2)
	// {
	// 	std::cout << "Which order do you want:" << std::endl;
	// 	std::cout << "1.Up" << std::endl << "2.Down" << std::endl << "select:";
	
	// 	std::cin >> order;
	// 	if (order < 1 || order > 2)
	// 	{
	// 		cls_pause("Input error try again!", 1);
	// 	}
	// }
	


	// if (order == 1)
	// {
	// 	std::sort
	// 	(
	// 		students.begin(), students.end(),
	// 		[](Student& a, Student& b) {return a.total_score() < b.total_score(); }
	// 	);
	// 	cls_pause("Sort successfully(Up)!", 1);
	// 	return;
	// }

	// if (order == 2)
	// {
	// 	std::sort
	// 	(
	// 		students.begin(),students.end()
	// 	);
	// 	cls_pause("Sort successfully(Down)!", 1);
	// 	return;
	// }
	if(student_empty())
	{
		cls_pause("Student is empty!",1);
		return;
	}
	add_total();add_average();
	std::cout << "Which order are you want sort(1.Up 2.Down):";
	size_t select = 0;
	while(select < 1 || select > 2)
	{
		select = get_right<size_t>("Which order are you want sort(1.Up 2.Down):");
		if(select < 1 || select > 2)
		{
			std::cout << "No effective input!" << std::endl;
		}
	}
	try
	{
		student_db.sqlite3cpp_exec
		(
			"ALTER TABLE 'student' ADD COLUMN TOTAL_SCORE REAL;",
			student_callback::null,
			0
		);
	}
	catch(...)
	{

	}
	

	student_db.sqlite3cpp_exec
	(
		"SELECT ID FROM 'student';",
		student_callback::add_total_score_to_table,
		0

	);

	if(select == 1)
	{
		cls();
		student_db.sqlite3cpp_exec("SELECT * FROM 'student' ORDER BY CAST(TOTAL_SCORE AS REAL) ASC;",student_callback::display,0);
		pause();
	}
	else
	{
		cls();
		student_db.sqlite3cpp_exec("SELECT * FROM 'student' ORDER BY CAST(TOTAL_SCORE AS REAL) DESC;",student_callback::display,0);
		pause();
	}
	return;

	

	
}

void max_min()
{
	// if (student_empty())
	// {
	// 	return;
	// }

	// cls();
	// std::cout << "The Max Score Student is:" << std::endl;
	// auto max_it = max_element
	// (
	// 	students.begin(), students.end(),
	// 	[](Student& a, Student& b) {return a.total_score() < b.total_score(); }
	// );

	// max_it->display_student();

	// std::cout << "The Min Score Student is:" << std::endl;

	// auto min_it = min_element
	// (
	// 	students.begin(), students.end(), 
	// 	[](Student& a, Student& b) {return a.total_score() < b.total_score(); }
	// );

	// min_it->display_student();

	// pause();
	if(student_empty())
	{
		cls_pause("Student is empty!",1);
		return;
	}
	try
	{
		student_db.sqlite3cpp_exec
		(
			"ALTER TABLE 'student' ADD COLUMN TOTAL_SCORE REAL;",
			student_callback::null,
			0
		);
	}
	catch(...)
	{

	}
	student_db.sqlite3cpp_exec
	(
		"SELECT ID FROM 'student';",
		student_callback::add_total_score_to_table,
		0

	);
	cls();
	std::cout << "The max total score student is : " << std::endl;
	student_db.sqlite3cpp_exec
	(
		"SELECT * FROM 'student' WHERE TOTAL_SCORE = (SELECT MAX (TOTAL_SCORE) FROM 'student'); ",
		student_callback::display,
		0
	);
	std::cout << "The min total score student is : " << std::endl;
	student_db.sqlite3cpp_exec
	(
		"SELECT * FROM 'student' WHERE TOTAL_SCORE = (SELECT MIN (TOTAL_SCORE) FROM 'student'); ",
		student_callback::display,
		0
	);

	pause();
	return;

}

void failing_student()
{
	// if (student_empty())
	// {
	// 	return;
	// }
	// cls();
	// std::cout << "The failing stduent:" << std::endl;

	// for (auto it = students.begin(); it != students.end(); ++it)
	// {
	// 	if (it->average_score() < 60)
	// 	{
	// 		it->display_student();
	// 	}
	// }

	// pause();
	if(student_empty())
	{
		cls_pause("Student is empty!",1);
		return;
	}
	add_total();add_average();
	cls();
	std::cout << "The failing student : " << std::endl;
	student_db.sqlite3cpp_exec
	(
		"SELECT * FROM 'student' WHERE AVERAGE_SCORE < 60;",
		student_callback::display,
		0
	);
	pause();
	return;

}

void display_all()
{
	if(student_empty())
	{
		cls_pause("Student is empty!",1);
		return;
	}
	else
	{
		add_total();add_average();
		cls();
		student_db.sqlite3cpp_exec("SELECT * FROM 'student';",student_callback::display,0);
		pause();
		return;
	}
}
//Select Function Zone End


void select_function(size_t select)
{
	std::vector<std::function<void()>>  function_menu =
	{
		add_student,
		delete_student,
		modify_student,
		find_name,
		find_id,
		add_subject,
		modify_score,
		check_score,
		average_score,
		sort_score,
		max_min,
		failing_student,
		display_all,



	};
	function_menu[select - 1]();
}
