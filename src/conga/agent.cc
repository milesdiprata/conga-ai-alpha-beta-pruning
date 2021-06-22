#include <conga/agent.h>
#include <conga/board.h>
#include <conga/player.h>

#include <vector>

namespace conga {

Agent::Agent(const Board::StoneType stone_type) : Player(stone_type) {}

Agent::~Agent() {}

Agent::Action::Action(const Board::Point& point, const Board::Move move,
                      const int value)
    : point(point), move(move), value(value) {}

Agent::Action::~Action() {}

const vector<Agent::Action> Agent::ValidActions(const Board& board) const {
  auto valid_actions = vector<Action>();
  auto occupied_points = OccupiedPoints(board, stone_type());
  for (const auto& occupied_point : occupied_points) {
    auto valid_moves = ValidMoves(board, occupied_point);
    for (const auto& valid_move : valid_moves) {
      valid_actions.push_back(Action(occupied_point, valid_move));
    }
  }

  return valid_actions;
}

ostream& operator<<(ostream& os, const Agent::Action& action) {
  return os << "(" << action.point << ", " << action.move << ")";
}

}  // namespace conga