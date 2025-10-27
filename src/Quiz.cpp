#include "Quiz.hpp"
#include "Utils.hpp"
#include <iostream>

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