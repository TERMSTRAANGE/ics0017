#include <player.h>
#include <iostream>
#include <limits>

void Player::receive_card(Card card) {
    if (hand_size < MAX_HAND) {
        hand[hand_size++] = card;
    }
}

int Player::hand_sum() const {
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

bool Player::has_blackjack() const {
    return hand_size == 2 && hand_sum() == 21;
}

bool Player::is_bust() const {
    return hand_sum() > 21;
}

void Player::print_hand() const {
    for (int i = 0; i < hand_size; i++) {
        print_card(hand[i]);
    }

    std::cout << " (" << hand_sum() << ")";
}

int Player::get_hand_size() const {
    return hand_size;
}

int Player::set_funds(int money) {
    if (money <= 0) {
        return 0;
    }
    else {
        funds = money;
        return 1;
    }
}

int Player::get_funds() const {
    return funds;
}

int Player::place_bet(int bet_amount) {
    if (bet_amount <= 0 || bet_amount > funds) {
        return 0;
    }
    funds -= bet_amount;
    return 1;
}

void Player::add_win(int amount) {
    funds += amount;
}

void Player::clear_hand() {
    hand_size = 0;
}

bool Dealer::should_hit() {
    return hand_sum() < 17;
}
