#ifndef CONGA_MINIMAX_AGENT_ALPHA_BETA_PRUNING_H_
#define CONGA_MINIMAX_AGENT_ALPHA_BETA_PRUNING_H_

#include <conga/agent.h>
#include <conga/board.h>
#include <conga/move.h>
#include <conga/stone.h>

#include <cstddef>
#include <vector>

namespace conga {

class MinimaxAgent : public Agent {
 public:
  enum class Evaluation {
    kPlayerMoves,
    kOpponentMoves,
    kPlayerMinusOpponentMoves,
  };

  static constexpr std::size_t kDefaultSearchDepth = 3;
  static constexpr int kPlayerMovesWeight = 1;
  static constexpr int kOpponentMovesWeight = -2;
  static constexpr double kSearchTimeLimitSecs = 1.0;

  MinimaxAgent(
      const Stone& stone,
      const Evaluation evaluation = Evaluation::kPlayerMinusOpponentMoves,
      const std::size_t search_depth = kDefaultSearchDepth);
  virtual ~MinimaxAgent();

  const Move ComputeMove(const Board& board) const override;

 private:
  const Move AlphaBetaSearch(const Board& board) const;

  const int MaxValue(const Board& board, const int depth, int alpha,
                     int beta) const;

  const int MinValue(const Board& board, const int depth, int alpha,
                     int beta) const;

  static const bool CutoffTest(const std::size_t depth,
                               const std::vector<Move>& moves);

  const int EvaluateState(const Board& board) const;

  Evaluation evaluation_;

  std::size_t search_depth_;
};

}  // namespace conga

#endif  // CONGA_MINIMAX_AGENT_ALPHA_BETA_PRUNING_H_
