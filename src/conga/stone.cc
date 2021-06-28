#include <conga/stone.h>

namespace conga {

Stone::Stone(const Value value) : value(value) {}

const Stone Stone::Complement() const {
  return value == Value::kBlack ? Stone(Stone::kWhite) : Stone(Stone::kBlack);
}

const bool operator==(const Stone& lhs, const Stone& rhs) {
  return lhs.value == rhs.value;
}

const bool operator!=(const Stone& lhs, const Stone& rhs) {
  return lhs.value != rhs.value;
}

}  // namespace conga
