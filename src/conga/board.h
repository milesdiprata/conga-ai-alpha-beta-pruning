#ifndef CONGA_BOARD_H_
#define CONGA_BOARD_H_

#include <conga/move.h>
#include <conga/point.h>
#include <conga/square.h>

#include <array>
#include <iostream>
#include <string>
#include <vector>

namespace conga {

class Board {
 public:
  static constexpr int kBoardLength = 4;
  static constexpr int kInitialNumStones = 10;

  inline static const auto kPlayer1Start = Point(1, 4);
  inline static const auto kPlayer2Start = Point(4, 1);

  Board();
  Board(const Board& board);
  Board(Board&& board);
  ~Board();

  inline Square& operator[](const Point& point) {
    return squares_[FlattenPoint(point)];
  }

  inline const Square& operator[](const Point& point) const {
    return squares_[FlattenPoint(point)];
  }

  const std::vector<Point> Points(const Stone& stone) const;

  void Reset();

  void MakeMove(const Move& move);

  friend std::ostream& operator<<(std::ostream& os, const Board& board);

 private:
  inline static const std::size_t FlattenPoint(const Point& point) {
    return (point.y - 1) * kBoardLength + (point.x - 1);
  }

  inline static const bool ValidPoint(const Point& point) {
    return point.x >= 1 && point.y >= 1 && point.x <= kBoardLength &&
           point.y <= kBoardLength;
  }

  const bool ValidMove(const Move& move) const;

  std::array<Square, kBoardLength * kBoardLength> squares_;
};

std::ostream& operator<<(std::ostream& os, const Board& board);

template <typename T>
const std::string to_string(const T& value);

}  // namespace conga

#endif  // CONGA_BOARD_H_
