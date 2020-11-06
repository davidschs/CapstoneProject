//
//  game.cpp
//  src
//
//  Created by David Schulte Südhoff on 11/6/20.
//  Copyright © 2020 David Schulte Südhoff. All rights reserved.
//

#include <vector>
#include "game.hpp"
#include "deck.hpp"


void initialize(Game& game)
{
    // Initialize, shuffle, add players and deal first round of cards
    initialize(game.deck);
    shuffle(game.deck);
    add_players(game, game.num_players);
    deal_cards(game);
}

void add_players(Game& game, int num_players)
{
    // Create players and push back to object "players"
    for (int player = 1; player <= game.num_players; player++)
    {
        Player new_player;
        game.players.push_back(new_player);
    }
    std::cout << game.players.size() << " Players have been created" << std::endl;
}

void deal_cards(Game& game)
{
    std::cout << "The cards will be dealt" << std::endl;
    //std::cout << game.deck.cards.size() << std::endl;
    if (game.deck.cards.size() < 10) // Dealer Cut at 10 cards remaining
    {
        std::cout << "End of Deck, Dealer shuffle" << std::endl;
    }
    else
    {
        for (int card = 1; card <= game.cards_per_hand; card++)
        {
            for (int player = 1; player <=game.num_players; player++)
            {
                game.players[player].hand.push_back(game.deck.cards[0]);
                game.deck.cards.erase(game.deck.cards.begin());
                std::cout << game.deck.cards.size() << std::endl; // print deck size
            }
           // print_hand(game.players[1].hand);
        }
    }
    std::cout << "\n";
}

void print_game(const Game& game)
{
    for (int player = 1; player <= game.num_players; player++)
    {
        print_hand(game.players[player].hand);
        std::cout << '\n';
    }
}
