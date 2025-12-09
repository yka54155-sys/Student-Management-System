#pragma once
#include"Include.hpp"


extern std::vector<std::string> menu;

void display_menu();
void select_function(size_t select);
bool Id_exist(std::string in_id,std::string  now_id);
bool Id_exist(std::string in_id);
bool student_empty();