#include "conga/minimax_agent.h"

#include <algorithm>
#include <limits>

#include "conga/board.h"

namespace conga {

MinimaxAgent::MinimaxAgent(const Stone& stone, const Evaluation evaluation,
                           const double search_time_limit_millis)
    : Agent(stone),
      evaluation_(evaluation),
      search_time_limit_millis_(search_time_limit_millis) {}

MinimaxAgent::~MinimaxAgent() {}

const Move MinimaxAgent::ComputeMove(const Board& board) const {
  return IterativeDeepeningSearch(board);
}

const Move MinimaxAgent::IterativeDeepeningSearch(const Board& board) const {
  std::clock_t clock_start = std::clock();
  std::size_t depth = 1;

  auto best_move = move::kNone;

  while (1) {
    auto move = AlphaBetaSearch(board, depth, clock_start);

    if (TimeCutoff(clock_start)) {
      std::cout << "Elapsed time: " << ElapsedTimeMillis(clock_start) << "ms"
                << std::endl;
      std::cout << "Depth: " << depth << std::endl;
      break;
    }

    best_move = move;

    ++depth;
  }

  return best_move;
}

const Move MinimaxAgent::AlphaBetaSearch(const Board& board,
                                         const std::size_t depth,
                                         const std::clock_t clock_start) const {
  int best_value = std::numeric_limits<int>::min();
  auto best_move = move::kNone;

  auto valid_moves = board.ValidMoves(stone());
  for (const auto& valid_move : valid_moves) {
    auto new_board = Board(board);
    new_board.MakeMove(valid_move);

    int value = MinValue(new_board, depth, std::numeric_limits<int>::min(),
                         std::numeric_limits<int>::max(), clock_start);
    if (value > best_value) {
      best_value = value;
      best_move = valid_move;
    }
  }

  return best_move;
}

const int MinimaxAgent::MaxValue(const Board& board, const int depth, int alpha,
                                 int beta,
                                 const std::clock_t clock_start) const {
  auto valid_moves = board.ValidMoves(stone());
  if (CutoffTest(depth, valid_moves) || TimeCutoff(clock_start)) {
    return EvaluateState(board);
  }

  // TODO: Increment number of explored nodes

  for (const auto& valid_move : valid_moves) {
    auto new_board = Board(board);
    new_board.MakeMove(valid_move);
    alpha = std::max(alpha,
                     MinValue(new_board, depth - 1, alpha, beta, clock_start));
    if (alpha >= beta) {
      return beta;
    }
  }

  return alpha;
}

const int MinimaxAgent::MinValue(const Board& board, const int depth, int alpha,
                                 int beta,
                                 const std::clock_t clock_start) const {
  auto valid_moves = board.ValidMoves(opponent_stone());
  if (CutoffTest(depth, valid_moves) || TimeCutoff(clock_start)) {
    return EvaluateState(board);
  }

  // TODO: Increment number of explored nodes

  for (const auto& valid_move : valid_moves) {
    auto new_board = Board(board);
    new_board.MakeMove(valid_move);
    beta = std::min(beta,
                    MaxValue(new_board, depth - 1, alpha, beta, clock_start));
    if (beta <= alpha) {
      return alpha;
    }
  }

  return beta;
}

const bool MinimaxAgent::TimeCutoff(const std::clock_t clock_start) const {
  return ElapsedTimeMillis(clock_start) > search_time_limit_millis_;
}

const double MinimaxAgent::ElapsedTimeMillis(const std::clock_t clock_start) {
  return ((double)kMillisPerSecond * (std::clock() - clock_start) /
          CLOCKS_PER_SEC);
}

inline const bool MinimaxAgent::CutoffTest(const std::size_t depth,
                                           const std::vector<Move>& moves) {
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
