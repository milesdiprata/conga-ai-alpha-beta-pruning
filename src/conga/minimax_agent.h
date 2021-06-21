#ifndef CONGA_MINIMAX_AGENT_ALPHA_BETA_PRUNING_H_
#define CONGA_MINIMAX_AGENT_ALPHA_BETA_PRUNING_H_

#include <conga/agent.h>
#include <conga/board.h>

#include <functional>

using namespace std;

namespace conga {

class MinimaxAgent : public Agent {
 public:
  MinimaxAgent(const Board::PlayerId player_id,
               const function<int(const Board& board)> f_evaluate);
  virtual ~MinimaxAgent();

  const Board::Move ComputeMove(const Board& board,
                                const Board::Point& point) const override;

 private:
  function<int(const Board& board)> f_evaluate_;
};

}  // namespace conga

#endif  // CONGA_MINIMAX_AGENT_ALPHA_BETA_PRUNING_H_
