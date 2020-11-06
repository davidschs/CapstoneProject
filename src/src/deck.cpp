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
#include "deck.h"


void initialize(Deck& deck)
// Filling the Deck with the appropriate specific cards
{
    Card card;
    for (int suit = 1; suit <= card.num_suit; suit++)
    {
        for (int rank = 1; rank <= card.num_rank; rank++)
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

void print_card(const Card& card)
{
        std::cout << "Suit: " << card.suit << " Card: " << card.rank << std::endl;
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

void deal_cards(Deck& deck, std::vector<Card>& player, std::vector<Card>& dealer, int num_cards)
{
    std::cout << deck.cards.size() << std::endl;
    if (deck.cards.size() < 10) // Dealer Cut at 10 cards remaining
    {
        std::cout << "End of Deck, Dealer shuffle" << std::endl;
    }
    else
    {
        for (int i = 1; i <= num_cards; i++)
        {
        player.push_back(deck.cards[0]);
        deck.cards.erase(deck.cards.begin());
        dealer.push_back(deck.cards[0]);
        deck.cards.erase(deck.cards.begin());
        }
    }
    print_hand(player);
    print_hand(dealer);
    std::cout << "\n";
}

void print_hand(const std::vector<Card>& hand)
{
    for (Card c : hand)
    {
        print_card(c);
    }
}
