#ifndef CONGA_RANDOM_AGENT_H_
#define CONGA_RANDOM_AGENT_H_

#include <conga/agent.h>
#include <conga/board.h>

namespace conga {

class RandomAgent : public Agent {
 public:
  RandomAgent(const Board::StoneType stone_type);
  virtual ~RandomAgent();

  const Action ComputeAction(const Board& board) const override;
};

}  // namespace conga

#endif  // CONGA_RANDOM_AGENT_H_
