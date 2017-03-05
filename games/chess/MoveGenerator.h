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
    bool PawnMoves(ChessPiece& Pawn, const int Direction, const bool HasMoved);
    bool KingMoves(ChessPiece& King);
    bool RookMoves(ChessPiece& Rook);
    bool BishopMoves(ChessPiece& Bishop);
    bool QueenMoves(ChessPiece& Queen);
    void CheckMovesInDirection(ChessPiece& StartingPiece, const int RowChange, const int ColumnChange);
    ChessPiece RandomMove();
  private:
    BoardState CurrentBoard;
    queue<ChessPiece> MovablePieces;
};//end class MoveGenerator

#endif