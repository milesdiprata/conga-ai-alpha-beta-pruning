#ifndef CONGA_GAME_H_
#define CONGA_GAME_H_

#include <conga/agent.h>
#include <conga/board.h>

namespace conga {

class Game {
 public:
  enum class Player {
    k1,
    k2,
    kNone,
  };

  enum class Move {
    kUp,
    kUpRight,
    kRight,
    kDownRight,
    kDown,
    kDownLeft,
    kLeft,
    kUpLeft,
  };

  Game(const Agent& player1, const Agent& player2,
       const Board& board = conga::Board());
  ~Game();

  const Agent& player1() const { return player1_; }
  const Agent& player2() const { return player2_; }
  const Board& board() const { return board_; }
  const bool over() const { return over_; }

  void PlayRound();

 private:
  void PlayTurn(const Agent& player);

  Agent player1_;
  Agent player2_;
  Board board_;
  bool over_;
};

}  // namespace conga

#endif  // CONGA_GAME_H_