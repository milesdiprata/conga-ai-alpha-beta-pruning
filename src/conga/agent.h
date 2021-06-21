#ifndef CONGA_AGENT_H_
#define CONGA_AGENT_H_

#include <conga/board.h>
#include <conga/player.h>

namespace conga {

class Agent : public Player {
 public:
  Agent(const Board::PlayerId player_id);
  virtual ~Agent();

  const Board::Move BestMove(const Board& board,
                             const Board::Point& point) const;

  const Board::Move RandomMove(const Board& board,
                               const Board::Point& point) const;
};

}  // namespace conga

#endif  // CONGA_AGENT_H_
