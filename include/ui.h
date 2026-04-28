#ifndef UI_H
#define UI_H

#include "player.h"
#include <string>

namespace UI {
    int get_initial_funds();
    int get_bet(int available_funds);
    int get_player_action();
    bool ask_play_again();

    void display_game_state(const Player& player, const Dealer& dealer, int current_bet);
    void display_error(const std::string& message);
    void display_player_bust();
    void display_dealer_blackjack();
    void display_player_blackjack(int payout);
    void display_both_blackjack();
    void display_player_wins(int payout);
    void display_dealer_wins();
    void display_push();
    void display_message(const std::string& message);
    void display_final_funds(int funds);
    void display_thanks();
    void display_game_over(int final_funds);
    void display_round_separator();
    void display_starting_funds(int funds);
}

#endif
