#ifndef DECK_H
#define DECK_H

#include "card.h"

class Card_deck {
public:
    Card_deck();

    void print();

    void shuffle();
    
    void reset();

    Card deal();

private:
    Card deck[52];
    int deck_size = 52;
};

#endif
