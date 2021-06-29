#include "conga/agent.h"

#include "conga/board.h"
#include "conga/move.h"
#include "conga/player.h"
#include "conga/stone.h"

namespace conga {

Agent::Agent(const Stone& stone) : Player(stone) {}

Agent::~Agent() {}

const Move Agent::GetMove(const Board& board) const {
  return ComputeMove(board);
}

}  // namespace conga