//Name: Joey Klix
//Class: 5400 Introduction to AI
//Description: Chess AI

#ifndef HEADER_H
#define HEADER_H

#include <vector>
#include <queue>

struct Location
{
  char Column;
  char Row;

  //Default constructor
  Location()
  {
    Column = '-';
    Row = '-';
  }//end default constructor

  //constructor
  Location(char NewRow, char NewColumn)
  {
    Column = NewColumn;
    Row = NewRow;
  }//end constructor
};//end location

struct ChessPiece
{
  bool EmptySpace;
  bool WhitePiece;
  char PieceType;
  int ListId;
  Location PieceLocation;    
  queue<Location> PossibleMoves;

  //Default constructor
  ChessPiece()
  {
    EmptySpace = true;
    WhitePiece = false;
    PieceType = '*';
    ListId = -1;
    PieceLocation = Location();
    //PossibleMoves.clear();
  }//end default constructor
};//end chesspiece

#endif