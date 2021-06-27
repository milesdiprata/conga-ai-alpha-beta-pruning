#include <conga/game.h>

#include <iostream>

using namespace std;

namespace conga {
Game::Game(Board* board, Player* player1, Player* player2)
    : board_(board), player1_(player1), player2_(player2) {}

Game::~Game() {}

void Game::Play() {
  cout << *board_ << endl;

  int num_moves = 0;

  while (1) {
    if (player1_->Lost(*board_)) {
      cout << "Game Over: Player 1 lost in " << num_moves << " moves." << endl;
      break;
    }

    // cin.get();

    auto player1_move = player1_->GetMove(*board_);
    cout << "Player 1 move: " << player1_move << endl;
    player1_->MakeMove(*board_, player1_move);
    cout << *board_ << endl << endl;

    ++num_moves;
    cout << "Moves: " << num_moves << endl;

    if (player2_->Lost(*board_)) {
      cout << "Game Over: Player 2 lost in " << num_moves << " moves." << endl;
      break;
    }

    // cin.get();

    auto player2_move = player2_->GetMove(*board_);
    cout << "Player 2 move: " << player2_move << endl;
    player2_->MakeMove(*board_, player2_move);
    cout << *board_ << endl << endl;
  }
}

}  // namespace conga
