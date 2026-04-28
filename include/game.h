#ifndef GAME_H
#define GAME_H

#include "deck.h"
#include "player.h"

class Game {
public:
    enum class GameOutcome {
        PLAYER_BLACKJACK,
        DEALER_BLACKJACK,
        BOTH_BLACKJACK,
        PLAYER_WIN,
        DEALER_WIN,
        PUSH,
        PLAYER_BUST,
        DEALER_BUST
    };

    Game();

    void run();

private:
    Card_deck deck;
    Player player;
    Dealer dealer;
    int current_bet = 0;
    
    void play_round();
    bool has_funds_to_play();
    void init_funds();
    int place_bet();
    void deal_initial_cards();
    bool check_bj();
    bool player_turn();
    void dealer_turn();
    GameOutcome determine_outcome();
    int calculate_payout(GameOutcome outcome) const;
    void apply_payout(GameOutcome outcome);
};

#endif
