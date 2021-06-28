#ifndef CONGA_RANDOM_AGENT_H_
#define CONGA_RANDOM_AGENT_H_

#include <conga/agent.h>
#include <conga/board.h>
#include <conga/move.h>
#include <conga/stone.h>

namespace conga {

class RandomAgent : public Agent {
 public:
  RandomAgent(const Stone& stone);
  virtual ~RandomAgent();

  const Move ComputeMove(const Board& board) const override;
};

}  // namespace conga

#endif  // CONGA_RANDOM_AGENT_H_
