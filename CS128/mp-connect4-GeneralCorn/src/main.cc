#include <iostream>

#include "board.hpp"

int main() {
  Board test;
  InitBoard(test);

  int lmao[Board::kBoardHeight][Board::kBoardWidth]{

  };

  DropDiskToBoard(test, DiskType::kPlayer1, 2);

  for (int i = 0; i < Board::kBoardHeight; i++) {
    for (int j = 0; j < Board::kBoardWidth; j++) {
      if (test.board[i][j] == DiskType::kEmpty)
        std::cout << 0 << "  ";
      else if (test.board[i][j] == DiskType::kPlayer1)
        std::cout << 1 << "  ";
      else if (test.board[i][j] == DiskType::kPlayer2)
        std::cout << 2 << "  ";
      else
        std::cout << "fail";
    }
    std::cout << std::endl;
  }

  if (CheckForWinner(test, DiskType::kPlayer1) &&
      CheckForWinner(test, DiskType::kPlayer2)) {
    std::cout << "Both Win!";
  } else if (CheckForWinner(test, DiskType::kPlayer1)) {
    std::cout << "Player 1 wins";
  } else if (CheckForWinner(test, DiskType::kPlayer2)) {
    std::cout << "PLayer 2 wins";
  } else {
    std::cout << "Noone wins!";
  }

  std::cout << std::endl;
  // Board b;
}