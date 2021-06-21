#ifndef CONGA_AGENT_H_
#define CONGA_AGENT_H_

#include <conga/board.h>

#include <unordered_map>
#include <vector>

using namespace std;

namespace conga {

class Agent {
 public:
  inline static const auto kMoves = unordered_map<Board::Move, Board::Point>{
      {Board::Move::kUp, Board::Point(0, 1)},
      {Board::Move::kUpRight, Board::Point(1, 1)},
      {Board::Move::kRight, Board::Point(1, 0)},
      {Board::Move::kDownRight, Board::Point(1, -1)},
      {Board::Move::kDown, Board::Point(0, -1)},
      {Board::Move::kDownLeft, Board::Point(-1, -1)},
      {Board::Move::kLeft, Board::Point(-1, 0)},
      {Board::Move::kUpLeft, Board::Point(-1, 1)}};

  Agent(const Board::Player player);
  ~Agent();

  inline const Board::Player player() const { return player_; }
  inline const Board::Player opponent() const { return opponent_; }

  const vector<Board::Point> OccupiedPoints(const Board& board) const;
  const bool HasMove(const Board& board, const Board::Point& from) const;
  const Board::Move BestMove(const Board& board,
                             const Board::Point& from) const;
  const Board::Move RandomMove(const Board& board,
                               const Board::Point& from) const;
  void MakeMove(Board& board, const Board::Point& from,
                const Board::Point& to) const;

 private:
  const vector<Board::Move> ValidMoves(const Board& board,
                                       const Board::Point& from) const;

  Board::Player player_;
  Board::Player opponent_;
};

}  // namespace conga

#endif  // CONGA_AGENT_H_
