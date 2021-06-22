#include <conga/board.h>
#include <conga/random_agent.h>

#include <random>

using namespace std;

namespace conga {

RandomAgent::RandomAgent(const Board::StoneType stone_type)
    : Agent(stone_type) {}

RandomAgent::~RandomAgent() {}

const Agent::Action RandomAgent::ComputeAction(const Board& board) const {
  auto valid_actions = ValidActions(board, stone_type());
  if (valid_actions.empty()) {
    return kNoAction;
  }

  static auto rand_device = random_device();
  static auto generator = mt19937(rand_device());
  auto distribution = uniform_int_distribution<>(
      0, distance(valid_actions.begin(), valid_actions.end()) - 1);
  auto it = valid_actions.begin();
  advance(it, distribution(generator));

  return *it;
}

}  // namespace conga
