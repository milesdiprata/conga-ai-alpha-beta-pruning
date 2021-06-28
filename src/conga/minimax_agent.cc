// #include <conga/board.h>
// #include <conga/minimax_agent.h>
// #include <time.h>

// #include <algorithm>
// #include <cmath>
// #include <functional>
// #include <memory>
// #include <vector>

// using namespace std;

// namespace conga {

// MinimaxAgent::MinimaxAgent(const Board::StoneType player_id,
//                            const Evaluation evaluation,
//                            const size_t search_depth)
//     : Agent(player_id), evaluation_(evaluation), search_depth_(search_depth)
//     {}

// MinimaxAgent::~MinimaxAgent() {}

// const Player::Move MinimaxAgent::ComputeMove(const Board& board) const {
//   return AlphaBetaSearch(board);
// }

// const Player::Move MinimaxAgent::AlphaBetaSearch(const Board& board) const {
//   int best_value = INT_MIN;
//   auto best_move = kNoMove;

//   auto valid_moves = ValidMoves(board, stone_type());
//   for (const auto& valid_move : valid_moves) {
//     auto new_board = Board(board);
//     MakeMove(new_board, valid_move);

//     int value = MinValue(new_board, search_depth_, INT_MIN, INT_MAX);
//     if (value > best_value) {
//       best_value = value;
//       best_move = valid_move;
//     }
//   }

//   return best_move;
// }

// const int MinimaxAgent::MaxValue(const Board& board, const int depth, int
// alpha,
//                                  int beta) const {
//   auto valid_moves = ValidMoves(board, stone_type());
//   if (CutoffTest(depth, valid_moves)) {
//     return EvaluateState(board);
//   }

//   for (const auto& valid_move : valid_moves) {
//     auto new_board = Board(board);
//     MakeMove(new_board, valid_move);
//     alpha = max(alpha, MinValue(new_board, depth - 1, alpha, beta));
//     if (alpha >= beta) {
//       return beta;
//     }
//   }

//   return alpha;
// }

// const int MinimaxAgent::MinValue(const Board& board, const int depth, int
// alpha,
//                                  int beta) const {
//   auto valid_moves = ValidMoves(board, opponent_stone_type());
//   if (CutoffTest(depth, valid_moves)) {
//     return EvaluateState(board);
//   }

//   for (const auto& valid_move : valid_moves) {
//     auto new_board = Board(board);
//     MakeMove(new_board, valid_move);
//     beta = min(beta, MaxValue(new_board, depth - 1, alpha, beta));
//     if (beta <= alpha) {
//       return alpha;
//     }
//   }

//   return beta;
// }

// inline const bool MinimaxAgent::CutoffTest(const int depth,
//                                            const vector<Move>& moves) {
//   return depth == 0 || moves.empty();
// }

// const int MinimaxAgent::EvaluateState(const Board& board) const {
//   if (evaluation_ == Evaluation::kPlayerMoves) {
//     return ValidMoves(board, stone_type()).size();
//   } else if (evaluation_ == Evaluation::kOpponentMoves) {
//     return -1 * ValidMoves(board, opponent_stone_type()).size();
//   } else if (evaluation_ == Evaluation::kPlayerMinusOpponentMoves) {
//     return ValidMoves(board, stone_type()).size() -
//            ValidMoves(board, opponent_stone_type()).size();
//   } else {
//     return INT_MIN;
//   }
// }

// }  // namespace conga
