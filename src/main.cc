#include <conga/board.h>
#include <conga/random_agent.h>

#include <iostream>

using namespace std;

int main(const int argc, const char* const argv[]) {
  auto player1 = conga::RandomAgent(conga::Board::StoneType::kBlack);
  auto player2 = conga::RandomAgent(conga::Board::StoneType::kWhite);

  auto board = conga::Board();
  // board.At(1, 3) = conga::Board::Cell(conga::Board::StoneType::kWhite, 5);
  // board.At(2, 3) = conga::Board::Cell(conga::Board::StoneType::kWhite, 5);
  // board.At(2, 4) = conga::Board::Cell(conga::Board::StoneType::kWhite, 5);
  cout << board << endl;

  for (int i = 0; i < 100; ++i)
    cout << player1.ComputeMove(board, conga::Board::Point(1, 4)) << endl;

  return 0;
}