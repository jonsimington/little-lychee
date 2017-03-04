//Name: Joey Klix
//Class: 5400 Introduction to AI
//Description: Chess AI

#ifndef HEADER_H
#define HEADER_H

#include <list>
#include <vector>

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
  Location(char NewColumn, char NewRow)
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
  vector<Location> PossibleMoves;

  //Default constructor
  ChessPiece()
  {
    bool EmptySpace = true;
    bool WhitePiece = false;
    char PieceType = '*';
    PieceLocation = Location();
    PossibleMoves.clear();
  }//end default constructor
};//end chesspiece

#endif