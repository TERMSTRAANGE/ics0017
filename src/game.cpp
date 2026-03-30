#include <game.h>
#include <utils.h>
#include <iostream>
#include <limits>

Game::Game() {
    deck.shuffle();
}

void Game::run() {
    init_funds();
    
    while (has_funds_to_play()) {
        play_round();
        if (!ask_play_again()) {
            break;
        }
    }
    
    clear_screen();
    std::cout << "Final funds: " << player.get_funds() << "$." << std::endl;
    std::cout << "Thanks for playing!" << std::endl;
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
    display_round_start();

    if (check_bj()) {
        return;
    }

    if (player_turn()) {
        return;
    }
    
    dealer_turn();
    display_round_result();
    
    GameOutcome outcome = determine_outcome();
    apply_payout(outcome);
}

bool Game::ask_play_again() {
    while (true) {
        std::string response;
        std::cout << std::endl << "Play another round? (yes/no): ";
        std::cin >> response;
        
        if (response == "yes" || response == "y") {
            return true;
        } else if (response == "no" || response == "n") {
            return false;
        } else {
            std::cout << "Please enter 'yes' or 'no'." << std::endl;
        }
    }
}

bool Game::has_funds_to_play() {
    if (player.get_funds() <= 0) {
        clear_screen();
        std::cout << "No funds remaining. Game over!" << std::endl;
        return false;
    }
    return true;
}

void Game::display() const {
    clear_screen();
    std::cout << "Funds: " << player.get_funds() << "$ | Bet: " << current_bet << "$." << std::endl;
    std::cout << std::endl;
    std::cout << "Dealer: ";
    dealer.print_hand();
    std::cout << std::endl;
    std::cout << "Player: ";
    player.print_hand();
    std::cout << std::endl;
}

void Game::display_round_start() const {
    display();
    std::cout << std::endl;
}

void Game::display_round_result() const {
    display();
}

void Game::init_funds(){
    while (true){
        int funds;
        std::cout << "Please enter the base funds: ";
        if (!(std::cin >> funds)){
                std::cout << "Invalid input, enter a number." << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                continue;
            }
        if (player.set_funds(funds) == 1) {
            std::cout << "Starting with " << player.get_funds() << "$." << std::endl;
            break;
        }
        else {
            std::cout << "Enter an appropriate amount." << std::endl;
        }
    }
}

int Game::place_bet() {
    while (true) {
        int bet;
        std::cout << "Current funds: " << player.get_funds() << "$." << std::endl;
        std::cout << "Place your bet: ";
        
        if (!(std::cin >> bet)){
            std::cout << "Invalid input, enter a number." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            continue;
        }
        
        if (player.place_bet(bet) == 1) {
            current_bet = bet;
            return bet;
        }
        else {
            std::cout << "Invalid bet amount. Must be between 1$ and " << (player.get_funds() + bet) << "$." << std::endl;
        }
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
        std::cout << "Both have Blackjack! Push." << std::endl;
    }
    else if (player_check) {
        outcome = GameOutcome::PLAYER_BLACKJACK;
        std::cout << "Blackjack! Player wins " << calculate_payout(outcome) << "$!" << std::endl;
    }
    else {
        outcome = GameOutcome::DEALER_BLACKJACK;
        std::cout << "Dealer has Blackjack! Dealer wins." << std::endl;
    }
    
    apply_payout(outcome);
    return true;
}

bool Game::player_turn() {
    while (true) {
        int choice;
        std::cout << "1) Hit  2) Stand: ";

        if (!(std::cin >> choice)){
            std::cout << "Invalid input, enter a number." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            continue;
        }

        if (choice == 1) {
            player.receive_card(deck.deal());
            display();
            if (player.is_bust()) {
                std::cout << "Player busts! Dealer wins." << std::endl;
                return true;
            }
        }

        else if (choice == 2) {
            return false;
        }

        else {
            std::cout << "Invalid number, enter 1 or 2." << std::endl;
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
            std::cout << "Player wins " << payout << "$!" << std::endl;
            break;
        case GameOutcome::BOTH_BLACKJACK:
        case GameOutcome::PUSH:
            std::cout << "Push (tie). You get your bet back." << std::endl;
            break;
        case GameOutcome::DEALER_BLACKJACK:
        case GameOutcome::PLAYER_BUST:
        case GameOutcome::DEALER_WIN:
            std::cout << "Dealer wins." << std::endl;
            break;
        default:
            break;
    }
    
    player.add_win(payout);
    std::cout << "Funds remaining: " << player.get_funds() << "$." << std::endl;
}
