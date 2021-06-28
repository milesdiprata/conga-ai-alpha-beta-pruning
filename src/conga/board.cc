#include <conga/board.h>
#include <conga/square.h>

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <utility>
#include <vector>

namespace conga {

Board::Board() { Reset(); }

Board::Board(const Board& board) : squares_(board.squares_) {}

Board::Board(Board&& board) : squares_(move(board.squares_)) {}

Board::Board::~Board() {}

const std::vector<Point> Board::Points(const Stone& stone) const {
  auto points = std::vector<Point>();
  for (int x = 1; x <= kBoardLength; ++x) {
    for (int y = 1; y <= kBoardLength; ++y) {
      auto point = Point(x, y);
      auto& square = squares_[TransformPoint(point)];
      if (square.stone && square.stone == stone) {
        points.push_back(point);
      }
    }
  }

  return points;
}

void Board::Reset() {
  for (auto& square : squares_) {
    square = Square();
  }

  squares_[TransformPoint(kPlayer1Start)] =
      Square(Stone::kBlack, kInitialNumStones);
  squares_[TransformPoint(kPlayer2Start)] =
      Square(Stone::kWhite, kInitialNumStones);
}

void Board::MakeMove(const Move& move) {
  if (!ValidMove(move)) {
    throw std::invalid_argument("Invalid move in direction " +
                                to_string(move.direction) + " from point " +
                                to_string(move.point) + "!");
  }

  auto& cell = (*this)[move.point];

  for (int i = 1; i <= 3; ++i) {
    if (!ValidPoint(move.point + (i * move.direction))) {
      break;
    }

    auto& curr_cell = (*this)[move.point + (i * move.direction)];
    if (curr_cell.stone && curr_cell.stone != cell.stone) {
      break;
    }

    curr_cell.stone = cell.stone;

    auto next_point = move.point + ((i + 1) * move.direction);
    auto& next_cell = (*this)[next_point];

    if (i == 3 || cell.num_stones < i || !ValidPoint(next_point) ||
        (next_cell.stone && next_cell.stone != cell.stone)) {
      curr_cell.num_stones += cell.num_stones;
      std::cout << cell.num_stones << "\n";
      cell.num_stones = 0;
    } else {
      curr_cell.num_stones += i;
      cell.num_stones -= i;
    }

    if (cell.num_stones == 0) {
      cell.stone.reset();
      break;
    }
  }
}

const bool Board::ValidMove(const Move& move) const {
  if (!ValidPoint(move.point) || !ValidPoint(move.point + move.direction)) {
    return false;
  }

  auto& square = (*this)[move.point];
  auto& next_square = (*this)[move.point + move.direction];

  if (!square.stone ||
      (next_square.stone && next_square.stone != square.stone)) {
    return false;
  }

  return true;
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

template <typename T>
const std::string to_string(const T& value) {
  auto sstream = std::stringstream();
  sstream << value;
  return sstream.str();
}

}  // namespace conga
