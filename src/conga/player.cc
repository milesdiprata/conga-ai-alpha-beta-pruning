#include <conga/board.h>
#include <conga/player.h>

#include <random>
#include <sstream>
#include <stdexcept>
#include <string>

using namespace std;

namespace conga {

Player::Player(const Board::PlayerId player_id)
    : player_id_(player_id),
      opponent_id_(player_id_ == Board::PlayerId::k1 ? Board::PlayerId::k2
                                                     : Board::PlayerId::k1) {
  if (player_id_ == Board::PlayerId::kNone) {
    throw invalid_argument("Invalid player ID given!");
  }
}

Player::~Player() {}

const vector<Board::Point> Player::OccupiedPoints(const Board& board) const {
  auto occupied_points = vector<Board::Point>();
  for (int x = 1; x <= Board::kBoardLength; ++x) {
    for (int y = 1; y <= Board::kBoardLength; ++y) {
      if (board.At(x, y).occupier == player_id_) {
        occupied_points.push_back(Board::Point(x, y));
      }
    }
  }

  return occupied_points;
}

const bool Player::ValidMove(const Board& board, const Board::Point& point,
                             const Board::Move move) const {
  if (!board.HasPoint(point) || board.At(point).occupier == opponent_id_ ||
      board.At(point).num_stones <= 0) {
    return false;
  }

  auto next_point = point + Board::kMoves.at(move);
  if (!board.HasPoint(next_point) ||
      board.At(next_point).occupier == opponent_id_) {
    return false;
  }

  return true;
}

const vector<Board::Move> Player::ValidMoves(const Board& board,
                                             const Board::Point& point) const {
  auto valid_moves = vector<Board::Move>();
  for (const auto& [possible_move, direction] : Board::kMoves) {
    if (ValidMove(board, point, possible_move)) {
      valid_moves.push_back(possible_move);
    }
  }

  return valid_moves;
}

const Board::Move Player::BestMove(const Board& board,
                                   const Board::Point& from) const {
  return Board::Move::kNone;
}

const Board::Move Player::RandomMove(const Board& board,
                                     const Board::Point& point) const {
  auto valid_moves = ValidMoves(board, point);
  if (valid_moves.empty()) {
    return Board::Move::kNone;
  }

  static random_device rd;
  static mt19937 gen(rd());

  auto distribution = uniform_int_distribution<>(
      0, distance(valid_moves.begin(), valid_moves.end()) - 1);
  auto it = valid_moves.begin();
  advance(it, distribution(gen));

  return *it;
}

void Player::MakeMove(Board& board, const Board::Point& point,
                      const Board::Move move) const {
  if (!ValidMove(board, point, move)) {
    throw invalid_argument("Invalid move " + to_string(move) + " for " +
                           to_string(player_id_) + " from position " +
                           to_string(point) + "!");
  }

  for (int i = 1; i <= 3; ++i) {
    auto curr_point = point + (i * Board::kMoves.at(move));
    if (board.At(point).num_stones > 0 && board.HasPoint(curr_point) &&
        board.At(curr_point).occupier != opponent_id_) {
      board.At(curr_point).occupier = player_id_;
      auto next_point = point + ((i + 1) * Board::kMoves.at(move));
      if ((i < 3 && (!board.HasPoint(next_point) ||
                     board.At(next_point).occupier == opponent_id_)) ||
          board.At(point).num_stones < i || i == 3) {
        board.At(curr_point).num_stones += board.At(point).num_stones;
        board.At(point).num_stones = 0;
        board.At(point).occupier = Board::PlayerId::kNone;
        break;
      } else {
        board.At(curr_point).num_stones += i;
        board.At(point).num_stones -= i;
      }
    }
  }
}

const bool Player::Lost(const Board& board) const {
  auto occupied_points = OccupiedPoints(board);
  for (const auto& occupied_point : occupied_points) {
    auto valid_moves = ValidMoves(board, occupied_point);
    if (!valid_moves.empty()) {
      return true;
    }
  }

  return false;
}

template <typename T>
string to_string(const T& value) {
  stringstream sstream;
  sstream << value;
  return sstream.str();
}

}  // namespace conga
