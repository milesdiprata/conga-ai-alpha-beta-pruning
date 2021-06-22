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
    Action(const Board::Point& point, const Board::Move move,
           const int value = INT_MIN);
    ~Action();

    Board::Point point;
    Board::Move move;
    int value;
  };

  inline static const auto kNoAction =
      Action(Board::kInvalidPoint, Board::Move::kNone, INT_MIN);

  Agent(const Board::StoneType stone_type);
  virtual ~Agent();

  virtual const Action ComputeAction(const Board& board) const = 0;

 protected:
  const vector<Action> ValidActions(const Board& board) const;
};

ostream& operator<<(ostream& os, const Agent::Action& action);

}  // namespace conga

#endif  // CONGA_AGENT_H_
