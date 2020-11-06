//
//  deck.h
//  src
//
//  Created by David Schulte Südhoff on 11/5/20.
//  Copyright © 2020 David Schulte Südhoff. All rights reserved.
//

#ifndef deck_h
#define deck_h
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
    std::vector<Card> cards;
    int deck_size = 52;
};

void initialize(Deck&);
void print_deck(const Deck&);
void print_card(const Card&);
void shuffle(Deck&);
void deal_cards(Deck&, std::vector<Card>&, std::vector<Card>&, int);
void print_hand(const std::vector<Card>&);

#endif /* deck_h */
