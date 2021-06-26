#ifndef CONGA_GAME_H_
#define CONGA_GAME_H_

#include <conga/board.h>
#include <conga/player.h>

namespace conga {
class Game {
 public:
  Game(Board* board, Player* player1, Player* player2);
  ~Game();

  void Play();

 private:
  Board* board_;
  Player* player1_;
  Player* player2_;
};

}  // namespace conga

#endif  // CONGA_GAME_H_