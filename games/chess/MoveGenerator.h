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
    MoveGenerator();
    /// <summary>
    /// create a board state with the given parameters
    /// <summary>
    MoveGenerator(BoardState GameBoard, vector<MyChessPiece> OldMoveHistory, bool pMaximizing, bool SwitchDir);
    /// <summary>
    /// Generate all moves for the given piece and save them in movable pieces
    /// <summary>
    void GenerateMoves(Location NewPieceLocation, const int PlaceInList, const string PieceType, const int pDepthToGo);
    /// <summary>
    /// Generatate all pawn moves
    /// <summary>
    void PawnMoves(MyChessPiece& Pawn);
    /// <summary>
    /// testing possible king moves
    /// <summary>
    void KingMoves(MyChessPiece& King);
    /// <summary>
    /// check if king is in check from king
    /// <summary>
    bool KingMovesCheck(MyChessPiece King);
    /// <summary>
    /// testing possible rook moves
    /// <summary>
    void RookMoves(MyChessPiece& Rook);
    /// <summary>
    /// check if rook is in check from rook
    /// <summary>
    bool RookMovesCheck(MyChessPiece Rook);
    /// <summary>
    /// testing possible bishop moves
    /// <summary>
    void BishopMoves(MyChessPiece& Bishop);
    /// <summary>
    /// check if bishop is in check from bishop
    /// <summary>
    bool BishopMovesCheck(MyChessPiece Bishop);
    /// <summary>
    /// testing possible queen moves
    /// <summary>
    void QueenMoves(MyChessPiece& Queen);
    /// <summary>
    /// check if queen is in check from queen
    /// <summary>
    bool QueenMovesCheck(MyChessPiece Queen);
    /// <summary>
    /// testing possible knight moves
    /// <summary>
    void KnightMoves(MyChessPiece& Knight);
    /// <summary>
    /// check if knight is in check from knight
    /// <summary>
    bool KnightMovesCheck(MyChessPiece Knight);
    /// <summary>
    /// check moves in straight lines around piece works for k,q,n,r,b
    /// <summary>
    bool CheckMovesInDirection(MyChessPiece& StartingPiece, const int RowChange, const int ColumnChange, const bool KingorKnight);
    /// <summary>
    /// check if any piece is threatening king
    /// <summary>
    bool IsPieceThreateningKing(const MyChessPiece King, const int RowChange, const int ColumnChange, const bool KingorKnight, const char LookingFor);
    /// <summary>
    /// check if move leaves king in check
    /// <summary>
    bool DoesMoveEndInCheck(MyChessPiece MovedPiece, Location EndLocation);
    /// <summary>
    /// return the max rated move on top of priority queue
    /// <summary>
    Location MiniMax(int& ListId);
    /// <summary>
    /// take move and generate new board state to find next moves
    /// <summary>
    int FindNextDepthHeuristic(Location DestinationLocation, char MovedPieceType);
    /// <summary>
    /// generate all moves possible for the next depth
    /// <summary>
    void NextDepthMoves(const int DepthToGo);
    /// <summary>
    /// add opponents move the the history queue
    /// <summary>
    void AddOpponentMove(Location NewPieceLocation, const string PieceType);
    /// <summary>
    /// return the heuristic calculated for the current board state
    /// <summary>
    int ReturnHeuristicValue() {return HeuristicValue;}

    vector<MyChessPiece> MoveHistory;
    priority_queue<MovePiece> MovePiecesQueue;
  private:
    BoardState CurrentBoard;
    int DepthToGo;
    int HeuristicValue;
    bool PossibleSimplifiedDraw;
    bool Maximizing;
    //queue<MyChessPiece> MovablePieces;
    //priority_queue<MyChessPiece> MovablePieces;
    
};//end class MoveGenerator

#endif