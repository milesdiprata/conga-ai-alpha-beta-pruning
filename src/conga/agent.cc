#include <conga/agent.h>
#include <conga/board.h>
#include <conga/player.h>

#include <random>

namespace conga {

Agent::Agent(const Board::PlayerId player_id) : Player(player_id) {}

Agent::~Agent() {}

const Board::Move Agent::BestMove(const Board& board,
                                  const Board::Point& from) const {
  return Board::Move::kNone;
}

const Board::Move Agent::RandomMove(const Board& board,
                                    const Board::Point& point) const {
  auto valid_moves = Player::ValidMoves(board, point);
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

}  // namespace conga