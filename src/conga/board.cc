#include <conga/board.h>

#include <string>
#include <utility>

namespace conga {

Board::Cell::Cell(const StoneType stone_type, const int num_stones)
    : stone_type(stone_type), num_stones(num_stones) {}

ostream& operator<<(ostream& os, const Board::Cell& cell) {
  os << "(";
  if (cell.stone_type == StoneType::kBlack)
    os << "B";
  else if (cell.stone_type == StoneType::kWhite)
    os << "W";
  else
    os << "N";
  os << ", " << cell.num_stones << ")";

  return os;
}

Board::Cell::~Cell() {}

Board::Point::Point(const int x, const int y) : x_(x), y_(y) {}

Board::Point::Point(const Point& point) : x_(point.x_), y_(point.y_) {}

Board::Point::~Point() {}

inline const Board::Point operator+(const Board::Point& lhs,
                                    const Board::Point& rhs) {
  return Board::Point(lhs.x_ + rhs.x_, lhs.y_ + rhs.y_);
}

inline const bool operator==(const Board::Point& lhs, const Board::Point& rhs) {
  return lhs.x_ == rhs.x_ && lhs.y_ == rhs.y_;
}

inline const bool operator!=(const Board::Point& lhs, const Board::Point& rhs) {
  return lhs.x_ != rhs.x_ || lhs.y_ != rhs.y_;
}

ostream& operator<<(ostream& os, const Board::Point& point) {
  os << "(" << point.x_ << ", " << point.y_ << ")";
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

  string seperator = "";
  for (int y = Board::kBoardLength; y > 0; --y) {
    for (int i = 0; i < Board::kBoardLength; ++i) {
      if (i == 0) {
        os << "*";
      }
      os << "     *";
    }
    os << endl;

    for (int x = 1; x <= Board::kBoardLength; ++x) {
      Board::Cell cell = board.board_.at(Board::Point(x, y));
      os << "*";
      if (cell.stone_type == StoneType::kBlack) {
        os << "\u001b[31m";  // Red
      } else if (cell.stone_type == StoneType::kWhite) {
        os << "\u001b[34m";  // Blue
      } else {
        os << "\033[93m";  // Yellow
      }

      if (cell.num_stones > 9) {
        os << " > 9 "
           << "\033[0m";
      } else {
        os << "  " << cell.num_stones << "\033[0m"
           << "  ";
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
