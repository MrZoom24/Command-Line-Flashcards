#pragma once
#include <string>

void clear_screen();
std::string escape_newlines(const std::string& s);
std::string unescape_newlines(const std::string& s);
void wait_for_enter();
int get_menu_choice(int min, int max);
bool ask_yes_no(const std::string& question);
