#include <iostream>
#include "deck.h"
#include "hand.h"

int main() {
    int num_decks = 6;  // you can change this
    Deck deck(num_decks);

    Hand player;
    Hand dealer;

    // Deal initial cards
    player.add(deck.draw());
    dealer.add(deck.draw());
    player.add(deck.draw());
    dealer.add(deck.draw());

    player.show("Player");
    dealer.show("Dealer");

    // Player turn
    while (player.score() < 21) {
        std::cout << "Hit or stand? (h/s): ";
        char choice;
        std::cin >> choice;

        if (choice == 'h') {
            player.add(deck.draw());
            player.show("Player");
        } else {
            break;
        }
    }

    if (player.score() > 21) {
        std::cout << "Player busts! Dealer wins.\n";
        return 0;
    }

    // Dealer turn
    while (dealer.score() < 17) {
        dealer.add(deck.draw());
    }

    dealer.show("Dealer");

    // Determine outcome
    int ps = player.score();
    int ds = dealer.score();

    if (ds > 21 || ps > ds) std::cout << "Player wins!\n";
    else if (ps < ds) std::cout << "Dealer wins!\n";
    else std::cout << "Push (tie).\n";

    return 0;
}