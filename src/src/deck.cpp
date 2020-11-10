//
//  deck.cpp
//  src
//
//  Created by David Schulte Südhoff on 11/5/20.
//  Copyright © 2020 David Schulte Südhoff. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <vector>
#include <iostream>
#include <cstdlib>
#include "deck.hpp"
#include "game.hpp"

// print name of enum class
void print_rank(Rank r) {
   switch(r) {
      case Two:
         std::cout << "Two";
         break;
      case Three:
         std::cout << "Three";
         break;
      case Four:
         std::cout << "Four";
         break;
      case Five:
         std::cout << "Five";
         break;
      case Six:
         std::cout << "Six";
         break;
      case Seven:
         std::cout << "Seven";
         break;
      case Eight:
         std::cout << "Eight";
         break;
      case Nine:
         std::cout << "Nine";
         break;
      case Ten:
         std::cout << "Ten";
         break;
      case Jack:
         std::cout << "Jack";
         break;
      case Queen:
         std::cout << "Queen";
         break;
      case King:
         std::cout << "King";
         break;
      case Ace:
         std::cout << "Ace";
         break;
   }
}

void print_suit(Suit s) {
switch(s) {
   case Spades:
      std::cout << "Spades";
      break;
   case Heards:
      std::cout << "Heards";
      break;
   case Clubs:
      std::cout << "Clubs";
      break;
   case Diamonds:
      std::cout << "Diamonds";
      break;
   }
}
void initialize(Deck& deck)
// Filling the Deck with the appropriate specific cards
{
    Card card;
    for (int suit = 0; suit < card.num_suit; suit++)
    {
        for (int rank = 0; rank < card.num_rank; rank++)
        {
            card.suit = Suit(suit);
            card.rank = Rank(rank);
            deck.cards.push_back(card);
        }
    }
}

void print_deck(const Deck& deck)
{
    for (Card c : deck.cards)
    {
        print_card(c);
    }
}

void print_hand(const std::vector<Card>& hand)
{
    for (Card c : hand)
    {
        print_card(c);
    }
}

void print_card(const Card& card)
{
    print_rank(card.rank);
    std::cout << " of ";
    print_suit(card.suit);
    std::cout << '\n';
}

void shuffle(Deck& deck)
{
    std::cout << "Deck will be shuffled" << std::endl;
    Deck shuffled;
    // Pull random cards from the deck and push it into shuffled.cards vector
    // Delete pulled card after pushing it into vector
    while (!deck.cards.empty())
    {
        size_t rand_card = rand() % deck.cards.size();
        shuffled.cards.push_back(deck.cards[rand_card]);
        deck.cards.erase(deck.cards.begin() + rand_card);
    }
    deck = shuffled;
}

