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
  
  //check for each peices movess
  if (PieceType == "Pawn" && PawnMoves(TempPiece, Direction, HasMoved))
    MovablePieces.push(TempPiece);
  else if (PieceType == "King" && KingMoves(TempPiece))
    MovablePieces.push(TempPiece);
  else if (PieceType == "Rook" && RookMoves(TempPiece))
    MovablePieces.push(TempPiece);
  else if (PieceType == "Bishop" && BishopMoves(TempPiece))
    MovablePieces.push(TempPiece);
  else if (PieceType == "Queen" && QueenMoves(TempPiece))
    MovablePieces.push(TempPiece);
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

bool MoveGenerator::KingMoves(ChessPiece& King)
{
  //vars
  Location TempLocation = King.PieceLocation;
  bool NotonTopRow = TempLocation.Row < '8';
  bool NotonBottomRow = TempLocation.Row > '1';
  bool NotonLeftColumn = TempLocation.Column > 'a';
  bool NotonRightColumn = TempLocation.Column < 'h';

  //Above
  TempLocation.Row = TempLocation.Row + 1;
  if (NotonTopRow && (CurrentBoard.IsLocationEmpty(TempLocation) || CurrentBoard.IsPieceEnemy(King.PieceLocation, TempLocation)))
    King.PossibleMoves.push_back(TempLocation);
  //Up right
  TempLocation.Column = TempLocation.Column + 1;
  if (NotonTopRow && NotonRightColumn && (CurrentBoard.IsLocationEmpty(TempLocation) || CurrentBoard.IsPieceEnemy(King.PieceLocation, TempLocation)))
    King.PossibleMoves.push_back(TempLocation);
  //right
  TempLocation.Row = TempLocation.Row - 1;
  if (NotonRightColumn && (CurrentBoard.IsLocationEmpty(TempLocation) || CurrentBoard.IsPieceEnemy(King.PieceLocation, TempLocation)))
    King.PossibleMoves.push_back(TempLocation);
  //right bottom
  TempLocation.Row = TempLocation.Row - 1;
  if (NotonRightColumn && NotonBottomRow && (CurrentBoard.IsLocationEmpty(TempLocation) || CurrentBoard.IsPieceEnemy(King.PieceLocation, TempLocation)))
    King.PossibleMoves.push_back(TempLocation);
  //bottom
  TempLocation.Column = TempLocation.Column - 1;
  if (NotonBottomRow && (CurrentBoard.IsLocationEmpty(TempLocation) || CurrentBoard.IsPieceEnemy(King.PieceLocation, TempLocation)))
    King.PossibleMoves.push_back(TempLocation);
  //bottom left
  TempLocation.Column = TempLocation.Column - 1;
  if (NotonBottomRow && NotonLeftColumn && (CurrentBoard.IsLocationEmpty(TempLocation) || CurrentBoard.IsPieceEnemy(King.PieceLocation, TempLocation)))
    King.PossibleMoves.push_back(TempLocation);
  //left
  TempLocation.Row = TempLocation.Row + 1;
  if (NotonLeftColumn && (CurrentBoard.IsLocationEmpty(TempLocation) || CurrentBoard.IsPieceEnemy(King.PieceLocation, TempLocation)))
    King.PossibleMoves.push_back(TempLocation);
  //top left
  TempLocation.Row = TempLocation.Row + 1;
  if (NotonLeftColumn && NotonTopRow && (CurrentBoard.IsLocationEmpty(TempLocation) || CurrentBoard.IsPieceEnemy(King.PieceLocation, TempLocation)))
    King.PossibleMoves.push_back(TempLocation);

  //make sure their is at least one valid move
  if (King.PossibleMoves.size() > 0)
    return true;
  else
    return false;
}//end KingMoves

bool MoveGenerator::RookMoves(ChessPiece& Rook)
{
  //check straight lines for moves
  CheckMovesInDirection(Rook, 1, 0);//down
  CheckMovesInDirection(Rook, -1, 0);//up
  CheckMovesInDirection(Rook, 0, -1);//left
  CheckMovesInDirection(Rook, 0, 1);//right

  //make sure their is at least one valid move
  if (Rook.PossibleMoves.size() > 0)
    return true;
  else
    return false;
}//end RookMoves

bool MoveGenerator::BishopMoves(ChessPiece& Bishop)
{
  //check diagonal lines for moves
  CheckMovesInDirection(Bishop, 1, 1);//down right
  CheckMovesInDirection(Bishop, -1, 1);//up right
  CheckMovesInDirection(Bishop, 1, -1);//down left
  CheckMovesInDirection(Bishop, -1, -1);//up left

  //make sure their is at least one valid move
  if (Bishop.PossibleMoves.size() > 0)
    return true;
  else
    return false;
}//end BishopMoves

bool MoveGenerator::QueenMoves(ChessPiece& Queen)
{
  //check strainght and diagonal lines for moves
  CheckMovesInDirection(Queen, 1, 0);//down
  CheckMovesInDirection(Queen, -1, 0);//up
  CheckMovesInDirection(Queen, 0, -1);//left
  CheckMovesInDirection(Queen, 0, 1);//right
  CheckMovesInDirection(Queen, 1, 1);//down right
  CheckMovesInDirection(Queen, -1, 1);//up right
  CheckMovesInDirection(Queen, 1, -1);//down left
  CheckMovesInDirection(Queen, -1, -1);//up left

  //make sure their is at least one valid move
  if (Queen.PossibleMoves.size() > 0)
    return true;
  else
    return false;
}//end QueenMoves

void MoveGenerator::CheckMovesInDirection(ChessPiece& StartingPiece, const int RowChange, const int ColumnChange)
{
  //vars
  Location TempLocation = StartingPiece.PieceLocation;

  //set new location
  TempLocation.Row = TempLocation.Row + RowChange;
  TempLocation.Column = TempLocation.Column + ColumnChange;

  //make sure location is still on board
  while (TempLocation.Row >= '1' && TempLocation.Row <= '8' && TempLocation.Column >= 'a' && TempLocation.Column <= 'h')
  {
    //if space is empty
    if (CurrentBoard.IsLocationEmpty(TempLocation))
      StartingPiece.PossibleMoves.push_back(TempLocation);
    //if space has enemy piece
    else if (CurrentBoard.IsPieceEnemy(StartingPiece.PieceLocation, TempLocation))
    {
      StartingPiece.PossibleMoves.push_back(TempLocation);
      return;
    }//end else if
    //if space has my piece
    else 
      return;

    //set new location
    TempLocation.Row = TempLocation.Row + RowChange;
    TempLocation.Column = TempLocation.Column + ColumnChange;
  }//end while

  return;
}//end CheckMovesInDirection

ChessPiece MoveGenerator::RandomMove()
{
  //vars
  int RandLocation = rand() % MovablePieces.size();

  //remove until rand
  for (int i = 0; i < RandLocation; i++)
    MovablePieces.pop();

  return MovablePieces.front();    
}//end RandomMove