#include "termio.h"
#include <algorithm> 
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct ForeColor{
    string base;
    string black;
    string red;
    string yellow;
    string green;
    string blue;
    string cyan;
    string magenta;
    string white;

    ForeColor(){
        base = "&00";
        black = "&10";
        red = "&20";
        yellow = "&30";
        green = "&40";
        blue = "&50";
        cyan = "&60";
        magenta = "&70";
        white = "&80";
    }
};


struct BackColor{
    string base;
    string black;
    string red;
    string yellow;
    string green;
    string blue;
    string cyan;
    string magenta;
    string white;

    BackColor(){
        base = "&10";
        black = "&11";
        red = "&12";
        yellow = "&13";
        green = "&14";
        blue = "&15";
        cyan = "&16";
        magenta = "&17";
        white = "&18";
    }
};

class Card {
private:
    const string ranks[13] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    const string suit[4] = {"♠", "♦", "♣", "♥"};
    int suitNum; // value 0-3: num index of suit
    int rank; // 0-13: num value of rank
    int number; // 1-52: unique value determines card
    int value; // 1-14: numeric value used for comparison
    string suitChar; // "♠", "♦", "♣", "♥"
    string rankChar; // Ace, 2, 3, 4, ... Q, K
    string color;    // Spade=blue, Diamond=red, etc.  

public:
    friend ostream;

    Card(int);
    string Repr();
    bool operator<(const Card &);
    bool operator>(const Card &);
    bool operator==(const Card &);
    bool operator!=(const Card &);
    bool operator()(const Card &);
    void setForegroundColor(string color);       
    // It sets foreground color of card
    void setBackgroundColor(string color);      
    // It sets background color of card
    void setColors(string fore,string back);      
    // It sets fore and back
    void setCharacterColor(string color);        
    // It sets symbol color 
    void setNumberColor(string color);          
    // It sets number color
    void setColors(string fore, string back, string symbol, string number);
    void baseColors();

};

   
Card::Card(int num) {
    number = num;
    suitNum = number / 13;
    suitChar = suit[suitNum];
    baseColors();
    rank = number % 13;
    rankChar = ranks[rank];
}


string Card::Repr() {
    string s = "";
    s += color + "┌──────────┐&00 \n";
    if(rank == 9){
      s += color + "│ " + suitChar + " " + rankChar + "&00      " + "|&00 \n";
    }else{
       s += color + "│ " + suitChar + " " + rankChar + "&00       " + "|&00 \n";
    }
    s += color + "|          |&00 \n";
    s += color + "|          |&00 \n";  
    if(rank == 9){
    s += color + "│    " + suitChar + " " + rankChar + "&00   " + "|&00 \n";
    }else{
      s += color + "│    " + suitChar + " " + rankChar + "&00    " + "|&00 \n";
    }
    s += color + "|          |&00 \n";
    s += color + "|          |&00 \n";  
    if(rank==9){
    s += color + "│       " + suitChar + " " + rankChar + "&00" + "|&00 \n";
    }else{
    s += color + "│       " + suitChar + " " + rankChar + "&00 " + "|&00 \n";
    }
    s += color + "└──────────┘&00 \n";
    return s;
}

ostream &operator<<(ostream &os, Card obj) {
    os << obj.Repr();
    return os;
}

bool Card::operator()(const Card &rhs) {
    return (this->rank < rhs.rank);
}

bool Card::operator>(const Card &rhs) {
    return this->rank > rhs.rank;
}
    
bool Card::operator<(const Card &rhs) {
    return this->rank < rhs.rank;
}

bool Card::operator!=(const Card &rhs) {
    return this->rank != rhs.rank;
}
    
bool Card::operator==(const Card &rhs) {
    return this->rank == rhs.rank;
}


void Card::baseColors(){
    if(suitNum == 0 || suitNum == 2){
        setColors("green", "white", "green", "green");
    }
    else if(suitNum == 1 || suitNum == 3){
        setColors("red", "white", "red", "red");
    }
}

void Card::setColors(string main, string back, string symbol, string number){
    setForegroundColor(main);       
    // It sets foreground card color
    setBackgroundColor(back);
    // It sets background card color   
    setCharacterColor(symbol);        
    // It sets symbol color 
    setNumberColor(number);  
}


void Card::setNumberColor(string color){
    if(color == "base"){
        rankChar = ForeColor().base;
    }
    if(color == "black"){
        rankChar = ForeColor().black;
    }
    if(color == "red"){
        rankChar = ForeColor().red;
    }
    if(color == "yellow"){
        rankChar = ForeColor().yellow;
    }
    if(color == "green"){
        rankChar = ForeColor().green;
    }
    if(color == "blue"){
        rankChar = ForeColor().blue;
    }
    if(color == "cyan"){
        rankChar = ForeColor().cyan;
    }
    if(color == "magenta"){
        rankChar = ForeColor().magenta;
    }
    if(color == "white"){
        rankChar = ForeColor().white;
    }
}


void Card::setCharacterColor(string color){
    if(color == "base"){
        suitChar = ForeColor().base;
    }
    if(color == "black"){
        suitChar = ForeColor().black;
    }
    if(color == "red"){
        suitChar = ForeColor().red;
    }
    if(color == "yellow"){
        suitChar = ForeColor().yellow;
    }
    if(color == "green"){
        suitChar = ForeColor().green;
    }
    if(color == "blue"){
        suitChar = ForeColor().blue;
    }
    if(color == "cyan"){
        suitChar = ForeColor().cyan;
    }
    if(color == "magenta"){
        suitChar = ForeColor().magenta;
    }
    if(color == "white"){
        suitChar = ForeColor().white;
    }
}

void Card::setColors(string fore,string back){
    setBackgroundColor(back);
    setForegroundColor(fore);

}

void Card::setBackgroundColor(string color){ 
    if(color == "base"){
        color = BackColor().base;
    }
    if(color == "black"){
        color = BackColor().black;
    }
    if(color == "red"){
        color = BackColor().red;
    }
    if(color == "yellow"){
        color = BackColor().yellow;
    }
    if(color == "green"){
        color = BackColor().green;
    }
    if(color == "blue"){
        color = BackColor().blue;
    }
    if(color == "cyan"){
        color = BackColor().cyan;
    }
    if(color == "magenta"){
        color = BackColor().magenta;
    }
    if(color == "white"){
        color = BackColor().white;
    }
}

void Card::setForegroundColor(string color){
    if(color == "base"){
        color = ForeColor().base;
    }
    if(color == "black"){
        color = ForeColor().black;
    }
    if(color == "red"){
        color = ForeColor().red;
    }
    if(color == "yellow"){
        color = ForeColor().yellow;
    }
    if(color == "green"){
        color = ForeColor().green;
    }
    if(color == "blue"){
        color = ForeColor().blue;
    }
    if(color == "cyan"){
        color = ForeColor().cyan;
    }
    if(color == "magenta"){
        color = ForeColor().magenta;
    }
    if(color == "white"){
        color = ForeColor().white;
    }
 }
