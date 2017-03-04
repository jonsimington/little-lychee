//Name: Joey Klix
//Class: 5400 Introduction to AI
//Description: Chess AI

//include files
#include "BoardState.h"
#include "header.h"

BoardState::BoardState()
{
  WhitesTurn = false;
  WhiteKingSideCastle = false;
  WhileQueenSideCastle = false;
  BlackKingSideCastle = false;
  BlackQueenSideCastle = false;
  EnPassantTarget = Location();
  HalfMoveClock = 0;
  FullMoveNumber = 0;
  vector<vector<ChessPiece> > TempMap(8, vector<ChessPiece>(8));
  BoardMap = TempMap;
}//end default constructor

void BoardState::ForsythEdwardsNotationBoardInput(string InputString)
{
  //vars
  InputString = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 0";//default state
  vector<string> SplitString = SplitByChar(InputString, ' ');
  vector<string> RowsString = SplitByChar(SplitString[0], '/');
  int ColumnLocation = 0;

  //get board state
  for (int i = 0; i < 8; i++)
  {
    //loop through items in row
    for (int j = 0; j < RowsString.size(); j++)
    {
      //if set of empty spaces
      if (RowsString[i][j] < '9')
      {
        for (int k = 0; k < RowsString[i][j] - '0'; k++)
        {
          //set empty space and increment column
          BoardMap[i][ColumnLocation].EmptySpace = true;
          BoardMap[i][ColumnLocation].WhitePiece = false;
          BoardMap[i][ColumnLocation].PieceType = '*';
          BoardMap[i][ColumnLocation].PieceLocation = Location();
          ColumnLocation++;
        }//end for
      }//end if
      else //a piece
      {
        //set piece parameters
        BoardMap[i][ColumnLocation].EmptySpace = false;
        BoardMap[i][ColumnLocation].WhitePiece = RowsString[i][j] > 'Z';
        BoardMap[i][ColumnLocation].PieceType = RowsString[i][j];
        BoardMap[i][ColumnLocation].PieceLocation.Row = i + '0';
        BoardMap[i][ColumnLocation].PieceLocation.Column = j + 'a';
        ColumnLocation++;
      }//end else
    }//end for j

    //reset column location
    ColumnLocation = 0;
  }//end for i

  //is it whites turn
  WhitesTurn = SplitString[1][0] == 'w';

  //Which castleings are allowed
  if (SplitString[2][ColumnLocation] == 'K')
  {
    WhiteKingSideCastle = true;
    ColumnLocation++;
  }//end if WhiteKingSideCastle
  if (SplitString[2].size() > ColumnLocation && SplitString[2][ColumnLocation] == 'Q')
  {
    WhileQueenSideCastle = true;
    ColumnLocation++;
  }//end if WhiteQueenSideCastle
  if (SplitString[2].size() > ColumnLocation && SplitString[2][ColumnLocation] == 'k')
  {
    BlackKingSideCastle = true;
    ColumnLocation++;
  }//end if BlackKingSideCastle
  if (SplitString[2].size() > ColumnLocation && SplitString[2][ColumnLocation] == 'q')
  {
    BlackQueenSideCastle = true;
    ColumnLocation++;
  }//end if BlackQueenSideCastle

  //set EnPassantTarget if there is one
  if (SplitString[3] != "-")
  {
    EnPassantTarget.Row = SplitString[3][0];
    EnPassantTarget.Column = SplitString[3][1];
  }//end if
  else
  {
    EnPassantTarget.Row = '-';
    EnPassantTarget.Column = '-';
  }//end else

  //set move numbers
  HalfMoveClock = stoi(SplitString[4], nullptr, 10);
  FullMoveNumber = stoi(SplitString[5], nullptr, 10);
}//end ForsythEdwardsNotationBoardInput

void BoardState::PrintMap()
{
  //print map
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
      cout << BoardMap[i][j].PieceType;
    cout << endl;
  }//end for i

  //print other variables
  cout << "WhitesTurn: " << WhitesTurn << endl;
  cout << "WhiteKingSideCastle: " << WhiteKingSideCastle << endl;
  cout << "WhileQueenSideCastle: " << WhileQueenSideCastle << endl;
  cout << "BlackKingSideCastle: " << BlackKingSideCastle << endl;
  cout << "BlackQueenSideCastle: " << BlackQueenSideCastle << endl;
  cout << "EnPassantTarget: " << EnPassantTarget.Row << EnPassantTarget.Column << endl;
  cout << "HalfMoveClock: " << HalfMoveClock << endl;
  cout << "FullMoveNumber: " << FullMoveNumber << endl;
}//end PrintMap

vector<string> BoardState::SplitByChar(const string StringtoSplit, char SeparatingChar)
{
  //vars
  vector<string> OutputString;
  stringstream SplitString;
  SplitString.str(StringtoSplit);
  string sTemp = "";

  //split string by char 
  while (getline(SplitString, sTemp, SeparatingChar))
    OutputString.push_back(sTemp);

  return OutputString;
}//end SplitByChar

bool BoardState::IsLocationEmpty(Location TargetLocation)
{
  return BoardMap[TargetLocation.Column - 'a'][TargetLocation.Row - '0'].EmptySpace == true;
}//end IsLocationEmpty

void BoardState::MovePiece(Location StartLocation, Location DestinationLocation)
{
  //vars
  ChessPiece TempPiece;
  TempPiece.EmptySpace = true;
  TempPiece.PieceType = '*';

  BoardMap[DestinationLocation.Row - '0'][DestinationLocation.Column - 'a'] = BoardMap[StartLocation.Row - '0'][StartLocation.Column - 'a'];
  BoardMap[StartLocation.Row - '0'][StartLocation.Column - 'a'] = TempPiece;
}//end MovePiece