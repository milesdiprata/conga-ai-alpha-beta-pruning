#include <conga/board.h>
#include <conga/minimax_agent.h>

#include <algorithm>
#include <functional>

using namespace std;

namespace conga {

MinimaxAgent::MinimaxAgent(
    const Board::StoneType player_id,
    const function<const int(const Board& board)> f_evaluate)
    : Agent(player_id), f_evaluate_(f_evaluate) {}

MinimaxAgent::~MinimaxAgent() {}

const Agent::Action MinimaxAgent::ComputeAction(const Board& board) const {
  auto valid_actions = ValidActions(board);
  if (valid_actions.empty()) {
    return kNoAction;
  }

  return *max_element(valid_actions.begin(), valid_actions.end(),
                      [](const Action& a1, const Action& a2) -> const bool {
                        return a1.value > a2.value;
                      });
}

}  // namespace conga
