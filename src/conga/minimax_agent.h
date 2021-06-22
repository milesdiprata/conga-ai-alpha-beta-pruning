#ifndef CONGA_MINIMAX_AGENT_ALPHA_BETA_PRUNING_H_
#define CONGA_MINIMAX_AGENT_ALPHA_BETA_PRUNING_H_

#include <conga/agent.h>
#include <conga/board.h>

#include <functional>

using namespace std;

namespace conga {

class MinimaxAgent : public Agent {
 public:
  MinimaxAgent(const Board::StoneType player_id,
               const function<const int(const Board& board)> f_evaluate);
  virtual ~MinimaxAgent();

  const Action ComputeAction(const Board& board) const override;

 private:
  function<const int(const Board& board)> f_evaluate_;
};

}  // namespace conga

#endif  // CONGA_MINIMAX_AGENT_ALPHA_BETA_PRUNING_H_
