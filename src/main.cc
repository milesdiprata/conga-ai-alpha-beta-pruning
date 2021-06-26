#include <conga/board.h>
#include <conga/minimax_agent.h>
#include <conga/random_agent.h>

#include <iostream>

using namespace std;

int main(const int argc, const char* const argv[]) {
  auto player1 = conga::MinimaxAgent(conga::Board::StoneType::kBlack,
                                     conga::MinimaxAgent::Evaluation::kPlayerMinusOpponentMoves);
  auto player2 = conga::RandomAgent(conga::Board::StoneType::kWhite);

  auto board = conga::Board();
  cout << board << endl;

  int num_player1_moves = 0;
  while (1) {
    if (player1.Lost(board)) {
      cout << "Game Over: Player 1 lost." << endl;
      break;
    }

    auto player1_move = player1.ComputeMove(board);
    cout << "Player 1 move: " << player1_move << endl;
    player1.MakeMove(board, player1_move);
    ++num_player1_moves;
    cout << board << endl;

    if (player2.Lost(board)) {
      cout << "Game Over: Player 2 lost in " << num_player1_moves << " moves." << endl;
      break;
    }

    auto player2_move = player2.ComputeMove(board);
    cout << "Player 2 move: " << player2_move << endl;
    player2.MakeMove(board, player2_move);
    cout << board << endl;
  }

  return 0;
}