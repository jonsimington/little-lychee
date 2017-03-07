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
    /// <summary>
    /// Constructor for movegenerator, takes in already defined Gameboard
    /// <summary>
    MoveGenerator(BoardState GameBoard);
    /// <summary>
    /// Generate all moves for the given piece and save them in movable pieces
    /// <summary>
    void GenerateMoves(Location NewPieceLocation, const int PlaceInList, const int Direction, const bool HasMoved, const string PieceType);
    /// <summary>
    /// Generatate all pawn moves
    /// <summary>
    bool PawnMoves(ChessPiece& Pawn, const int Direction, const bool HasMoved);
    /// <summary>
    /// testing possible king moves
    /// <summary>
    bool KingMoves(ChessPiece& King, const bool TestingCheck);
    /// <summary>
    /// testing possible rook moves
    /// <summary>
    bool RookMoves(ChessPiece& Rook, const bool TestingCheck);
    /// <summary>
    /// testing possible bishop moves
    /// <summary>
    bool BishopMoves(ChessPiece& Bishop, const bool TestingCheck);
    /// <summary>
    /// testing possible queen moves
    /// <summary>
    bool QueenMoves(ChessPiece& Queen, const bool TestingCheck);
    /// <summary>
    /// testing possible knight moves
    /// <summary>
    bool KnightMoves(ChessPiece& Knight, const bool TestingCheck);
    /// <summary>
    /// check moves in straight lines around piece works for k,q,n,r,b
    /// <summary>
    bool CheckMovesInDirection(ChessPiece& StartingPiece, const int RowChange, const int ColumnChange, const bool KingorKnight, const char LookingFor);
    /// <summary>
    /// remove any generated moves that end my king in check
    /// <summary>
    bool RemoveInCheckMoves(ChessPiece& MovedPiece, const int Direction);
    /// <summary>
    /// pick random piece and then random move for that piece
    /// <summary>
    Location RandomMove(int& ListId);
  private:
    BoardState CurrentBoard;
    queue<ChessPiece> MovablePieces;
};//end class MoveGenerator

#endif