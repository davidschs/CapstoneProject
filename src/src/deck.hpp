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
enum Rank
{
    Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King, Ace
};

enum Suit
{
    Spades, Heards, Clubs, Diamonds
};

/*
//operator overloading to access strings of enum
std::ostream &operator << (std:: ostream& os, Rank r)
{
   const std::string rank[] = {"Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"};
   return os << rank[r];
}
*/
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
