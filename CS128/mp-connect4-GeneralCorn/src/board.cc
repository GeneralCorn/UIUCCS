#include "board.hpp"

// you might need additional includes
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

// starting with my functions

void InitBoard(Board& b) {
  for (unsigned int i = 0; i < Board::kBoardHeight; ++i) {
    for (unsigned int j = 0; j < Board::kBoardWidth; ++j) {
      b.board[i][j] = DiskType::kEmpty;
    }
  }
}

void DropDiskToBoard(Board& b, DiskType disk, int col) {
  if (col < 0 || col >= Board::kBoardWidth)
    throw std::runtime_error("invalid column");

  bool sent = false;
  for (int i = 0; i < Board::kBoardHeight; i++) {
    if (b.board[i][col] == DiskType::kEmpty) {
      b.board[i][col] = disk;
      sent = true;
      break;
    }
  }
  if (!sent) throw std::runtime_error("column filled");
}

bool CheckForWinner(Board& b, DiskType disk) {
  bool sentinel = false;
  if (SearchForWinner(b, disk, WinningDirection::kRightDiag) ||
      SearchForWinner(b, disk, WinningDirection::kLeftDiag) ||
      SearchForWinner(b, disk, WinningDirection::kHorizontal) ||
      SearchForWinner(b, disk, WinningDirection::kVertical)) {
    sentinel = true;
  }
  return sentinel;
}

bool SearchForWinner(Board& b, DiskType disk, WinningDirection to_check) {
  switch (to_check) {
  case WinningDirection::kRightDiag:
    return RDiagDir(b, disk);
  case WinningDirection::kLeftDiag:
    return LDiagDir(b, disk);
  case WinningDirection::kHorizontal:
    return HorizDir(b, disk);
  case WinningDirection::kVertical:
    return VertDir(b, disk);
  default:
    return false;
  }
}

int t1 = Board::kBoardHeight;

bool LDiagDir(Board& b, DiskType disk) {
  for (int index = 3; index < t1; index++) {
    for (int j = index; j > 2; j--) {
      if (b.board[j][index - j] == disk &&
          b.board[j - 1][index - j + 1] == disk &&
          b.board[j - 2][index - j + 2] == disk &&
          b.board[j - 3][index - j + 3] == disk) {
        return true;
      }
    }
  }
  for (int index = 3; index < t1; index++) {
    for (int j = t1 - 1; j > index - 1; j--) {
      if (b.board[j][index - j + 3] == disk &&
          b.board[j - 1][index - j + 4] == disk &&
          b.board[j - 2][index - j + (t1 - 1)] == disk &&
          b.board[j - 3][index - j + t1] == disk) {
        return true;
      }
    }
  }
  return false;
}

bool RDiagDir(Board& b, DiskType disk) {
  for (int index = 0; index < t1; index++) {
    for (int j = t1; j > index + 2; j--) {
      if (b.board[j - index][j + 1] == disk &&
          b.board[j - index - 1][j] == disk &&
          b.board[j - index - 2][j - 1] == disk &&
          b.board[j - index - 3][j - 2] == disk) {
        return true;
      }
    }
  }
  for (int index = 3; index < t1; index++) {
    for (int j = t1 - 1; j > t1 + 1 - index; j--) {
      if (b.board[j][index + j - (t1 - 1)] == disk &&
          b.board[j - 1][index + j - t1] == disk &&
          b.board[j - 2][index + j - (t1 + 1)] == disk &&
          b.board[j - 3][index + j - (t1 + 2)] == disk) {
        return true;
      }
    }
  }
  return false;
}

bool HorizDir(Board& b, DiskType disk) {
  for (unsigned int i = 0; i < Board::kBoardHeight; ++i) {
    for (unsigned int j = 0; j < Board::kBoardHeight - 2; ++j) {
      if (b.board[i][j] == disk && b.board[i][j + 1] == disk &&
          b.board[i][j + 2] == disk && b.board[i][j + 3] == disk) {
        return true;
      }
    }
  }
  return false;
}

bool VertDir(Board& b, DiskType disk) {
  for (unsigned int i = 0; i < Board::kBoardWidth; ++i) {
    for (unsigned int j = 0; j < Board::kBoardHeight - 3; ++j) {
      if (b.board[j][i] == disk && b.board[j + 1][i] == disk &&
          b.board[j + 2][i] == disk && b.board[j + 3][i] == disk) {
        return true;
      }
    }
  }
  return false;
}

bool BoardLocationInBounds(int row, int col) {
  if (row >= 0 && row < Board::kBoardHeight) {
    if (col >= 0 && col < Board::kBoardWidth) {
      return true;
    }
  }
  return false;
}
/*
void CopyBoard(DiskType solution[Board::kBoardHeight][Board::kBoardWidth],
               Board& student) {
  for (unsigned int i = 0; i < Board::kBoardHeight; ++i) {
    for (unsigned int j = 0; j < Board::kBoardWidth; ++j) {
      student.board[i][j] = solution[i][j];
    }
  }
}
*/
/**************************************************************************/
/* provided to you */
/**************************************************************************/
std::string BoardToStr(const Board& b) {
  constexpr int kTotalWidth = Board::kBoardWidth * 11 - Board::kBoardHeight - 1;
  std::stringstream ss;
  ss << std::endl;
  for (int row = Board::kBoardHeight; row > 0; --row) {
    ss << " |";
    for (int col = 0; col < Board::kBoardWidth; ++col) {
      std::string value_here;
      value_here.push_back(static_cast<char>(b.board[row - 1][col]));
      ss << ' ' << CenterStr(value_here, Board::kBoardWidth + 1) << '|';
    }
    ss << std::endl;
    ss << " |" << std::setw(kTotalWidth) << std::setfill('-') << '|'
       << std::endl;
  }
  ss << " |";
  for (int col = 0; col < Board::kBoardWidth; ++col) {
    ss << ' ' << CenterStr(std::to_string(col), Board::kBoardWidth + 1) << '|';
  }
  return ss.str();
}

std::string CenterStr(const std::string& str, int col_width) {
  // quick and easy (but error-prone) implementation
  auto padl = (col_width - str.length()) / 2;
  auto padr = (col_width - str.length()) - padl;
  std::string strf = std::string(padl, ' ') + str + std::string(padr, ' ');
  return strf;
}