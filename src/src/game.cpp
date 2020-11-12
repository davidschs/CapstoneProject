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
#include <numeric>

void initialize(Game& game)
{
    // Initialize, shuffle, add players and deal first round of cards
    initialize(game.deck);
    shuffle(game.deck);
    add_players(game, game.num_players);
    deal_cards(game);
    play_round(game);
}

void add_players(Game& game, int num_players)
{
    // Create players and push back to object "players"
    for (int player = 0; player < game.num_players; player++)
    {
        Player new_player;
        game.players.push_back(new_player);
    }
    std::cout << game.players.size() << " Players have been created" << std::endl;
}

void deal_cards(Game& game)
{
    std::cout << "The cards will be dealt" << std::endl;
    if (game.deck.cards.size() < 10) // Dealer Cut at 10 cards remaining
    {
        std::cout << "End of Deck, Dealer shuffle" << std::endl;
    }
    else
    {
        // Deal the first round, each player + dealer gets two cards
        for (int card = 0; card < game.cards_per_hand; card++)
        {
            for (int player = 0; player < game.num_players; player++)
            {
                game.players[player].hand.push_back(game.deck.cards[0]);
                game.deck.cards.erase(game.deck.cards.begin());
                //std::cout << game.deck.cards.size() << std::endl; // print deck size
            }
            game.dealer.hand.push_back(game.deck.cards[0]);
            game.deck.cards.erase(game.deck.cards.begin());
            //std::cout << game.deck.cards.size() << std::endl; // print deck size
        }
    }
        std::cout << "\n";
}

void print_game(const Game& game)
{
    for (int player = 0; player < game.num_players; player++)
    {
        print_hand(game.players[player].hand);
        std::cout << '\n';
    }
    print_hand(game.dealer.hand);
}

char make_decision()
{
    // Player has to decide the next move
    char decision = '\0';
    bool decision_made = false;
    while (decision_made == false)
    {
        std::cout << "Do you want to hit or stay? (Press [H] or [S])? >>";
        std::cin >> decision;
        if (decision == 'h')
        {
            std::cout << "Player made decision to hit" << std::endl;
            decision_made = true;
        }
        else if (decision == 's')
        {
            std::cout << "Player made decision to stay" << std::endl;
            decision_made = true;
        }
        else
        {
            std::cout << "Invalid Decision" << std::endl;
            decision_made = true;
        }
    }
    return decision;
}

int check_score(const std::vector<Card>& hand)
{
    // Loop over card values of hand and return the score
    int score = 0;
    for (int card=0; card<hand.size(); card++)
    {
        score = score + get_value(hand[card].rank);
    }
    //std::cout << score << std::endl;
    return score;
}

void compare_score(Game& game)
{
    //Compare the players score with the dealers hand
    std::cout << "Dealer has the hand ";
    print_hand(game.dealer.hand);
    for (int player = 0; player < game.num_players; player++)
    {
        game.dealer.score = check_score(game.dealer.hand);
        game.players[player].score = check_score(game.players[player].hand);
        if (game.players[player].score > game.dealer.score)
        {
            std::cout << "Player number " << player+1 << " wins" <<std::endl;
        }
        else if (game.players[player].score == game.dealer.score)
        {
            std::cout << "Player number " << player+1 << " pushes" <<std::endl;
        }
        else
        {
            std::cout << "Player " << player+1 << "looses" << std::endl;
        }
    }
}
               
void play_round(Game& game)
{
    std::cout << "Dealer has the Upcard ";
    print_card(game.dealer.hand[0]); // Print out first card of Dealers hand
    for(int player = 0; player < game.num_players; player++)
       {
           std::cout << "Player number " << player+1 << " has the hand:" << std::endl;
           print_hand(game.players[player].hand);
           game.players[player].score = check_score(game.players[player].hand); //players score
           
           bool player_finished = false;
           while (player_finished != true)
           {
               if (make_decision() == 'h')
               {
                   // If players hits, he gets a new card and the score is checked again
                   game.players[player].hand.push_back(game.deck.cards[0]);
                   game.deck.cards.erase(game.deck.cards.begin());
                   game.players[player].score = check_score(game.players[player].hand);
                   if (game.players[player].score > 21)
                   {
                       std::cout << "Player bust" << std::endl;
                       player_finished = true;
                   }
               }
               else
               {
                   player_finished = true;
               }
           }
       }
    compare_score(game);
}
