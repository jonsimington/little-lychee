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
#include <algorithm>

class BoardState
{
  public:
    /// <summary>
    /// default initilizer for boardstate
    /// <summary>
    BoardState();
    /// <summary>
    /// input boardstate from FEN string
    /// <summary>
    void ForsythEdwardsNotationBoardInput(string InputString);
    /// <summary>
    /// print out the map for debugging
    /// <summary>
    void PrintMap();
    /// <summary>
    /// print information from piece at given location
    /// <summary>
    void PrintLocation(Location LocationtoPrint);
    /// <summary>
    /// split the given string by the given char
    /// <summary>
    vector<string> SplitByChar(const string StringtoSplit, char SeparatingChar);
    /// <summary>
    /// test if location is empty of any pieces
    /// <summary>
    bool IsLocationEmpty(Location TargetLocation);
    /// <summary>
    /// test if location has enemy piece
    /// <summary>
    bool IsPieceEnemy(Location MyPiece, Location OtherPiece);
    /// <summary>
    /// move piece from start to destination reseting start to empty space
    /// <summary>
    void MovePiece(Location StartLocation, Location DestinationLocation);
    /// <summary>
    /// is the piece at location the same type as char given, can be from either team
    /// <summary>
    bool IsPieceType(const Location LookHere, const char CompareChar);
    /// <summary>
    /// is the piece at the given location match the direction
    /// <summary>
    bool IsPieceMine(const Location MyPiece);
    /// <summary>
    /// return location of EnPassant
    /// <summary>
    Location EnPassantLocation();
    /// <summary>
    /// reutnr locaiton of King
    /// <summary>
    Location returnKingLocation();
    bool WhiteKingSideCastle;
    bool WhiteQueenSideCastle;
    bool BlackKingSideCastle;
    bool BlackQueenSideCastle;
    int Direction;
    vector<vector<MyChessPiece> > BoardMap;
  private:
    
    //vector<MyChessPiece*> MyPieces;
    //vector<MyChessPiece*> EnemyPieces;
    bool WhitesTurn;    
    Location EnPassantTarget;
    int HalfMoveClock;
    int FullMoveNumber;
    Location KingLocation;    
};//end class ChessLogic

#endif