#include <conga/board.h>
#include <conga/minimax_agent.h>

#include <algorithm>
#include <functional>
#include <stack>

using namespace std;

namespace conga {

MinimaxAgent::MinimaxAgent(const Board::StoneType player_id,
                           const EvaluationFunction evaluation_function,
                           const size_t search_depth)
    : Agent(player_id),
      evaluation_function_(evaluation_function),
      search_depth_(search_depth) {}

MinimaxAgent::~MinimaxAgent() {}

const Agent::Action MinimaxAgent::ComputeAction(const Board& board) const {
  auto best_action = kNoAction;
  AlphaBeta(board, search_depth_, INT_MIN, INT_MAX, best_action);
  return best_action;
}

const int MinimaxAgent::AlphaBeta(const Board& board, const int depth,
                                  int alpha, int beta, Action& best_action,
                                  const bool maximizing) const {
  auto valid_actions = ValidActions(board, stone_type());
  if (depth == 0 || valid_actions.empty()) {
    return EvaluateState(board);
  }

  if (maximizing) {
    int value = INT_MIN;
    auto action = kNoAction;

    for (const auto& valid_action : valid_actions) {
      auto new_board = Board(board);
      MakeMove(new_board, valid_action.point, valid_action.move);
      int new_value =
          AlphaBeta(new_board, depth - 1, alpha, beta, best_action, false);

      if (new_value > value) {
        value = new_value;
        action = valid_action;
      }

      alpha = max(alpha, value);

      if (value >= beta) {
        break;
      }
    }

    best_action = action;
    return value;
  } else {
    int value = INT_MAX;
    auto action = kNoAction;

    for (const auto& valid_action : valid_actions) {
      auto new_board = Board(board);
      MakeMove(new_board, valid_action.point, valid_action.move);
      int new_value =
          AlphaBeta(new_board, depth - 1, alpha, beta, best_action, true);

      if (new_value < value) {
        value = new_value;
        action = valid_action;
      }

      beta = min(beta, value);

      if (value <= alpha) {
        break;
      }
    }

    best_action = action;
    return value;
  }
}

const int MinimaxAgent::EvaluateState(const Board& board) const {
  if (evaluation_function_ == EvaluationFunction::kMaximizePlayerMoves) {
    return ValidActions(board, stone_type()).size();
  } else if (evaluation_function_ ==
             EvaluationFunction::kPlayerMinusOpponentMoves) {
    return ValidActions(board, stone_type()).size() -
           ValidActions(board, opponent_stone_type()).size();
  } else {
    return INT_MIN;
  }
}

}  // namespace conga
