#ifndef CONGA_AGENT_H_
#define CONGA_AGENT_H_

#include <conga/board.h>

#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

namespace conga {

class Agent {
 public:
  Agent(const Board::Player player);
  ~Agent();

  inline const Board::Player player() const { return player_; }
  inline const Board::Player opponent() const { return opponent_; }

  const vector<Board::Point> OccupiedPoints(const Board& board) const;

  const bool ValidMove(const Board& board, const Board::Point& point,
                       const Board::Move move) const;

  const vector<Board::Move> ValidMoves(const Board& board,
                                       const Board::Point& point) const;

  const Board::Move BestMove(const Board& board,
                             const Board::Point& point) const;

  const Board::Move RandomMove(const Board& board,
                               const Board::Point& point) const;

  void MakeMove(Board& board, const Board::Point& point,
                const Board::Move move) const;

  const bool Lost(const Board& board) const;

 private:
  Board::Player player_;
  Board::Player opponent_;
};

template <typename T>
string to_string(const T& value);

}  // namespace conga

#endif  // CONGA_AGENT_H_
