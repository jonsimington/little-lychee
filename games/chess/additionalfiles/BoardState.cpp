//Name: Joey Klix
//Class: 5400 Introduction to AI
//Description: Chess AI

using namespace std;
#ifndef BOARDSTATE_H
#define BOARDSTATE_H

#include <iostream>
#include <vector>

class BoardState
{
  public:
    BoardState();
  private:
    bool bCastleValid;
    string sLastMove;
    vector<vector<char> > Board;  
};//end class ChessLogic

#endif