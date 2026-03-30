#ifndef CARD_H
#define CARD_H

#include <iostream>

struct Card {
public:
    int value, suite = -1;
};

int card_points(Card card);
void print_card(Card card);

#endif
