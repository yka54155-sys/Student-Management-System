#pragma once

#include"Include.hpp"

class Student
{
private:
	std::string Name;
	int Age;
	
	std::map < std::string ,int > Score;
	std::string Id;
public:

	Student(std::string name, int age,std::string id);
	~Student();

	std::string get_Name() const;
	
	int get_Age()const;
	
	std::map<std::string, int>& get_Score() ;
	
	std::string get_Id()const;
	

	void set_name(std::string name);
	
	void set_age(int age);
	
	void set_id(std::string id , Student& s);
	
	void set_score();

	void modify_score(std::string in_sub,int in_score);

	void display_score(const std::map<std::string, int>& s) ;

	void display_student() ;

	bool subject_add(std::string sub);

	int total_score();

	double average_score();

	bool operator < (Student& other);
	
};

extern std::vector<Student> students;




