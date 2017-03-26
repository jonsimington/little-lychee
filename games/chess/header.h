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

struct MyChessPiece
{
  bool EmptySpace;
  char PieceType;
  int ListId;
  //int HeurValue;
  Location PieceLocation;
  //queue<Location> PossibleMoves;

  //Default constructor
  MyChessPiece()
  {
    EmptySpace = true;
    PieceType = '*';
    ListId = -1;
    //HeurValue = 0;
    PieceLocation = Location();
  }//end default constructor
};//end Mychesspiece

struct MovePiece
{
  MyChessPiece CurrentPiece;
  Location EndLoc;
  int HeurValue;

  //Default constructor
  MovePiece()
  {
    CurrentPiece = MyChessPiece();
    EndLoc = Location();
    HeurValue = 0;
  }//end defualt constructor

  //constructor
  MovePiece(MyChessPiece PieceBeingMoved, Location End, int Value)
  {
    CurrentPiece = PieceBeingMoved;
    EndLoc = End;
    HeurValue = Value;
  }//end
};

#endif