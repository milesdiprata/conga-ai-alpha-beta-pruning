#include "conga/player.h"

#include <stdexcept>

#include "conga/board.h"
#include "conga/stone.h"

using namespace std;

namespace conga {

Player::Player(const Stone& stone)
    : stone_(stone), opponent_stone_(stone.Complement()) {}

Player::~Player() {}

const Move Player::GetMove(const Board& board) const {
  // TODO: cin player move
  throw std::logic_error("Function Player::GetMove not implemented yet!");
}

}  // namespace conga
