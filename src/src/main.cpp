//
//  main.cpp
//
//  Created by David Schulte Südhoff on 11/4/20.
//  Copyright © 2020 David Schulte Südhoff. All rights reserved.
//  Udacity Capstone Project
//

#include <iostream>
#include <vector>
#include <thread>
#include "deck.h"

int main() {
    Deck my_deck;
    initialize(my_deck);
    shuffle(my_deck);
    std::vector<Card> player;
    std::vector<Card> dealer;
    deal_cards(my_deck, player, dealer, 2);
    
}

