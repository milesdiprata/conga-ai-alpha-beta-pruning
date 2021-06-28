#include <conga/move.h>
#include <conga/point.h>

#include <iostream>

namespace conga {

std::ostream& operator<<(std::ostream& os, const Move& move) {
  return os << "(" << move.point << ", " << move.direction << ")";
}

}  // namespace conga
