#ifndef DECK_H
#define DECK_H

#include "card.h"
#include <vector>
#include <random>
#include <algorithm>

class Deck {
public:
    std::vector<Card> cards;

    Deck(int num_decks = 1);  // takes number of decks
    void shuffle();
    Card draw();
};

#endif
