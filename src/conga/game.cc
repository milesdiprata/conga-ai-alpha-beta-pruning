// #include <conga/game.h>

// #include <iostream>
// #include <utility>

// namespace conga {
// Game::Game(std::unique_ptr<Board> board, std::unique_ptr<Player> player1,
//            std::unique_ptr<Player> player2)
//     : board_(std::move(board)),
//       player1_(std::move(player1)),
//       player2_(std::move(player2)) {}

// Game::~Game() {}

// void Game::Play() {
//   cout << *board_ << endl;

//   int num_moves = 0;

//   while (1) {
//     if (player1_->Lost(*board_)) {
//       cout << "Game Over: Player 1 lost in " << num_moves << " moves." <<
//       endl; break;
//     }

//     auto player1_move = player1_->GetMove(*board_);
//     player1_->MakeMove(*board_, player1_move);
//     // cin.get();
//     cout << *board_ << endl << endl;
//     cout << "Player 1 move: " << player1_move << endl;

//     ++num_moves;
//     cout << "Moves: " << num_moves << endl;

//     if (player2_->Lost(*board_)) {
//       cout << "Game Over: Player 2 lost in " << num_moves << " moves." <<
//       endl; break;
//     }

//     auto player2_move = player2_->GetMove(*board_);
//     player2_->MakeMove(*board_, player2_move);
//     // cin.get();
//     cout << *board_ << endl << endl;
//     cout << "Player 2 move: " << player2_move << endl;
//   }
// }

// }  // namespace conga
