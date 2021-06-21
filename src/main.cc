#include <conga/agent.h>
#include <conga/board.h>
#include <conga/player.h>

#include <iostream>

using namespace std;

int main(const int argc, const char* const argv[]) {
  auto player1 = conga::Agent(conga::Board::PlayerId::k1);
  auto player2 = conga::Agent(conga::Board::PlayerId::k1);

  auto board = conga::Board();
  board.At(1, 3) = conga::Board::Cell(conga::Board::PlayerId::k2, 5);
  board.At(2, 3) = conga::Board::Cell(conga::Board::PlayerId::k2, 5);
  board.At(2, 4) = conga::Board::Cell(conga::Board::PlayerId::k2, 5);
  cout << board << endl;

  player1.MakeMove(board, conga::Board::Point(1, 4),
                   conga::Board::Move::kRight);
  cout << board << endl;

  return 0;
}