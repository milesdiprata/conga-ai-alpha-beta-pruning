#include <conga/agent.h>
#include <conga/board.h>
#include <conga/player.h>

namespace conga {

Agent::Agent(const Board::PlayerId player_id) : Player(player_id) {}

Agent::~Agent() {}

}  // namespace conga