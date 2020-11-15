//
//  game.hpp
//  src
//
//  Created by David Schulte Südhoff on 11/6/20.
//  Copyright © 2020 David Schulte Südhoff. All rights reserved.
//

#ifndef game_hpp
#define game_hpp

#include <stdio.h>
#include <vector>
#include "deck.hpp"

struct Player {
    std::vector<Card> hand;
    int score;
};

struct Game {
    std::vector<Player> players;
    Player dealer;
    int num_players;
    int cards_per_hand = 2;
    Deck deck;
};

void initialize(Game&);
void add_players(Game&);
void deal_cards(Game&);
void print_game(const Game&);
void play_round(Game&);
char make_decision();
int check_score(const std::vector<Card>&);
void compare_score(Game&);
void dealer_move(Game&);
bool check_blackjack(int);
bool all_player_bust(Game&);
void game_loop(Game&);
void clear_hands(Game&);
#endif /* game_hpp */
    
