// #ifndef CONGA_MINIMAX_AGENT_ALPHA_BETA_PRUNING_H_
// #define CONGA_MINIMAX_AGENT_ALPHA_BETA_PRUNING_H_

// #include <conga/agent.h>
// #include <conga/board.h>
// #include <time.h>

// #include <vector>

// using namespace std;

// namespace conga {

// class MinimaxAgent : public Agent {
//  public:
//   enum class Evaluation {
//     kPlayerMoves,
//     kOpponentMoves,
//     kPlayerMinusOpponentMoves,
//   };

//   inline static constexpr int kDefaultSearchDepth = 3;

//   inline static constexpr double kSearchTimeLimitSecs = 1.0;

//   MinimaxAgent(const Board::StoneType player_id,
//                const Evaluation evaluation = Evaluation::kPlayerMoves,
//                const size_t search_depth = kDefaultSearchDepth);
//   virtual ~MinimaxAgent();

//   const Move ComputeMove(const Board& board) const override;

//  private:
//   struct SearchResult {
//     inline SearchResult(const int value, const Move& move, const bool
//     remaining)
//         : value(value), move(move), remaining(remaining) {}
//     inline ~SearchResult() {}

//     int value;
//     Move move;
//     bool remaining;
//   };

//   const Move AlphaBetaSearch(const Board& board) const;

//   const int MaxValue(const Board& board, const int depth, int alpha,
//                      int beta) const;

//   const int MinValue(const Board& board, const int depth, int alpha,
//                      int beta) const;

//   static const bool CutoffTest(const int depth, const vector<Move>& moves);

//   const int IterativeDeepeningSearch(const Board& board,
//                                      const Board::StoneType stone_type,
//                                      const time_t& start_time) const;

//   const SearchResult AlphaBeta(const Board& board, const int depth, int
//   alpha,
//                                int beta, const bool maximizing = true) const;

//   const int EvaluateState(const Board& board) const;

//   const int NumOpponentMoves(const Board& board) const;

//   Evaluation evaluation_;

//   size_t search_depth_;
// };

// }  // namespace conga

// #endif  // CONGA_MINIMAX_AGENT_ALPHA_BETA_PRUNING_H_
