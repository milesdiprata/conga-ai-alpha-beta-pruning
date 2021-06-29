#include "conga/minimax_agent.h"

#include <algorithm>
#include <cstddef>
#include <limits>
#include <vector>

#include "conga/board.h"

using namespace std;

namespace conga {

MinimaxAgent::MinimaxAgent(const Stone& stone, const Evaluation evaluation,
                           const std::size_t search_depth)
    : Agent(stone), evaluation_(evaluation), search_depth_(search_depth) {}

MinimaxAgent::~MinimaxAgent() {}

const Move MinimaxAgent::ComputeMove(const Board& board) const {
  return AlphaBetaSearch(board);
}

const Move MinimaxAgent::AlphaBetaSearch(const Board& board) const {
  int best_value = std::numeric_limits<int>::min();
  auto best_move = move::kNone;

  auto valid_moves = board.ValidMoves(stone());
  for (const auto& valid_move : valid_moves) {
    auto new_board = Board(board);
    new_board.MakeMove(valid_move);

    int value =
        MinValue(new_board, search_depth_, std::numeric_limits<int>::min(),
                 std::numeric_limits<int>::max());
    if (value > best_value) {
      best_value = value;
      best_move = valid_move;
    }
  }

  return best_move;
}

const int MinimaxAgent::MaxValue(const Board& board, const int depth, int alpha,
                                 int beta) const {
  auto valid_moves = board.ValidMoves(stone());
  if (CutoffTest(depth, valid_moves)) {
    return EvaluateState(board);
  }

  for (const auto& valid_move : valid_moves) {
    auto new_board = Board(board);
    new_board.MakeMove(valid_move);
    alpha = max(alpha, MinValue(new_board, depth - 1, alpha, beta));
    if (alpha >= beta) {
      return beta;
    }
  }

  return alpha;
}

const int MinimaxAgent::MinValue(const Board& board, const int depth, int alpha,
                                 int beta) const {
  auto valid_moves = board.ValidMoves(opponent_stone());
  if (CutoffTest(depth, valid_moves)) {
    return EvaluateState(board);
  }

  for (const auto& valid_move : valid_moves) {
    auto new_board = Board(board);
    new_board.MakeMove(valid_move);
    beta = min(beta, MaxValue(new_board, depth - 1, alpha, beta));
    if (beta <= alpha) {
      return alpha;
    }
  }

  return beta;
}

inline const bool MinimaxAgent::CutoffTest(const std::size_t depth,
                                           const vector<Move>& moves) {
  return depth == 0 || moves.empty();
}

const int MinimaxAgent::EvaluateState(const Board& board) const {
  if (evaluation_ == Evaluation::kPlayerMoves) {
    return kPlayerMovesWeight * board.ValidMoves(stone()).size();
  } else if (evaluation_ == Evaluation::kOpponentMoves) {
    return kOpponentMovesWeight * board.ValidMoves(opponent_stone()).size();
  } else if (evaluation_ == Evaluation::kPlayerMinusOpponentMoves) {
    return (kPlayerMovesWeight * board.ValidMoves(stone()).size()) +
           (kOpponentMovesWeight * board.ValidMoves(opponent_stone()).size());
  } else {
    return INT_MIN;
  }
}

}  // namespace conga
