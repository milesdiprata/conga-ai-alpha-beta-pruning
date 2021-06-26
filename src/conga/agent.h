#ifndef CONGA_AGENT_H_
#define CONGA_AGENT_H_

#include <conga/board.h>
#include <conga/player.h>

#include <limits>

namespace conga {

class Agent : public Player {
 public:
  inline static const auto kNoAction =
      Move(Board::kInvalidPoint, Board::Action::kNone);

  Agent(const Board::StoneType stone_type);
  virtual ~Agent();

  virtual const Move ComputeMove(const Board& board) const = 0;
};

ostream& operator<<(ostream& os, const Agent::Move& action);

}  // namespace conga

#endif  // CONGA_AGENT_H_
