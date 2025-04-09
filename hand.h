#ifndef HAND_H
#define HAND_H

#include "card.h"
#include <vector>
#include <string>
#include <iostream>

class Hand {
public:
    std::vector<Card> cards;

    void add(const Card& card);
    int score(bool* is_soft_out = nullptr) const;
    void show(const std::string& label) const;
};

#endif
