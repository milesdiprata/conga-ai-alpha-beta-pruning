#include <conga/board.h>
#include <conga/minimax_agent.h>

#include <algorithm>
#include <functional>

using namespace std;

namespace conga {

MinimaxAgent::MinimaxAgent(const Board::StoneType player_id,
                           const EvaluationFunction evaluation_function)
    : Agent(player_id),
      evaluation_function_(evaluation_function),
      maximize_evaluation_(evaluation_function_ ==
                                   EvaluationFunction::kMinimizeOpponentMoves
                               ? false
                               : true) {}

MinimaxAgent::~MinimaxAgent() {}

const Agent::Action MinimaxAgent::ComputeAction(const Board& board) const {
  int alpha = INT_MIN;
  int beta = INT_MAX;
  auto best_action = kNoAction;
  cout << "A-B: "
       << AlphaBeta(board, 3, alpha, beta, best_action, maximize_evaluation_)
       << endl;

  return best_action;
}

const int MinimaxAgent::AlphaBeta(const Board& board, const int depth,
                                  int& alpha, int& beta, Action& best_action,
                                  const bool maximizing) const {
  if (depth == 0) {
    return EvaluateState(board);
  }

  auto actions = ValidActions(board, stone_type());
  if (actions.empty()) {
    return EvaluateState(board);
  }

  // for (auto a : actions) cout << a << endl;
  // return 1;

  if (maximizing) {
    int value = INT_MIN;
    for (const auto& action : actions) {
      auto new_board = Board(board);
      MakeMove(new_board, action.point, action.move);
      int new_value =
          AlphaBeta(new_board, depth - 1, alpha, beta, best_action, false);

      if (new_value > value) {
        value = new_value;
        best_action = action;
      }

      alpha = max(alpha, value);

      if (value >= beta) {
        break;
      }
    }

    return value;
  } else {
    int value = INT_MAX;
    for (const auto& action : actions) {
      auto new_board = Board(board);
      MakeMove(new_board, action.point, action.move);
      int new_value =
          AlphaBeta(new_board, depth - 1, alpha, beta, best_action, true);

      if (new_value < value) {
        value = new_value;
        best_action = action;
      }

      beta = min(beta, value);

      if (value <= alpha) {
        break;
      }
    }

    return value;
  }
}

const int MinimaxAgent::EvaluateState(const Board& board) const {
  if (evaluation_function_ == EvaluationFunction::kMinimizeOpponentMoves) {
    return NumOpponentMoves(board);
  }

  return INT_MIN;
}

const int MinimaxAgent::NumOpponentMoves(const Board& board) const {
  return ValidActions(board, opponent_stone_type()).size();
}

}  // namespace conga
