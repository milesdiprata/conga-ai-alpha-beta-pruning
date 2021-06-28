#ifndef CONGA_POINT_H_
#define CONGA_POINT_H_

#include <cstddef>
#include <iostream>

namespace conga {

struct Point {
  Point(const int x = 0, const int y = 0);
  Point(const Point& point);
  ~Point();

  int x;
  int y;
};

namespace direction {

static const auto kUp = Point(0, 1);
static const auto kUpRight = Point(1, 1);
static const auto kRight = Point(1, 0);
static const auto kDownRight = Point(1, -1);
static const auto kDown = Point(0, -1);
static const auto kDownLeft = Point(-1, -1);
static const auto kLeft = Point(-1, 0);
static const auto kUpLeft = Point(-1, 1);

}  // namespace direction

std::ostream& operator<<(std::ostream& os, const Point& point);

const Point operator+(const Point& lhs, const Point& rhs);
const Point operator*(const Point& lhs, const int rhs);
const Point operator*(const int lhs, const Point& rhs);

const bool operator==(const Point& lhs, const Point& rhs);
const bool operator!=(const Point& lhs, const Point& rhs);

}  // namespace conga

#endif  // CONGA_POINT_H_
