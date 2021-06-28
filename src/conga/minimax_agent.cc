#include <conga/board.h>
#include <conga/minimax_agent.h>
#include <time.h>

#include <algorithm>
#include <cmath>
#include <functional>
#include <memory>

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

  auto result = AlphaBeta(board, search_depth_, INT_MIN, INT_MAX);
  return result.move;
}

const int MinimaxAgent::IterativeDeepeningSearch(
    const Board& board, const Board::StoneType stone_type,
    const time_t& start_time) const {
  int value = 0;
  // int depth = 1;

  // bool time_cutoff = false;

  // while (1) {
  //   auto result = AlphaBeta(board, depth, INT_MIN, INT_MAX, stone_type,
  //                           start_time, time_cutoff);

  //   // TODO: if (value >= value_cutoff) ?

  //   if (time_cutoff) {
  //     break;
  //   }

  //   value = result.value;

  //   // if (!result.remaining) {
  //   //   break;
  //   // }

  //   ++depth;
  // }

  return value;
}

const MinimaxAgent::SearchResult MinimaxAgent::AlphaBeta(
    const Board& board, const int depth, int alpha, int beta,
    const bool maximizing) const {
  auto valid_moves =
      ValidMoves(board, maximizing ? stone_type() : opponent_stone_type());
  if (depth == 0 || valid_moves.empty()) {
    return SearchResult(EvaluateState(board), kNoMove, true);
  }

  auto move = kNoMove;
  bool any_remaining = false;

  if (maximizing) {
    for (const auto& valid_move : valid_moves) {
      auto new_board = Board(board);
      MakeMove(new_board, valid_move);
      auto result = AlphaBeta(new_board, depth - 1, alpha, beta, !maximizing);
      if (result.value > alpha) {
        alpha = result.value;
        move = valid_move;
      }

      if (result.remaining) {
        any_remaining = true;
      }

      if (alpha >= beta) {
        return SearchResult(beta, move, any_remaining);
      }
    }

    return SearchResult(alpha, move, any_remaining);
  } else {
    for (const auto& valid_move : valid_moves) {
      auto new_board = Board(board);
      MakeMove(new_board, valid_move);
      auto result = AlphaBeta(new_board, depth - 1, alpha, beta, !maximizing);
      if (result.value < beta) {
        beta = result.value;
        move = valid_move;
      }

      if (result.remaining) {
        any_remaining = true;
      }

      if (alpha >= beta) {
        return SearchResult(alpha, move, any_remaining);
      }
    }

    return SearchResult(beta, move, any_remaining);
  }
}

const int MinimaxAgent::EvaluateState(const Board& board) const {
  if (evaluation_ == Evaluation::kPlayerMoves) {
    return ValidMoves(board, stone_type()).size();
  } else if (evaluation_ == Evaluation::kOpponentMoves) {
    return -1 * ValidMoves(board, opponent_stone_type()).size();
  } else if (evaluation_ == Evaluation::kPlayerMinusOpponentMoves) {
    return ValidMoves(board, stone_type()).size() -
           2 * ValidMoves(board, opponent_stone_type()).size();
  } else if (evaluation_ == Evaluation::kTest) {
    // auto occupied_points = board.OccupiedPoints(stone_type());
    // auto opponent_occupied_points =
    // board.OccupiedPoints(opponent_stone_type());

    // int delta_material =
    //     occupied_points.size() - opponent_occupied_points.size();

    // int diagonal_distance = 0;
    // for (const auto& occupied_point : occupied_points) {
    //   for (const auto& opponent_occupied_point : opponent_occupied_points) {
    //     diagonal_distance -=
    //         max(abs(occupied_point.x - opponent_occupied_point.x),
    //             abs(occupied_point.y - opponent_occupied_point.y));
    //   }
    // }

    // int opponent_trapped = 0;
    // for (const auto& opponent_occupied_point : opponent_occupied_points) {
    //   if (opponent_occupied_point.x == 1 ||
    //       opponent_occupied_point.x == Board::kBoardLength) {
    //     ++opponent_trapped;
    //   }
    //   if (opponent_occupied_point.y == 1 ||
    //       opponent_occupied_point.y == Board::kBoardLength) {
    //     ++opponent_trapped;
    //   }
    // }

    // if (board.At(1, 1).stone_type == opponent_stone_type() &&
    //     board.At(1, 2).stone_type == stone_type() &&
    //     board.At(2, 1).stone_type == stone_type() &&
    //     board.At(2, 2).stone_type == stone_type()) {
    //   ++opponent_trapped;
    // }
    // if (board.At(1, 4).stone_type == opponent_stone_type() &&
    //     board.At(1, 3).stone_type == stone_type() &&
    //     board.At(2, 3).stone_type == stone_type() &&
    //     board.At(2, 4).stone_type == stone_type()) {
    //   ++opponent_trapped;
    // }
    // if (board.At(4, 1).stone_type == opponent_stone_type() &&
    //     board.At(3, 1).stone_type == stone_type() &&
    //     board.At(3, 2).stone_type == stone_type() &&
    //     board.At(4, 2).stone_type == stone_type()) {
    //   ++opponent_trapped;
    // }
    // if (board.At(4, 4).stone_type == opponent_stone_type() &&
    //     board.At(4, 3).stone_type == stone_type() &&
    //     board.At(3, 4).stone_type == stone_type() &&
    //     board.At(3, 3).stone_type == stone_type()) {
    //   ++opponent_trapped;
    // }

    // return delta_material + 10 * opponent_trapped +
    //        (ValidMoves(board, stone_type()).size() -
    //         2 * ValidMoves(board, opponent_stone_type()).size());

    // int delta_material = occupied_points - opponent_occupied_points;
    // return delta_material + ValidMoves(board, stone_type()).size() -
    //        ValidMoves(board, opponent_stone_type()).size();
    // int control =
    //     ((float)occupied_points / (Board::kBoardLength *
    //     Board::kBoardLength)) * 100;

    // if (control > 10) {
    //   return -1 * ValidMoves(board, opponent_stone_type()).size();
    // } else {
    //   return ValidMoves(board, stone_type()).size();
    // }

    // return (occupied_points - opponent_occupied_points) +

    // return delta_material +
    //        (100 - control) * ValidMoves(board, stone_type()).size() -
    //        control * ValidMoves(board, opponent_stone_type()).size();
    return INT_MIN;
  } else {
    return INT_MIN;
  }
}

}  // namespace conga
