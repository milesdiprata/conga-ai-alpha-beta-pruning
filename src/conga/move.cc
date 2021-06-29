#include "conga/move.h"

#include <iostream>

#include "conga/point.h"

namespace conga {

std::ostream& operator<<(std::ostream& os, const Move& move) {
  return os << "(" << move.point << ", " << move.direction << ")";
}

}  // namespace conga
