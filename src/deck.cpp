#include <deck.h>
#include <utils.h>
#include <random>

Card_deck::Card_deck() {
    for (int i = 0; i < 52; ++i) {
        deck[i].suite = i % 4;
        deck[i].value = i % 13;
    }
}

void Card_deck::print() {
    for (int i = 0; i < deck_size; i++) {
        print_card(deck[i]);
        if ((i + 1) % 4 == 0) {
            std::cout << std::endl;
        }
    }
}

void Card_deck::shuffle() {
    static std::default_random_engine generator(std::random_device{}());
    for (int i = deck_size - 1; i > 0; i--) {
        std::uniform_int_distribution<int> distribution(0,i);
        int j = distribution(generator);
        swap(&deck[i], &deck[j]);
    }
}

void Card_deck::reset() {
    deck_size = 52;
}

Card Card_deck::deal(){
    if (deck_size > 0) {
        return deck[--deck_size];
    }
    return Card{};
}
