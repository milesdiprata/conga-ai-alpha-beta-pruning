#ifndef CONGA_SQUARE_H_
#define CONGA_SQUARE_H_

#include <conga/stone.h>

#include <cstddef>
#include <iostream>
#include <optional>

namespace conga {

struct Square {
  inline static constexpr const char* const kBlackStonesColor = "\u001b[31m";
  inline static constexpr const char* const kWhiteStonesColor = "\u001b[34m";
  inline static constexpr const char* const kNoStonesColor = "\033[93m";
  inline static constexpr const char* const kResetColor = "\033[0m";

  Square(const std::optional<Stone>& stone = std::nullopt,
         const std::size_t num_stones = 0);
  Square(const Square& square);
  ~Square();

  std::optional<Stone> stone;
  std::size_t num_stones;
};

std::ostream& operator<<(std::ostream& os, const Square& square);

}  // namespace conga

#endif  // CONGA_SQUARE_H_