#ifndef CONGA_MINIMAX_AGENT_ALPHA_BETA_PRUNING_H_
#define CONGA_MINIMAX_AGENT_ALPHA_BETA_PRUNING_H_

#include <conga/agent.h>
#include <conga/board.h>

#include <functional>

using namespace std;

namespace conga {

class MinimaxAgent : public Agent {
 public:
  enum class EvaluationFunction {
    kMinimizeOpponentMoves,
  };

  MinimaxAgent(const Board::StoneType player_id,
               const EvaluationFunction evaluation_function =
                   EvaluationFunction::kMinimizeOpponentMoves);
  virtual ~MinimaxAgent();

  const Action ComputeAction(const Board& board) const override;

 private:
  const int AlphaBeta(const Board& board, const int depth, int& alpha,
                      int& beta, Action& best_action,
                      const bool maximizing) const;

  const int EvaluateState(const Board& board) const;

  const int NumOpponentMoves(const Board& board) const;

  EvaluationFunction evaluation_function_;

  bool maximize_evaluation_;
};

}  // namespace conga

#endif  // CONGA_MINIMAX_AGENT_ALPHA_BETA_PRUNING_H_
