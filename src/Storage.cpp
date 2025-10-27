#include "Storage.hpp"
#include "Utils.hpp"
#include <fstream>

void save_cards(const std::vector<Flashcard>& vecCards, const std::string& filename) {
    std::ofstream file(filename);
    if(!file) return;

    for(const Flashcard& card : vecCards) {
        file << escape_newlines(card.front) << '\n';
        file << escape_newlines(card.back) << '\n';
    }
}

void load_cards(std::vector<Flashcard>& vecCards, const std::string& filename) {
    std::ifstream file(filename);
    if(!file) return;

    std::string front, back;
    while(std::getline(file, front) && std::getline(file, back)) {
        vecCards.push_back({unescape_newlines(front), unescape_newlines(back)});
    }
}