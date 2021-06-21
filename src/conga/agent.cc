#include <conga/agent.h>
#include <conga/board.h>

namespace conga {

Agent::Agent(const Board::Player player)
    : player_(player),
      opponent_(player == Board::Player::k1 ? Board::Player::k2
                                            : Board::Player::k2) {}

Agent::~Agent() {}

const vector<Board::Point> Agent::OccupiedPoints(const Board& board) const {
  auto occupied_points = vector<Board::Point>();
  for (int x = 1; x <= Board::kBoardLength; ++x) {
    for (int y = 1; y <= Board::kBoardLength; ++y) {
      if (board.At(x, y).occupier == player_) {
        occupied_points.push_back(Board::Point(x, y));
      }
    }
  }

  return occupied_points;
}

const bool Agent::HasMove(const Board& board, const Board::Point& from) const {
  return false;
}

const Board::Move Agent::BestMove(const Board& board,
                                  const Board::Point& from) const {
  return Board::Move::kNone;
}

const Board::Move Agent::RandomMove(const Board& board,
                                    const Board::Point& from) const {
  return Board::Move::kNone;
}

void Agent::MakeMove(Board& board, const Board::Point& from,
                     const Board::Point& to) const {}

const vector<Board::Move> Agent::ValidMoves(const Board& board,
                                            const Board::Point& from) const {
  auto valid_moves = vector<Board::Move>();
  for (const auto& [possible_move, direction] : kMoves) {
    if (board.HasPoint(from + direction)) {
      valid_moves.push_back(possible_move);
    }
  }

  return valid_moves;
}

}  // namespace conga
