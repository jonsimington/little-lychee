//Name: Joey Klix
//Class: 5400 Introduction to AI
//Description: Chess AI

//include files
#include "MoveGenerator.h"

MoveGenerator::MoveGenerator(BoardState GameBoard)
{
  //set default state
  CurrentBoard = GameBoard;
  return;
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
  if (PieceType == "Pawn" && PawnMoves(TempPiece, Direction, HasMoved))
    MovablePieces.push(TempPiece);
  else if (PieceType == "Night")
  {

  }
  //MovablePieces.push(TempPiece);
  return;
}//end GenerateAllMoves

bool MoveGenerator::PawnMoves(ChessPiece& Pawn, const int Direction, const bool HasMoved)
{
  //single move if possible
  if (CurrentBoard.IsLocationEmpty(Location(Pawn.PieceLocation.Row + Direction, Pawn.PieceLocation.Column)))
  {
    Pawn.PossibleMoves.push_back(Location(Pawn.PieceLocation.Row + Direction, Pawn.PieceLocation.Column));

    //double move if possible
    if (!HasMoved && CurrentBoard.IsLocationEmpty(Location(Pawn.PieceLocation.Row + (2*Direction), Pawn.PieceLocation.Column)))
    {
      Pawn.PossibleMoves.push_back(Location(Pawn.PieceLocation.Row + (2*Direction), Pawn.PieceLocation.Column));
      //cout << "2 Row:" << Pawn.PieceLocation.Row - '0' << " Column:" << Pawn.PieceLocation.Column << endl;
    }
  }
  //check for leftward diagonal moves
  if (Pawn.PieceLocation.Column > 'a')
  {
    if (CurrentBoard.IsPieceEnemy(Pawn.PieceLocation, Location(Pawn.PieceLocation.Row + Direction, Pawn.PieceLocation.Column - 1)))
      Pawn.PossibleMoves.push_back(Location(Pawn.PieceLocation.Row + Direction, Pawn.PieceLocation.Column - 1));
    else if (CurrentBoard.EnPassantLocation().Row == Pawn.PieceLocation.Row + Direction && CurrentBoard.EnPassantLocation().Column == Pawn.PieceLocation.Column - 1)
      Pawn.PossibleMoves.push_back(Location(Pawn.PieceLocation.Row + Direction, Pawn.PieceLocation.Column - 1));
  }//end else if
  //check for rightward diagonal moves
  if (Pawn.PieceLocation.Column < 'h')
  {
    if (CurrentBoard.IsPieceEnemy(Pawn.PieceLocation, Location(Pawn.PieceLocation.Row + Direction, Pawn.PieceLocation.Column + 1)))
      Pawn.PossibleMoves.push_back(Location(Pawn.PieceLocation.Row + Direction, Pawn.PieceLocation.Column + 1));
    else if (CurrentBoard.EnPassantLocation().Row == Pawn.PieceLocation.Row + Direction && CurrentBoard.EnPassantLocation().Column == Pawn.PieceLocation.Column + 1)
      Pawn.PossibleMoves.push_back(Location(Pawn.PieceLocation.Row + Direction, Pawn.PieceLocation.Column + 1));
  }//end else if
  
  //CurrentBoard.MovePiece(Location(Pawn.PieceLocation.Column, Pawn.PieceLocation.Row), Location(Pawn.PieceLocation.Column, Pawn.PieceLocation.Row + Direction));
  //capture if possible
  //if (Pawn.Column > 'a' && CurrentBoard.BoardMap[Pawn.Column][Pawn.Row + Direction] )

  //cout << "Pawn moves:" << Pawn.PossibleMoves.size() << endl;
  if (Pawn.PossibleMoves.size() > 0)
    return true;
  else 
    return false;
}//end PawnMoves

ChessPiece MoveGenerator::RandomMove()
{
  //vars
  int RandLocation = rand() % MovablePieces.size();

  //remove until rand
  for (int i = 0; i < RandLocation; i++)
    MovablePieces.pop();

  return MovablePieces.front();    
}//end RandomMove