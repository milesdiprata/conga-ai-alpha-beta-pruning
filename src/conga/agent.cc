#include <conga/agent.h>
#include <conga/board.h>

namespace conga {

Agent::Agent(const Game::Player player)
    : player_(player),
      opponent_(player == Game::Player::k1 ? Game::Player::k2
                                           : Game::Player::k2) {}

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

const bool Agent::HasMove(const Board::Point& from) const {}
const Game::Move Agent::BestMove(const Board::Point& from) const {}
const Game::Move Agent::RandomMove(const Board::Point& from) const {}
void Agent::MakeMove(const Board::Point& from, const Board::Point& to,
                     Board& board) const {}

const bool Agent::ValidMove(const Game::Move move, const Board& board) const {}
const vector<Game::Move> Agent::ValidMovesFromPoint(
    const Board::Point& point) const {}

}  // namespace conga