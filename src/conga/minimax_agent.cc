#include <conga/board.h>
#include <conga/minimax_agent.h>

#include <algorithm>
#include <functional>
#include <stack>

using namespace std;

namespace conga {

MinimaxAgent::MinimaxAgent(const Board::StoneType player_id, const Evaluation evaluation,
                           const size_t search_depth)
    : Agent(player_id), evaluation_(evaluation), search_depth_(search_depth) {}

MinimaxAgent::~MinimaxAgent() {}

const Player::Move MinimaxAgent::ComputeMove(const Board& board) const {
  auto best_move = kNoMove;
  AlphaBeta(board, search_depth_, INT_MIN, INT_MAX, best_move);
  return best_move;
}

const int MinimaxAgent::AlphaBeta(const Board& board, const int depth, int alpha, int beta,
                                  Move& best_move, const bool maximizing) const {
  auto valid_moves = ValidMoves(board, stone_type());
  if (depth == 0 || valid_moves.empty()) {
    return EvaluateState(board);
  }

  int value = 0;
  auto move = kNoMove;

  if (maximizing) {
    value = INT_MIN;

    for (const auto& valid_move : valid_moves) {
      auto new_board = Board(board);
      MakeMove(new_board, valid_move);
      int new_value = AlphaBeta(new_board, depth - 1, alpha, beta, best_move, false);

      if (new_value > value) {
        value = new_value;
        move = valid_move;
      }

      alpha = max(alpha, value);

      if (value >= beta) {
        break;
      }
    }
  } else {
    value = INT_MAX;

    for (const auto& valid_move : valid_moves) {
      auto new_board = Board(board);
      MakeMove(new_board, valid_move);
      int new_value = AlphaBeta(new_board, depth - 1, alpha, beta, best_move, true);

      if (new_value < value) {
        value = new_value;
        move = valid_move;
      }

      beta = min(beta, value);

      if (value <= alpha) {
        break;
      }
    }
  }

  best_move = move;
  return value;
}

const int MinimaxAgent::EvaluateState(const Board& board) const {
  if (evaluation_ == Evaluation::kPlayerMoves) {
    return ValidMoves(board, stone_type()).size();
  } else if (evaluation_ == Evaluation::kPlayerMinusOpponentMoves) {
    return ValidMoves(board, stone_type()).size() - ValidMoves(board, opponent_stone_type()).size();
  } else {
    return INT_MIN;
  }
}

}  // namespace conga
