#include <conga/board.h>
#include <conga/point.h>
// #include <conga/game.h>
// #include <conga/minimax_agent.h>
// #include <conga/random_agent.h>

#include <iostream>
using namespace std;
using namespace conga;

int main(const int argc, const char* const argv[]) {
  // auto player1 = conga::MinimaxAgent(
  //     conga::Board::StoneType::kBlack,
  //     conga::MinimaxAgent::Evaluation::kPlayerMinusOpponentMoves);
  // auto player2 = conga::RandomAgent(conga::Board::StoneType::kWhite);
  auto board = Board();
  cout << board << endl;

  board.MakeMove(Move(Point(1, 4), conga::direction::kRight));
  cout << board << endl;

  board.MakeMove(Move(Point(2, 4), conga::direction::kDown));
  board.MakeMove(Move(Point(3, 4), conga::direction::kDown));
  board.MakeMove(Move(Point(4, 4), conga::direction::kDown));
  cout << board << endl;

  board.MakeMove(Move(Point(4, 2), conga::direction::kDownLeft));
  cout << board << endl;

  board.MakeMove(Move(Point(3, 1), conga::direction::kUp));
  cout << board << endl;

  // auto game = conga::Game(&board, &player1, &player2);
  // game.Play();

  return 0;
}