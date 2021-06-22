#include <conga/board.h>
#include <conga/random_agent.h>

#include <random>

using namespace std;

namespace conga {

RandomAgent::RandomAgent(const Board::StoneType stone_type)
    : Agent(stone_type) {}

RandomAgent::~RandomAgent() {}

const Board::Move RandomAgent::ComputeMove(const Board& board,
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

}  // namespace conga
