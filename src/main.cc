#include <conga/board.h>
#include <conga/game.h>
#include <conga/minimax_agent.h>
#include <conga/random_agent.h>

int main(const int argc, const char* const argv[]) {
  auto player1 = conga::MinimaxAgent(
      conga::Board::StoneType::kBlack,
      conga::MinimaxAgent::Evaluation::kPlayerMinusOpponentMoves);
  auto player2 = conga::RandomAgent(conga::Board::StoneType::kWhite);
  auto board = conga::Board();

  auto game = conga::Game(&board, &player1, &player2);
  game.Play();

  return 0;
}