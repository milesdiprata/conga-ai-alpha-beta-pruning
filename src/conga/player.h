#ifndef CONGA_PLAYER_H_
#define CONGA_PLAYER_H_

#include <conga/board.h>

#include <string>
#include <vector>

using namespace std;

namespace conga {

class Player {
 public:
  Player(const Board::StoneType stone_type);
  virtual ~Player();

  inline const Board::StoneType stone_type() const { return stone_type_; }
  inline const Board::StoneType opponent_stone_type() const {
    return opponent_stone_type_;
  }

  void MakeMove(Board& board, const Board::Point& point,
                const Board::Move move) const;

  const bool Lost(const Board& board) const;

 protected:
  const bool ValidMove(const Board& board, const Board::Point& point,
                       const Board::Move move) const;

  const vector<Board::Move> ValidMoves(const Board& board,
                                       const Board::Point& point) const;

 private:
  Board::StoneType stone_type_;
  Board::StoneType opponent_stone_type_;
};

template <typename T>
string to_string(const T& value);

}  // namespace conga

#endif  // CONGA_PLAYER_H_
