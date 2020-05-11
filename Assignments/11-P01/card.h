/*
  File: Card.h
  Author:  Brian Frempa-Dekyi
  Course:  OOP
  Date:    03/26/2020
  Description:  This file provides the definitions of the data types
                Suit, Value, and Card.
*/

#ifndef ___CARD_H
#define ___CARD_H

#include <string>
using std::string;

enum Suit {clubs, diamonds, hearts, spades};
enum Value {deuce, trey, four, five, six, seven, eight, nine, ten, jack, queen, king, ace};

class Card {
public:
	Card (Value faceValue=deuce, Suit suit = clubs):
		suit (suit), faceValue(faceValue) {}
	Suit getSuit() { return suit; }
	Value getValue() { return faceValue; }
	static string suitName (Suit s);
	static string valueName (Value v);
	string name() { return valueName (faceValue) + " of " + suitName(suit);}
private:
		Suit suit;
		Value faceValue;
};


#endif
