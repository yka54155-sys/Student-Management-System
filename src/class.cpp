#include"Include.hpp"
#include"Class.hpp"
#include"Menu.hpp"
#include"Head.hpp"
std::vector<Student> students;


	Student::Student(std::string name, int age, std::string id) :Name(name), Age(age), Id(id) 
	{
		Score["math"] = 0;
		Score["chinese"] = 0;
		Score["english"] = 0;
	}

	Student::~Student() = default;


	std::string Student::get_Name() const
	{
		return Name;
	}
	int Student::get_Age()const
	{
		return Age;
	}
	std::map<std::string,int>&  Student::get_Score() 
	{
		return this->Score;
	}
	std::string Student::get_Id()const
	{
		return Id;
	}

	void Student::set_name(std::string name)
	{
		Name = name;
	}
	void Student::set_age(int age)
	{
		Age = age;
	}
	void Student::set_id(std::string id , Student& s)
	{
		if (id == s.get_Id())
		{
			return;
		}

		if (Id_exist(id,s.get_Id()))
		{
			std::cout << "modify ID failed!" << std::endl;
			while (Id_exist(id,s.get_Id()))
			{
				std::cout << "Id:";
				std::cin >> id;
			}
			Id = id;
			return;
		}

		Id = id;
	}
	void Student::set_score()
	{
		for (std::map<std::string, int>::iterator it = this->Score.begin(); it != this->Score.end(); ++it)
		{
			std::cout << "    " << it->first << ":";
			it->second = get_right<int>(it->first);
		}
	}

	void Student::modify_score(std::string in_sub,int in_score)
	{
		this->Score[in_sub] = in_score;
		cls_pause("Modify Score Successfully!", 1);
	}

	void Student::display_score(const std::map<std::string, int>& s)
	{
		std::cout << std::endl;
		for (std::map<std::string, int>::const_iterator it = s.cbegin(); it != s.cend(); ++it)
		{
			using namespace std;
			cout << "    " << it->first << ":" << it->second << endl;
		}
	}

	void Student::display_student() 
	{
		
		std::cout << "==================" << std::endl;
		std::cout << "Name:" << this->get_Name() << std::endl;
		std::cout << "Age:" << this->get_Age() << std::endl;
		std::cout << "Id:" << this->get_Id() << std::endl;
		std::cout << "Score:"; this->display_score(this->get_Score()); std::cout << std::endl;
		std::cout << "Total Score:" << this->total_score() << std::endl;
		std::cout << "Average Score:" << this->average_score() << std::endl;
		std::cout << "==================" << std::endl;
		

	}

	bool Student::subject_add(std::string sub)
	{
		for (auto it = this->Score.begin(); it != this->Score.end(); ++it)
		{
			if (sub == it->first)
			{
				cls_pause("Subject is existed.", 1);
				return false;
			}
		}
		this->Score[sub] = 0;
		return true;
	}

	int Student::total_score()
	{
		int total_score = 0;
		for (std::map<std::string, int>::const_iterator it = this->Score.cbegin(); it != this->Score.cend(); ++it)
		{
			total_score = total_score + it->second;
		}

		return total_score;
	}

	double Student::average_score()
	{
		double average_score = (this->total_score() * 1.0) / this->Score.size() ;
		return average_score;
	}

	bool Student::operator<(Student& other)
	{
		return this->total_score() > other.total_score();
	}