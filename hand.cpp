#include "hand.h"

void Hand::add(const Card& card) {
    cards.push_back(card);
}

int Hand::score(bool* is_soft_out) const {
    int total = 0;
    int aces = 0;

    for (const auto& card : cards) {
        total += card.value;
        if (card.face == "A") ++aces;
    }

    bool soft = false;
    if (aces > 0 && total <= 21) soft = true;

    while (total > 21 && aces > 0) {
        total -= 10;
        --aces;
    }

    if (is_soft_out) *is_soft_out = soft;

    return total;
}

void Hand::show(const std::string& label) const {
    std::cout << label << ": ";
    for (const auto& card : cards) {
        std::cout << card.to_string() << " ";
    }
    std::cout << "(score: " << score() << ")\n";
}
