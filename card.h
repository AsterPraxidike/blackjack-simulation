#ifndef CARD_H
#define CARD_H

#include <string>

class Card {
public:
    std::string face;  // "A", "2", ..., "K"
    std::string suit;  // "♥", "♠", "♦", "♣"
    int value;         // 1–11 depending on face

    Card(std::string f, std::string s, int v)
        : face(std::move(f)), suit(std::move(s)), value(v) {}

    std::string to_string() const {
        return face + suit;
    }
};

#endif
