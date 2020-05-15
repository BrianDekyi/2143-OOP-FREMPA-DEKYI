// Name:  Brian Frempa-Dekyi
// Email: brian.dekyi@yahoo.com
// Program: PO1
// Title: Game of War
// Course: CMPS 2143
// Semester: Spring 2020
// Description:  This is the main program to uses all the 
// files meant to create and play the game
// Files: main.cpp, PlayingCards.hpp, poker_game.hpp, 
// termio.h 

#include "poker_game.hpp"
#include <iomanip>

int main(){

    Term::IO io;
    Game y;
    Deck C(52);
    Hand player1(26);
    Hand player2(26);
    bool cont = true;
    for(int i=0;i<50;i++){
        C.Shuffle();
        break;
        io << Term::sleep(1000); 
    }

   C.Split(player1, player2);
   player1.Shuffle();
   // function for player1 to shuffle
   
 
   player2.Shuffle();
   // function for player2 to shuffle

while(cont){
  io << "Cards: " << player1.Size() << "     Cards: " << player2.Size() <<"\n";
   CardContainer i(player1.Play(), player2.Play());
    
   i.Print(2, false);
    io<<"Player 1        Player 2\n";

    y.Distribute(y.Compare(i.Get(0), i.Get(1)), player1, player2, i);
     
    if(player1.Size() == 0 || player2.Size() == 0){
     cont = y.End(player1.Size(), player2.Size());
    }
 io << Term::sleep(1000); 
}
    return 0;
}
