#include <conga/agent.h>
#include <conga/board.h>
#include <conga/move.h>
#include <conga/random_agent.h>
#include <conga/stone.h>

#include <iterator>
#include <random>

namespace conga {

RandomAgent::RandomAgent(const Stone& stone) : Agent(stone) {}

RandomAgent::~RandomAgent() {}

const Move RandomAgent::ComputeMove(const Board& board) const {
  auto valid_moves = board.ValidMoves(stone());
  if (valid_moves.empty()) {
    return move::kNoMove;
  }

  static auto random_device = std::random_device();
  static auto generator = std::mt19937(random_device());

  auto distribution = std::uniform_int_distribution<>(
      0, std::distance(valid_moves.begin(), valid_moves.end()) - 1);

  auto it = valid_moves.begin();
  std::advance(it, distribution(generator));

  return *it;
}

}  // namespace conga
