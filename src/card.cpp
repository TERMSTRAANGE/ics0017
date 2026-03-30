#include <card.h>

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
    switch (card.value) {
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

    switch (card.suite) {
        case 0:
            std::cout << "♠";
            break;
        case 1:
            std::cout << "\033[31m" << "♥" << "\033[0m";
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
