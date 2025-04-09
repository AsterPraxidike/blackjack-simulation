#include "deck.h"

static const std::string faces[] = {
    "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"
};
static const std::string suits[] = { "♥", "♠", "♦", "♣" };
static const int values[] = {
    11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10
};

Deck::Deck(int num_decks) {
    for (int d = 0; d < num_decks; ++d) {
        for (const auto& s : suits) {
            for (int i = 0; i < 13; ++i) {
                cards.emplace_back(faces[i], s, values[i]);
            }
        }
    }
    shuffle(); // auto-shuffle after construction
}

void Deck::shuffle() {
    std::shuffle(cards.begin(), cards.end(), std::mt19937(std::random_device{}()));
}

Card Deck::draw() {
    Card c = cards.back();
    cards.pop_back();
    return c;
}
