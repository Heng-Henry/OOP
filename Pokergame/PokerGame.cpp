#include "PokerGame.h"

PokerGame::PokerGame() {
	//TO_DO: initial constructor
	
}

void PokerGame::distribute(bool usedCards[52]) 
{
	//TO_DO: Random generate five cards to player
	//Hint: Use usedCards to record which card have been distributed

	

	srand(time(0));
	int x;
	for (int i = 0; i < 5; i++) {
		x = rand() % (51 - 0 + 1) + 0;
		while (usedCards[x] == true) {
			x = rand() % (51 - 0 + 1) + 0;
		}
		usedCards[x] = true;
		playerCards[i] = x;
		//cout << playerCards[i] << endl;
		// cout << x << endl; // card generating test
	}


	for (int i = 0; i <= 4; i++)
	{

		if (playerCards[i] >= 0 && playerCards[i] <= 12) {
			playerCards[i + 5] = playerCards[i] + 1;
			
		}
		else if (playerCards[i] >= 13 && playerCards[i] <= 25) {
			playerCards[i + 5] = playerCards[i] - 12;
		}
		else if (playerCards[i] >= 26 && playerCards[i] <= 38) {
			playerCards[i + 5] = playerCards[i] - 25;
			
		}
		else if (playerCards[i] >= 39 && playerCards[i] <= 51) {
			playerCards[i + 5] = playerCards[i] - 38;
		
		}
	}

	// 用bubble sor把牌依照號碼大小排序

	int tmp;
	for (int i = 4; i > 0; i--)
	{
		for (int j = 5; j <= i + 4; j++)
		{
			if (playerCards[j] > playerCards[j + 1])
			{
				tmp = playerCards[j];
				playerCards[j] = playerCards[j + 1];
				playerCards[j + 1] = tmp;
				tmp = playerCards[j - 5];
				playerCards[j - 5] = playerCards[j - 4];
				playerCards[j - 4] = tmp;
			}
		}
	}
}

// this is for the cheating mode,which jump the distribute part
// just directly set cards to player
void PokerGame::set(vector<int> playerCard) 
{
	//TO_DO: Set the cards to player
	
}
void PokerGame::printCardsForCheat(vector<int>playerCards) 
{
	cout << "Player cards:" << endl;
	for (int i = 0; i <= 4; i++) {
		//TO_DO: Print the player's cards.
		// For example: "C1" "S2" "H3" ...
	
		if (playerCards[i] >= 0 && playerCards[i] <= 12) {
			cout << " C" << playerCards[i]+1;

		}
		else if (playerCards[i] >= 13 && playerCards[i] <= 25) {
			cout << " D" << playerCards[i]-12 ;

		}
		else if (playerCards[i] >= 26 && playerCards[i] <= 38) {
			cout << " H" << playerCards[i] - 25;

		}
		else if (playerCards[i] >= 39 && playerCards[i] <= 51) {
			cout << " S" << playerCards[i] - 38;

		} 
	}
	type = HighCard;

	straight = 0;
	club = 0, diamond = 0, heart = 0, spade = 0;
	fourOfKind = 0;
	threeOfKind = 0;
	pair = 0;

	maxNumber = 0, maxSuit = 0, maxNumberLocation = 0;
	//TO_DO: Sort the cards accroding to thier number



	//數各種號碼的牌有幾張
	int countNumber[14]; //countNumber[i] 表示號碼為i的牌有幾張
	for (int i = 0; i < 14; i++) {
		countNumber[i] = 0; //陣列清0 
	}
	for (int i = 0; i <= 4; i++) {
		countNumber[playerCards[i + 5]]++;
	}
	int i = 0;
	while (i <= 4)
	{
		//forStraight
		if (playerCards[i + 6] == playerCards[i + 5] + 1) {
			straight++;
		}
		cout << straight << endl;
		//forFlush
		if (playerCards[i] >= 0 && playerCards[i] <= 12) club++;
		else if (playerCards[i] >= 13 && playerCards[i] <= 25) diamond++;
		else if (playerCards[i] >= 26 && playerCards[i] <= 38) heart++;
		else if (playerCards[i] >= 39 && playerCards[i] <= 51)spade++;

		i++;
	} //while結束

	for (int i = 1; i <= 13; i++)
	{
		if (countNumber[i] == 4) fourOfKind = 1;
		else if (countNumber[i] == 3) threeOfKind = 1;
		else if (countNumber[i] == 2) pair++;
	}



	
	for (int i = 0; i < 14; i++) countNumber[i] = 0;
	for (int i = 5; i <= 9; i++) countNumber[playerCards[i]]++;

	if (straight == 4 && (club == 5 || diamond == 5 || heart == 5 || spade == 5)) {
		type = StraightFlush;
		maxNumber = playerCards[5];
		for (int i = 6; i <= 9; i++) {
			if (playerCards[i] > maxNumber) maxNumber = playerCards[i];
		}
	}
	else if (fourOfKind == 1) {
		type = FourOfKind;
		for (int i = 1; i < 13; i++) if (countNumber[i] == 4) maxNumber = i;
		maxSuit = 0;
	}
	else if (threeOfKind == 1 && pair == 1) {
		type = FullHouse;
		for (int i = 1; i < 13; i++) if (countNumber[i] == 3) maxNumber = i;
		maxSuit = 0;
	}
	else if (club == 5 || diamond == 5 || heart == 5 || spade == 5) {
		type = Flush;
		maxNumber = playerCards[5];
		for (int i = 6; i <= 9; i++) if (playerCards[i] > maxNumber) maxNumber = playerCards[i];
		if (club == 5) maxSuit = 1;
		else if (diamond == 5) maxSuit = 2;
		else if (heart == 5) maxSuit = 3;
		else if (spade == 5) maxSuit = 4;
	}
	else if (straight == 4) {
		type = Straight;
		maxNumber = playerCards[5];
		for (int i = 6; i <= 9; i++) if (playerCards[i] > maxNumber) maxNumber = playerCards[i];
	}
	else if (threeOfKind == 1) {
		type = ThreeOfKind;
		for (int i = 1; i <= 13; i++) if (countNumber[i] == 3) maxNumber = i;
	}
	else if (pair == 2) {
		type = TwoPairs;
	}
	else if (pair == 1) {
		type = OnePair;
		for (int i = 1; i <= 13; i++) if (countNumber[i] == 2) maxNumber = i;

		//比花色

	}
	else {
		type = HighCard;
		//TO_DO: Set the maxNumber
		maxNumber = playerCards[5];
		maxNumberLocation = 5;
		for (int i = 6; i <= 9; i++) {
			if (playerCards[i] > maxNumber) {
				maxNumber = playerCards[i];
				maxNumberLocation = i;
			}
		}

		if (playerCards[maxNumberLocation - 5] >= 0 && playerCards[maxNumberLocation - 5] <= 12)
			maxSuit = 1;
		else if (playerCards[maxNumberLocation - 5] >= 13 && playerCards[maxNumberLocation - 5] <= 25)
			maxSuit = 2;
		else if (playerCards[maxNumberLocation - 5] >= 26 && playerCards[maxNumberLocation - 5] <= 38)
			maxSuit = 3;
		else if (playerCards[maxNumberLocation - 5] >= 39 && playerCards[maxNumberLocation - 5] <= 51)
			maxSuit = 4;
	}
}
void PokerGame::printCards() {
	cout << "Player cards:" << endl;
	for (int i = 0; i < 5; i++) {
		//TO_DO: Print the player's cards.
		// For example: "C1" "S2" "H3" ...
	
		if (playerCards[i] >= 0 && playerCards[i] <= 12) {
			cout << " C" << playerCards[i]+1 ;
	
		}
		else if (playerCards[i] >= 13 && playerCards[i] <= 25) {
			cout << " D" << playerCards[i] - 12;
			
		}
		else if (playerCards[i] >= 26 && playerCards[i] <= 38) {
			cout << " H" << playerCards[i] - 25;
			
		}
		else if (playerCards[i] >= 39 && playerCards[i] <= 51) {
			cout << " S" << playerCards[i] - 38;
			
		}
	}

	cout << endl;
}

void PokerGame::sortCards()
{
	type = HighCard;

	straight = 0;
	club = 0, diamond = 0, heart = 0, spade = 0;
	fourOfKind = 0;
	threeOfKind = 0;
	pair = 0;

	maxNumber = 0, maxSuit = 0, maxNumberLocation = 0;
	//TO_DO: Sort the cards accroding to thier number
	
	

	//數各種號碼的牌有幾張
	int countNumber[14]; //countNumber[i] 表示號碼為i的牌有幾張
	for (int i = 0; i < 14; i++) {
		countNumber[i] = 0; //陣列清0 
	}
	for (int i = 0; i <= 4; i++) {
		countNumber[playerCards[i + 5]]++;
	}
	int i = 0;
	while (i<=4)
	{
		//forStraight
		if (playerCards[i + 6] == playerCards[i + 5] + 1) {
			straight++;
		}
		cout << straight << endl;
		//forFlush
		if (playerCards[i] >= 0 && playerCards[i] <= 12) club++;
		else if (playerCards[i] >= 13 && playerCards[i] <= 25) diamond++;
		else if (playerCards[i] >= 26 && playerCards[i] <= 38) heart++;
		else if (playerCards[i] >= 39 && playerCards[i] <= 51)spade++;
		
			i++;
	} //while結束

	for (int i = 1; i <= 13; i++)
	{
		if (countNumber[i] == 4) fourOfKind = 1;
		else if (countNumber[i] == 3) threeOfKind = 1;
		else if (countNumber[i] == 2) pair++;
	}
	

}

void PokerGame::evaluate() {
	sortCards();
	int countNumber[14];
	for (int i = 0; i < 14; i++) countNumber[i] = 0;
	for (int i = 5; i <= 9; i++) countNumber[playerCards[i]]++;

	if (straight==4 && (club==5 || diamond==5 || heart==5 || spade==5)) {
		type = StraightFlush;
		maxNumber = playerCards[5];
		for (int i = 6; i <= 9; i++) {
			if (playerCards[i] > maxNumber) maxNumber = playerCards[i];
		}
	}
	else if (fourOfKind==1) {
		type = FourOfKind;
		for (int i = 1; i < 13; i++) if (countNumber[i] == 4) maxNumber = i;
		maxSuit = 0;
	}
	else if (threeOfKind==1 && pair ==1) {
		type = FullHouse;
		for (int i = 1; i < 13; i++) if (countNumber[i] == 3) maxNumber = i;
		maxSuit = 0;
	}
	else if (club ==5 || diamond==5 || heart ==5 || spade ==5) {
		type = Flush;
		maxNumber = playerCards[5];
		for (int i = 6; i <= 9; i++) if (playerCards[i] > maxNumber) maxNumber = playerCards[i];
		if (club == 5) maxSuit = 1;
		else if (diamond == 5) maxSuit = 2;
		else if (heart == 5) maxSuit = 3;
		else if (spade == 5) maxSuit = 4;
	}
	else if (straight==4) {
		type = Straight;
		maxNumber = playerCards[5];
		for (int i = 6; i <= 9; i++) if (playerCards[i] > maxNumber) maxNumber = playerCards[i];
	}
	else if (threeOfKind==1) {
		type = ThreeOfKind;
		for (int i = 1; i <= 13; i++) if (countNumber[i] == 3) maxNumber = i;
	}
	else if (pair==2) {
		type = TwoPairs;
	}
	else if (pair==1) {
		type = OnePair;
		for (int i = 1; i <= 13; i++) if (countNumber[i] == 2) maxNumber = i;
		
		//比花色

	}
	else {
		type = HighCard;
		//TO_DO: Set the maxNumber
		maxNumber = playerCards[5];
		maxNumberLocation = 5;
		for (int i = 6; i <= 9; i++) {
			if (playerCards[i] > maxNumber) {
				maxNumber = playerCards[i];
				maxNumberLocation = i;
			}
		}

		if (playerCards[maxNumberLocation - 5] >= 0 && playerCards[maxNumberLocation - 5] <= 12)
			maxSuit = 1;
		else if (playerCards[maxNumberLocation - 5] >= 13 && playerCards[maxNumberLocation - 5] <= 25)
			maxSuit = 2;
		else if (playerCards[maxNumberLocation - 5] >= 26 && playerCards[maxNumberLocation - 5] <= 38)
			maxSuit = 3;
		else if (playerCards[maxNumberLocation - 5] >= 39 && playerCards[maxNumberLocation - 5] <= 51)
			maxSuit = 4;
	}
}

 
int PokerGame::getType() {
	return type;
}


int PokerGame::getMaxNumber() {
	return maxNumber;
}
int PokerGame::getmaxSuit() {
	return maxSuit;
}

void PokerGame::compare(int type_, int maxNumber_,int maxSuit_) {
	//TO_DO: Compare the type and output who is winner
	//Compare the type of card first. If types are the same, compare which is max the number of card.
	//If the max number is the same, compare the suit of card.
	if (type > type_) { cout << "Player 1 Win" << endl; }
	else if (type_ > type) { cout << "Player 2 Win" << endl; }
	else if (type == type_) 
	{
		if (maxNumber > maxNumber_) 
		{
			cout << "Player 1 Win" << endl;
		}
		else if (maxNumber_ > maxNumber) {
			cout << "Player 2 Win" << endl;
		}
		else if (maxNumber == maxNumber) {
			if (maxSuit > maxSuit_) cout << "Player 1 Win" << endl;
			else if (maxSuit_ > maxSuit) cout << "Player 2 Win" << endl;
		}

	}
}


bool PokerGame::isStraight() {
	//TO_DO: Check whether the hand of cards is Straight or not and set the maxNumber
	
	return false;

}

bool PokerGame::isFlush() {
	//TO_DO: Check whether the hand of cards is Flush or not and set the maxNumber

	 return false;
}

bool PokerGame::isFourOfKind() {
	//TO_DO: Check whether the hand of cards is FourOfaKind or not and set the maxNumber
	
	return false;

}

bool PokerGame::isFullHouse() {
//TO_DO: Check whether the hand of cards is FullHouse or not and set the maxNumber
	
	return false;
}

bool PokerGame::isThreeOfKind() {
	//TO_DO: Check whether the hand of cards is ThreeOfaKind or not and set the maxNumber
	
	return false;
}

bool PokerGame::isTwoPairs() {
	//TO_DO: Check whether the hand of cards is TwoPairs or not and set the maxNumber

	return false;

}

bool PokerGame::isOnePair() {
	//TO_DO: Check whether the hand of cards is OnePair or not and set the maxNumber
	
	return false;

}
