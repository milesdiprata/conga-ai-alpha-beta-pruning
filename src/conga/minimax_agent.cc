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
  // auto best_move = kNoMove;
  // int depth = 1;

  // auto start_time = make_unique<time_t>();
  // time(start_time.get());

  // while (difftime(time(NULL), *start_time) <= kSearchTimeLimitSecs) {
  //   auto result =
  //       AlphaBeta(board, search_depth_, INT_MIN, INT_MAX, *start_time);
  //   best_move = result.move;

  //   if (!result.remaining) {
  //     break;
  //   }

  //   ++depth;
  // }

  // cout << "depth: " << depth << endl;
  // return best_move;

  int best_value = INT_MIN;
  auto best_move = kNoMove;

  auto valid_moves = ValidMoves(board, stone_type());
  for (const auto& valid_move : valid_moves) {
    auto new_board = Board(board);
    MakeMove(new_board, valid_move);

    int value = AlphaBeta(new_board, search_depth_, INT_MIN, INT_MAX,
                          opponent_stone_type());

    // TODO: if (value >= value_cutoff) ?

    if (value > best_value) {
      best_value = value;
      best_move = valid_move;
    }
  }

  return best_move;
}

const int MinimaxAgent::AlphaBeta(const Board& board, const int depth,
                                  int alpha, int beta,
                                  const Board::StoneType stone_type) const {
  auto valid_moves = ValidMoves(board, stone_type);

  if (depth == 0 || valid_moves.empty()) {
    return EvaluateState(board);
  } else if (stone_type == Player::stone_type()) {
    int value = INT_MIN;

    for (const auto& valid_move : valid_moves) {
      auto new_board = Board(board);
      MakeMove(new_board, valid_move);
      value = max(value, AlphaBeta(new_board, depth - 1, alpha, beta,
                                   Player::opponent_stone_type()));

      if (value >= beta) {
        break;
      }

      alpha = max(alpha, value);
    }

    return value;
  } else {
    int value = INT_MAX;

    for (const auto& valid_move : valid_moves) {
      auto new_board = Board(board);
      MakeMove(new_board, valid_move);
      value = min(value, AlphaBeta(new_board, depth - 1, alpha, beta,
                                   Player::stone_type()));

      if (value <= alpha) {
        break;
      }

      beta = min(beta, value);
    }

    return value;
  }
}

const int MinimaxAgent::EvaluateState(const Board& board) const {
  if (evaluation_ == Evaluation::kPlayerMoves) {
    return ValidMoves(board, stone_type()).size();
  } else if (evaluation_ == Evaluation::kPlayerMinusOpponentMoves) {
    return ValidMoves(board, stone_type()).size() -
           ValidMoves(board, opponent_stone_type()).size();
  } else {
    return INT_MIN;
  }
}

}  // namespace conga
