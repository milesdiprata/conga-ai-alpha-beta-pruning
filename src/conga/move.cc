#include <conga/move.h>
#include <conga/point.h>

namespace conga {

Move::Move(const Point& point, const Point& direction)
    : point(point), direction(direction) {}

Move::Move(const Move& move) : point(move.point), direction(move.direction) {}

Move::~Move() {}

}  // namespace conga
