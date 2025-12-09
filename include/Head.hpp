#pragma once

#include"Include.hpp"


void pause();
void cls();
void cls_pause(std::string print,bool endl);
void load_anime(std::string load_name,int time);

template<typename T>
T get_right(std::string input_name)
{
	
	
	if constexpr (std::is_same_v<T, std::string>)
	{
		std::string value;
		while (true)
		{
			std::getline(std::cin, value);
			if (value.size() > 0)
			{
				return value;
			}
			else
			{
				std::cout << "Input error!" << std::endl;
				pause();
				std::cout << input_name << ":";
				std::cin.clear();
				std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
			}
		}
	}
	else
	{
		T value;
		while (true)
		{
			if (std::cin >> value)
			{
				std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n'); // 清理缓冲区
				return value;
			}
			else
			{
				std::cout << "Input error!" << std::endl;
				pause();
				std::cout << input_name << ":";
				std::cin.clear();
				std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
			}
		}
	
	}

}
