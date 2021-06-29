#include <memory>

#include "conga/board.h"
#include "conga/game.h"
#include "conga/minimax_agent.h"
#include "conga/random_agent.h"
#include "conga/stone.h"

int main(const int argc, const char* const argv[]) {
  auto game = conga::Game(
      std::make_unique<conga::Board>(),
      std::make_unique<conga::MinimaxAgent>(
          conga::Stone::kBlack,
          conga::MinimaxAgent::Evaluation::kPlayerMinusOpponentMoves),
      std::make_unique<conga::RandomAgent>(conga::Stone::kWhite));
  game.Play();

  return 0;
}