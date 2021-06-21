#include <conga/agent.h>
#include <conga/board.h>

#include <iostream>

using namespace std;

int main(const int argc, const char* const argv[]) {
  auto player1 = conga::Agent(conga::Board::Player::k1);
  auto player2 = conga::Agent(conga::Board::Player::k1);

  auto board = conga::Board();
  cout << board << endl;

  return 0;
}