#include <conga/agent.h>
#include <conga/board.h>
#include <conga/player.h>

namespace conga {

Agent::Agent(const Board::StoneType stone_type) : Player(stone_type) {}

Agent::~Agent() {}

ostream& operator<<(ostream& os, const Agent::Move& move) {
  return os << "(" << move.point << ", " << move.action << ")";
}

}  // namespace conga