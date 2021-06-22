#include <conga/board.h>
#include <conga/player.h>

#include <sstream>
#include <stdexcept>
#include <string>

using namespace std;

namespace conga {

Player::Player(const Board::StoneType stone_type)
    : stone_type_(stone_type),
      opponent_stone_type_(stone_type == Board::StoneType::kBlack
                               ? Board::StoneType::kWhite
                               : Board::StoneType::kBlack) {
  if (stone_type == Board::StoneType::kNone) {
    throw invalid_argument("Invalid stone type given for player!");
  }
}

Player::~Player() {}

void Player::MakeMove(Board& board, const Board::Point& point,
                      const Board::Move move) const {
  if (!ValidMove(board, point, move)) {
    throw invalid_argument("Invalid move " + to_string(move) + " for " +
                           to_string(stone_type_) + " from position " +
                           to_string(point) + "!");
  }

  for (int i = 1; i <= 3; ++i) {
    auto curr_point = point + (i * Board::kMoveDirections.at(move));
    if (board.At(point).num_stones > 0 && board.HasPoint(curr_point) &&
        board.At(curr_point).stone_type != opponent_stone_type_) {
      board.At(curr_point).stone_type = stone_type_;
      auto next_point = point + ((i + 1) * Board::kMoveDirections.at(move));
      if (i == 3 || board.At(point).num_stones < i ||
          !board.HasPoint(next_point) ||
          board.At(next_point).stone_type == opponent_stone_type_) {
        board.At(curr_point).num_stones += board.At(point).num_stones;
        board.At(point).num_stones = 0;
        board.At(point).stone_type = Board::StoneType::kNone;
        break;
      } else {
        board.At(curr_point).num_stones += i;
        board.At(point).num_stones -= i;
      }
    }
  }
}

const bool Player::Lost(const Board& board) const {
  auto occupied_points = board.OccupiedPoints(stone_type_);
  for (const auto& occupied_point : occupied_points) {
    auto valid_moves = ValidMoves(board, occupied_point);
    if (!valid_moves.empty()) {
      return true;
    }
  }

  return false;
}

const bool Player::ValidMove(const Board& board, const Board::Point& point,
                             const Board::Move move) const {
  if (!board.HasPoint(point) ||
      board.At(point).stone_type == opponent_stone_type_ ||
      board.At(point).num_stones <= 0 || move == Board::Move::kNone) {
    return false;
  }

  auto next_point = point + Board::kMoveDirections.at(move);
  if (!board.HasPoint(next_point) ||
      board.At(next_point).stone_type == opponent_stone_type_) {
    return false;
  }

  return true;
}

const vector<Board::Move> Player::ValidMoves(const Board& board,
                                             const Board::Point& point) const {
  auto valid_moves = vector<Board::Move>();
  for (const auto& [possible_move, direction] : Board::kMoveDirections) {
    if (ValidMove(board, point, possible_move)) {
      valid_moves.push_back(possible_move);
    }
  }

  return valid_moves;
}

template <typename T>
string to_string(const T& value) {
  stringstream sstream;
  sstream << value;
  return sstream.str();
}

}  // namespace conga
