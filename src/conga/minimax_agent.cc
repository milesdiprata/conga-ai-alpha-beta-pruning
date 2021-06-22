#include <conga/board.h>
#include <conga/minimax_agent.h>

#include <functional>

using namespace std;

namespace conga {

MinimaxAgent::MinimaxAgent(const Board::StoneType player_id,
                           const function<int(const Board& board)> f_evaluate)
    : Agent(player_id), f_evaluate_(f_evaluate) {}

MinimaxAgent::~MinimaxAgent() {}

const Board::Move MinimaxAgent::ComputeMove(const Board& board,
                                            const Board::Point& point) const {
  return Board::Move::kNone;
}

}  // namespace conga
