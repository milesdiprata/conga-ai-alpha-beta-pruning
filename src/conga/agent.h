#ifndef CONGA_AGENT_H_
#define CONGA_AGENT_H_

#include <conga/board.h>
#include <conga/player.h>

#include <limits>

namespace conga {

class Agent : public Player {
 public:
  Agent(const Board::StoneType stone_type);
  virtual ~Agent();

  const Move GetMove(const Board& board) const final;

  virtual const Move ComputeMove(const Board& board) const = 0;
};

}  // namespace conga

#endif  // CONGA_AGENT_H_
