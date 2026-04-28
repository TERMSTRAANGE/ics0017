#include "ui.h"
#include "utils.h"
#include "exceptions.h"
#include <iostream>
#include <limits>

namespace UI {
    int get_initial_funds() {
        while (true) {
            try {
                int funds;
                std::cout << "Enter your initial funds: ";
                std::cin >> funds;
                
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    throw InvalidInputException("Please enter a valid number.");
                }
                
                if (funds <= 0) {
                    throw InvalidFundsException(funds);
                }
                
                std::cout << "Starting funds: " << funds << "$." << std::endl;
                return funds;
            }
            catch (const InvalidInputException& e) {
                display_error(e.what());
            }
            catch (const InvalidFundsException& e) {
                display_error(e.what());
            }
        }
    }
    
    int get_bet(int available_funds) {
        while (true) {
            try {
                int bet;
                std::cout << "Your available funds: " << available_funds << "$." << std::endl;
                std::cout << "Enter your bet: ";
                
                std::cin >> bet;
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    throw InvalidInputException("Please enter a valid number.");
                }
                
                if (bet <= 0 || bet > available_funds) {
                    throw InvalidBetException(bet, available_funds);
                }
                
                return bet;
            }
            catch (const InvalidInputException& e) {
                display_error(e.what());
            }
            catch (const InvalidBetException& e) {
                display_error(e.what());
            }
        }
    }
    
    int get_player_action() {
        while (true) {
            try {
                int choice;
                std::cout << "1. Hit  2. Stand" << std::endl;
                std::cout << "Your choice: ";
                
                std::cin >> choice;
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    throw InvalidInputException("Please enter a valid number.");
                }
                
                if (choice != 1 && choice != 2) {
                    throw InvalidChoiceException(choice);
                }
                
                return choice;
            }
            catch (const InvalidInputException& e) {
                display_error(e.what());
            }
            catch (const InvalidChoiceException& e) {
                display_error(e.what());
            }
        }
    }
    
    bool ask_play_again() {
        while (true) {
            try {
                std::string response;
                std::cout << "Play again? (yes/no): ";
                std::cin >> response;
                
                if (response == "yes" || response == "y") {
                    return true;
                } else if (response == "no" || response == "n") {
                    return false;
                } else {
                    throw InvalidResponseException(response);
                }
            }
            catch (const InvalidResponseException& e) {
                display_error(e.what());
            }
        }
    }
    
    void display_game_state(const Player& player, const Dealer& dealer, int current_bet) {
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
    
    void display_error(const std::string& message) {
        std::cout << "[ERROR] " << message << std::endl;
    }
    
    void display_player_bust() {
        std::cout << "Player bust! Dealer wins." << std::endl;
    }
    
    void display_dealer_blackjack() {
        std::cout << "Dealer has blackjack! Dealer wins." << std::endl;
    }
    
    void display_player_blackjack(int payout) {
        std::cout << "Blackjack! You win: " << payout << "$." << std::endl;
    }
    
    void display_both_blackjack() {
        std::cout << "Both have blackjack! It's a push." << std::endl;
    }
    
    void display_player_wins(int payout) {
        std::cout << "Player wins: " << payout << "$." << std::endl;
    }
    
    void display_dealer_wins() {
        std::cout << "Dealer wins. You lose your bet." << std::endl;
    }
    
    void display_push() {
        std::cout << "Push! Your bet is returned." << std::endl;
    }
    
    void display_message(const std::string& message) {
        std::cout << message << std::endl;
    }
    
    void display_final_funds(int funds) {
        std::cout << "Final funds: " << funds << "$." << std::endl;
    }
    
    void display_thanks() {
        std::cout << "Thanks for playing!" << std::endl;
    }
    
    void display_game_over(int final_funds) {
        std::cout << "Game over! Your funds have run out." << std::endl;
        std::cout << "Final funds: " << final_funds << "$." << std::endl;
    }
    
    void display_round_separator() {
        std::cout << std::string(40, '-') << std::endl;
    }
    
    void display_starting_funds(int funds) {
        std::cout << "Starting funds: " << funds << "$." << std::endl;
    }
    
}
