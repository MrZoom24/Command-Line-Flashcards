#include "Deck.hpp"
#include "Utils.hpp"
#include "Storage.hpp"
#include <iostream>
#include <algorithm>

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