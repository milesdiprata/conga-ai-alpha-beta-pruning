#ifndef CONGA_POINT_H_
#define CONGA_POINT_H_

#include <array>
#include <cstdlib>
#include <iostream>
#include <limits>

namespace conga {

struct Point {
  constexpr Point(const int x = 0, const int y = 0) : x(x), y(y) {}
  constexpr Point(const Point& point) : x(point.x), y(point.y) {}

  int x;
  int y;
};

namespace point {

static constexpr auto kInvalidPoint =
    Point(std::numeric_limits<int>::max(), std::numeric_limits<int>::max());

namespace direction {

static constexpr std::size_t kNumDirections = 8;

static constexpr auto kUp = Point(0, 1);
static constexpr auto kUpRight = Point(1, 1);
static constexpr auto kRight = Point(1, 0);
static constexpr auto kDownRight = Point(1, -1);
static constexpr auto kDown = Point(0, -1);
static constexpr auto kDownLeft = Point(-1, -1);
static constexpr auto kLeft = Point(-1, 0);
static constexpr auto kUpLeft = Point(-1, 1);

static constexpr auto kDirections = std::array<Point, kNumDirections>{
    kUp, kUpRight, kRight, kDownRight, kDown, kDownLeft, kLeft, kUpLeft,
};

}  // namespace direction

}  // namespace point

constexpr Point operator+(const Point& lhs, const Point& rhs) {
  return Point(lhs.x + rhs.x, lhs.y + rhs.y);
}

constexpr Point operator*(const Point& lhs, const int rhs) {
  return Point(lhs.x * rhs, lhs.y * rhs);
}

constexpr Point operator*(const int lhs, const Point& rhs) {
  return Point(rhs.x * lhs, rhs.y * lhs);
}

constexpr bool operator==(const Point& lhs, const Point& rhs) {
  return lhs.x == rhs.x && lhs.y == rhs.y;
}

constexpr bool operator!=(const Point& lhs, const Point& rhs) {
  return lhs.x != rhs.x || lhs.y != rhs.y;
}

std::ostream& operator<<(std::ostream& os, const Point& point);

}  // namespace conga

#endif  // CONGA_POINT_H_
