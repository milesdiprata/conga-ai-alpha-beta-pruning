#ifndef CONGA_AGENT_H_
#define CONGA_AGENT_H_

#include <conga/board.h>
#include <conga/player.h>

namespace conga {

class Agent : public Player {
 public:
  Agent(const Board::PlayerId player_id);
  virtual ~Agent();

  virtual const Board::Move ComputeMove(const Board& board,
                                        const Board::Point& point) const = 0;
};

}  // namespace conga

#endif  // CONGA_AGENT_H_
