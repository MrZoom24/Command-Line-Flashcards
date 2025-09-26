#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <limits>

struct Flashcard {
    std::string front; // Question
    std::string back;  // Answer
};

// -----------------------------
// Utility Functions

void clear_screen();
std::string escape_newlines(const std::string& s);
std::string unescape_newlines(const std::string& s);
void wait_for_enter();
int get_menu_choice(int min, int max);
bool ask_yes_no(const std::string& question);

// -----------------------------
// Flashcard Functions

void add_card(std::vector<Flashcard>& vecCards);
void list_cards(const std::vector<Flashcard>& vecCards);
void quiz(const std::vector<Flashcard>& vecCards);
void load_cards(std::vector<Flashcard>& vecCards);
void save_cards(const std::vector<Flashcard>& vecCards);

const std::string SAVE_FILE = "data/cards.txt";

// -----------------------------
// Main

int main() {
    std::vector<Flashcard> cards;
    load_cards(cards);

    while(true) {
        clear_screen();
        std::cout << "Choose an option by inputing number: " << std::endl;
        std::cout << "1) Add" << std::endl;
        std::cout << "2) List" << std::endl;
        std::cout << "3) Quiz" << std::endl;
        std::cout << "4) Quit" << std::endl;

        int optionInput = get_menu_choice(1,4);

        if(optionInput == 1) {
            add_card(cards);
            save_cards(cards);
        } else if(optionInput == 2) {
            list_cards(cards);
        } else if(optionInput == 3) {
            quiz(cards);
        } else if(optionInput == 4) {
            save_cards(cards);
            break;
        }
    }

    return 0;
}

// -----------------------------
// Clear Screen

void clear_screen() {
#ifdef _WIN32
    system("cls");
#else 
    system("clear");
#endif
}

// -----------------------------
// Escape/Unescape newlines for file storage

std::string escape_newlines(const std::string& s) {
    std::string result = s;
    size_t pos = 0;
    while((pos = result.find('\n', pos)) != std::string::npos) {
        result.replace(pos, 1, "\\n");
        pos += 2;
    }
    return result;
}

std::string unescape_newlines(const std::string& s) {
    std::string result = s;
    size_t pos = 0;
    while ((pos = result.find("\\n", pos)) != std::string::npos) {
        result.replace(pos, 2, "\n");
        pos += 1;
    }
    return result;
}

// -----------------------------
// Helper functions

int get_menu_choice(int min, int max) {
    while(true) {
        std::string input;
        std::getline(std::cin, input);
        try {
            int choice = std::stoi(input);
            if(choice >= min && choice <= max) return choice;
        } catch(...) {}
        std::cout << "Invalid input. Please enter a number between " << min << " and " << max << "." << std::endl;
    }
}

bool ask_yes_no(const std::string& question) {
    while(true) {
        std::cout << question << " (y/n): ";
        std::string input;
        std::getline(std::cin, input);
        if(input == "y" || input == "Y") return true;
        if(input == "n" || input == "N") return false;
        std::cout << "Invalid input. Please enter y or n." << std::endl;
    }
}

void wait_for_enter() {
    std::cout << "(Press Enter to continue)";
    std::string dummy;
    std::getline(std::cin, dummy);
}

// -----------------------------
// Add Card

void add_card(std::vector<Flashcard>& vecCards) {
    clear_screen();
    std::cout << "Option 'Add Card' Selected" << std::endl;
    std::cout << "Enter :q in front/back field to return to main menu" << std::endl;
    wait_for_enter();

    while(true){
        clear_screen();
        std::cout << "Please write the content of the front page: " << std::endl;
        std::string inputFront;
        std::getline(std::cin, inputFront);
        if(inputFront == ":q" || inputFront == ":Q"){
            return;
        }

        std::cout << "Please write the content of the back page: " << std::endl;
        std::string inputBack;
        std::getline(std::cin, inputBack);
        if(inputBack == ":q" || inputBack == ":Q"){
            std::cout << "Card not saved. Returning to main menu" << std::endl;
            wait_for_enter();
            return;
        }

        // Check duplicate
        bool isDuplicate = false;
        for(Flashcard& card : vecCards) {
            if(card.front == inputFront) {
                isDuplicate = true;
                std::cout << "This card already exists. Back page content: " << std::endl << card.back << std::endl;

                if(ask_yes_no("Rewrite back?")) {
                    card.back = inputBack;
                    std::cout << "Card updated." << std::endl;
                }

                wait_for_enter();
                break;
            }
        }

        if(isDuplicate){
            continue;
        }

        Flashcard card{inputFront, inputBack};
        vecCards.push_back(card);
        std::cout << "Card added." << std::endl;
        wait_for_enter();
    }
}

// -----------------------------
// List Cards

void list_cards(const std::vector<Flashcard>& vecCards) {
    clear_screen();
    std::cout << "Option 'List Cards' Selected" << std::endl;

    if (vecCards.empty()) {
        std::cout << "No cards available yet." << std::endl;
    } else {
        for(size_t i = 0; i < vecCards.size(); i++) {
            std::cout << "Card " << i + 1 << ": " << std::endl;
            std::cout << "Question: " << vecCards[i].front << std::endl;
            std::cout << "Answer: " << vecCards[i].back << std::endl;
            std::cout << "---------------------------" << std::endl;
        }
    }

    wait_for_enter();
} 

// -----------------------------
// Quiz

void quiz(const std::vector<Flashcard>& vecCards) {
    if(vecCards.empty()) {
        clear_screen();
        std::cout << "No cards available yet." << std::endl;
        wait_for_enter();
        return;
    }

    for(const Flashcard& card : vecCards) {
        clear_screen();
        std::cout << "Question: " << card.front << std::endl;
        std::cout << "(Press Enter to see answer)" << std::endl;
        std::string dummy;
        std::getline(std::cin, dummy);

        std::cout << std::endl << "Answer: " << card.back << std::endl;
        wait_for_enter();
    }
}

// -----------------------------
// Save / Load Cards

void save_cards(const std::vector<Flashcard>& vecCards) {
    std::ofstream file(SAVE_FILE);
    if(!file) return;

    for(const Flashcard& card : vecCards) {
        file << escape_newlines(card.front) << '\n';
        file << escape_newlines(card.back) << '\n';
    }
}

void load_cards(std::vector<Flashcard>& vecCards) {
    std::ifstream file(SAVE_FILE);
    if(!file) return;

    std::string front, back;
    while(std::getline(file, front) && std::getline(file, back)) {
        vecCards.push_back({unescape_newlines(front), unescape_newlines(back)});
    }
}
