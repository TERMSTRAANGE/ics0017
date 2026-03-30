#include <utils.h>
#include <card.h>
#include <iostream>

void clear_screen() {
    std::cout << "\033[2J\033[H";
}

void swap(Card* a, Card* b) {
    Card temp;
    temp.value = a -> value;
    temp.suite = a -> suite;
    a -> suite = b -> suite;
    a -> value = b -> value;
    b -> suite = temp.suite;
    b -> value = temp.value;
}
