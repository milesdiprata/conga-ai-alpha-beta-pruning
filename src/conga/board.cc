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
        board_[point] = Cell(PlayerId::k1, kInitialNumStones);
      } else if (point == kPlayer2Start) {
        board_[point] = Cell(PlayerId::k2, kInitialNumStones);
      } else {
        board_[point] = Cell();
      }
    }
  }
}

Board::Cell::Cell(const PlayerId occupier, const int num_stones)
    : occupier(occupier), num_stones(num_stones) {}

Board::Cell::~Cell() {}

Board::Point::Point(const int x, const int y) : x(x), y(y) {}

Board::Point::Point(const Point& point) : x(point.x), y(point.y) {}

Board::Point::~Point() {}

ostream& operator<<(ostream& os, const Board::PlayerId player_id) {
  static unordered_map<Board::PlayerId, string> strings;
  if (strings.empty()) {
    strings[Board::PlayerId::k1] = "Player 1";
    strings[Board::PlayerId::k2] = "Player 2";
    strings[Board::PlayerId::kNone] = "Unoccupied";
  }

  return os << strings[player_id];
}

ostream& operator<<(ostream& os, const Board::Move move) {
  static unordered_map<Board::Move, string> strings;
  if (strings.empty()) {
    strings[Board::Move::kUp] = "Up";
    strings[Board::Move::kUpRight] = "Up, right";
    strings[Board::Move::kRight] = "Right";
    strings[Board::Move::kDownRight] = "Down, right";
    strings[Board::Move::kDown] = "Down";
    strings[Board::Move::kDownLeft] = "Down, left";
    strings[Board::Move::kLeft] = "Left";
    strings[Board::Move::kUpLeft] = "Up, left";
  }

  return os << strings[move];
}

ostream& operator<<(ostream& os, const Board::Cell& cell) {
  if (cell.occupier == Board::PlayerId::k1) {
    os << Board::Cell::kPlayer1Color;
  } else if (cell.occupier == Board::PlayerId::k2) {
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
