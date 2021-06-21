#include <conga/board.h>

#include <utility>

using namespace std;

namespace conga {

Board::Cell::Cell(const Player occupier, const int num_stones)
    : occupier(occupier), num_stones(num_stones) {}

ostream& operator<<(ostream& os, const Board::Cell& cell) {
  if (cell.occupier == Board::Player::k1) {
    os << Board::Cell::kPlayer1Color;
  } else if (cell.occupier == Board::Player::k2) {
    os << Board::Cell::kPlayer2Color;
  } else {
    os << Board::Cell::kNoPlayerColor;
  }

  if (cell.num_stones > 9) {
    os << "> 9";
  } else {
    os << cell.num_stones;
  }

  os << Board::Cell::kResetColor;

  return os;
}

Board::Cell::~Cell() {}

Board::Point::Point(const int x, const int y) : x(x), y(y) {}

Board::Point::Point(const Point& point) : x(point.x), y(point.y) {}

Board::Point::~Point() {}

inline const Board::Point operator+(const Board::Point& lhs,
                                    const Board::Point& rhs) {
  return Board::Point(lhs.x + rhs.x, lhs.y + rhs.y);
}

inline const bool operator==(const Board::Point& lhs, const Board::Point& rhs) {
  return lhs.x == rhs.x && lhs.y == rhs.y;
}

inline const bool operator!=(const Board::Point& lhs, const Board::Point& rhs) {
  return lhs.x != rhs.x || lhs.y != rhs.y;
}

ostream& operator<<(ostream& os, const Board::Point& point) {
  os << "(" << point.x << ", " << point.y << ")";
  return os;
}

Board::Board() { Reset(); }

Board::Board(const Board& board) : board_(board.board_) {}

Board::Board(Board&& board) : board_(move(board.board_)) {}

Board::Board::~Board() {}

void Board::Reset() {
  if (!board_.empty()) {
    board_.clear();
  }

  for (int x = 1; x <= kBoardLength; ++x) {
    for (int y = 1; y <= kBoardLength; ++y) {
      auto point = Point(x, y);
      if (point == kPlayer1Start) {
        board_[point] = Cell(Player::k1, kInitialNumStones);
      } else if (point == kPlayer2Start) {
        board_[point] = Cell(Player::k2, kInitialNumStones);
      } else {
        board_[point] = Cell();
      }
    }
  }
}

ostream& operator<<(ostream& os, const Board& board) {
  for (int i = 0; i <= Board::kBoardLength; ++i) {
    os << "*****";
  }
  os << endl;

  for (int y = Board::kBoardLength; y > 0; --y) {
    for (int i = 0; i < Board::kBoardLength; ++i) {
      if (i == 0) {
        os << "*";
      }
      os << "     *";
    }
    os << endl;

    for (int x = 1; x <= Board::kBoardLength; ++x) {
      os << "*";
      auto cell = board.board_.at(Board::Point(x, y));
      if (cell.num_stones > 9) {
        os << " " << cell << " ";
      } else {
        os << "  " << cell << "  ";
      }
    }
    cout << "*" << endl;

    for (int i = 0; i < Board::kBoardLength; ++i) {
      if (i == 0) {
        os << "*";
      }
      os << "     *";
    }
    os << endl;

    for (int i = 0; i <= Board::kBoardLength; ++i) {
      os << "*****";
    }

    if (y != 1) {
      os << endl;
    }
  }

  return os;
}

}  // namespace conga
