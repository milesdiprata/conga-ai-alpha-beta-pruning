#include "conga/stone.h"

namespace conga {

std::ostream& operator<<(std::ostream& os, const Stone& stone) {
  return os << (stone == Stone::kBlack ? Stone::kBlackName : Stone::kWhiteName);
}

}  // namespace conga
