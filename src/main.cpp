#include <iostream>
#include <random>  //for shuffling

struct Card {
public:
    int value, suite = -1;
};

void clear_screen() {
    std::cout << "\033[2J\033[H"; //ANSI escape code to clear the screen(ESC[2J) and return cursor to the home position(ESC[H)
}

void swap(Card* a, Card* b) { //temporary swap implementation until move operator is implemented for card class
    Card temp;
    temp.value = a -> value;
    temp.suite = a -> suite;
    a -> suite = b -> suite;
    a -> value = b -> value;
    b -> suite = temp.suite;
    b -> value = temp.value;
}

int card_points(Card card) {
    if (card.value <= 8) {
        return card.value + 2;
    }

    else if (card.value <= 11) {
        return 10;
    }

    return 11;
}

void print_card(Card card) {
    switch(card.value) {
        case 9:
            std::cout << "J";
            break;
        case 10:
            std::cout << "Q";
            break;
        case 11:
            std::cout << "K";
            break;
        case 12:
            std::cout << "A";
            break;
        default:
            std::cout << card.value + 2;
            break;
    }

    switch(card.suite) {
        case 0:
            std::cout << "♠";
            break;
        case 1:
            std::cout << "\033[31m" << "♥" << "\033[0m"; //ANSI escape-code colouring, first part indicates the colour, second resets it
            break;
        case 2:
            std::cout << "♣";
            break;
        case 3:
            std::cout << "\033[31m" << "♦" << "\033[0m";
            break;
    }

    std::cout << " ";
}

class Card_deck {
public:
    Card_deck() {
        for (int i = 0; i < 52; ++i) {
            deck[i].suite = i % 4;
            deck[i].value = i % 13;
        }
    }

    void print() {
        for(int i = 0; i < deck_size; i++) {
            print_card(deck[i]);
            if ((i + 1) % 4 == 0) {
                std::cout << std::endl;
            }
        }
    }

    void shuffle() {
        static std::default_random_engine generator(std::random_device{}()); /*
        seed random generator with random_device which uses hardware/OS for the entropy
        static is used to make sure that generator doesn't get recreated every time shuffle is run
        */
        for(int i = deck_size - 1; i > 0; i--) { //durstenfeld version of fisher-yates shuffle algorithm(more random and much faster(O(n)vs O(n^2)))
            std::uniform_int_distribution<int> distribution(0,i);
            int j = distribution(generator);
            swap(&deck[i], &deck[j]);
        }
    }

    Card deal(){
        if (deck_size > 0) {
            return deck[--deck_size];
        }
        return Card{};
    }

private:
    Card deck[52];
    int deck_size = 52;
};

class Player {
public:
    void receive_card(Card card) {
        if (hand_size < MAX_HAND) {
            hand[hand_size++] = card;
        }
    }

    int hand_sum() {
        int sum = 0;
        int aces = 0;
        for (int i = 0; i < hand_size; i++) {
            sum += card_points(hand[i]);
            if (hand[i].value == 12) {
                aces++;
            }
        }

        while (sum > 21 && aces > 0) {
            sum -= 10;
            aces--;
        }

        return sum;
    }

    bool has_blackjack() {
        return hand_size == 2 && hand_sum() == 21;
    }

     bool is_bust() {
        return hand_sum() > 21;
    }

    void print_hand() {
        for (int i = 0; i < hand_size; i++) {
            print_card(hand[i]);
        }

        std::cout << " (" << hand_sum() << ")";
    }

    int get_hand_size() {
        return hand_size;
    }

private:
    static const int MAX_HAND = 11; //11 is the absolute maximum number of cards before busting
    Card hand[MAX_HAND];
    int hand_size = 0;
};


class Dealer {
public:
    void receive_card(Card card) {
        if (hand_size < MAX_HAND) {
            hand[hand_size++] = card;
        }
    }

    int hand_sum() {
        int sum = 0;
        int aces = 0;
        for (int i = 0; i < hand_size; i++) {
            sum += card_points(hand[i]);
            if (hand[i].value == 12) {
                aces++;
            }
        }

        while (sum > 21 && aces > 0) {
            sum -= 10;
            aces--;
        }

        return sum;
    }

    bool has_blackjack() {
        return hand_size == 2 && hand_sum() == 21;
    }

     bool is_bust() {
        return hand_sum() > 21;
    }

    bool should_hit() {
        return hand_sum() < 17;
    }

    void print_hand() {
        for (int i = 0; i < hand_size; i++) {
            print_card(hand[i]);
        }

        std::cout << " (" << hand_sum() << ")";
    }

    int get_hand_size() {
        return hand_size;
    }
private:
    static const int MAX_HAND = 11; //11 is the absolute maximum number of cards before busting
    Card hand[MAX_HAND];
    int hand_size = 0;
};

class Game {
public:
    Game() {
        deck.shuffle();
    }

    void play() {
        deal_initial_cards();
        display();
        std::cout << std::endl;

        if (check_bj()) {
            return;
        }

        if (player_turn()) {
            return;
        }
        
        dealer_turn();
        display();
        check_win();
    }
private:
    Card_deck deck;
    Player player;
    Dealer dealer;
    void display() {
        clear_screen();
        std::cout << "Dealer: ";
        dealer.print_hand();
        std::cout << std::endl;
        std::cout << "Player: ";
        player.print_hand();
        std::cout << std::endl;
    }

    void deal_initial_cards() {
        player.receive_card(deck.deal());
        dealer.receive_card(deck.deal());
        player.receive_card(deck.deal());
        dealer.receive_card(deck.deal());
    }

    bool check_bj() {
        bool player_check = player.has_blackjack();
        bool dealer_check = dealer.has_blackjack();
        if (player_check || dealer_check) {
            if (player_check && dealer_check) {
                std::cout << "Both have Blackjack! Push." << std::endl;
            }

            else if (player_check) {
                std::cout << "Blackjack! Player wins!" << std::endl;
            }

            else {
                std::cout << "Dealer has Blackjack! Dealer wins." << std::endl;
            }

            return true;
        }

        else {
            return false;
        }
    }

    bool player_turn() {
        while (true) {
            int choice;
            std::cout << "1) Hit  2) Stand: ";
            std::cin >> choice;

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
                std::cout << "Invalid choice. Please enter 1 or 2." << std::endl;
                std::cin.clear();
                std::cin.ignore(); //clear stdin to fix infinite loop when incorrect character is entered.
            }
        }
    }
    
    void dealer_turn() {
        while (dealer.should_hit()) {
            dealer.receive_card(deck.deal());
        }
    }

    void check_win() {
        int player_score = player.hand_sum();
        int dealer_score = dealer.hand_sum();
        
        if (dealer_score > 21) {
            std::cout << "Dealer busts! Player wins!" << std::endl;
        }

        else if (dealer_score > player_score) {
            std::cout << "Dealer wins." << std::endl;
        }

        else if (player_score > dealer_score) {
            std::cout << "Player wins!" << std::endl;
        }

        else {
            std::cout << "Push (tie)." << std::endl;
        }
    }
};

int main() {
    Game game;
    game.play();
    return 0;
}