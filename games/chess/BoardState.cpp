//Name: Joey Klix
//Class: 5400 Introduction to AI
//Description: Chess AI

//include files
#include "BoardState.h"
#include "header.h"

BoardState::BoardState()
{
  //set default state
  WhitesTurn = false;
  WhiteKingSideCastle = false;
  WhiteQueenSideCastle = false;
  BlackKingSideCastle = false;
  BlackQueenSideCastle = false;
  EnPassantTarget = Location();
  HalfMoveClock = 0;
  FullMoveNumber = 0;
  vector<vector<ChessPiece> > TempMap(8, vector<ChessPiece>(8, ChessPiece()));
  BoardMap = TempMap;
  return;
}//end default constructor

void BoardState::ForsythEdwardsNotationBoardInput(string InputString)
{
  //vars
  //InputString = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 2 32";//default state
  vector<string> SplitString = SplitByChar(InputString, ' ');
  vector<string> RowsString = SplitByChar(SplitString[0], '/');
  int ColumnLocation = 0;

  //get board state
  for (int i = 0; i < 8; i++)
  {
    //loop through items in row
    for (int j = 0; j < RowsString[i].size(); j++)
    {
      //if set of empty spaces
      if (RowsString[i][j] < '9')
      {
        for (int k = 0; k < RowsString[i][j] - '0'; k++)
        {
          //set empty space and increment column
          BoardMap[7-i][ColumnLocation].EmptySpace = true;
          BoardMap[7-i][ColumnLocation].WhitePiece = false;
          BoardMap[7-i][ColumnLocation].PieceType = '*';
          BoardMap[7-i][ColumnLocation].ListId = -1;
          BoardMap[7-i][ColumnLocation].PieceLocation.Row = '-';
          BoardMap[7-i][ColumnLocation].PieceLocation.Column = '-';
          ColumnLocation++;
        }//end for
      }//end if
      else //a piece
      {
        //set piece parameters
        BoardMap[7-i][ColumnLocation].EmptySpace = false;
        BoardMap[7-i][ColumnLocation].WhitePiece = (RowsString[i][j] > 'Z');
        BoardMap[7-i][ColumnLocation].PieceType = RowsString[i][j];
        BoardMap[7-i][ColumnLocation].ListId = -1;
        BoardMap[7-i][ColumnLocation].PieceLocation.Row = 7 - i + '1';
        BoardMap[7-i][ColumnLocation].PieceLocation.Column = j + 'a';
        ColumnLocation++;
      }//end else
    }//end for j

    //reset column location
    ColumnLocation = 0;
  }//end for i

  cout << "Map done" << endl;

  //reverse(BoardMap.begin(), BoardMap.end());

  //is it whites turn
  WhitesTurn = SplitString[1][0] == 'w';

  ColumnLocation = 0;
  //Which castleings are allowed
  if (SplitString[2][ColumnLocation] == 'K')
  {
    WhiteKingSideCastle = true;
    ColumnLocation++;
  }//end if WhiteKingSideCastle
  if (SplitString[2].size() > ColumnLocation && SplitString[2][ColumnLocation] == 'Q')
  {
    WhiteQueenSideCastle = true;
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
  HalfMoveClock = stoi(SplitString[4]);
  FullMoveNumber = stoi(SplitString[5]);

  return;
}//end ForsythEdwardsNotationBoardInput

void BoardState::PrintMap()
{
  //print map
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
      cout << BoardMap[i][j].PieceType << BoardMap[i][j].PieceLocation.Row << BoardMap[i][j].PieceLocation.Column << " ";
    cout << endl;
  }//end for i

  //print other variables
  cout << "WhitesTurn: " << WhitesTurn << endl;
  cout << "WhiteKingSideCastle: " << WhiteKingSideCastle << endl;
  cout << "WhiteQueenSideCastle: " << WhiteQueenSideCastle << endl;
  cout << "BlackKingSideCastle: " << BlackKingSideCastle << endl;
  cout << "BlackQueenSideCastle: " << BlackQueenSideCastle << endl;
  cout << "EnPassantTarget: " << EnPassantTarget.Row << EnPassantTarget.Column << endl;
  cout << "HalfMoveClock: " << HalfMoveClock << endl;
  cout << "FullMoveNumber: " << FullMoveNumber << endl;

  return;
}//end PrintMap

void BoardState::PrintLocation(Location LocationtoPrint)
{
  //cout << "EmptySpace  " << BoardMap[LocationtoPrint.Row - '1'][LocationtoPrint.Column - 'a'].EmptySpace << endl;
  //cout << "WhitePieve  " << BoardMap[LocationtoPrint.Row - '1'][LocationtoPrint.Column - 'a'].WhitePiece << endl;
  //cout << "PieceType   " << BoardMap[LocationtoPrint.Row - '1'][LocationtoPrint.Column - 'a'].PieceType << endl;
  cout << "Row:" << BoardMap[LocationtoPrint.Row - '1'][LocationtoPrint.Column - 'a'].PieceLocation.Row << " Column:" << BoardMap[LocationtoPrint.Row - '1'][LocationtoPrint.Column - 'a'].PieceLocation.Column << endl;
  cout << "Row:" << (LocationtoPrint.Row - '1') << " Column:" << (LocationtoPrint.Column) << endl;
}//end PrintLocation

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
  return BoardMap[TargetLocation.Row - '1'][TargetLocation.Column - 'a'].EmptySpace;
}//end IsLocationEmpty

bool BoardState::IsPieceEnemy(Location MyPiece, Location OtherPiece)
{
  //test if I am white and they are black
  if (BoardMap[MyPiece.Row - '1'][MyPiece.Column - 'a'].PieceType < 'Z' && BoardMap[OtherPiece.Row - '1'][OtherPiece.Column - 'a'].PieceType > 'Z')
    return true;
  //test if I am black and they are white
  else if (BoardMap[MyPiece.Row - '1'][MyPiece.Column - 'a'].PieceType > 'Z' && BoardMap[OtherPiece.Row - '1'][OtherPiece.Column - 'a'].PieceType < 'Z' && BoardMap[OtherPiece.Row - '1'][OtherPiece.Column - 'a'].PieceType > 'A')
    return true;
  //not a enemy piece
  else
    return false;
}//end IsPieceEnemy

void BoardState::MovePiece(Location StartLocation, Location DestinationLocation)
{
  //vars
  ChessPiece TempPiece;
  TempPiece.EmptySpace = true;
  TempPiece.PieceType = '%';

  //move piece to destination
  BoardMap[DestinationLocation.Row - '1'][DestinationLocation.Column - 'a'] = BoardMap[StartLocation.Row - '1'][StartLocation.Column - 'a'];
  //reset locaiton moving from
  BoardMap[StartLocation.Row - '1'][StartLocation.Column - 'a'] = TempPiece;

  return;
}//end MovePiece

Location BoardState::EnPassantLocation()
{
  return EnPassantTarget;
}//end EnPassantValid