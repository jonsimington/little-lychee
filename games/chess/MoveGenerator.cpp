//Name: Joey Klix
//Class: 5400 Introduction to AI
//Description: Chess AI

//include files
#include "MoveGenerator.h"

MoveGenerator::MoveGenerator(BoardState GameBoard)
{
  CurrentBoard = GameBoard;
}//end constructor

void MoveGenerator::GenerateMoves(Location NewPieceLocation, const int PlaceInList, const int Direction, const bool HasMoved, const string PieceType)
{
  //vars
  ChessPiece TempPiece;
  
  //set values to temp
  TempPiece.ListId = PlaceInList;
  TempPiece.PieceLocation.Column = NewPieceLocation.Column;
  TempPiece.PieceLocation.Row = NewPieceLocation.Row;
  
  //check for pawn moves
  if (PieceType == "Pawn")
  {
    PawnMoves(TempPiece, Direction, HasMoved);
    MovablePieces.push(TempPiece);
  }//end if pawn
  //MovablePieces.push(TempPiece);
  return;
}//end GenerateAllMoves

void MoveGenerator::PawnMoves(ChessPiece& Pawn, const int Direction, const bool HasMoved)
{
  //single move if possible
  if (CurrentBoard.IsLocationEmpty(Location(Pawn.PieceLocation.Column, Pawn.PieceLocation.Row + Direction)))
  {
    Pawn.PossibleMoves.push_back(Location(Pawn.PieceLocation.Column, Pawn.PieceLocation.Row + Direction));
    cout << "move1" << endl;

    //double move if possible
    if (!HasMoved && CurrentBoard.IsLocationEmpty(Location(Pawn.PieceLocation.Column, Pawn.PieceLocation.Row + (2*Direction))));
    {
      Pawn.PossibleMoves.push_back(Location(Pawn.PieceLocation.Column, Pawn.PieceLocation.Row + (2*Direction)));
      cout << "move2" << endl;
    }

  }
  //capture if possible
  //if (Pawn.Column > 'a' && CurrentBoard.BoardMap[Pawn.Column][Pawn.Row + Direction] )
  cout << "Pawn moves:" << Pawn.PossibleMoves.size() << endl;
  return;
}//end PawnMoves

ChessPiece MoveGenerator::RandomMove()
{
  //vars
  int RandLocation = rand() % MovablePieces.size();
  cout << "MovablePieces:" << MovablePieces.size() << endl;

  //remove until rand
  for (int i = 0; i < RandLocation; i++)
    MovablePieces.pop();

  cout << "Moves:" << MovablePieces.front().PossibleMoves.size() << endl;

  return MovablePieces.front();    
}//end RandomMove