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
  //set piece type baised on direction

  if (Direction == 1)//white
    TempPiece.PieceType = PieceType[0];
  else //black
    TempPiece.PieceType = PieceType[0] + ('a' - 'A');
  //spcial case for knights
  if (PieceType == "Knight")
    TempPiece.PieceType += 'N' - 'K';
  
  //check for each peices movess
  if (PieceType == "Pawn" && PawnMoves(TempPiece, Direction, HasMoved) && RemoveInCheckMoves(TempPiece, Direction))
    MovablePieces.push(TempPiece);
  else if (PieceType == "King" && KingMoves(TempPiece, false) && RemoveInCheckMoves(TempPiece, Direction))
    MovablePieces.push(TempPiece);
  else if (PieceType == "Rook" && RookMoves(TempPiece, false) && RemoveInCheckMoves(TempPiece, Direction))
    MovablePieces.push(TempPiece);
  else if (PieceType == "Bishop" && BishopMoves(TempPiece, false) && RemoveInCheckMoves(TempPiece, Direction))
    MovablePieces.push(TempPiece);
  else if (PieceType == "Queen" && QueenMoves(TempPiece, false) && RemoveInCheckMoves(TempPiece, Direction))
    MovablePieces.push(TempPiece);
  else if (PieceType == "Knight" && KnightMoves(TempPiece, false) && RemoveInCheckMoves(TempPiece, Direction))
    MovablePieces.push(TempPiece);
  return;
}//end GenerateAllMoves

bool MoveGenerator::PawnMoves(ChessPiece& Pawn, const int Direction, const bool HasMoved)
{
  //single move if possible
  if (CurrentBoard.IsLocationEmpty(Location(Pawn.PieceLocation.Row + Direction, Pawn.PieceLocation.Column)))
  {
    Pawn.PossibleMoves.push(Location(Pawn.PieceLocation.Row + Direction, Pawn.PieceLocation.Column));

    //double move if possible
    if (!HasMoved && CurrentBoard.IsLocationEmpty(Location(Pawn.PieceLocation.Row + (2*Direction), Pawn.PieceLocation.Column)))
    {
      Pawn.PossibleMoves.push(Location(Pawn.PieceLocation.Row + (2*Direction), Pawn.PieceLocation.Column));
      //cout << "2 Row:" << Pawn.PieceLocation.Row - '0' << " Column:" << Pawn.PieceLocation.Column << endl;
    }
  }
  //check for leftward diagonal moves
  if (Pawn.PieceLocation.Column > 'a')
  {
    if (CurrentBoard.IsPieceEnemy(Pawn.PieceLocation, Location(Pawn.PieceLocation.Row + Direction, Pawn.PieceLocation.Column - 1)))
      Pawn.PossibleMoves.push(Location(Pawn.PieceLocation.Row + Direction, Pawn.PieceLocation.Column - 1));
    else if (CurrentBoard.EnPassantLocation().Row == Pawn.PieceLocation.Row + Direction && CurrentBoard.EnPassantLocation().Column == Pawn.PieceLocation.Column - 1)
      Pawn.PossibleMoves.push(Location(Pawn.PieceLocation.Row + Direction, Pawn.PieceLocation.Column - 1));
  }//end else if
  //check for rightward diagonal moves
  if (Pawn.PieceLocation.Column < 'h')
  {
    if (CurrentBoard.IsPieceEnemy(Pawn.PieceLocation, Location(Pawn.PieceLocation.Row + Direction, Pawn.PieceLocation.Column + 1)))
      Pawn.PossibleMoves.push(Location(Pawn.PieceLocation.Row + Direction, Pawn.PieceLocation.Column + 1));
    else if (CurrentBoard.EnPassantLocation().Row == Pawn.PieceLocation.Row + Direction && CurrentBoard.EnPassantLocation().Column == Pawn.PieceLocation.Column + 1)
      Pawn.PossibleMoves.push(Location(Pawn.PieceLocation.Row + Direction, Pawn.PieceLocation.Column + 1));
  }//end else if
  
  //cout << "Pawn moves:" << Pawn.PossibleMoves.size() << endl;
  if (Pawn.PossibleMoves.size() > 0)
    return true;
  else 
    return false;
}//end PawnMoves

// bool MoveGenerator::PawnMovesCheck(const ChessPiece Pawn, const int Direction)
// {
//   Ch
// }//end PawnMovesCheck

bool MoveGenerator::KingMoves(ChessPiece& King, const bool TestingCheck)
{
  //check area around king
  if (!TestingCheck)
  {
    CheckMovesInDirection(King,  1,  0, true, TestingCheck); 
    CheckMovesInDirection(King,  1,  1, true, TestingCheck);
    CheckMovesInDirection(King,  0,  1, true, TestingCheck);
    CheckMovesInDirection(King, -1,  1, true, TestingCheck);
    CheckMovesInDirection(King, -1,  0, true, TestingCheck);
    CheckMovesInDirection(King, -1, -1, true, TestingCheck);
    CheckMovesInDirection(King,  0, -1, true, TestingCheck);
    CheckMovesInDirection(King,  1, -1, true, TestingCheck);

    //castleing
    if (CurrentBoard.IsLocationEmpty(Location(King.PieceLocation.Row, King.PieceLocation.Column - 1)) &&
      CurrentBoard.IsLocationEmpty(Location(King.PieceLocation.Row, King.PieceLocation.Column - 2)) &&
      CurrentBoard.IsLocationEmpty(Location(King.PieceLocation.Row, King.PieceLocation.Column - 3)))
    {
      if (King.PieceType == 'K' && CurrentBoard.WhiteQueenSideCastle)
        King.PossibleMoves.push(Location(King.PieceLocation.Row, King.PieceLocation.Column - 2));
      else if (King.PieceType == 'k' && CurrentBoard.BlackQueenSideCastle)
        King.PossibleMoves.push(Location(King.PieceLocation.Row, King.PieceLocation.Column - 2));
    }//end if
    else if (CurrentBoard.IsLocationEmpty(Location(King.PieceLocation.Row, King.PieceLocation.Column + 1)) && 
      CurrentBoard.IsLocationEmpty(Location(King.PieceLocation.Row, King.PieceLocation.Column + 2)))
    {
      if (King.PieceType == 'K' && CurrentBoard.WhiteKingSideCastle)
        King.PossibleMoves.push(Location(King.PieceLocation.Row, King.PieceLocation.Column + 2));
      else if (King.PieceType == 'k' && CurrentBoard.BlackKingSideCastle)
        King.PossibleMoves.push(Location(King.PieceLocation.Row, King.PieceLocation.Column + 2));
    }//end else if
  }//end if
  else if (CheckMovesInDirection(King,  1,  0, true, 'K') || 
      CheckMovesInDirection(King,  1,  1, true, 'K') ||
      CheckMovesInDirection(King,  0,  1, true, 'K') ||
      CheckMovesInDirection(King, -1,  1, true, 'K') ||
      CheckMovesInDirection(King, -1,  0, true, 'K') ||
      CheckMovesInDirection(King, -1, -1, true, 'K') ||
      CheckMovesInDirection(King,  0, -1, true, 'K') ||
      CheckMovesInDirection(King,  1, -1, true, 'K'))
    return true;
  else 
    return false;

  //make sure their is at least one valid move
  if (King.PossibleMoves.size() > 0)
    return true;
  else
    return false;
}//end KingMoves

bool MoveGenerator::RookMoves(ChessPiece& Rook, const bool TestingCheck)
{
  //check straight lines for moves
  if (!TestingCheck)
  {
    CheckMovesInDirection(Rook,  1,  0, false, TestingCheck);//down
    CheckMovesInDirection(Rook, -1,  0, false, TestingCheck);//up
    CheckMovesInDirection(Rook,  0, -1, false, TestingCheck);//left
    CheckMovesInDirection(Rook,  0,  1, false, TestingCheck);
  }//end if
  else if (CheckMovesInDirection(Rook,  1,  0, false, 'R') ||//down
      CheckMovesInDirection(Rook, -1,  0, false, 'R') ||//up
      CheckMovesInDirection(Rook,  0, -1, false, 'R') ||//left
      CheckMovesInDirection(Rook,  0,  1, false, 'R'))  //right
    return true;
  else 
    return false;

  //make sure their is at least one valid move
  if (Rook.PossibleMoves.size() > 0)
    return true;
  else
    return false;
}//end RookMoves

bool MoveGenerator::BishopMoves(ChessPiece& Bishop, const bool TestingCheck)
{
  //check diagonal lines for moves
  if (!TestingCheck)
  {
    CheckMovesInDirection(Bishop,  1,  1, false, TestingCheck);//down right
    CheckMovesInDirection(Bishop, -1,  1, false, TestingCheck);//up right
    CheckMovesInDirection(Bishop,  1, -1, false, TestingCheck);//down left
    CheckMovesInDirection(Bishop, -1, -1, false, TestingCheck);//up left
  }//end if
  else if (CheckMovesInDirection(Bishop,  1,  1, false, 'B') ||//down right
      CheckMovesInDirection(Bishop, -1,  1, false, 'B') ||//up right
      CheckMovesInDirection(Bishop,  1, -1, false, 'B') ||//down left
      CheckMovesInDirection(Bishop, -1, -1, false, 'B'))//up left
    return true;
  else 
    return false;

  //make sure their is at least one valid move
  if (Bishop.PossibleMoves.size() > 0)
    return true;
  else
    return false;
}//end BishopMoves

bool MoveGenerator::QueenMoves(ChessPiece& Queen, const bool TestingCheck)
{
  //check strainght and diagonal lines for moves
  if (!TestingCheck)
  {
    CheckMovesInDirection(Queen, -1,  0, false, TestingCheck);//up
    CheckMovesInDirection(Queen,  0, -1, false, TestingCheck);//left
    CheckMovesInDirection(Queen,  0,  1, false, TestingCheck);//right
    CheckMovesInDirection(Queen,  1,  1, false, TestingCheck);//down right
    CheckMovesInDirection(Queen, -1,  1, false, TestingCheck);//up right
    CheckMovesInDirection(Queen,  1, -1, false, TestingCheck);//down left
    CheckMovesInDirection(Queen, -1, -1, false, TestingCheck);//up left
  }//end if
  else if (CheckMovesInDirection(Queen,  1,  0, false, 'Q') ||//down
      CheckMovesInDirection(Queen, -1,  0, false, 'Q') ||//up
      CheckMovesInDirection(Queen,  0, -1, false, 'Q') ||//left
      CheckMovesInDirection(Queen,  0,  1, false, 'Q') ||//right
      CheckMovesInDirection(Queen,  1,  1, false, 'Q') ||//down right
      CheckMovesInDirection(Queen, -1,  1, false, 'Q') ||//up right
      CheckMovesInDirection(Queen,  1, -1, false, 'Q') ||//down left
      CheckMovesInDirection(Queen, -1, -1, false, 'Q'))//up left
    return true;
  else 
    return false;

  //make sure their is at least one valid move
  if (Queen.PossibleMoves.size() > 0)
    return true;
  else
    return false;
}//end QueenMoves

bool MoveGenerator::KnightMoves(ChessPiece& Knight, const bool TestingCheck)
{
  //check for valid Knight moves
  if (!TestingCheck)
  {
    CheckMovesInDirection(Knight,  2,  1, true, TestingCheck);
    CheckMovesInDirection(Knight, -2,  1, true, TestingCheck);
    CheckMovesInDirection(Knight, -2, -1, true, TestingCheck);
    CheckMovesInDirection(Knight,  2, -1, true, TestingCheck);
    CheckMovesInDirection(Knight,  1,  2, true, TestingCheck);
    CheckMovesInDirection(Knight, -1,  2, true, TestingCheck);
    CheckMovesInDirection(Knight, -1, -2, true, TestingCheck);
    CheckMovesInDirection(Knight,  1, -2, true, TestingCheck);
  }//end if
  else if (CheckMovesInDirection(Knight,  2,  1, true, 'N') ||
    CheckMovesInDirection(Knight, -2,  1, true, 'N') ||
    CheckMovesInDirection(Knight, -2, -1, true, 'N') ||
    CheckMovesInDirection(Knight,  2, -1, true, 'N') ||
    CheckMovesInDirection(Knight,  1,  2, true, 'N') ||
    CheckMovesInDirection(Knight, -1,  2, true, 'N') ||
    CheckMovesInDirection(Knight, -1, -2, true, 'N') ||
    CheckMovesInDirection(Knight,  1, -2, true, 'N'))
    return true;
  else 
    return false;

  //make sure their is at least one valid move
  if (Knight.PossibleMoves.size() > 0)
    return true;
  else
    return false;
}//end KnightMoves

bool MoveGenerator::CheckMovesInDirection(ChessPiece& StartingPiece, const int RowChange, const int ColumnChange, const bool KingorKnight, const char LookingFor)
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
    if (CurrentBoard.IsLocationEmpty(TempLocation) && LookingFor != '*')
    {
      StartingPiece.PossibleMoves.push(TempLocation);
      if (KingorKnight)
        return false;
    }//end if
    //if space has enemy piece
    else if (CurrentBoard.IsPieceEnemy(StartingPiece.PieceLocation, TempLocation))
    {
      //don't add piece if testing for check
      if (LookingFor != '*')
      {
        //if piece puts king in check
        if (CurrentBoard.IsPieceType(TempLocation, LookingFor))
          return true;
        else
          return false;
      }//end if
      else 
      {
        StartingPiece.PossibleMoves.push(TempLocation);
        return true;
      }//end else
    }//end else if
    //if space has my piece
    else 
      return false;

    //set new location
    TempLocation.Row = TempLocation.Row + RowChange;
    TempLocation.Column = TempLocation.Column + ColumnChange;
  }//end while

  return false;
}//end CheckMovesInDirection

bool MoveGenerator::RemoveInCheckMoves(ChessPiece& MovedPiece, const int Direction)
{
  //vars
  int MoveCount = MovedPiece.PossibleMoves.size();
  Location TempLocation = MovedPiece.PossibleMoves.front();
  ChessPiece TempPiece = MovedPiece;
  BoardState TempBoard = CurrentBoard;

  //set TempPiece to king location
  TempPiece.PieceLocation = CurrentBoard.returnKingLocation();

  //loop through each move
  for (int i = 0; i < MoveCount; i++)
  {
    //if king set new location to where it moved
    if (MovedPiece.PieceType == 'k' || MovedPiece.PieceType == 'K')
      TempPiece.PieceLocation = MovedPiece.PossibleMoves.front();

    //move piece to location and test if king is in check
    CurrentBoard.MovePiece(MovedPiece.PieceLocation, MovedPiece.PossibleMoves.front()); 
    //remove location in front
    MovedPiece.PossibleMoves.pop();

    //see if x piece is threatening the king
    if (!KingMoves(TempPiece, true) &&
      !RookMoves(TempPiece, true) &&
      !BishopMoves(TempPiece, true) &&
      !QueenMoves(TempPiece, true) &&
      !KnightMoves(TempPiece, true) && 
      !CheckMovesInDirection(TempPiece, Direction, 1, true, 'P') &&
      !CheckMovesInDirection(TempPiece, Direction, -1, true, 'P'))
    {
      //readd if not in check
      MovedPiece.PossibleMoves.push(TempLocation);
    }//end if

    //get next location
    TempLocation = MovedPiece.PossibleMoves.front();
    //reset board
    CurrentBoard = TempBoard;
  }//end for i

  //make sure there are still possible moves
  if (MovedPiece.PossibleMoves.size() > 0)
    return true;
  else
    return false;
}//end RemoveInCheckMoves

Location MoveGenerator::RandomMove(int& ListId)
{
  //vars
  int RandLocation = rand() % MovablePieces.size();
  int RandMove;
  Location Output;

  //remove until location
  for (int i = 0; i < RandLocation; i++)
    MovablePieces.pop();
  
  //output piece
  cout << "________________________________________" << endl;
  cout << "Piece Type: " << MovablePieces.front().PieceType << endl;
  cout << "  Column: " << MovablePieces.front().PieceLocation.Column << endl;
  cout << "  Row: " << MovablePieces.front().PieceLocation.Row << endl;
  cout << "Possible Move Destinations(Column, Row):" << endl;

  //remove until move
  RandMove = rand() % MovablePieces.front().PossibleMoves.size();
  for (int i = 0; i < RandMove; i++)
  {
    cout << "  (" << MovablePieces.front().PossibleMoves.front().Column << ", " << MovablePieces.front().PossibleMoves.front().Row << ")" << endl;
    MovablePieces.front().PossibleMoves.pop();
  }//end for i

  //set output location
  Output = MovablePieces.front().PossibleMoves.front();
  //set ListId
  ListId = MovablePieces.front().ListId;
  //print location moving to
  cout << "  (" << MovablePieces.front().PossibleMoves.front().Column << ", " << MovablePieces.front().PossibleMoves.front().Row << ")<--Moving to this location" << endl;
  MovablePieces.front().PossibleMoves.pop();

  //print remaining moves for piece
  while (MovablePieces.front().PossibleMoves.size() > 0)
  {
    cout << "  (" << MovablePieces.front().PossibleMoves.front().Column << ", " << MovablePieces.front().PossibleMoves.front().Row << ")" << endl;
    MovablePieces.front().PossibleMoves.pop();
  }//end for i
  
  return Output;
}//end RandomMove