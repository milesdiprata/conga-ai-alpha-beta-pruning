#include "conga/point.h"

namespace conga {

std::ostream& operator<<(std::ostream& os, const Point& point) {
  return os << "(" << point.x << ", " << point.y << ")";
}

}  // namespace conga
