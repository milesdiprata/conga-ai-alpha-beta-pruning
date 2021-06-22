#include <conga/agent.h>
#include <conga/board.h>
#include <conga/player.h>

namespace conga {

Agent::Agent(const Board::StoneType stone_type) : Player(stone_type) {}

Agent::~Agent() {}

Agent::Action::Action(const Board::Point& point, const Board::Move move)
    : point(point), move(move) {}

Agent::Action::~Action() {}

ostream& operator<<(ostream& os, const Agent::Action& action) {
  return os << "(" << action.point << ", " << action.move << ")";
}

}  // namespace conga