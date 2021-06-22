#ifndef CONGA_AGENT_H_
#define CONGA_AGENT_H_

#include <conga/board.h>
#include <conga/player.h>

#include <limits>
#include <vector>

namespace conga {

class Agent : public Player {
 public:
  struct Action {
    Action(const Board::Point& point, const Board::Move move);
    ~Action();

    Board::Point point;
    Board::Move move;
  };

  inline static const auto kNoAction =
      Action(Board::kInvalidPoint, Board::Move::kNone);

  Agent(const Board::StoneType stone_type);
  virtual ~Agent();

  virtual const Action ComputeAction(const Board& board) const = 0;

 protected:
  static const vector<Action> ValidActions(const Board& board,
                                           const Board::StoneType stone_type);
};

ostream& operator<<(ostream& os, const Agent::Action& action);

}  // namespace conga

#endif  // CONGA_AGENT_H_
