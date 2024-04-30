#include<iostream>
#include "PokerGame.h"
using namespace std;

void cheatInput(vector<int>& player)
{
	//TO_DO: Ask user input five number and store them to vector of player

	for (int i = 0; i <= 4; i++) 
	{
		cin >> player[i];
	}

	for (int i = 0; i <= 4; i++)
	{

		if (player[i] >= 0 && player[i] <= 12) {
			player[i + 5] = player[i] + 1;
		}
		else if (player[i] >= 13 && player[i] <= 25) {
			player[i + 5] = player[i] - 12;
		}
		else if (player[i] >= 26 && player[i] <= 38) {
			player[i + 5] = player[i] - 25;
		}
		else if (player[i] >= 39 && player[i] <= 51) {
			player[i + 5] = player[i] - 38;
		}
	}

	//«ö·Ó¸¹½X±Æ§Ç
	int tmp;
	for (int i = 4; i > 0; i--)
	{
		for (int j = 5; j <= i + 4; j++)
		{
			if (player[j] > player[j + 1])
			{
				tmp = player[j];
				player[j] = player[j + 1];
				player[j + 1] = tmp;

				tmp = player[j - 5];
				player[j - 5] = player[j - 4];
				player[j - 4] = tmp;
			}
		}
	}

	
}
int main() {
	bool Exit = false;

	while (!Exit) {
		PokerGame player1, player2;
		vector<int> cheatCards1(10), cheatCards2(10);
		
		bool usedCards[52] = { false };
		int winner;
		char GameType;
		cout << "Enter S to start the game, C to enter cheating mode, Q to Exit the process" << endl;
		cin >> GameType;
		cout << endl;

		switch (GameType) {
		case 's':
		case 'S':
			//Normal mode, generate five cards for each players
			player1.distribute(usedCards);
			player2.distribute(usedCards);

			//Evaluate the type of cards and which is maxNumber in the cards
			player1.evaluate();
			player2.evaluate();

			//Print the cards of each players
			player1.printCards();
			player2.printCards();

			cout << "Player1 Type = " << table[player1.getType()] << endl;
			cout << "Player2 Type = " << table[player2.getType()] << endl;

			//Compare and output winner
			player1.compare(player2.getType(),player2.getMaxNumber(),player2.getmaxSuit());
			break;
		case 'c':
		case 'C':
			//Cheat mode , input the player cards
			cout << "Input player 1's card:";
			cheatInput(cheatCards1);
			cout << endl;
			cout << "Input player 2's card:";
			cheatInput(cheatCards2);

			//player1.set(cheatCards1);
			//player2.set(cheatCards2);

			//Evaluate the type of cards and which is maxNumber in the cards
			player1.evaluate();
			player2.evaluate();

			//Print the cards of each players
			player1.printCardsForCheat(cheatCards1); 
			player2.printCardsForCheat(cheatCards2);

			cout << "Player1 Type = " << table[player1.getType()] << endl;
			cout << "Player2 Type = " << table[player2.getType()] << endl;

			//Compare and output winner
			player1.compare(player2.getType(),player2.getMaxNumber(),player2.getmaxSuit());
			break;
		case 'q':
		case 'Q':
			Exit = true;
		default:
			break;
		}
	}
}