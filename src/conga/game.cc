#include <conga/game.h>

namespace conga {

Game::Game(const Agent& player1, const Agent& player2, const Board& board)
    : player1_(player1), player2_(player2), board_(board), over_(false) {}

Game::~Game() {}

void Game::PlayRound() {}

void Game::PlayTurn(const Agent& player) {}

}  // namespace conga