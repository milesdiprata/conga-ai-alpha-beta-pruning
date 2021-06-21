#include <conga/agent.h>
#include <conga/game.h>

#include <iostream>

using namespace std;

int main(const int argc, const char* const argv[]) {
  auto player1 = conga::Agent(conga::Game::Player::k1);
  auto player2 = conga::Agent(conga::Game::Player::k1);

  auto board = conga::Board();
  cout << board << endl;

  auto game = conga::Game(player1, player2, board);

  while (!game.over()) {
    game.PlayRound();
  }

  return 0;
}