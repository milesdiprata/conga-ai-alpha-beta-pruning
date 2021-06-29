#ifndef CONGA_GAME_H_
#define CONGA_GAME_H_

#include <memory>

#include "conga/board.h"
#include "conga/player.h"

namespace conga {
class Game {
 public:
  Game(std::unique_ptr<Board> board, std::unique_ptr<Player> player1,
       std::unique_ptr<Player> player2);
  ~Game();

  void Play();

 private:
  std::unique_ptr<Board> board_;
  std::unique_ptr<Player> player1_;
  std::unique_ptr<Player> player2_;
};

}  // namespace conga

#endif  // CONGA_GAME_H_