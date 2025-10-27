#pragma once
#include <vector>
#include "Flashcard.hpp"

void save_cards(const std::vector<Flashcard>& vecCards, const std::string& filename);
void load_cards(std::vector<Flashcard>& vecCards, const std::string& filename);
