//Name: Joey Klix
//Class: 5400 Introduction to AI
//Description: Chess AI

#ifndef MOVEGENERATOR_H
#define MOVEGENERATOR_H

using namespace std;
#include "BoardState.h"

class MoveGenerator
{
  public:
    MoveGenerator(BoardState GameBoard);
    void GenerateMoves(Location NewPieceLocation, const int PlaceInList, const int Direction, const bool HasMoved, const string PieceType);
    void PawnMoves(ChessPiece& Pawn, const int Direction, const bool HasMoved);
    ChessPiece RandomMove();
  private:
    BoardState CurrentBoard;
    queue<ChessPiece> MovablePieces;
};//end class MoveGenerator

#endif