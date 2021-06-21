#ifndef CONGA_RANDOM_AGENT_H_
#define CONGA_RANDOM_AGENT_H_

#include <conga/agent.h>
#include <conga/board.h>

namespace conga {

class RandomAgent : public Agent {
 public:
  RandomAgent(const Board::PlayerId player_id);
  virtual ~RandomAgent();

  const Board::Move ComputeMove(const Board& board,
                                const Board::Point& point) const override;
};

}  // namespace conga

#endif  // CONGA_RANDOM_AGENT_H_
