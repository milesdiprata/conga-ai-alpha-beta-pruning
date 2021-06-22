#include <conga/board.h>

#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>

using namespace std;

namespace conga {

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
        board_[point] = Cell(StoneType::kBlack, kInitialNumStones);
      } else if (point == kPlayer2Start) {
        board_[point] = Cell(StoneType::kWhite, kInitialNumStones);
      } else {
        board_[point] = Cell();
      }
    }
  }
}

Board::Cell::Cell(const StoneType stone_type, const int num_stones)
    : stone_type(stone_type), num_stones(num_stones) {}

Board::Cell::~Cell() {}

Board::Point::Point(const int x, const int y) : x(x), y(y) {}

Board::Point::Point(const Point& point) : x(point.x), y(point.y) {}

Board::Point::~Point() {}

ostream& operator<<(ostream& os, const Board::StoneType stone_type) {
  static unordered_map<Board::StoneType, string> strings;
  if (strings.empty()) {
#define INSERT_ELEMENT(p) strings[p] = #p
    INSERT_ELEMENT(Board::StoneType::kBlack);
    INSERT_ELEMENT(Board::StoneType::kWhite);
    INSERT_ELEMENT(Board::StoneType::kNone);
#undef INSERT_ELEMENT
  }

  return os << strings[stone_type];
}

ostream& operator<<(ostream& os, const Board::Move move) {
  static unordered_map<Board::Move, string> strings;
  if (strings.empty()) {
#define INSERT_ELEMENT(p) strings[p] = #p
    INSERT_ELEMENT(Board::Move::kUp);
    INSERT_ELEMENT(Board::Move::kUpRight);
    INSERT_ELEMENT(Board::Move::kRight);
    INSERT_ELEMENT(Board::Move::kDownRight);
    INSERT_ELEMENT(Board::Move::kDown);
    INSERT_ELEMENT(Board::Move::kDownLeft);
    INSERT_ELEMENT(Board::Move::kLeft);
    INSERT_ELEMENT(Board::Move::kUpLeft);
    INSERT_ELEMENT(Board::Move::kNone);
#undef INSERT_ELEMENT
  }

  return os << strings[move];
}

ostream& operator<<(ostream& os, const Board::Cell& cell) {
  if (cell.stone_type == Board::StoneType::kBlack) {
    os << Board::Cell::kPlayer1Color;
  } else if (cell.stone_type == Board::StoneType::kWhite) {
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

ostream& operator<<(ostream& os, const Board::Point& point) {
  os << "(" << point.x << ", " << point.y << ")";
  return os;
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

const Board::Point operator+(const Board::Point& lhs, const Board::Point& rhs) {
  return Board::Point(lhs.x + rhs.x, lhs.y + rhs.y);
}

const Board::Point operator*(const Board::Point& lhs, const int rhs) {
  return Board::Point(lhs.x * rhs, lhs.y * rhs);
}

const Board::Point operator*(const int lhs, const Board::Point& rhs) {
  return Board::Point(rhs.x * lhs, rhs.y * lhs);
}

const bool operator==(const Board::Point& lhs, const Board::Point& rhs) {
  return lhs.x == rhs.x && lhs.y == rhs.y;
}

const bool operator!=(const Board::Point& lhs, const Board::Point& rhs) {
  return lhs.x != rhs.x || lhs.y != rhs.y;
}

}  // namespace conga
