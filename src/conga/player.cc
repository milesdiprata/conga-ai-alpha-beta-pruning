#include <conga/board.h>
#include <conga/player.h>

#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

namespace conga {

Player::Player(const Board::StoneType stone_type)
    : stone_type_(stone_type),
      opponent_stone_type_(stone_type == Board::StoneType::kBlack
                               ? Board::StoneType::kWhite
                               : Board::StoneType::kBlack) {
  if (stone_type_ == Board::StoneType::kNone) {
    throw invalid_argument("Invalid stone type given!");
  }
}

Player::~Player() {}

const Player::Move Player::GetMove(const Board& board) const {
  // TODO: cin player move
  return kNoMove;
}

void Player::MakeMove(Board& board, const Move& move) const {
  if (!ValidMove(board, move)) {
    throw invalid_argument("Invalid action " + to_string(move.action) +
                           " for " + to_string(stone_type_) +
                           " from position " + to_string(move.point) + "!");
  }

  for (int i = 1; i <= 3; ++i) {
    auto curr_point =
        move.point + (i * Board::kActionDirections.at(move.action));
    if (board.At(move.point).num_stones > 0 && board.HasPoint(curr_point) &&
        board.At(curr_point).stone_type != opponent_stone_type_) {
      board.At(curr_point).stone_type = stone_type_;

      auto next_point =
          move.point + ((i + 1) * Board::kActionDirections.at(move.action));
      if (i == 3 || board.At(move.point).num_stones < i ||
          !board.HasPoint(next_point) ||
          board.At(next_point).stone_type == opponent_stone_type_) {
        board.At(curr_point).num_stones += board.At(move.point).num_stones;
        board.At(move.point).num_stones = 0;
        break;
      } else {
        board.At(curr_point).num_stones += i;
        board.At(move.point).num_stones -= i;
      }
    }
  }

  if (board.At(move.point).num_stones == 0) {
    board.At(move.point).stone_type = Board::StoneType::kNone;
  }
}

const bool Player::Lost(const Board& board) const {
  return ValidMoves(board, stone_type_).empty();
}

// inline static const Board::StoneType ComplementStoneType(
//     const Board::StoneType stone_type) {
//   if (stone_type == Board::StoneType::kBlack) {
//     return Board::StoneType::kWhite;
//   } else if (stone_type == Board::StoneType::kWhite) {
//     return Board::StoneType::kBlack;
//   } else {
//     throw invalid_argument("Invalid stone type given!");
//   }
// }

const bool Player::ValidMove(const Board& board, const Move& move) {
  if (!board.HasPoint(move.point) ||
      board.At(move.point).stone_type == Board::StoneType::kNone ||
      board.At(move.point).num_stones <= 0 ||
      move.action == Board::Action::kNone) {
    return false;
  }

  auto opponent_stone_type =
      board.At(move.point).stone_type == Board::StoneType::kBlack
          ? Board::StoneType::kWhite
          : Board::StoneType::kBlack;

  auto next_point = move.point + Board::kActionDirections.at(move.action);
  if (!board.HasPoint(next_point) ||
      board.At(next_point).stone_type == opponent_stone_type) {
    return false;
  }

  return true;
}

const vector<Board::Action> Player::ValidActions(const Board& board,
                                                 const Board::Point& point) {
  auto valid_actions = vector<Board::Action>();
  for (const auto& [possible_action, direction] : Board::kActionDirections) {
    if (ValidMove(board, Move(point, possible_action))) {
      valid_actions.push_back(possible_action);
    }
  }

  return valid_actions;
}

const vector<Player::Move> Player::ValidMoves(
    const Board& board, const Board::StoneType stone_type) {
  auto valid_moves = vector<Move>();
  auto occupied_points = board.OccupiedPoints(stone_type);
  for (const auto& occupied_point : occupied_points) {
    auto valid_actions = ValidActions(board, occupied_point);
    for (const auto& valid_action : valid_actions) {
      valid_moves.push_back(Move(occupied_point, valid_action));
    }
  }

  return valid_moves;
}

Player::Move::Move(const Board::Point& point, const Board::Action action)
    : point(point), action(action) {}

Player::Move::~Move() {}

ostream& operator<<(ostream& os, const Player::Move& move) {
  return os << "(" << move.point << ", " << move.action << ")";
}

template <typename T>
string to_string(const T& value) {
  stringstream sstream;
  sstream << value;
  return sstream.str();
}

}  // namespace conga
