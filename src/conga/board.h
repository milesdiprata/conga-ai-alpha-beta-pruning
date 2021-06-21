#ifndef CONGA_BOARD_H_
#define CONGA_BOARD_H_

#include <iostream>
#include <string>
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

    inline static const string kBlackStoneColor = "\u001b[31m";
    inline static const string kWhiteStoneColor = "\u001b[34m";
    inline static const string kNoStoneColor = "\033[93m";
    inline static const string kResetColor = "\033[0m";

    StoneType stone_type;
    int num_stones;
  };

  struct Point {
    struct Hasher {
      const size_t operator()(const Point& point) const noexcept {
        return hash<int>()(point.x) ^ (hash<int>()(point.y) << 1);
      }
    };

    Point(const int x = 0, const int y = 0);
    Point(const Point& point);
    ~Point();

    int x;
    int y;
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

const Board::Point operator+(const Board::Point& lhs, const Board::Point& rhs);
const bool operator==(const Board::Point& lhs, const Board::Point& rhs);
const bool operator!=(const Board::Point& lhs, const Board::Point& rhs);

}  // namespace conga

#endif  // CONGA_BOARD_H_
