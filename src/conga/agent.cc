#include <conga/agent.h>
#include <conga/board.h>
#include <conga/player.h>

namespace conga {

Agent::Agent(const Board::StoneType stone_type) : Player(stone_type) {}

Agent::~Agent() {}

}  // namespace conga