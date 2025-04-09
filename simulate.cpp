#include "deck.h"
#include "hand.h"
#include <iostream>
#include <iomanip>
#include <string>

struct OutcomeStats {
    int wins = 0;
    int losses = 0;
    int pushes = 0;
    int doubled = 0;  // how many times double down was used

    void record(int ps, int ds, bool was_doubled = false) {
        if (was_doubled) ++doubled;
        int weight = was_doubled ? 2 : 1;

        if (ps > 21) {
            losses += weight;
        } else if (ds > 21 || ps > ds) {
            wins += weight;
        } else if (ps < ds) {
            losses += weight;
        } else {
            pushes += weight;
        }
    }

    double win_rate() const {
        int total = wins + losses + pushes;
        return total ? 100.0 * wins / total : 0.0;
    }
};

int get_face_index(const std::string& face) {
    if (face == "A") return 0;
    if (face == "J") return 10;
    if (face == "Q") return 11;
    if (face == "K") return 12;
    return std::stoi(face) - 1;
}

const std::string faces[] = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};

int main() {
    const int num_games = 100000;
    const int min_stand = 12;
    const int max_stand = 20;

    for (int stand_at = min_stand; stand_at <= max_stand; ++stand_at) {
        OutcomeStats outcomes[2][13] = {}; // [is_soft][dealer_upcard_face_index]

        for (int game = 0; game < num_games; ++game) {
            Deck deck(6);
            Hand player, dealer;

            player.add(deck.draw());
            dealer.add(deck.draw());
            player.add(deck.draw());
            dealer.add(deck.draw());

            bool doubled_down = false;

            int initial_score = player.score();
            if (initial_score == 10 || initial_score == 11) {
                // Basic double down strategy
                player.add(deck.draw());
                doubled_down = true;
            } else {
                // Normal play if not doubling
                while (player.score() < stand_at) {
                    player.add(deck.draw());
                }
            }

            bool is_soft = false;
            int ps = player.score(&is_soft);

            while (dealer.score() < 17) {
                dealer.add(deck.draw());
            }

            int ds = dealer.score();
            int dealer_index = get_face_index(dealer.cards[0].face);
            int soft_index = is_soft ? 1 : 0;

            outcomes[soft_index][dealer_index].record(ps, ds, doubled_down);
        }

        std::cout << "\n========================\n";
        std::cout << "Player stands at: " << stand_at << "\n";

        std::cout << "\nSoft hand outcomes:\n";
        for (int i = 0; i < 13; ++i) {
            const auto& o = outcomes[1][i];
            std::cout << std::setw(6) << faces[i] << ": "
                      << std::setw(5) << o.wins << "W "
                      << std::setw(5) << o.losses << "L "
                      << std::setw(5) << o.pushes << "P "
                      << "Win%: " << std::fixed << std::setprecision(2) << o.win_rate() << "% "
                      << "Doubled: " << o.doubled << "\n";
        }

        std::cout << "\nHard hand outcomes:\n";
        for (int i = 0; i < 13; ++i) {
            const auto& o = outcomes[0][i];
            std::cout << std::setw(6) << faces[i] << ": "
                      << std::setw(5) << o.wins << "W "
                      << std::setw(5) << o.losses << "L "
                      << std::setw(5) << o.pushes << "P "
                      << "Win%: " << std::fixed << std::setprecision(2) << o.win_rate() << "% "
                      << "Doubled: " << o.doubled << "\n";
        }
    }

    return 0;
}
