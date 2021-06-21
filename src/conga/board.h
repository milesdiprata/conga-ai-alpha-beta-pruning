#ifndef CONGA_BOARD_H_
#define CONGA_BOARD_H_

#include <iostream>
#include <unordered_map>

using namespace std;

namespace conga {

enum class Player {
  kPlayer1,
  kPlayer2,
};

enum class StoneType {
  kBlack,
  kWhite,
  kNone,
};

class Board {
 public:
  struct Cell {
    Cell(const StoneType stone_type = StoneType::kNone,
         const int num_stones = 0);
    ~Cell();

    StoneType stone_type;
    int num_stones;
  };

  class Point {
   public:
    struct Hasher {
      const size_t operator()(const Point& point) const noexcept {
        return hash<int>()(point.x_) ^ (hash<int>()(point.y_) << 1);
      }
    };

    Point(const int x = 0, const int y = 0);
    Point(const Point& point);
    ~Point();

    inline int& x() { return x_; }
    inline const int x() const { return x_; }

    inline int& y() { return y_; }
    inline const int y() const { return y_; }

    friend const Point operator+(const Point& lhs, const Point& rhs);
    friend const bool operator==(const Point& lhs, const Point& rhs);
    friend const bool operator!=(const Point& lhs, const Point& rhs);
    friend ostream& operator<<(ostream& os, const Point& point);

   private:
    int x_;
    int y_;
  };

  static constexpr int kBoardLength = 4;
  static constexpr int kInitialNumStones = 10;

  inline static const Point kPlayer1Start = Point(1, 4);
  inline static const Point kPlayer2Start = Point(4, 1);

  Board();
  Board(const Board& board);
  Board(Board&& board);
  ~Board();

  void Clear();

  inline Cell& At(const int x, const int y) { return board_[Point(x, y)]; }
  inline const Cell& At(const int x, const int y) const {
    return board_.at(Point(x, y));
  }

  inline Cell& At(const Point& point) { return board_[point]; }
  inline const Cell& At(const Point& point) const { return board_.at(point); }

  friend ostream& operator<<(ostream& os, const Board& board);

 private:
  unordered_map<Point, Cell, Point::Hasher> board_;
};

ostream& operator<<(ostream& os, const Board::Cell& cell);
ostream& operator<<(ostream& os, const Board::Point& point);
ostream& operator<<(ostream& os, const Board& board);

}  // namespace conga

#endif  // CONGA_BOARD_H_
