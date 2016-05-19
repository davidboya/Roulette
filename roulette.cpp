/*
    Roulette - Programming Fundamentals with C++
    Copyright (C) 2016 David Boya <david@boya.se>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
// include necessary libraries so we can use functions that are needed for this program.
#include <iostream>
#include <ctime>

// search the std library so we can skip adding the "std::" prefix for input and output streams.
using namespace std;

int main()
{
	// define game variables.
	int account = 1000;
	int bet;
	int player_number;
	int win_number;
	int total_money_lost = 0;
	int total_money_won = 0;
	int total_games_lost = 0;
	int total_games_won = 0;
	
	string player_choice;
	string player_color;
	string win_color;
	string play_again_choice;
	
	bool play_again;
	bool error;
	
	// generate a seed from current unix timestamp
	srand(time(0));
	
	// welcome message to the player.
	cout << "[Roulette] Welcome to Roulette!" << endl;
	cout << "[Roulette] Your account balance is " << account << " kr." << endl;
	
	// loop: game loop.
	do
	{
		cout << endl << "* * * * * * * The bet * * * * * * *" << endl;
		// loop: choose bet amount, 3 choices. 100, 300, 500.
		do
		{
			cout << ">> Choose a bet amount ( 100 | 300 | 500 ): ";
			cin >> bet;
			
			if((bet != 100) && (bet != 300) && (bet != 500))
			{
				// input is invalid, value must be either '100', '300' or '500'.
				cout << "[Roulette] Invalid amount. You can only bet 100, 300 or 500." << endl;
				error = true;
			}
			else if(bet > account)
			{
				// input is invalid, player doesn't have enough money to make the bet.
				cout << "[Roulette] Invalid amount. You dont have that much money. Your account balance is " << account << " kr." << endl;
				error = true;
			}
			else
			{
				// input is valid, continue.
				error = false;
			}
		}
		while(error);
		
		// loop: make a choice, 2 choices. color or number.
		do
		{
			cout << ">> Do you want to bet on a color or a number? ( color | number ): ";
			cin >> player_choice;
			
			if(player_choice != "color" && player_choice != "number")
			{
				// input is not valid, input must be either 'color' or 'number'.
				cout << "[Roulette] Invalid choice. Please answer with 'color' or 'number'." << endl;
				error = true;
			}
			else
			{
				// input is valid, continue.
				error = false;
			}
		}
		while(error);
		
		// loop: choose between either the colors ('red' or 'black') or between number 1 to 36, depends on previous choice.
		do
		{
			if(player_choice == "color")
			{
				// player chose to bet on a color.
				cout << ">> Please choose the color you want to bet on. ( red | black ): ";
				cin >> player_color;
				
				if(player_color != "red" && player_color != "black")
				{
					// input is not valid, input must be either 'red' or 'black'.
					cout << "[Roulette] Invalid choice. Please answer with 'red' or 'black'." << endl;
					error = true;
				}
				else
				{
					// input is valid, continue.
					cout << "[Roulette] Bet summary: You bet " << bet << " kr on color " << player_color << "." << endl;
					error = false;
				}
			}
			else if(player_choice == "number")
			{
				// player chose to bet on a number.
				cout << ">> Please choose a number you want to bet on. ( 1 - 36 ): ";
				cin >> player_number;
				
				if(player_number < 1 || player_number > 36)
				{
					// input is not valid, input must be an integer between 1 to 36.
					cout << "[Roulette] Invalid choice. Please answer with an integer from 1 to 36." << endl;
					error = true;
				}
				else
				{
					// input is valid, continue.
					cout << "[Roulette] Bet summary: You bet " << bet << " kr on number " << player_number << "." << endl;
					error = false;
				}
			}
		}
		while(error);
		cout << "* * * * * * * * * * * * * * * * * *" << endl;
		
		cout << endl << "* * * * * Roulette result * * * * *" << endl;
		// spin the wheel.
		win_number = rand() % 36 + 1;
		
		// determine what color the wheel stopped on from the number with a simple modulo operation. even = black, odd = red.
		win_color = (win_number % 2) ? "red" : "black";
		
		// output winning number and color
		cout << "[Roulette] The roulette stopped on number " << win_number << " which is colored " << win_color << "." << endl;
		
		if(player_choice == "color" && player_color == win_color)
		{
			// player won a color bet.
			account += bet * 2;
			total_money_won += bet * 2;
			total_games_won++;
			
			cout << "[Roulette] You won " << bet * 2 << " kr. Congratulations!" << endl;
		}
		else if(player_choice == "number" && player_number == win_number)
		{
			// player won a number bet.
			account += bet * 10;
			total_money_won += bet * 10;
			total_games_won++;
			
			cout << "[Roulette] You won " << bet * 10 << " kr. Congratulations!" << endl;
		}
		else
		{
			// player lost.
			account -= bet;
			total_money_lost += bet;
			total_games_lost++;
			
			cout << "[Roulette] You lost " << bet << " kr. Bad luck!" << endl;
		}
		
		if(((player_choice == "color" && player_color == win_color) || (player_choice == "number" && player_number == win_number)) && (total_games_won > 1))
		{
			// player won the current bet and has won at least one time before.
			cout << "[Roulette] You've now won a total of " << total_money_won << " kr in " << total_games_won + total_games_lost << " games." << endl;
		}
		
		cout << "[Roulette] Your account balance is now " << account << " kr." << endl;
		cout << "* * * * * * * * * * * * * * * * * *" << endl << endl;
		
		// if player has enough money to make the minimum bet (100) ask player if he wants to play again
		if(account >= 100)
		{
			// loop: play again
			do
			{
				cout << ">> Do you want to play again? ( y(es) | n(o) ): ";
				cin >> play_again_choice;
				
				if(play_again_choice == "y" || play_again_choice == "yes")
				{
					// player wants to play again.
					play_again = true;
					error = false;
				}
				else if(play_again_choice == "n" || play_again_choice == "no")
				{
					// player doesn't want to play again.
					play_again = false;
					error = false;
				}
				else
				{
					// input is invalid, input must be either 'y', 'yes', 'n' or 'no'.
					cout << "[Roulette] Invalid choice. Please answer with 'y' / 'yes' or 'n' / 'no'." << endl;
					error = true;
				}
			}
			while(error);
		}
		else
		{
			// player doesn't have enough money to make minimum bet, redundant to ask player if he wants to play again, end the game.
			cout << "[Roulette] Insufficient amount of money to make a new bet." << endl;
			play_again = false;
		}
	}
	while(play_again);
	
	// print out game statistics
	cout << endl << "* * * * * Game statistics * * * * *" << endl;
	cout << "[Roulette] Total games played: " << total_games_won + total_games_lost << "." << endl;
	cout << "[Roulette] Games won: " << total_games_won << "." << endl;
	cout << "[Roulette] Games lost: " << total_games_lost << "." << endl;
	cout << "[Roulette] Total money won: " << total_money_won << " kr." << endl;
	cout << "[Roulette] Total money lost: " << total_money_lost << " kr." << endl;
	cout << "[Roulette] Account balance when game ended " << account << " kr." << endl;
	cout << "* * * * * * * * * * * * * * * * * *" << endl << endl;
	
	// print out goodbye message
	cout << "[Roulette] Thanks for playing Roulette. Welcome back later!" << endl;
	return 0;
}
