#ifndef CONGA_PLAYER_H_
#define CONGA_PLAYER_H_

#include <conga/board.h>

#include <string>
#include <vector>

using namespace std;

namespace conga {

class Player {
 public:
  Player(const Board::PlayerId player_id);
  ~Player();

  inline const Board::PlayerId player_id() const { return player_id_; }
  inline const Board::PlayerId opponent_id() const { return opponent_id_; }

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
  Board::PlayerId player_id_;
  Board::PlayerId opponent_id_;
};

template <typename T>
string to_string(const T& value);

}  // namespace conga

#endif  // CONGA_PLAYER_H_
