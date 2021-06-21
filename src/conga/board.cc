#include <conga/board.h>

#include <utility>

namespace conga {

Board::Cell::Cell(const StoneType stone_type, const int num_stones)
    : stone_type(stone_type), num_stones(num_stones) {}

ostream& operator<<(ostream& os, const Board::Cell& cell) {
  if (cell.stone_type == StoneType::kBlack) {
    os << Board::Cell::kBlackStoneColor;
  } else if (cell.stone_type == StoneType::kWhite) {
    os << Board::Cell::kWhiteStoneColor;
  } else {
    os << Board::Cell::kNoStoneColor;
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

Board::Board() { Clear(); }

Board::Board(const Board& board) : board_(board.board_) {}

Board::Board(Board&& board) : board_(std::move(board.board_)) {}

Board::Board::~Board() {}

void Board::Clear() {
  for (int i = 1; i <= kBoardLength; ++i) {
    for (int j = 1; j <= kBoardLength; ++j) {
      auto point = Point(i, j);
      if (point == kPlayer1Start) {
        board_[point] = Cell(StoneType::kWhite, kInitialNumStones);
      } else if (point == kPlayer2Start) {
        board_[point] = Cell(StoneType::kBlack, kInitialNumStones);
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
