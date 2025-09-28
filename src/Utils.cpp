#include "Utils.hpp"
#include <iostream>
#include <string>
#include <limits>
#include <algorithm>
#include <cctype>

// Clear screen (cross-platform)
void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Escape newlines for storage
std::string escape_newlines(const std::string& s) {
    std::string result = s;
    size_t pos = 0;
    while ((pos = result.find('\n', pos)) != std::string::npos) {
        result.replace(pos, 1, "\\n");
        pos += 2;
    }
    return result;
}

// Unescape newlines when loading
std::string unescape_newlines(const std::string& s) {
    std::string result = s;
    size_t pos = 0;
    while ((pos = result.find("\\n", pos)) != std::string::npos) {
        result.replace(pos, 2, "\n");
        pos += 1;
    }
    return result;
}

// Wait for enter
void wait_for_enter() {
    std::cout << "(Press Enter to continue)";
    std::string dummy;
    std::getline(std::cin, dummy);
}

// Menu choice with validation
int get_menu_choice(int min, int max) {
    while (true) {
        std::string input;
        std::getline(std::cin, input);
        try {
            int choice = std::stoi(input);
            if (choice >= min && choice <= max) return choice;
        } catch (...) {}
        std::cout << "Invalid input. Please enter a number between " << min << " and " << max << "." << std::endl;
    }
}

// Yes/no prompt
bool ask_yes_no(const std::string& question) {
    while (true) {
        std::cout << question << " (y/n): ";
        std::string input;
        std::getline(std::cin, input);
        if (input == "y" || input == "Y") return true;
        if (input == "n" || input == "N") return false;
        std::cout << "Invalid input. Please enter y or n." << std::endl;
    }
}
