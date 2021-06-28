#include <conga/board.h>
#include <conga/random_agent.h>

#include <iterator>
#include <random>

using namespace std;

namespace conga {

RandomAgent::RandomAgent(const Board::StoneType stone_type)
    : Agent(stone_type) {
  srand(time(NULL));
}

RandomAgent::~RandomAgent() {}

const Agent::Move RandomAgent::ComputeMove(const Board& board) const {
  auto valid_moves = ValidMoves(board, stone_type());
  if (valid_moves.empty()) {
    return kNoMove;
  }

  return *select_randomly(valid_moves.begin(), valid_moves.end());
}

template <typename Iter, typename RandomGenerator>
Iter select_randomly(Iter start, Iter end, RandomGenerator& g) {
  uniform_int_distribution<> dis(0, distance(start, end) - 1);
  advance(start, dis(g));
  return start;
}

template <typename Iter>
Iter select_randomly(Iter start, Iter end) {
  static random_device rd;
  static mt19937 gen(rd());
  return select_randomly(start, end, gen);
}

}  // namespace conga
