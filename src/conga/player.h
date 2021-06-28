// #ifndef CONGA_PLAYER_H_
// #define CONGA_PLAYER_H_

// #include <conga/board.h>

// #include <string>
// #include <vector>

// using namespace std;

// namespace conga {

// class Player {
//  public:
//   struct Move {
//     Move(const Board::Point& point, const Board::Action action);
//     ~Move();

//     Board::Point point;
//     Board::Action action;
//   };

//   inline static const auto kNoMove =
//       Move(Board::kInvalidPoint, Board::Action::kNone);

//   Player(const Board::StoneType stone_type);
//   virtual ~Player();

//   inline const Board::StoneType stone_type() const { return stone_type_; }
//   inline const Board::StoneType opponent_stone_type() const {
//     return opponent_stone_type_;
//   }

//   virtual const Move GetMove(const Board& board) const;

//   void MakeMove(Board& board, const Move& move) const;

//   const bool Lost(const Board& board) const;

//  protected:
//   static const bool ValidMove(const Board& board, const Move& move);

//   static const vector<Board::Action> ValidActions(const Board& board,
//                                                   const Board::Point& point);

//   static const vector<Move> ValidMoves(const Board& board,
//                                        const Board::StoneType stone_type);

//  private:
//   Board::StoneType stone_type_;
//   Board::StoneType opponent_stone_type_;
// };

// ostream& operator<<(ostream& os, const Player::Move& action);

// template <typename T>
// string to_string(const T& value);

// }  // namespace conga

// #endif  // CONGA_PLAYER_H_
