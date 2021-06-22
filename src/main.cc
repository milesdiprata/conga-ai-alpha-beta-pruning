#include <conga/board.h>
#include <conga/minimax_agent.h>
#include <conga/random_agent.h>

#include <iostream>

using namespace std;

int main(const int argc, const char* const argv[]) {
  auto player1 = conga::MinimaxAgent(
      conga::Board::StoneType::kBlack,
      conga::MinimaxAgent::EvaluationFunction::kMinimizeOpponentMoves);
  auto player2 = conga::MinimaxAgent(
      conga::Board::StoneType::kWhite,
      conga::MinimaxAgent::EvaluationFunction::kMinimizeOpponentMoves);
  // auto player2 = conga::RandomAgent(conga::Board::StoneType::kWhite);

  auto board = conga::Board();
  // board.At(2, 4) = conga::Board::Cell(conga::Board::StoneType::kWhite, 1);
  // board.At(1, 3) = conga::Board::Cell(conga::Board::StoneType::kWhite, 1);
  // board.At(2, 3) = conga::Board::Cell(conga::Board::StoneType::kWhite, 1);
  cout << board << endl;

  while (!player1.Lost(board) && !player2.Lost(board)) {
    // cin.get();
    auto player1_action = player1.ComputeAction(board);
    cout << "Player 1 action: " << player1_action << endl;
    player1.MakeMove(board, player1_action.point, player1_action.move);
    cout << board << endl;

    // cin.get();
    auto player2_action = player2.ComputeAction(board);
    cout << "Player 2 action: " << player2_action << endl;
    player2.MakeMove(board, player2_action.point, player2_action.move);
    cout << board << endl;
  }

  if (player1.Lost(board)) {
    cout << "Player 1 lost" << endl;
  } else {
    cout << "Player 2 lost" << endl;
  }

  return 0;
}