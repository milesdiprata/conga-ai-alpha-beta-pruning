#include <conga/board.h>
#include <conga/minimax_agent.h>
#include <time.h>

#include <algorithm>
#include <functional>
#include <memory>
#include <stack>

using namespace std;

namespace conga {

MinimaxAgent::MinimaxAgent(const Board::StoneType player_id,
                           const Evaluation evaluation,
                           const size_t search_depth)
    : Agent(player_id), evaluation_(evaluation), search_depth_(search_depth) {}

MinimaxAgent::~MinimaxAgent() {}

const Player::Move MinimaxAgent::ComputeMove(const Board& board) const {
  auto start_time = make_unique<time_t>();
  time(start_time.get());

  int best_value = INT_MIN;
  auto best_move = kNoMove;

  auto valid_moves = ValidMoves(board, stone_type());
  for (const auto& valid_move : valid_moves) {
    auto new_board = Board(board);
    MakeMove(new_board, valid_move);

    int value =
        IterativeDeepeningSearch(new_board, opponent_stone_type(), *start_time);

    // TODO: if (value >= value_cutoff) ?

    if (value > best_value) {
      best_value = value;
      best_move = valid_move;
    }
  }

  return best_move;
}

const int MinimaxAgent::IterativeDeepeningSearch(
    const Board& board, const Board::StoneType stone_type,
    const time_t& start_time) const {
  int value = 0;
  int depth = 1;

  bool time_cutoff = false;

  while (1) {
    auto result = AlphaBeta(board, depth, INT_MIN, INT_MAX, stone_type,
                            start_time, time_cutoff);

    // TODO: if (value >= value_cutoff) ?

    if (time_cutoff) {
      break;
    }

    value = result.value;

    // if (!result.remaining) {
    //   break;
    // }

    ++depth;
  }

  return value;
}

const MinimaxAgent::SearchResult MinimaxAgent::AlphaBeta(
    const Board& board, const int depth, int alpha, int beta,
    const Board::StoneType stone_type, const time_t& start_time,
    bool& time_cutoff) const {
  auto valid_moves = ValidMoves(board, stone_type);

  if (difftime(time(NULL), start_time) > kSearchTimeLimitSecs) {
    time_cutoff = true;
  }

  if (depth == 0 || valid_moves.empty() || time_cutoff) {
    return SearchResult(EvaluateState(board), true);
  }

  bool any_remaining = false;

  if (stone_type == Player::stone_type()) {
    int value = INT_MIN;

    for (const auto& valid_move : valid_moves) {
      auto new_board = Board(board);
      MakeMove(new_board, valid_move);
      auto result =
          AlphaBeta(new_board, depth - 1, alpha, beta,
                    Player::opponent_stone_type(), start_time, time_cutoff);
      value = max(value, result.value);

      if (value >= beta) {
        break;
      }

      alpha = max(alpha, value);

      // if (result.remaining) {
      //   any_remaining = true;
      // }
    }

    return SearchResult(value, any_remaining);
  } else {
    int value = INT_MAX;

    for (const auto& valid_move : valid_moves) {
      auto new_board = Board(board);
      MakeMove(new_board, valid_move);
      auto result = AlphaBeta(new_board, depth - 1, alpha, beta,
                              Player::stone_type(), start_time, time_cutoff);
      value = min(value, result.value);

      if (value <= alpha) {
        break;
      }

      beta = min(beta, value);

      // if (result.remaining) {
      //   any_remaining = true;
      // }
    }

    return SearchResult(value, any_remaining);
  }
}

const int MinimaxAgent::EvaluateState(const Board& board) const {
  if (evaluation_ == Evaluation::kPlayerMoves) {
    return ValidMoves(board, stone_type()).size();
  } else if (evaluation_ == Evaluation::kOpponentMoves) {
    return -1 * ValidMoves(board, opponent_stone_type()).size();
  } else if (evaluation_ == Evaluation::kPlayerMinusOpponentMoves) {
    return ValidMoves(board, stone_type()).size() -
           ValidMoves(board, opponent_stone_type()).size();
  } else {
    return INT_MIN;
  }
}

}  // namespace conga
