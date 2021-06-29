#include "conga/game.h"

#include <cstddef>
#include <iostream>
#include <memory>
#include <utility>

#include "conga/board.h"
#include "conga/player.h"

namespace conga {
Game::Game(std::unique_ptr<Board>&& board, std::unique_ptr<Player>&& player1,
           std::unique_ptr<Player>&& player2)
    : board_(std::move(board)),
      player1_(std::move(player1)),
      player2_(std::move(player2)) {}

Game::~Game() {}

void Game::Play() {
  std::cout << "Initial board configuration:" << std::endl;
  std::cout << *board_ << std::endl;

  std::size_t num_moves = 0;

  while (1) {
    if (board_->Lost(player1_->stone())) {
      std::cout << "Game Over: Player 1 lost in " << num_moves << " moves."
                << std::endl;
      break;
    }

    auto player1_move = player1_->GetMove(*board_);
    board_->MakeMove(player1_move);
    std::cout << "Player 1 move - " << player1_move << ":" << std::endl;
    std::cout << *board_ << std::endl << std::endl;

    ++num_moves;
    std::cout << "Moves: " << num_moves << std::endl << std::endl;

    if (board_->Lost(player2_->stone())) {
      std::cout << "Game Over: Player 2 lost in " << num_moves << " moves."
                << std::endl;
      break;
    }

    auto player2_move = player2_->GetMove(*board_);
    board_->MakeMove(player2_move);
    std::cout << "Player 2 move - " << player2_move << ":" << std::endl;
    std::cout << *board_ << std::endl << std::endl;
  }
}

}  // namespace conga
