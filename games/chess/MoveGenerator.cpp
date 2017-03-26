//Name: Joey Klix
//Class: 5400 Introduction to AI
//Description: Chess AI

//include files
#include "MoveGenerator.h"

bool operator<(const MovePiece& MP1, const MovePiece& MP2)
{
  //compare heuristic value assigned to both pieces
  return (MP1.HeurValue > MP2.HeurValue);
}

MoveGenerator::MoveGenerator()
{
  //set default state
  CurrentBoard = BoardState();
  HeuristicValue = 0;
  PossibleSimplifiedDraw = false;
  DepthToGo = 0;
  Maximizing = true;
  return;
}//end constructor

MoveGenerator::MoveGenerator(BoardState GameBoard, vector<MyChessPiece> OldMoveHistory, bool pMaximizing, bool SwitchDir)
{
  //set default state
  CurrentBoard = GameBoard;
  HeuristicValue = 0;
  PossibleSimplifiedDraw = false;
  DepthToGo = 0;
  Maximizing = pMaximizing;
  if (SwitchDir)
    CurrentBoard.Direction *= -1;

  //copy up to last 8 moves
  if (OldMoveHistory.size() < 10)
    MoveHistory = OldMoveHistory;
  else
  {
    //add last 8 moves to history
    for (int i = OldMoveHistory.size() - 9; i <= (OldMoveHistory.size() - 1); i++)
    {
      MoveHistory.push_back(OldMoveHistory[i]);
    }//end for
  }//emd else
  
  return;
}//end constructor

void MoveGenerator::GenerateMoves(Location NewPieceLocation, const int PlaceInList, const string PieceType, const int pDepthToGo)
{
  //vars
  MyChessPiece TempPiece;
  
  //set values to temp
  TempPiece.ListId = PlaceInList;
  TempPiece.PieceLocation.Column = NewPieceLocation.Column;
  TempPiece.PieceLocation.Row = NewPieceLocation.Row;
  
  //if enough moves check for repeats
  if (MoveHistory.size() >= 7)
    PossibleSimplifiedDraw = true;
  //set depth to go
  DepthToGo = pDepthToGo;

  //set piece type baised on direction
  if (CurrentBoard.Direction == 1)//white
    TempPiece.PieceType = PieceType[0];
  else //black
    TempPiece.PieceType = PieceType[0] + ('a' - 'A');
  //spcial case for knights
  if (PieceType == "Knight")
    TempPiece.PieceType += 'N' - 'K';
  
  //check for each peices movess
  if (PieceType == "Pawn") 
    PawnMoves(TempPiece);
  else if (PieceType == "King")
    KingMoves(TempPiece);
  else if (PieceType == "Rook")
    RookMoves(TempPiece);
  else if (PieceType == "Bishop")
    BishopMoves(TempPiece);
  else if (PieceType == "Queen")
    QueenMoves(TempPiece);
  else if (PieceType == "Knight")
    KnightMoves(TempPiece);

  return;
}//end GenerateAllMoves

void MoveGenerator::PawnMoves(MyChessPiece& Pawn)
{
  //vars
  bool HasMoved = true;

  if ((Pawn.PieceLocation.Row == '2' && CurrentBoard.Direction == 1) || (Pawn.PieceLocation.Row == '7' && CurrentBoard.Direction == -1))
    HasMoved = false;

  //single move if possible
  if (CurrentBoard.IsLocationEmpty(Location(Pawn.PieceLocation.Row + CurrentBoard.Direction, Pawn.PieceLocation.Column)))
  {
    DoesMoveEndInCheck(Pawn, Location(Pawn.PieceLocation.Row + CurrentBoard.Direction, Pawn.PieceLocation.Column));

    //double move if possible
    if (!HasMoved && CurrentBoard.IsLocationEmpty(Location(Pawn.PieceLocation.Row + (2*CurrentBoard.Direction), Pawn.PieceLocation.Column)))
    {
      DoesMoveEndInCheck(Pawn, Location(Pawn.PieceLocation.Row + (2*CurrentBoard.Direction), Pawn.PieceLocation.Column));
    }
  }
  //check for leftward diagonal moves
  if (Pawn.PieceLocation.Column > 'a')
  {
    if (CurrentBoard.IsPieceEnemy(Pawn.PieceLocation, Location(Pawn.PieceLocation.Row + CurrentBoard.Direction, Pawn.PieceLocation.Column - 1)))
      DoesMoveEndInCheck(Pawn, Location(Pawn.PieceLocation.Row + CurrentBoard.Direction, Pawn.PieceLocation.Column - 1));
    else if (CurrentBoard.EnPassantLocation().Row == Pawn.PieceLocation.Row + CurrentBoard.Direction && CurrentBoard.EnPassantLocation().Column == Pawn.PieceLocation.Column - 1)
      DoesMoveEndInCheck(Pawn, Location(Pawn.PieceLocation.Row + CurrentBoard.Direction, Pawn.PieceLocation.Column - 1));
  }//end else if
  //check for rightward diagonal moves
  if (Pawn.PieceLocation.Column < 'h')
  {
    if (CurrentBoard.IsPieceEnemy(Pawn.PieceLocation, Location(Pawn.PieceLocation.Row + CurrentBoard.Direction, Pawn.PieceLocation.Column + 1)))
      DoesMoveEndInCheck(Pawn, Location(Pawn.PieceLocation.Row + CurrentBoard.Direction, Pawn.PieceLocation.Column + 1));
    else if (CurrentBoard.EnPassantLocation().Row == Pawn.PieceLocation.Row + CurrentBoard.Direction && CurrentBoard.EnPassantLocation().Column == Pawn.PieceLocation.Column + 1)
      DoesMoveEndInCheck(Pawn, Location(Pawn.PieceLocation.Row + CurrentBoard.Direction, Pawn.PieceLocation.Column + 1));
  }//end else if

  //add piece value to heuristic
  HeuristicValue += 1;
  return;
}//end PawnMoves

void MoveGenerator::KingMoves(MyChessPiece& King)
{
  //check area around king
  CheckMovesInDirection(King,  1,  0, true); 
  CheckMovesInDirection(King,  1,  1, true);
  CheckMovesInDirection(King,  0,  1, true);
  CheckMovesInDirection(King, -1,  1, true);
  CheckMovesInDirection(King, -1,  0, true);
  CheckMovesInDirection(King, -1, -1, true);
  CheckMovesInDirection(King,  0, -1, true);
  CheckMovesInDirection(King,  1, -1, true);

  //queen side castleing
  if (CurrentBoard.IsLocationEmpty(Location(King.PieceLocation.Row, King.PieceLocation.Column - 1)) &&
    CurrentBoard.IsLocationEmpty(Location(King.PieceLocation.Row, King.PieceLocation.Column - 2)) &&
    CurrentBoard.IsLocationEmpty(Location(King.PieceLocation.Row, King.PieceLocation.Column - 3)))
  {
    if (King.PieceType == 'K' && CurrentBoard.WhiteQueenSideCastle)
      DoesMoveEndInCheck(King, Location(King.PieceLocation.Row, King.PieceLocation.Column - 2));
    else if (King.PieceType == 'k' && CurrentBoard.BlackQueenSideCastle)
      DoesMoveEndInCheck(King, Location(King.PieceLocation.Row, King.PieceLocation.Column - 2));
  }//end if
  //king side castleing
  if (CurrentBoard.IsLocationEmpty(Location(King.PieceLocation.Row, King.PieceLocation.Column + 1)) && 
    CurrentBoard.IsLocationEmpty(Location(King.PieceLocation.Row, King.PieceLocation.Column + 2)))
  {
    if (King.PieceType == 'K' && CurrentBoard.WhiteKingSideCastle)
      DoesMoveEndInCheck(King, Location(King.PieceLocation.Row, King.PieceLocation.Column + 2));
    else if (King.PieceType == 'k' && CurrentBoard.BlackKingSideCastle)
      DoesMoveEndInCheck(King, Location(King.PieceLocation.Row, King.PieceLocation.Column + 2));
  }//end else if

  return;
}//end KingMoves

bool MoveGenerator::KingMovesCheck(MyChessPiece King)
{
  //return true if a king is threatened
  if (IsPieceThreateningKing(King,  1,  0, true, 'K') || 
      IsPieceThreateningKing(King,  1,  1, true, 'K') ||
      IsPieceThreateningKing(King,  0,  1, true, 'K') ||
      IsPieceThreateningKing(King, -1,  1, true, 'K') ||
      IsPieceThreateningKing(King, -1,  0, true, 'K') ||
      IsPieceThreateningKing(King, -1, -1, true, 'K') ||
      IsPieceThreateningKing(King,  0, -1, true, 'K') ||
      IsPieceThreateningKing(King,  1, -1, true, 'K'))
    return true;
  else 
    return false;
}//end KingMovesCheck

void MoveGenerator::RookMoves(MyChessPiece& Rook)
{
  //check straight lines for moves
  CheckMovesInDirection(Rook,  1,  0, false);//down
  CheckMovesInDirection(Rook, -1,  0, false);//up
  CheckMovesInDirection(Rook,  0, -1, false);//left
  CheckMovesInDirection(Rook,  0,  1, false);//right

  //add piece value to heuristic
  HeuristicValue += 5;
  return;
}//end RookMoves

bool MoveGenerator::RookMovesCheck(MyChessPiece Rook)
{
  //is king in check from rook
  if (IsPieceThreateningKing(Rook,  1,  0, false, 'R') ||//down
      IsPieceThreateningKing(Rook, -1,  0, false, 'R') ||//up
      IsPieceThreateningKing(Rook,  0, -1, false, 'R') ||//left
      IsPieceThreateningKing(Rook,  0,  1, false, 'R'))  //right
    return true;
  else 
    return false;
}//end RookMovesCheck

void MoveGenerator::BishopMoves(MyChessPiece& Bishop)
{
  //check diagonal lines for moves
  CheckMovesInDirection(Bishop,  1,  1, false);//down right
  CheckMovesInDirection(Bishop, -1,  1, false);//up right
  CheckMovesInDirection(Bishop,  1, -1, false);//down left
  CheckMovesInDirection(Bishop, -1, -1, false);//up left

  //add piece value to heuristic
  HeuristicValue += 3;
  return;
}//end BishopMoves

bool MoveGenerator::BishopMovesCheck(MyChessPiece Bishop)
{
  //is king in check from bishop
  if (IsPieceThreateningKing(Bishop,  1,  1, false, 'B') ||//down right
      IsPieceThreateningKing(Bishop, -1,  1, false, 'B') ||//up right
      IsPieceThreateningKing(Bishop,  1, -1, false, 'B') ||//down left
      IsPieceThreateningKing(Bishop, -1, -1, false, 'B'))//up left
    return true;
  else 
    return false;
}//end BishopMovesCheck

void MoveGenerator::QueenMoves(MyChessPiece& Queen)
{
  //check strainght and diagonal lines for moves
  CheckMovesInDirection(Queen, -1,  0, false);//up
  CheckMovesInDirection(Queen,  0, -1, false);//left
  CheckMovesInDirection(Queen,  0,  1, false);//right
  CheckMovesInDirection(Queen,  1,  1, false);//down right
  CheckMovesInDirection(Queen, -1,  1, false);//up right
  CheckMovesInDirection(Queen,  1, -1, false);//down left
  CheckMovesInDirection(Queen, -1, -1, false);//up left

  //add piece value to heuristic
  HeuristicValue += 9;
  return;
}//end QueenMoves

bool MoveGenerator::QueenMovesCheck(MyChessPiece Queen)
{
  //is king in check from queen
  if (IsPieceThreateningKing(Queen,  1,  0, false, 'Q') ||//down
      IsPieceThreateningKing(Queen, -1,  0, false, 'Q') ||//up
      IsPieceThreateningKing(Queen,  0, -1, false, 'Q') ||//left
      IsPieceThreateningKing(Queen,  0,  1, false, 'Q') ||//right
      IsPieceThreateningKing(Queen,  1,  1, false, 'Q') ||//down right
      IsPieceThreateningKing(Queen, -1,  1, false, 'Q') ||//up right
      IsPieceThreateningKing(Queen,  1, -1, false, 'Q') ||//down left
      IsPieceThreateningKing(Queen, -1, -1, false, 'Q'))//up left
    return true;
  else 
    return false;
}//end QueenMovesCheck

void MoveGenerator::KnightMoves(MyChessPiece& Knight)
{
  //check for valid Knight moves
  CheckMovesInDirection(Knight,  2,  1, true);
  CheckMovesInDirection(Knight, -2,  1, true);
  CheckMovesInDirection(Knight, -2, -1, true);
  CheckMovesInDirection(Knight,  2, -1, true);
  CheckMovesInDirection(Knight,  1,  2, true);
  CheckMovesInDirection(Knight, -1,  2, true);
  CheckMovesInDirection(Knight, -1, -2, true);
  CheckMovesInDirection(Knight,  1, -2, true);

  //add piece value to heuristic
  HeuristicValue += 3;
  return;
}//end KnightMoves

bool MoveGenerator::KnightMovesCheck(MyChessPiece Knight)
{
  //is king in check from knight
  if (IsPieceThreateningKing(Knight,  2,  1, true, 'N') ||
    IsPieceThreateningKing(Knight, -2,  1, true, 'N') ||
    IsPieceThreateningKing(Knight, -2, -1, true, 'N') ||
    IsPieceThreateningKing(Knight,  2, -1, true, 'N') ||
    IsPieceThreateningKing(Knight,  1,  2, true, 'N') ||
    IsPieceThreateningKing(Knight, -1,  2, true, 'N') ||
    IsPieceThreateningKing(Knight, -1, -2, true, 'N') ||
    IsPieceThreateningKing(Knight,  1, -2, true, 'N'))
    return true;
  else 
    return false;
}//end KnightMovesCheck

bool MoveGenerator::CheckMovesInDirection(MyChessPiece& StartingPiece, const int RowChange, const int ColumnChange, const bool KingorKnight)
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
    {
      DoesMoveEndInCheck(StartingPiece, TempLocation);
      if (KingorKnight)
        return false;
    }//end if
    //if space has enemy piece
    else if (CurrentBoard.IsPieceEnemy(StartingPiece.PieceLocation, TempLocation))
    {
      DoesMoveEndInCheck(StartingPiece, TempLocation);
      return true;
    }//end else if
    //found my piece
    else
      return false;

    //set new location
    TempLocation.Row = TempLocation.Row + RowChange;
    TempLocation.Column = TempLocation.Column + ColumnChange;
  }//end while

  return false;
}//end CheckMovesInDirection

bool MoveGenerator::IsPieceThreateningKing(const MyChessPiece King, const int RowChange, const int ColumnChange, const bool KingorKnight, const char LookingFor)
{
  //vars
  Location TempLocation = King.PieceLocation;

  //set new location
  TempLocation.Row = TempLocation.Row + RowChange;
  TempLocation.Column = TempLocation.Column + ColumnChange;

  //make sure location is still on board
  while (TempLocation.Row >= '1' && TempLocation.Row <= '8' && TempLocation.Column >= 'a' && TempLocation.Column <= 'h')
  {
    //check if enemy is treatening king
    if (CurrentBoard.IsPieceEnemy(King.PieceLocation, TempLocation) && CurrentBoard.IsPieceType(TempLocation, LookingFor))
      return true;
    //found my piece
    else if (!CurrentBoard.IsLocationEmpty(TempLocation))
      return false;
    else if (KingorKnight)
      return false;

    //set new location
    TempLocation.Row = TempLocation.Row + RowChange;
    TempLocation.Column = TempLocation.Column + ColumnChange;
  }//end while

  return false;
}//end IsPieceThreateningKing

bool MoveGenerator::DoesMoveEndInCheck(MyChessPiece MovedPiece, Location EndLocation)
{
  //vars
  BoardState TempBoard = CurrentBoard;
  MyChessPiece TempPiece = MovedPiece;

  //set TempPiece to king location
  TempPiece.PieceLocation = CurrentBoard.returnKingLocation();

  //if king set new location to where it moved
  if (MovedPiece.PieceType == 'k' || MovedPiece.PieceType == 'K')
    TempPiece.PieceLocation = EndLocation;
  
  //move piece to location and test if king is in check
  CurrentBoard.MovePiece(MovedPiece.PieceLocation, EndLocation);
  if (!KingMovesCheck(TempPiece) &&
    !RookMovesCheck(TempPiece) &&
    !BishopMovesCheck(TempPiece) &&
    !QueenMovesCheck(TempPiece) &&
    !KnightMovesCheck(TempPiece) && 
    !IsPieceThreateningKing(TempPiece, CurrentBoard.Direction, 1, true, 'P') &&
    !IsPieceThreateningKing(TempPiece, CurrentBoard.Direction, -1, true, 'P'))
  {
    if (PossibleSimplifiedDraw && TempPiece.PieceType == MoveHistory[MoveHistory.size() - 4].PieceType
      && MoveHistory[MoveHistory.size() - 4].PieceLocation.Column == EndLocation.Column
      && MoveHistory[MoveHistory.size() - 4].PieceLocation.Row == EndLocation.Row)
    {
      //don't add because causes early draw
    }
    else //re-add if not in check
    {
      MovePiecesQueue.push(MovePiece(MovedPiece, EndLocation, FindNextDepthHeuristic(EndLocation, MovedPiece.PieceType)));
    }//end else
  }//end if
  CurrentBoard = TempBoard;
  return true;
}//end DoesMoveEndInCheck

Location MoveGenerator::MiniMax(int& ListId)
{
  //vars
  MyChessPiece TempPiece = MovePiecesQueue.top().CurrentPiece;
  TempPiece.PieceLocation = MovePiecesQueue.top().EndLoc;

  //add chosen move to history
  MoveHistory.push_back(TempPiece);
  //return listid and locaiton
  ListId = MovePiecesQueue.top().CurrentPiece.ListId;
  return TempPiece.PieceLocation;
}//end GenerateAllMoves

int MoveGenerator::FindNextDepthHeuristic(Location DestinationLocation, char MovedPieceType)
{
  //see if their are steps to go
  if (DepthToGo >= 0)
  {
    //vars
    MyChessPiece TempPiece = MyChessPiece();
    MoveGenerator NextDepth = MoveGenerator();
    vector<MyChessPiece> TempPieceList = MoveHistory;

    //set temp piece values
    TempPiece.PieceLocation = DestinationLocation;
    TempPiece.PieceType = MovedPieceType;
    //add piece to move history
    TempPieceList.push_back(TempPiece);
    NextDepth = MoveGenerator(CurrentBoard, TempPieceList, !Maximizing, true);
    
    //find heuristic for next depth
    NextDepth.NextDepthMoves(DepthToGo-1);
    
    if (DepthToGo == 0)
    {
      //max depth reached, return value of current state
      return NextDepth.ReturnHeuristicValue();
    }//end if
    else if (Maximizing)
    {
      //return max value at top of queue
      return NextDepth.MovePiecesQueue.top().HeurValue;
    } //end else if
    else
    {
      //pop until min move is found
      while (NextDepth.MovePiecesQueue.size() > 1)
        NextDepth.MovePiecesQueue.pop();
      return NextDepth.MovePiecesQueue.top().HeurValue;
    }//end else
  }//end if

  return 0;
}//end FindNextDepthHeuristic

void  MoveGenerator::NextDepthMoves(const int pDepthToGo)
{
  //vars
  MyChessPiece TempPiece = MyChessPiece();
  DepthToGo = pDepthToGo;
  
  //check every location for my pieces to move
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      if (CurrentBoard.BoardMap[i][j].PieceType != '*' && CurrentBoard.IsPieceMine(CurrentBoard.BoardMap[i][j].PieceLocation))
      {
        TempPiece = CurrentBoard.BoardMap[i][j];
        //check for each peices movess
        if (TempPiece.PieceType == 'P' || TempPiece.PieceType == 'p')
          PawnMoves(TempPiece);
        else if (TempPiece.PieceType == 'K' || TempPiece.PieceType == 'k')
          KingMoves(TempPiece);
        else if (TempPiece.PieceType == 'R' || TempPiece.PieceType == 'r')
          RookMoves(TempPiece);
        else if (TempPiece.PieceType == 'B' || TempPiece.PieceType == 'b')
          BishopMoves(TempPiece);
        else if (TempPiece.PieceType == 'Q' || TempPiece.PieceType == 'q')
          QueenMoves(TempPiece);
        else if (TempPiece.PieceType == 'N' || TempPiece.PieceType == 'n')
          KnightMoves(TempPiece);
      }//end if
    }//end for j
  }//end for i

  return;
}//end Max

void MoveGenerator::AddOpponentMove(Location NewPieceLocation, const string PieceType)
{
  //vars
  MyChessPiece TempPiece = MyChessPiece();

  //set location and type of oponents piece
  TempPiece.PieceLocation = NewPieceLocation;
  if (CurrentBoard.Direction == -1)//black
    TempPiece.PieceType = PieceType[0];
  else //white
    TempPiece.PieceType = PieceType[0] + ('a' - 'A');
  //spcial case for knights
  if (PieceType == "Knight")
    TempPiece.PieceType += 'N' - 'K';

  //add to move history vector
  MoveHistory.push_back(TempPiece);
  return;
}//end AddOpponentMove