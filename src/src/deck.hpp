//
//  deck.hpp
//  src
//
//  Created by David Schulte Südhoff on 11/5/20.
//  Copyright © 2020 David Schulte Südhoff. All rights reserved.
//

#ifndef deck_hpp
#define deck_hpp
#include <vector>
#include <iostream>

// Define all possible Rank and Suit of cards
enum Rank { two, three, four, five, six, seven, eight, nine, ten, jack, queen, king, ace};
enum Suit { Spades, Heards, Clubs, Diamonds};

// Define the Card
struct Card {
    Rank rank;
    Suit suit;
    int num_rank = 13;
    int num_suit = 4;
    
};

// Define the Deck containing of the Cards
struct Deck {
    int deck_size = 52;
    std::vector<Card> cards;
};

void initialize(Deck&);
void print_deck(const Deck&);
void print_card(const Card&);
void shuffle(Deck&);
void print_hand(const std::vector<Card>&);

#endif /* deck_hpp */
