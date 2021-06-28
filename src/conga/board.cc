#include <conga/board.h>
#include <conga/square.h>

#include <iostream>
#include <utility>
#include <vector>

namespace conga {

Board::Board() { Reset(); }

Board::Board(const Board& board) : squares_(board.squares_) {}

Board::Board(Board&& board) : squares_(move(board.squares_)) {}

Board::Board::~Board() {}

const std::vector<Point> Board::Points(const Square::State state) const {
  auto points = std::vector<Point>();
  for (int x = 1; x <= kBoardLength; ++x) {
    for (int y = 1; y <= kBoardLength; ++y) {
      auto point = Point(x, y);
      if (squares_[TransformPoint(point)].state == state) {
        points.push_back(point);
      }
    }
  }

  return points;
}

void Board::Reset() {
  for (std::size_t i = 0; i < kBoardLength * kBoardLength; ++i) {
    squares_[i] = Square();
  }

  squares_[TransformPoint(kPlayer1Start)] =
      Square(Square::State::kBlackStones, kInitialNumStones);
  squares_[TransformPoint(kPlayer2Start)] =
      Square(Square::State::kWhiteStones, kInitialNumStones);
}

std::ostream& operator<<(std::ostream& os, const Board& board) {
  for (int i = 0; i <= Board::kBoardLength; ++i) {
    os << "*****";
  }
  os << std::endl;

  for (int y = Board::kBoardLength; y > 0; --y) {
    for (int i = 0; i < Board::kBoardLength; ++i) {
      if (i == 0) {
        os << "*";
      }
      os << "     *";
    }
    os << std::endl;

    for (int x = 1; x <= Board::kBoardLength; ++x) {
      os << "*";
      auto square = board[Point(x, y)];
      if (square.num_stones > 9) {
        os << " " << square << " ";
      } else {
        os << "  " << square << "  ";
      }
    }
    os << "*" << std::endl;

    for (int i = 0; i < Board::kBoardLength; ++i) {
      if (i == 0) {
        os << "*";
      }
      os << "     *";
    }
    os << std::endl;

    for (int i = 0; i <= Board::kBoardLength; ++i) {
      os << "*****";
    }

    if (y != 1) {
      os << std::endl;
    }
  }

  return os;
}

}  // namespace conga
