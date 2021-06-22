#include <conga/board.h>
#include <conga/minimax_agent.h>

#include <functional>

using namespace std;

namespace conga {

MinimaxAgent::MinimaxAgent(
    const Board::StoneType player_id,
    const function<const int(const Board& board)> f_evaluate)
    : Agent(player_id), f_evaluate_(f_evaluate) {}

MinimaxAgent::~MinimaxAgent() {}

const Agent::Action MinimaxAgent::ComputeAction(const Board& board) const {
  return kNoAction;
}

}  // namespace conga
