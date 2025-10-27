#include <iostream>
#include "Utils.hpp"
#include "Flashcard.hpp"
#include "Deck.hpp"
#include "Storage.hpp"
#include "Quiz.hpp"

const std::string SAVE_FILE = "data/cards.txt";

int main() {
    std::vector<Flashcard> cards;
    load_cards(cards, SAVE_FILE);

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
            save_cards(cards, SAVE_FILE);
        } else if(optionInput == 2) {
            list_cards(cards);
        } else if(optionInput == 3) {
            quiz(cards);
        } else if(optionInput == 4) {
            save_cards(cards, SAVE_FILE);
            break;
        }
    }

    return 0;
}