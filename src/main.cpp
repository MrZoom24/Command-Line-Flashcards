#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <limits>
#include <algorithm>
#include <cctype>
#include "Utils.hpp"

struct Flashcard {
    std::string front; // Question
    std::string back;  // Answer
};

// -----------------------------
// Flashcard Functions

void add_card(std::vector<Flashcard>& vecCards);
void list_cards(std::vector<Flashcard>& vecCards);
void quiz(const std::vector<Flashcard>& vecCards);
void load_cards(std::vector<Flashcard>& vecCards);
void save_cards(const std::vector<Flashcard>& vecCards);
void edit_card(std::vector<Flashcard>& vecCards);
void delete_card(std::vector<Flashcard>& vecCards);

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
// Edit Card

void edit_card(std::vector<Flashcard>& vecCards) {
    std::cout << "Choose a card to edit by typing card's ID, or 0 to quit" << std::endl;
    int maxId = vecCards.size();
    int optionInput = get_menu_choice(0, maxId);
    if(optionInput == 0){
        return;
    }
    optionInput--; // convert to ID

    std::cout << "Editing card " << vecCards[optionInput].front << std::endl;
    std::cout << "Enter new front (leave blank to keep same, or :q to quit): ";
    std::string newFront;
    std::getline(std::cin, newFront);
    if(newFront == ":q" || newFront == ":Q") return;
    std::cout << "Enter new back (leave blank to keep same, or :q to quit): ";
    std::string newBack;
    std::getline(std::cin, newBack);
    if(newBack == ":q" || newBack == ":Q") return;

    // check if input is only whitespace
    bool onlySpacesFront = std::all_of(newFront.begin(), newFront.end(), isspace);
    bool onlySpacesBack = std::all_of(newBack.begin(), newBack.end(), isspace);
    if(!newFront.empty() && !onlySpacesFront) {
        vecCards[optionInput].front = newFront;
    }
    if(!newBack.empty() && !onlySpacesBack) {
        vecCards[optionInput].back = newBack;
    }

    std::cout << "Card Edited." << std::endl;
    wait_for_enter();
    return;
}

// -----------------------------
// Delete Card

void delete_card(std::vector<Flashcard>& vecCards) {
    std::cout << "Choose a card to delete by typing card's ID, or 0 to quit" << std::endl;
    int maxId = vecCards.size();
    int optionInput = get_menu_choice(0, maxId);
    if(optionInput == 0){
        return;
    }
    optionInput--; // convert to ID

    if(ask_yes_no(std::string("Are you sure you want to delete card ") + vecCards[optionInput].front + "?")){
        vecCards.erase(vecCards.begin() + optionInput);
        std::cout << "Card Deleted." << std::endl;
    } else{
        std::cout << "Operation Canceled." << std::endl;
    }

    wait_for_enter();
    return;
}

// -----------------------------
// List Cards

void list_cards(std::vector<Flashcard>& vecCards) {
    while(true) {
        clear_screen();
        std::cout << "Option 'List Cards' Selected" << std::endl;

        if (vecCards.empty()) {
            std::cout << "No cards available yet." << std::endl;
            wait_for_enter();
            return;
        } else {
            for(size_t i = 0; i < vecCards.size(); i++) {
                std::cout << "Card " << i + 1 << ": " << std::endl;
                std::cout << "Question: " << vecCards[i].front << std::endl;
                std::cout << "Answer: " << vecCards[i].back << std::endl;
                std::cout << "---------------------------" << std::endl;
            }
        }

        std::cout << "Choose an option by inputing number: " << std::endl;
        std::cout << "1) Edit" << std::endl;
        std::cout << "2) Delete" << std::endl;
        std::cout << "3) Quit" << std::endl;
        
        int optionInput = get_menu_choice(1,3);
        if(optionInput == 1) {
            edit_card(vecCards);
            save_cards(vecCards);
        } else if(optionInput == 2) {
            delete_card(vecCards);
            save_cards(vecCards);
        } else if(optionInput == 3) {
            return;
        }
    }
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
