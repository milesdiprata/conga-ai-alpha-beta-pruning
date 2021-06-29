#ifndef CONGA_MINIMAX_AGENT_ALPHA_BETA_PRUNING_H_
#define CONGA_MINIMAX_AGENT_ALPHA_BETA_PRUNING_H_

#include <cstddef>
#include <ctime>
#include <vector>

#include "conga/agent.h"
#include "conga/board.h"
#include "conga/move.h"
#include "conga/stone.h"

namespace conga {

class MinimaxAgent : public Agent {
 public:
  enum class Evaluation {
    kPlayerMoves,
    kOpponentMoves,
    kPlayerMinusOpponentMoves,
  };

  static constexpr int kPlayerMovesWeight = 1;
  static constexpr int kOpponentMovesWeight = -5;
  static constexpr double kDeafultSearchTimeLimitMillis = 1000.0;
  static constexpr int kMillisPerSecond = 1000;

  MinimaxAgent(
      const Stone& stone,
      const Evaluation evaluation = Evaluation::kPlayerMinusOpponentMoves,
      const double search_time_limit_millis = kDeafultSearchTimeLimitMillis);
  virtual ~MinimaxAgent();

  const Move ComputeMove(const Board& board) const override;

 private:
  const Move IterativeDeepeningSearch(const Board& board) const;

  const Move AlphaBetaSearch(const Board& board, const std::size_t depth,
                             const std::clock_t clock_start,
                             std::size_t& num_explored) const;

  const int MaxValue(const Board& board, const int depth, int alpha, int beta,
                     const std::clock_t clock_start,
                     std::size_t& num_explored) const;

  const int MinValue(const Board& board, const int depth, int alpha, int beta,
                     const std::clock_t clock_start,
                     std::size_t& num_explored) const;

  const bool TimeCutoff(const std::clock_t clock_start) const;

  static const double ElapsedTimeMillis(const std::clock_t clock_start);

  static const bool CutoffTest(const std::size_t depth,
                               const std::vector<Move>& moves);

  const int EvaluateState(const Board& board) const;

  Evaluation evaluation_;

  double search_time_limit_millis_;
};

}  // namespace conga

#endif  // CONGA_MINIMAX_AGENT_ALPHA_BETA_PRUNING_H_
