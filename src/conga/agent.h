#ifndef CONGA_AGENT_H_
#define CONGA_AGENT_H_

#include <conga/board.h>
#include <conga/game.h>

#include <unordered_map>
#include <vector>

namespace conga {

class Agent {
 public:
  inline static const auto kMoves = unordered_map<Game::Move, Board::Point>{
      {Game::Move::kUp, Board::Point(0, 1)},
      {Game::Move::kUpRight, Board::Point(1, 1)},
      {Game::Move::kRight, Board::Point(1, 0)},
      {Game::Move::kDownRight, Board::Point(1, -1)},
      {Game::Move::kDown, Board::Point(0, -1)},
      {Game::Move::kDownLeft, Board::Point(-1, -1)},
      {Game::Move::kLeft, Board::Point(-1, 0)},
      {Game::Move::kUpLeft, Board::Point(-1, 1)}};

  Agent(const Game::Player player);
  ~Agent();

  inline const Game::Player player() const { return player_; }
  inline const Game::Player opponent() const { return opponent_; }

  const vector<Board::Point> OccupiedPoints(const Board& board) const;
  const bool HasMove(const Board::Point& from) const;
  const Game::Move BestMove(const Board::Point& from) const;
  const Game::Move RandomMove(const Board::Point& from) const;
  void MakeMove(const Board::Point& from, const Board::Point& to,
                Board& board) const;

 private:
  const bool ValidMove(const Game::Move move, const Board& board) const;
  const vector<Game::Move> ValidMovesFromPoint(const Board::Point& point) const;

  Game::Player player_;
  Game::Player opponent_;
};

}  // namespace conga

#endif  // CONGA_AGENT_H_