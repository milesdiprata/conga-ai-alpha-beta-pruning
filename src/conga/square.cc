#include <conga/square.h>

namespace conga {

Square::Square(const State state, const std::size_t num_stones)
    : state(state), num_stones(num_stones) {}

Square::Square(const Square& square)
    : state(square.state), num_stones(square.num_stones) {}

Square::~Square() {}

std::ostream& operator<<(std::ostream& os, const Square& square) {
  if (square.state == Square::State::kBlackStones) {
    os << Square::kBlackStonesColor;
  } else if (square.state == Square::State::kWhiteStones) {
    os << Square::kWhiteStonesColor;
  } else {
    os << Square::kNoStonesColor;
  }

  if (square.num_stones > 9) {
    os << "> 9";
  } else {
    os << square.num_stones;
  }

  os << Square::kResetColor;

  return os;
}

}  // namespace conga
