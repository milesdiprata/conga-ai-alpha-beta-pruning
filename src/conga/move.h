#ifndef CONGA_MOVE_H_
#define CONGA_MOVE_H_

#include <iostream>

#include "conga/point.h"

namespace conga {

struct Move {
  constexpr Move(const Point& point, const Point& direction)
      : point(point), direction(direction) {}

  constexpr Move(const Move& move)
      : point(move.point), direction(move.direction) {}

  Point point;
  Point direction;
};

namespace move {

static constexpr auto kNone = Move(point::kInvalid, point::kInvalid);

}  // namespace move

std::ostream& operator<<(std::ostream& os, const Move& move);

}  // namespace conga

#endif  // CONGA_MOVE_H_