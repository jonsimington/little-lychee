// AI
// This is where you build your AI

#include "ai.hpp"

// You can add #includes here for your AI.

namespace cpp_client
{

namespace chess
{
//Global Vars
//MoveGenerator MasterList = MoveGenerator(BoardState());

/// <summary>
/// This returns your AI's name to the game server.
/// Replace the string name.
/// </summary>
/// <returns>The name of your AI.</returns>
std::string AI::get_name() const
{
    // REPLACE WITH YOUR TEAM NAME!
    return "Last Pawn Standing";
}

/// <summary>
/// This is automatically called when the game first starts, once the game objects are created
/// </summary>
void AI::start()
{
    // This is a good place to initialize any variables
    srand(time(NULL));

    // //set initial board state and add to master list
    // cout << "loading";
    // BoardState StartingBoard;
    // StartingBoard.ForsythEdwardsNotationBoardInput("");
    // //MasterList = MoveGenerator(StartingBoard);
    // cout << "----loading finished" << endl;
    // //StartingBoard.PrintMap();
    // cout << "printed" << endl;
}

/// <summary>
/// This is automatically called the game (or anything in it) updates
/// </summary>
void AI::game_updated()
{
    // If a function you call triggers an update this will be called before it returns.
}

/// <summary>
/// This is automatically called when the game ends.
/// </summary>
/// <param name="won">true if you won, false otherwise</param>
/// <param name="reason">An explanation for why you either won or lost</param>
void AI::ended(bool won, const std::string& reason)
{
    // You can do any cleanup of your AI here.  The program ends when this function returns.
}

/// <summary>
/// This is called every time it is this AI.player's turn.
/// </summary>
/// <returns>Represents if you want to end your turn. True means end your turn, False means to keep your turn going and re-call this function.</returns>
bool AI::run_turn()
{
    MoveGenerator MasterList = MoveGenerator(BoardState());
    //set initial board state and add to master list
    //cout << "loading";
    BoardState StartingBoard = BoardState();
    StartingBoard.ForsythEdwardsNotationBoardInput(game->fen);
    MasterList = MoveGenerator(StartingBoard);
    //cout << "----loading finished" << endl;
    //StartingBoard.PrintMap();
    //cout << "printed" << endl;

    // Here is where you'll want to code your AI.
    //cout << "in my turn" << endl;

    // We've provided sample code that:
    //    1) prints the board to the console
    //    2) prints the opponent's last move to the console
    //    3) prints how much time remaining this AI has to calculate moves
    //    4) makes a random (and probably invalid) move.

    // 1) print the board to the console
    print_current_board();

    // 2) print the opponent's last move to the console
    // if(game->moves.size() > 0)
    // {
    //     std::cout << "Opponent's Last Move: '" << game->moves[game->moves.size() - 1]->san << "'" << std::endl;
    // }

    // // 3) print how much time remaining this AI has to calculate moves
    // std::cout << "Time Remaining: " << player->time_remaining << " ns" << std::endl;

    //cout << "Test:" << player->rank_direction << ":Color:" << player->color << endl;

    // 4) make a random (and probably invalid) move.
    // chess::Piece random_piece = player->pieces[rand() % player->pieces.size()];
    // std::string random_file(1, 'a' + rand() % 8);
    // int random_rank = (rand() % 8) + 1;
    // random_piece->move(random_file, random_rank);
    // while (!player->made_move)
    // {
    //     cout << "end test2" << endl;
    //     chess::Piece random_pawn = player->pieces[rand() % player->pieces.size()];
    //     cout << random_pawn->file << " " << (random_pawn->rank + player->rank_direction) << endl;
    //     if (random_pawn->type == "Pawn")
    //         random_pawn->move(random_pawn->file, random_pawn->rank + player->rank_direction);
    // }//end while
    //  cout << "end test" << endl;

    //generate possible moves for my pieces
    for (int i = 0; i < player->pieces.size(); i++)
    {
        //cout << i << endl;
        MasterList.GenerateMoves(Location(static_cast<char>(player->pieces[i]->rank + '0'), player->pieces[i]->file[0]), i, player->rank_direction, player->pieces[i]->has_moved, player->pieces[i]->type);
    }//end for
    int ListId = 0;
    Location DestinationLocation = MasterList.RandomMove(ListId);
    player->pieces[ListId]->move(string(1, DestinationLocation.Column), (DestinationLocation.Row - '0'), "Queen");

    return true; // to signify we are done with our turn.
}

/// <summary>
///  Prints the current board using pretty ASCII art
/// </summary>
/// <remarks>
/// Note: you can delete this function if you wish
/// </remarks>
void AI::print_current_board()
{
    for(int rank = 9; rank >= -1; rank--)
    {
        std::string str = "";
        if(rank == 9 || rank == 0) // then the top or bottom of the board
        {
            str = "   +------------------------+";
        }
        else if(rank == -1) // then show the ranks
        {
            str = "     a  b  c  d  e  f  g  h";
        }
        else // board
        {
            str += " ";
            str += std::to_string(rank);
            str += " |";
            // fill in all the files with pieces at the current rank
            for(int file_offset = 0; file_offset < 8; file_offset++)
            {
                std::string file(1, 'a' + file_offset); // start at a, with with file offset increasing the char;
                chess::Piece current_piece = nullptr;
                for(const auto& piece : game->pieces)
                {
                    if(piece->file == file && piece->rank == rank) // then we found the piece at (file, rank)
                    {
                        current_piece = piece;
                        break;
                    }
                }

                char code = '.'; // default "no piece";
                if(current_piece != nullptr)
                {
                    code = current_piece->type[0];

                    if(current_piece->type == "Knight") // 'K' is for "King", we use 'N' for "Knights"
                    {
                        code = 'N';
                    }

                    if(current_piece->owner->id == "1") // the second player (black) is lower case. Otherwise it's upppercase already
                    {
                        code = tolower(code);
                    }
                }

                str += " ";
                str += code;
                str += " ";
            }

            str += "|";
        }

        std::cout << str << std::endl;
    }
}

// You can add additional methods here for your AI to call

} // chess

} // cpp_client
