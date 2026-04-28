#include <game.h>
#include <ui.h>
#include <exceptions.h>

Game::Game() {
    deck.shuffle();
}

void Game::run() {
    init_funds();
    
    while (has_funds_to_play()) {
        play_round();
        if (!UI::ask_play_again()) {
            break;
        }
    }
    
    UI::display_final_funds(player.get_funds());
    UI::display_thanks();
}

void Game::play_round() {
    player.clear_hand();
    dealer.clear_hand();
    
    int bet = place_bet();
    if (bet == 0) {
        return;
    }
    
    deck.reset();
    deck.shuffle();
    deal_initial_cards();
    UI::display_game_state(player, dealer, current_bet);
    UI::display_round_separator();

    if (check_bj()) {
        return;
    }

    if (player_turn()) {
        return;
    }
    
    dealer_turn();
    UI::display_game_state(player, dealer, current_bet);
    
    GameOutcome outcome = determine_outcome();
    apply_payout(outcome);
}

bool Game::has_funds_to_play() {
    if (player.get_funds() <= 0) {
        UI::display_game_over(player.get_funds());
        return false;
    }
    return true;
}

void Game::init_funds() {
    try {
        int funds = UI::get_initial_funds();
        player.set_funds(funds);
    }
    catch (const InvalidFundsException& e) {
        UI::display_error(e.what());
        init_funds();
    }
}

int Game::place_bet() {
    try {
        int bet = UI::get_bet(player.get_funds());
        player.place_bet(bet);
        current_bet = bet;
        return bet;
    }
    catch (const InvalidBetException& e) {
        UI::display_error(e.what());
        return place_bet();
    }
}

void Game::deal_initial_cards() {
    player.receive_card(deck.deal());
    dealer.receive_card(deck.deal());
    player.receive_card(deck.deal());
    dealer.receive_card(deck.deal());
}

bool Game::check_bj() {
    bool player_check = player.has_blackjack();
    bool dealer_check = dealer.has_blackjack();
    
    if (!player_check && !dealer_check) {
        return false;
    }
    
    GameOutcome outcome;
    if (player_check && dealer_check) {
        outcome = GameOutcome::BOTH_BLACKJACK;
        UI::display_both_blackjack();
    }
    else if (player_check) {
        outcome = GameOutcome::PLAYER_BLACKJACK;
        UI::display_player_blackjack(calculate_payout(outcome));
    }
    else {
        outcome = GameOutcome::DEALER_BLACKJACK;
        UI::display_dealer_blackjack();
    }
    
    apply_payout(outcome);
    return true;
}

bool Game::player_turn() {
    while (true) {
        int choice = UI::get_player_action();

        if (choice == 1) {
            player.receive_card(deck.deal());
            UI::display_game_state(player, dealer, current_bet);
            if (player.is_bust()) {
                UI::display_player_bust();
                return true;
            }
        }
        else {
            return false;
        }
    }
}

void Game::dealer_turn() {
    while (dealer.should_hit()) {
        dealer.receive_card(deck.deal());
    }
}

int Game::calculate_payout(GameOutcome outcome) const {
    const int BET = current_bet;
    const int BLACKJACK_PAYOUT = BET + (BET * 3 / 2);
    const int WIN_PAYOUT = BET * 2;
    const int PUSH_PAYOUT = BET;
    const int LOSS_PAYOUT = 0;
    
    switch (outcome) {
        case GameOutcome::PLAYER_BLACKJACK:
            return BLACKJACK_PAYOUT;
        case GameOutcome::BOTH_BLACKJACK:
        case GameOutcome::PUSH:
            return PUSH_PAYOUT;
        case GameOutcome::PLAYER_WIN:
        case GameOutcome::DEALER_BUST:
            return WIN_PAYOUT;
        case GameOutcome::DEALER_BLACKJACK:
        case GameOutcome::PLAYER_BUST:
        case GameOutcome::DEALER_WIN:
        default:
            return LOSS_PAYOUT;
    }
}

Game::GameOutcome Game::determine_outcome() {
    int player_score = player.hand_sum();
    int dealer_score = dealer.hand_sum();
    
    if (player_score > 21) {
        return GameOutcome::PLAYER_BUST;
    }
    else if (dealer_score > 21) {
        return GameOutcome::DEALER_BUST;
    }
    else if (player_score > dealer_score) {
        return GameOutcome::PLAYER_WIN;
    }
    else if (player_score == dealer_score) {
        return GameOutcome::PUSH;
    }
    else {
        return GameOutcome::DEALER_WIN;
    }
}

void Game::apply_payout(GameOutcome outcome) {
    int payout = calculate_payout(outcome);
    
    switch (outcome) {
        case GameOutcome::PLAYER_BLACKJACK:
        case GameOutcome::PLAYER_WIN:
        case GameOutcome::DEALER_BUST:
            UI::display_player_wins(payout);
            break;
        case GameOutcome::BOTH_BLACKJACK:
        case GameOutcome::PUSH:
            UI::display_push();
            break;
        case GameOutcome::DEALER_BLACKJACK:
        case GameOutcome::PLAYER_BUST:
        case GameOutcome::DEALER_WIN:
            UI::display_dealer_wins();
            break;
        default:
            break;
    }
    
    player.add_win(payout);
    UI::display_message("Funds remaining: " + std::to_string(player.get_funds()) + "$.");
}

