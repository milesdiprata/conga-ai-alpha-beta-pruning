#ifndef CONGA_MOVE_H_
#define CONGA_MOVE_H_

#include <conga/point.h>

namespace conga {

struct Move {
  Move(const Point& point, const Point& direction);
  Move(const Move& move);
  ~Move();

  Point point;
  Point direction;
};

}  // namespace conga

#endif  // CONGA_MOVE_H_