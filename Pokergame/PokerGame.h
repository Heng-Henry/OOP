#pragma once

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <string>
#include<random>   //

using namespace std;

enum cardType
{
	HighCard, //0
	OnePair, //1
	TwoPairs, //2
	ThreeOfKind, //3
	Straight, //4
	Flush, //5
	FullHouse, //6
	FourOfKind,//7
	StraightFlush, //8
};

static string table[] = {
	"HighCard",
	"OnePair",
	"TwoPairs",
	"ThreeOfKind",
	"Straight",
	"Flush",
	"FullHouse",
	"FourOfKind",
	"StraightFlush"
};

class PokerGame 
{
private:
	vector<int> playerCards = { 0,0,0,0,0,0,0,0,0,0,0,0 };
	
	cardType type;

	// 記錄牌型
	int straight;
	int club, diamond , heart , spade ;
	bool fourOfKind ;
	bool threeOfKind ;
	int pair ;

	int maxNumber,maxSuit,maxNumberLocation; 
	//maxSuit : Club =1 , Diamond = 2, Heart = 3, Spade = 4;
	//maxNumber stores the maximum number of the type.
	//It's easy to compare which number is large when both of card types are the same. 
public:
	PokerGame();
	void distribute(bool usedCards[52]);
	void set(vector<int> cards);
	void printCards();
	void printCardsForCheat(vector<int>playerCards); //將s和c的情況分開
	void sortCards();
	void evaluate();
	int getType();
	int getMaxNumber();
	int getmaxSuit(); //自己加的
	void compare(int type_, int maxNumber_,int maxSuit_); //maxSuit是自己加的

	bool isStraight();
	bool isFlush();
	bool isFourOfKind();
	bool isFullHouse();
	bool isThreeOfKind();
	bool isTwoPairs();
	bool isOnePair();
	
};

/*
int main() {

	
	return 0;
}
*/