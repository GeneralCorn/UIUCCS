#ifndef BOARD_HPP
#define BOARD_HPP

#include <string>

enum class WinningDirection { kHorizontal, kVertical, kRightDiag, kLeftDiag };
enum class DiskType { kPlayer1 = 82, kPlayer2 = 66, kEmpty = 32 };

struct Board {
  static constexpr int kBoardWidth = 7;
  static constexpr int kBoardHeight = 6;
  DiskType board[kBoardHeight][kBoardWidth];
};

void InitBoard(Board& b);
void DropDiskToBoard(Board& b, DiskType disk, int col);
bool CheckForWinner(Board& b, DiskType disk);
bool SearchForWinner(Board& b, DiskType disk, WinningDirection to_check);
bool BoardLocationInBounds(int row, int col);

bool HorizDir(Board& b, DiskType disk);
bool VertDir(Board& b, DiskType disk);
bool RDiagDir(Board& b, DiskType disk);
bool LDiagDir(Board& b, DiskType disk);
// void CopyBoard(DiskType solution[Board::kBoardHeight][Board::kBoardWidth],
//                Board& student);

// provided
std::string BoardToStr(const Board& b);
std::string CenterStr(const std::string& str, int col_width);

#endif