#include "conga/square.h"

#include <optional>

#include "conga/stone.h"

namespace conga {

Square::Square(const std::optional<Stone>& stone, const int num_stones)
    : stone(stone), num_stones(num_stones) {}

Square::Square(const Square& square)
    : stone(square.stone), num_stones(square.num_stones) {}

Square::~Square() {}

std::ostream& operator<<(std::ostream& os, const Square& square) {
  if (square.stone) {
    os << (square.stone == Stone::kBlack ? Square::kBlackStonesColor
                                         : Square::kWhiteStonesColor);
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
