#pragma once
#include <vector>
#include "Flashcard.hpp"

void add_card(std::vector<Flashcard>& vecCards);
void edit_card(std::vector<Flashcard>& vecCards);
void delete_card(std::vector<Flashcard>& vecCards);
void list_cards(std::vector<Flashcard>& vecCards);