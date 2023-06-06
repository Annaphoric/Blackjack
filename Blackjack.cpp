#include <iostream>
#include <cstdlib>
#include <ctime>
#include <map>
#include <string>
#include <cmath>
#define combine(name, number) name##number

using namespace std;

int randInt(int a);
int randInt(int a, int b);
short chance(short numerator, short denominator);
void Fractionate(short sum);
void Show_Hand(string hand, string suits, short player);
short Sum_Cards(string hand);

char valueName[14] = "A234567890JQK";
map<char,  short> value {{'A', 1}, {'2', 2}, {'3', 3}, {'4', 4}, {'5', 5}, {'6', 6}, {'7', 7}, {'8', 8}, {'9', 9}, {'0', 10}, {'J', 10}, {'Q', 10}, {'K', 10}};

char suitName[5] = "SHCD";
map<char, string> suit {{'S', "Spades"}, {'H', "Hearts"}, {'C', "Clovers"}, {'D', "Diamonds"}};

//short a = 1, b = 1;
//short *dividend = &a, *divisor = &b;
static short dividend = 1, divisor = 1;

//__Main__

int main() {
	srand(time(0));
	short sum1, sum2;
	string hand1, suits1, hand2, suits2;
	short turn = 1, finish2 = 0, lost1 = 0, lost2 = 0, gameCount = 0, winCount1 = 0, winCount2 = 0, reset = 0;
	char command;
	
	cout << "Welcome to Blackjack! You exchange a \"Good luck\" with Player 2.\n\nTurn: " << turn << "\n\nYou draw 2 cards.\nPlayer 2 draws 2 cards." << endl;
	
	for(short n = 0; n < 2; n++) {
		hand1 += valueName[randInt(13)];
		suits1 += suitName[randInt(4)];
		
		hand2 += valueName[randInt(13)];
		suits2 += suitName[randInt(4)];
	}
	
	Show_Hand(hand1, suits1, 1);
	
	cout << "\n\nWhat would you like to do?\n-----'d' for DRAW CARD-----\n-----'b' for BID HIGHER-----\n-----'f' for FINISH-----\n-----'q' for QUIT-----" << endl;
	cin >> command;
	
	while(command != 'q') {		
		if(command == 'd') {
			hand1 += valueName[randInt(13)];
		    suits1 += suitName[randInt(4)];
		    Show_Hand(hand1, suits1, 1);		 
		    
			cout << "\n\nTurn: " << ++turn << "\n\nWhat would you like to do?\n-----'d' for DRAW CARD-----\n-----'b' for BID HIGHER-----\n-----'f' for FINISH-----\n-----'q' for QUIT-----" << endl;
			cin >> command;
		}
		else if(command == 'f') {
			sum1 = Sum_Cards(hand1);
			if(sum1 < 21) cout << "\n\nThe sum of your cards is " << sum1 << "\n" << endl;
			else if(sum1 > 21) cout << "\n\nThe sum of your cards is " << sum1 << ".\n\nYour hand is over 21! Better luck next time!\n" << endl;
			else cout << "\n\nThe sum of your cards is " << sum1 << ".\n\nBlackjack!\n" << endl;
			
			while(finish2 == 0) {
				sum2 = Sum_Cards(hand2);
				Fractionate(sum2);
				
				if(sum2 < 21 && chance(dividend, divisor)) {
		    		hand2 += valueName[randInt(13)];
					suits2 += suitName[randInt(4)];
		   	 }
		    	else finish2 = 1;
			}
			sum2 = Sum_Cards(hand2);
			
			Show_Hand(hand2, suits2, 2);
			
			if(sum2 < 21) cout << "The sum of Player 2's cards is " << sum2 << "\n" << endl;
			else if(sum2 > 21) cout << "The sum of Player 2's cards is " << sum2 << "\n\nPlayer 2's hand is over 21!\n" << endl;
			else cout << "The sum of Player 2's cards is " << sum2 << ".\n\nBlackjack!\n" << endl;
			
			if(sum1 > 21) lost1 = 1;
			if(sum2 > 21) lost2 = 1;
			
			 if(lost1 && lost2) cout << "No one won!" << endl;
			 else if((sum1 > sum2 && lost1 == 0) || (lost1 == 0 && lost2)) {
			 	cout << "Congratulations! You win!!" << endl;
			 	winCount1++;
			 }
			 else if(sum1 == sum2) cout << "Tied!" << endl;
			 else {
			 	cout << "Player 2 has won." << endl;
			 	winCount2++;
			 }
			gameCount++;
			
			cout << "\n\nGames Played: " << gameCount << "\nYour Win Count: " << winCount1 << "\nPlayer 2 Win Count: "<< winCount2 << "\n\n\nPlay again?\n-----'y' for YES-----\n-----'n' for NO-----" << endl;
			cin >> command;
			
			while(reset == 0) {
				if(command == 'y') {
				hand1 = ""; suits1 = ""; hand2 = ""; suits2 = ""; finish2 = 0; lost1 = 0; lost2 = 0; turn = 1, reset = 1;
				
				cout << "\nYou draw 2 cards.\nPlayer 2 draws 2 cards.\n\n";
	
				for(short n = 0; n < 2; n++) {
					hand1 += valueName[randInt(13)];
					suits1 += suitName[randInt(4)];
		
					hand2 += valueName[randInt(13)];
					suits2 += suitName[randInt(4)];
				}
	
				Show_Hand(hand1, suits1, 1);
	
				cout << "\n\nTurn: " << turn << "\n\nWhat would you like to do?\n-----'d' for DRAW CARD-----\n-----'b' for BID HIGHER-----\n-----'f' for FINISH-----\n-----'q' for QUIT-----" << endl;
				cin >> command;
				}
				else if (command == 'n') {
					command = 'q'; break;
				}
				else {
					cout << "Invalid entry. Enter an appropriate character." << endl;
					cin >> command;
				}
			}
			reset = 0;
		}
		else {
			cout << "Invalid entry. Enter an appropriate character." << endl;
			cin >> command;
		}
	}
	
	cout << "\n\n-----Thanks for playing!-----\n\n";
	
	exit(0);
}

//__Functions__

int randInt(int a) {
	int random = rand() % a;
	return(random);
}

int randInt(int a, int b) {
	int random = rand() % b;
	while(random < a) {
		random = rand() % b;
	}
	return(random);
}

short chance(short numerator, short denominator) {	
	if(denominator == 1) return(true);
	
	int random = rand() % denominator;
	
	if(numerator == 1) {
		if(random == 0) return(true);
		else return(false);
	}
	else if(numerator == denominator - 1) {
		if(random != 0) return(true);
		else return(false);
	}
	else if(numerator == 2) {
		if(random == 0 || random == 1) return(true);
		else return(false);
	}
	else if(numerator == 3) {
		if(random == 0 || random == 1 || random == 2) return(true);
		else return(false);
	}
	else return(true);
}

void Fractionate(short sum) {
	dividend = 1; divisor = 1;
	
	switch(sum) {
		case 12:
    		dividend = 3; divisor = 4; break;
    	case 13:
    		dividend = 2; divisor = 3; break;
    	case 14:
    		divisor = 2; break;
    	case 15:
    		divisor = 3; break;
    	case 16:
    		divisor = 4; break;
    	case 17:
    		divisor = 5; break;
    	case 18:
    		divisor = 6; break;
    	case 19:
    		divisor = 7; break;
    	case 20:
    		divisor = 8; break;
	}
}

void Show_Hand(string hand, string suits, short player) {
	if(player == 1) cout << "Cards in your hand:\n" << endl;
	else cout << "Cards in Player " << player << "'s hand:\n" << endl;
	
	for(short n = 0; n < hand.length(); n++) {
		if(hand[n] == '0') cout << "10 of " << suit[suits[n]] << endl;
		else cout <<  hand[n] << " of " << suit[suits[n]] << endl;
	}
}

short Sum_Cards(string hand) {
	short sum = 0;
	
	for(short n = 0; n < hand.length(); n++) {
		sum += value[hand[n]];
	}
	if(sum > 21) return(sum);
    if(hand.find('A') != string::npos && sum < 21) sum += 10;
    if(hand.find('A') != string::npos && sum > 21) sum -= 10;
	return(sum);
}
