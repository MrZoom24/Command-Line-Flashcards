#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <limits>
#include <algorithm>
#include <cctype>
#include "Utils.hpp"
#include "Flashcard.hpp"
#include "Deck.hpp"

// -----------------------------
// Flashcard Functions

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
// Quiz

void quiz(const std::vector<Flashcard>& vecCards) {
    if(vecCards.empty()) {
        clear_screen();
        std::cout << "No cards available yet." << std::endl;
        wait_for_enter();
        return;
    }

    int counterAnswered = 0;
    int counterCorrect = 0;

    for(const Flashcard& card : vecCards) {
        clear_screen();
        std::cout << "Question: " << card.front << std::endl;
        std::cout << "(Press Enter to see answer)" << std::endl;
        std::string dummy;
        std::getline(std::cin, dummy);

        std::cout << std::endl << "Answer: " << card.back << std::endl;

        if(ask_yes_no("Did you answer correctly?")){
            counterAnswered++;
            counterCorrect++;
        } else {
            counterAnswered++;
        }
    }

    clear_screen();
    double percent = counterAnswered > 0 ? (double)counterCorrect / counterAnswered * 100 : 0;
    std::cout << "Total cards answered: " << counterAnswered << std::endl;
    std::cout << "Correct answers: " << counterCorrect << std::endl;
    std::cout << "Incorrect answers: " << counterAnswered - counterCorrect << std::endl;
    std::cout << "Correct percentage: " << percent << "%" << std::endl;
    wait_for_enter();
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
