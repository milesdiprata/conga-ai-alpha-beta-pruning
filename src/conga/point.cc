#include <conga/point.h>

#include <iostream>

namespace conga {

std::ostream& operator<<(std::ostream& os, const Point& point) {
  return os << "(" << point.x << ", " << point.y << ")";
}

}  // namespace conga
