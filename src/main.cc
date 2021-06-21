#include <conga/board.h>

#include <iostream>

using namespace std;

int main(const int argc, const char* const argv[]) {
  auto board = conga::Board();
  cout << board << endl;
  return 0;
}