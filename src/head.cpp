#include"Head.hpp"

void pause()
{
	system("pause");
}

void cls()
{
	system("cls");
}

void cls_pause(std::string print,bool endl)
{
	system("cls");
	std::cout << print;
	if (endl == 1)
	{
		std::cout << std::endl;
	}
	system("pause");
}

void load_anime(std::string load_name , int time)
{
	using namespace std;

	char s[] = {'|','/','-','\\'};
	for (int i = 0; i < 20; i++)
	{
		cout << '\r' << load_name<< s[i % 4];
		cout.flush();
		Sleep(time);
	}
	cout << "\r";
}


