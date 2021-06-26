#ifndef CONGA_MINIMAX_AGENT_ALPHA_BETA_PRUNING_H_
#define CONGA_MINIMAX_AGENT_ALPHA_BETA_PRUNING_H_

#include <conga/agent.h>
#include <conga/board.h>

#include <functional>

using namespace std;

namespace conga {

class MinimaxAgent : public Agent {
 public:
  enum class Evaluation {
    kPlayerMoves,
    kPlayerMinusOpponentMoves,
  };

  inline static constexpr size_t kDefaultSearchDepth = 3;

  MinimaxAgent(const Board::StoneType player_id,
               const Evaluation evaluation = Evaluation::kPlayerMoves,
               const size_t search_depth = kDefaultSearchDepth);
  virtual ~MinimaxAgent();

  const Action ComputeAction(const Board& board) const override;

 private:
  const int AlphaBeta(const Board& board, const int depth, int alpha, int beta,
                      Action& best_action, const bool maximizing = true) const;

  const int EvaluateState(const Board& board) const;

  const int NumOpponentMoves(const Board& board) const;

  Evaluation evaluation_;

  size_t search_depth_;
};

}  // namespace conga

#endif  // CONGA_MINIMAX_AGENT_ALPHA_BETA_PRUNING_H_
