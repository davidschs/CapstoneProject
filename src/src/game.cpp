//
//  game.cpp
//  src
//
//  Created by David Schulte Südhoff on 11/6/20.
//  Copyright © 2020 David Schulte Südhoff. All rights reserved.
//

#include <vector>
#include <numeric>
#include <thread>
#include <chrono>
#include <algorithm>
#include "game.hpp"
#include "deck.hpp"

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
    std::this_thread::sleep_for (std::chrono::seconds(2));
}

void deal_cards(Game& game)
{
    std::cout << "The cards will be dealt" << std::endl;
    std::this_thread::sleep_for (std::chrono::seconds(1));
    std::cout << "-------------------------------------" << std::endl;
    std::this_thread::sleep_for (std::chrono::seconds(1));
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
        std::cout << "Do you want to hit or stay? (Press [H] or [S]) >>";
        std::cin >> decision;
        if (decision == 'h')
        {
            std::cout << "Player made decision to hit" << std::endl;
            std::this_thread::sleep_for (std::chrono::seconds(2));
            decision_made = true;
        }
        else if (decision == 's')
        {
            std::cout << "Player made decision to stay" << std::endl;
            std::cout << '\n';
            std::this_thread::sleep_for (std::chrono::seconds(2));
            decision_made = true;
        }
        else
        {
            std::cout << "Invalid Decision" << std::endl;
        }
    }
    return decision;
}


int check_score(const std::vector<Card>& hand)
{
    // Loop over card values of hand and return the score
    int score = 0;
    // deklaring two Aces if players gets two aces in a hand
    bool ace1 = false;
    bool ace2 = false;
    for (int card=0; card<hand.size(); card++)
    {
        score = score + get_value(hand[card].rank);
        // Aces get handled uniquely since their value is either 1 or 11
        if (get_value(hand[card].rank) == 11)
        {
            if (ace1 == true)
            {
                ace2 = true; //setting ace2 to true if second ace appears in hand
            }
            else
            {
                ace1 = true; //setting ace1 to true when first ace appears in hand
            }
        }
        if (score > 21 && ace1 == true)
        {
            if (ace2 == true)
            {
                score = score-10;
                ace2 = false; // ace2 is set to value 1 when player surpasses 21
            }
            else
            {
                score = score-10;
                ace1 = false; // ace1 is set to value 1 if player surpasses 21 again
            }
        }
    }
    return score;
}

bool all_player_bust(Game& game)
{
    bool players_bust = true;
    int player = 0;
    //check if all players busted in this round
    while (players_bust == true && player < game.num_players)
    {
        game.players[player].score = check_score(game.players[player].hand);
        if (game.players[player].score < 22)
        {
            // If one player did not bust, set players_bust to false
            players_bust = false;
        }
        player = player + 1;
    }
    return players_bust;
}


bool check_blackjack(int score)
{
    bool blackjack = false;
    if (score == 21)
    {
        blackjack = true;
    }
    else
    {
        blackjack = false;
    }
    return blackjack;
}


void compare_score(Game& game)
{
    //Compare the players score with the dealers hand
    // If dealer busted, every player wins
    std::cout << "Dealer has the score " << game.dealer.score << std::endl;
    std::cout << '\n';
    std::this_thread::sleep_for (std::chrono::seconds(2));
    for (int player = 0; player < game.num_players; player++)
    {
        game.dealer.score = check_score(game.dealer.hand);
        game.players[player].score = check_score(game.players[player].hand);
        // Neither dealer or player bust, but player has higher score
        if (game.players[player].score > game.dealer.score && game.players[player].score <  22)
        {
            std::cout << "Player " << player+1 << " wins" <<std::endl;
        }
        // If dealer busts, but player doesn't
        else if (game.players[player].score < 22 && game.dealer.score > 21)
        {
            std::cout << "Player " << player+1 << " wins" <<std::endl;
        }
        // If player has a blackjack (first two cards)
        else if (game.players[player].score == 21 && game.players[player].hand.size() == 2 && game.dealer.score != 21)
        {
            std::cout << "Player " << player+1 << " wins due to Blackjack" << std::endl;
        }
        // Dealer and player push
        else if (game.players[player].score == game.dealer.score && game.players[player].score < 22)
        {
            std::cout << "Player " << player+1 << " pushes" <<std::endl;
        }
        else
        {
        std::cout << "Player " << player+1 << " looses" << std::endl;
        }
    }
}
        

void dealer_move(Game& game)
{
    std::cout << "Players decisions are made, Dealers turn" << std::endl;
    std::this_thread::sleep_for (std::chrono::seconds(1));
    std::cout << "----------------------------------------" << std::endl;
    std::this_thread::sleep_for (std::chrono::seconds(2));
    std::cout << "Dealers hole card is a ";
    print_card(game.dealer.hand[1]);
    std::this_thread::sleep_for (std::chrono::seconds(2));
    std::cout << "Dealer has the full hand: " << std::endl;
    print_hand(game.dealer.hand);
    game.dealer.score = check_score(game.dealer.hand);
    std::this_thread::sleep_for (std::chrono::seconds(2));
    //  If all players busted already, Dealer does not need to pull another card
    if (all_player_bust(game) == false)
    {
        bool dealer_finished = false;
        while (dealer_finished == false)
        {
            if (game.dealer.score < 17)
            {
                std::cout << "Dealer takes another card" << std::endl;
                game.dealer.hand.push_back(game.deck.cards[0]);
                std::cout << "Next card is a ";
                print_card(game.deck.cards[0]);
                std::this_thread::sleep_for (std::chrono::seconds(2));
                game.deck.cards.erase(game.deck.cards.begin()); // remove card from deck
                game.dealer.score = check_score(game.dealer.hand); // check score
                if (game.dealer.score > 21)
                {
                    std::cout << "Dealer bust!" << std::endl;
                    std::cout << '\n';
                    std::this_thread::sleep_for (std::chrono::seconds(2));
                    dealer_finished = true;
                }
            }
            else
            {
                std::cout << '\n';
                dealer_finished = true;
            }
        }
    }
    else
    {
        std::cout << "All players busted, Dealer wins" << std::endl;
    }
}

void play_round(Game& game)
{
    std::cout << "Dealer has the Upcard ";
    print_card(game.dealer.hand[0]); // Print out first card of Dealers hand
    std::cout << '\n';
    std::this_thread::sleep_for (std::chrono::seconds(2));
    // check if dealer has a Blackjack
    if (check_blackjack(game.dealer.score) != true)
    {
        // If dealer does not have a Blackjack, continue play
        for(int player = 0; player < game.num_players; player++)
        {
           std::cout << "Player number " << player+1 << " has the hand:" << std::endl;
           print_hand(game.players[player].hand);
           std::this_thread::sleep_for (std::chrono::seconds(2));
           game.players[player].score = check_score(game.players[player].hand);
           std::cout << "Current Score: " << game.players[player].score << std::endl;
           std::this_thread::sleep_for (std::chrono::seconds(2));
           
           if (check_blackjack(game.players[player].score) == true)
           {
               std::cout << "Player has a Blackjack!" << std::endl;
               continue;
           }
           
           bool player_finished = false;
           while (player_finished != true)
           {
               if (make_decision() == 'h')
               {
                   // If players hits, he gets a new card and the score is checked again
                   game.players[player].hand.push_back(game.deck.cards[0]);
                   std::cout << "Player gets the card ";
                   print_card(game.deck.cards[0]);
                   std::this_thread::sleep_for (std::chrono::seconds(2));
                   game.players[player].score = check_score(game.players[player].hand);
                   std::cout << "Current Score: " << game.players[player].score << std::endl;
                   std::this_thread::sleep_for (std::chrono::seconds(2));
                   game.deck.cards.erase(game.deck.cards.begin());
                   if (game.players[player].score > 21)
                   {
                       std::cout << "Player bust!" << std::endl;
                       std::cout << '\n';
                       std::this_thread::sleep_for (std::chrono::seconds(2));
                       player_finished = true;
                   }
               }
               else
               {
                   // Player decides to stay
                   player_finished = true;
               }
           }
       }
        dealer_move(game);
        compare_score(game);
    }
    else
    {
        // If dealer does have a Blackjack, compare score with players
        std::cout << "Dealer has a Blackjack!" << std::endl;
        compare_score(game);
    }
}
