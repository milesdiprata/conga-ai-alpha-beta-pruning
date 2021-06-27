#ifndef CONGA_MINIMAX_AGENT_ALPHA_BETA_PRUNING_H_
#define CONGA_MINIMAX_AGENT_ALPHA_BETA_PRUNING_H_

#include <conga/agent.h>
#include <conga/board.h>
#include <time.h>

using namespace std;

namespace conga {

class MinimaxAgent : public Agent {
 public:
  enum class Evaluation {
    kPlayerMoves,
    kPlayerMinusOpponentMoves,
  };

  inline static constexpr int kDefaultSearchDepth = 3;

  inline static constexpr double kSearchTimeLimitSecs = 5.0;

  MinimaxAgent(const Board::StoneType player_id,
               const Evaluation evaluation = Evaluation::kPlayerMoves,
               const size_t search_depth = kDefaultSearchDepth);
  virtual ~MinimaxAgent();

  const Move ComputeMove(const Board& board) const override;

 private:
  struct AlphaBetaResult {
    AlphaBetaResult(const int value, const Move& move);
    virtual ~AlphaBetaResult();

    int value;
    Move move;
  };

  struct IterDeepeningResult : public AlphaBetaResult {
    IterDeepeningResult(const int value = 0, const Move& move = kNoMove,
                        const bool remaining = false);
    virtual ~IterDeepeningResult();

    bool remaining;
  };

  const int AlphaBeta(const Board& board, const int depth, int alpha, int beta,
                      const Board::StoneType stone_type) const;

  const int EvaluateState(const Board& board) const;

  const int NumOpponentMoves(const Board& board) const;

  Evaluation evaluation_;

  size_t search_depth_;
};

}  // namespace conga

#endif  // CONGA_MINIMAX_AGENT_ALPHA_BETA_PRUNING_H_
