#ifndef CONGA_PLAYER_H_
#define CONGA_PLAYER_H_

#include <conga/board.h>
#include <conga/stone.h>

namespace conga {

class Player {
 public:
  Player(const Stone& stone);
  virtual ~Player();

  inline const Stone& stone() const { return stone_; }
  inline const Stone& opponent_stone() const { return opponent_stone_; }

  virtual const Move GetMove(const Board& board) const;

 private:
  Stone stone_;
  Stone opponent_stone_;
};

}  // namespace conga

#endif  // CONGA_PLAYER_H_
