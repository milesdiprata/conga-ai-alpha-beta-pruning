#ifndef CONGA_SQUARE_H_
#define CONGA_SQUARE_H_

#include <conga/stone.h>

#include <iostream>
#include <optional>

namespace conga {

struct Square {
  static constexpr const char* const kBlackStonesColor = "\u001b[31m";
  static constexpr const char* const kWhiteStonesColor = "\u001b[34m";
  static constexpr const char* const kNoStonesColor = "\033[93m";
  static constexpr const char* const kResetColor = "\033[0m";

  Square(const std::optional<Stone>& stone = std::nullopt,
         const int num_stones = 0);
  Square(const Square& square);
  ~Square();

  std::optional<Stone> stone;
  int num_stones;
};

std::ostream& operator<<(std::ostream& os, const Square& square);

}  // namespace conga

#endif  // CONGA_SQUARE_H_