#include <conga/point.h>

namespace conga {

Point::Point(const int x, const int y) : x(x), y(y) {}

Point::Point(const Point& point) : x(point.x), y(point.y) {}

Point::~Point() {}

const Point operator+(const Point& lhs, const Point& rhs) {
  return Point(lhs.x + rhs.x, lhs.y + rhs.y);
}

const Point operator*(const Point& lhs, const int rhs) {
  return Point(lhs.x * rhs, lhs.y * rhs);
}

const Point operator*(const int lhs, const Point& rhs) {
  return Point(rhs.x * lhs, rhs.y * lhs);
}

const bool operator==(const Point& lhs, const Point& rhs) {
  return lhs.x == rhs.x && lhs.y == rhs.y;
}

const bool operator!=(const Point& lhs, const Point& rhs) {
  return lhs.x != rhs.x || lhs.y != rhs.y;
}

std::ostream& operator<<(std::ostream& os, const Point& point) {
  return os << "(" << point.x << ", " << point.y << ")";
}

}  // namespace conga
