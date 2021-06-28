#ifndef CONGA_STONE_H_
#define CONGA_STONE_H_

#include <iostream>

namespace conga {

struct Stone {
 public:
  enum Value {
    kBlack,
    kWhite,
  };

  static constexpr const char* const kBlackName = "Black";
  static constexpr const char* const kWhiteName = "White";

  constexpr Stone(const Value value) : value(value) {}
  constexpr Stone(const Stone& stone) : value(stone.value) {}

  constexpr Stone Complement() const {
    return value == Value::kBlack ? Stone(Stone::kWhite) : Stone(Stone::kBlack);
  }

  Value value;
};

constexpr bool operator==(const Stone& lhs, const Stone& rhs) {
  return lhs.value == rhs.value;
}

constexpr bool operator!=(const Stone& lhs, const Stone& rhs) {
  return lhs.value != rhs.value;
}

std::ostream& operator<<(std::ostream& os, const Stone& stone);

}  // namespace conga

#endif  // CONGA_STONE_H_
