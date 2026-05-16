#ifndef PLAYER_H
#define PLAYER_H

#include <card.h>

class Player {
public:
    virtual void receive_card(Card card);

    virtual int hand_sum() const;

    virtual bool has_blackjack() const;

    virtual bool is_bust() const;

    virtual void print_hand() const;

    virtual int get_hand_size() const;

    virtual int set_funds(int money);

    int get_funds() const;

    int place_bet(int bet_amount);

    void add_win(int amount);

    virtual void clear_hand();

protected:
    static const int MAX_HAND = 11;
    Card hand[MAX_HAND];
    int hand_size = 0;
private:
    int funds = 0;
};

class Dealer : public Player {
public:
    bool should_hit();
};

#endif
