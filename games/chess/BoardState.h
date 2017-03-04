//Name: Joey Klix
//Class: 5400 Introduction to AI
//Description: Chess AI

#ifndef BOARDSTATE_H
#define BOARDSTATE_H

using namespace std;
#include "header.h"
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <sstream>
#include <iterator>

class BoardState
{
  public:
    BoardState();
    void ForsythEdwardsNotationBoardInput(string InputString);
    void PrintMap();
    vector<string> SplitByChar(const string StringtoSplit, char SeparatingChar);
    bool IsLocationEmpty(Location TargetLocation);
    void MovePiece(Location StartLocation, Location DestinationLocation);
  private:
    vector<vector<ChessPiece> > BoardMap;
    bool WhitesTurn;
    bool WhiteKingSideCastle;
    bool WhileQueenSideCastle;
    bool BlackKingSideCastle;
    bool BlackQueenSideCastle;
    Location EnPassantTarget;
    int HalfMoveClock;
    int FullMoveNumber;
    queue<string> MoveHistory;      
};//end class ChessLogic

#endif