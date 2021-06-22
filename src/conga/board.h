#ifndef CONGA_BOARD_H_
#define CONGA_BOARD_H_

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

namespace conga {

class Board {
 public:
  enum class StoneType {
    kBlack,
    kWhite,
    kNone,
  };

  enum class Move {
    kUp,
    kUpRight,
    kRight,
    kDownRight,
    kDown,
    kDownLeft,
    kLeft,
    kUpLeft,
    kNone,
  };

  struct Cell {
    Cell(const StoneType stone_type = StoneType::kNone,
         const int num_stones = 0);
    ~Cell();

    inline static const string kPlayer1Color = "\u001b[31m";
    inline static const string kPlayer2Color = "\u001b[34m";
    inline static const string kNoPlayerColor = "\033[93m";
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

  inline static const auto kPlayer1Start = Point(1, 4);
  inline static const auto kPlayer2Start = Point(4, 1);

  inline static const auto kMoveDirections = unordered_map<Move, Point>{
      {Move::kUp, Point(0, 1)},    {Move::kUpRight, Point(1, 1)},
      {Move::kRight, Point(1, 0)}, {Move::kDownRight, Point(1, -1)},
      {Move::kDown, Point(0, -1)}, {Move::kDownLeft, Point(-1, -1)},
      {Move::kLeft, Point(-1, 0)}, {Move::kUpLeft, Point(-1, 1)}};

  Board();
  Board(const Board& board);
  Board(Board&& board);
  ~Board();

  inline const bool HasPoint(const int x, const int y) const {
    return board_.count(Point(x, y));
  }

  inline const bool HasPoint(const Point& point) const {
    return board_.count(point);
  }

  inline const Cell& At(const int x, const int y) const {
    return board_.at(Point(x, y));
  }

  inline const Cell& At(const Point& point) const { return board_.at(point); }

  inline Cell& At(const int x, const int y) { return board_[Point(x, y)]; }

  inline Cell& At(const Point& point) { return board_[point]; }

  void Reset();

  const vector<Point> OccupiedPoints(const StoneType stone_type) const;

  friend ostream& operator<<(ostream& os, const Board& board);

 private:
  unordered_map<Point, Cell, Point::Hasher> board_;
};

ostream& operator<<(ostream& os, const Board::StoneType player_id);
ostream& operator<<(ostream& os, const Board::Move move);
ostream& operator<<(ostream& os, const Board::Cell& cell);
ostream& operator<<(ostream& os, const Board::Point& point);
ostream& operator<<(ostream& os, const Board& board);

const Board::Point operator+(const Board::Point& lhs, const Board::Point& rhs);
const Board::Point operator*(const Board::Point& lhs, const int rhs);
const Board::Point operator*(const int lhs, const Board::Point& rhs);

const bool operator==(const Board::Point& lhs, const Board::Point& rhs);
const bool operator!=(const Board::Point& lhs, const Board::Point& rhs);

}  // namespace conga

#endif  // CONGA_BOARD_H_
