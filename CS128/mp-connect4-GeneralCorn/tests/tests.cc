// clang-format off
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//  Written By : Michael R. Nowak                Environment : ubuntu:latest               //
//  Date ......: 2022/02/07                      Compiler ...: clang-10                    //
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
// clang-format on
/////////////////////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up //
/////////////////////////////////////////////////////////////////////////////////////////////
#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif
#include "catch.hpp"
/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Includes //
/////////////////////////////////////////////////////////////////////////////////////////////
#include <stdexcept>

#include "board.hpp"
/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
/////////////////////////////////////////////////////////////////////////////////////////////
constexpr int kBoardWidth = 7;
constexpr int kBoardHeight = 6;

bool AreEqual(DiskType solution[][kBoardWidth],
              DiskType student[][kBoardWidth]) {
  for (int i = 0; i < kBoardHeight; ++i) {
    for (int j = 0; j < kBoardWidth; ++j) {
      if (solution[i][j] != student[i][j]) return false;
    }
  }
  return true;
}

void CopyBoard(DiskType solution[][kBoardWidth],
               DiskType student[][kBoardWidth]) {
  for (unsigned int i = 0; i < Board::kBoardHeight; ++i) {
    for (unsigned int j = 0; j < Board::kBoardWidth; ++j) {
      student[i][j] = solution[i][j];
    }
  }
}
/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Board initialization", "[board_init]") {
  // SECTION("Can use sections") {}
  // clang-format off
  DiskType solution[kBoardHeight][kBoardWidth] = { 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  };
  // clang-format on
  Board student;  // NOLINT
  InitBoard(student);
  REQUIRE(AreEqual(solution, student.board));
}

TEST_CASE("BoardInBounds", "[large][col]") {
  // SECTION("Can use sections") {}
  // clang-format off
  DiskType solution[kBoardHeight][kBoardWidth] = { 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  };
  // clang-format on
  Board student;  // NOLINT
  InitBoard(student);
  CopyBoard(solution, student.board);
  REQUIRE_FALSE(BoardLocationInBounds(-1, 4));
  REQUIRE_FALSE(BoardLocationInBounds(4, -1));
  REQUIRE_FALSE(BoardLocationInBounds(-1, -1));
  REQUIRE_FALSE(BoardLocationInBounds(8, 8));
  REQUIRE_FALSE(BoardLocationInBounds(8, 3));
  REQUIRE(BoardLocationInBounds(4, 4));
  REQUIRE(BoardLocationInBounds(5, 6));
  REQUIRE(BoardLocationInBounds(0, 0));
}

TEST_CASE("drop disk", "[success]") {
  SECTION("[drop][player1][win][vertical]") {
    DiskType solution[kBoardHeight][kBoardWidth] = {{DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer1,
                                                     DiskType::kPlayer2,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer1,
                                                     DiskType::kPlayer2,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer1,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty}};
    // clang-format on
    Board student;  // NOLINT
    InitBoard(student);
    CopyBoard(solution, student.board);
    DropDiskToBoard(student, DiskType::kPlayer1, 2);

    REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer2));
    REQUIRE(CheckForWinner(student, DiskType::kPlayer1));

    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kVertical));
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kVertical));

    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kHorizontal));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kHorizontal));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kRightDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kRightDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kLeftDiag));
  };

  SECTION("[drop][both][player1][win][horizontal]") {
    DiskType solution[kBoardHeight][kBoardWidth] = {{DiskType::kPlayer1,
                                                     DiskType::kPlayer1,
                                                     DiskType::kPlayer1,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer2,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer2,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty}};
    // clang-format on
    Board student;  // NOLINT
    InitBoard(student);
    CopyBoard(solution, student.board);
    DropDiskToBoard(student, DiskType::kPlayer1, 3);

    REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer2));
    REQUIRE(CheckForWinner(student, DiskType::kPlayer1));

    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kHorizontal));
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kHorizontal));

    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kVertical));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kVertical));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kRightDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kRightDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kLeftDiag));
  };

  SECTION("[drop][both][player1][win][ldiag]") {
    DiskType solution[kBoardHeight][kBoardWidth] = {{DiskType::kPlayer1,
                                                     DiskType::kPlayer1,
                                                     DiskType::kPlayer1,
                                                     DiskType::kPlayer2,
                                                     DiskType::kPlayer2,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kPlayer1,
                                                     DiskType::kPlayer2,
                                                     DiskType::kPlayer1,
                                                     DiskType::kPlayer2,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer1,
                                                     DiskType::kPlayer2,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty}};
    // clang-format on
    Board student;  // NOLINT
    InitBoard(student);
    CopyBoard(solution, student.board);

    DropDiskToBoard(student, DiskType::kPlayer1, 3);
    DropDiskToBoard(student, DiskType::kPlayer2, 4);

    REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer2));
    REQUIRE(CheckForWinner(student, DiskType::kPlayer1));

    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kRightDiag));
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kRightDiag));

    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kVertical));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kVertical));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kHorizontal));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kHorizontal));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kLeftDiag));
  };

  SECTION("[drop][both][player1][win][rdiag]") {
    DiskType solution[kBoardHeight][kBoardWidth] = {{DiskType::kPlayer1,
                                                     DiskType::kPlayer1,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer1,
                                                     DiskType::kPlayer2,
                                                     DiskType::kPlayer1,
                                                     DiskType::kPlayer1},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer2,
                                                     DiskType::kPlayer2,
                                                     DiskType::kPlayer1,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer2,
                                                     DiskType::kPlayer1,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty}};
    // clang-format on
    Board student;  // NOLINT
    InitBoard(student);
    CopyBoard(solution, student.board);
    DropDiskToBoard(student, DiskType::kPlayer1, 3);
    DropDiskToBoard(student, DiskType::kPlayer2, 4);

    REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer2));
    REQUIRE(CheckForWinner(student, DiskType::kPlayer1));

    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kLeftDiag));
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kLeftDiag));

    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kVertical));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kVertical));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kHorizontal));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kHorizontal));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kRightDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kRightDiag));
  };

  SECTION("[drop][both][player2][win]") {
    DiskType solution[kBoardHeight][kBoardWidth] = {{DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer2,
                                                     DiskType::kPlayer1,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer2,
                                                     DiskType::kPlayer1,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer2,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty}};
    // clang-format on
    Board student;  // NOLINT
    InitBoard(student);
    CopyBoard(solution, student.board);

    DropDiskToBoard(student, DiskType::kPlayer2, 2);
    DropDiskToBoard(student, DiskType::kPlayer1, 3);

    REQUIRE(CheckForWinner(student, DiskType::kPlayer2));
    REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer1));

    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kVertical));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kVertical));

    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kRightDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kRightDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kHorizontal));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kHorizontal));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kLeftDiag));
  };

  SECTION("[drop][both][win]") {
    DiskType solution[kBoardHeight][kBoardWidth] = {{DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer2,
                                                     DiskType::kPlayer1,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer2,
                                                     DiskType::kPlayer1,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer2,
                                                     DiskType::kPlayer1,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty}};
    // clang-format on
    Board student;  // NOLINT
    InitBoard(student);
    CopyBoard(solution, student.board);

    DropDiskToBoard(student, DiskType::kPlayer2, 2);
    DropDiskToBoard(student, DiskType::kPlayer1, 3);

    REQUIRE(CheckForWinner(student, DiskType::kPlayer2));
    REQUIRE(CheckForWinner(student, DiskType::kPlayer1));

    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kVertical));
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kVertical));

    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kRightDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kRightDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kHorizontal));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kHorizontal));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kLeftDiag));
  };
}

TEST_CASE("drop disk fail", "[runtime error]") {
  DiskType solution[kBoardHeight][kBoardWidth] = {{DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kPlayer2,
                                                   DiskType::kPlayer1,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty},
                                                  {DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kPlayer2,
                                                   DiskType::kPlayer1,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty},
                                                  {DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kPlayer1,
                                                   DiskType::kPlayer1,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty},
                                                  {DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kPlayer2,
                                                   DiskType::kPlayer2,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty},
                                                  {DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kPlayer2,
                                                   DiskType::kPlayer1,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty},
                                                  {DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kPlayer2,
                                                   DiskType::kPlayer1,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty}};
  // clang-format on
  Board student;  // NOLINT
  InitBoard(student);
  CopyBoard(solution, student.board);
  REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer2, 2),
                    std::runtime_error);
  REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer2, 8),
                    std::runtime_error);
  REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer1, 8),
                    std::runtime_error);
  REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer1, 3),
                    std::runtime_error);
  REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer2, -1),
                    std::runtime_error);
  REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer1, -2),
                    std::runtime_error);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Row Win", "[kHorizontal]") {
  SECTION("bottom row", "[player1][win][left]") {
    DiskType solution[kBoardHeight][kBoardWidth] = {{DiskType::kPlayer1,
                                                     DiskType::kPlayer1,
                                                     DiskType::kPlayer1,
                                                     DiskType::kPlayer1,
                                                     DiskType::kPlayer2,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty}

    };
    Board student;
    InitBoard(student);  // NOLINT
    CopyBoard(solution, student.board);

    REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer2));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kHorizontal));

    REQUIRE(CheckForWinner(student, DiskType::kPlayer1));
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kHorizontal));

    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kRightDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kRightDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kVertical));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kVertical));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kLeftDiag));
  };

  SECTION("[player1][win][right]") {
    DiskType solution[kBoardHeight][kBoardWidth] = {{DiskType::kPlayer1,
                                                     DiskType::kPlayer2,
                                                     DiskType::kPlayer2,
                                                     DiskType::kPlayer1,
                                                     DiskType::kPlayer1,
                                                     DiskType::kPlayer1,
                                                     DiskType::kPlayer1},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty}};
    Board student;
    InitBoard(student);  // NOLINT
    CopyBoard(solution, student.board);
    REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer2));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kHorizontal));

    REQUIRE(CheckForWinner(student, DiskType::kPlayer1));
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kHorizontal));

    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kRightDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kRightDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kVertical));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kVertical));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kLeftDiag));
  };

  SECTION("[player2][win][right]") {
    DiskType solution[kBoardHeight][kBoardWidth] = {{DiskType::kPlayer1,
                                                     DiskType::kPlayer2,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer1,
                                                     DiskType::kPlayer1,
                                                     DiskType::kPlayer2,
                                                     DiskType::kPlayer1},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer2,
                                                     DiskType::kPlayer1,
                                                     DiskType::kPlayer2,
                                                     DiskType::kPlayer1},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer1,
                                                     DiskType::kPlayer2,
                                                     DiskType::kPlayer2,
                                                     DiskType::kPlayer1},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer2,
                                                     DiskType::kPlayer2,
                                                     DiskType::kPlayer1,
                                                     DiskType::kPlayer2},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer2,
                                                     DiskType::kPlayer1,
                                                     DiskType::kPlayer1,
                                                     DiskType::kPlayer1},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer2,
                                                     DiskType::kPlayer2,
                                                     DiskType::kPlayer2,
                                                     DiskType::kPlayer2}};
    Board student;
    InitBoard(student);  // NOLINT
    CopyBoard(solution, student.board);

    REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer1));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kHorizontal));

    REQUIRE(CheckForWinner(student, DiskType::kPlayer2));
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kHorizontal));

    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kRightDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kRightDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kVertical));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kVertical));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kLeftDiag));
  };

  SECTION("[player2][win][left]") {
    DiskType solution[kBoardHeight][kBoardWidth] = {{DiskType::kPlayer1,
                                                     DiskType::kPlayer1,
                                                     DiskType::kPlayer2,
                                                     DiskType::kPlayer1,
                                                     DiskType::kPlayer1,
                                                     DiskType::kPlayer2,
                                                     DiskType::kEmpty},
                                                    {DiskType::kPlayer2,
                                                     DiskType::kPlayer1,
                                                     DiskType::kPlayer2,
                                                     DiskType::kPlayer1,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kPlayer1,
                                                     DiskType::kPlayer2,
                                                     DiskType::kPlayer2,
                                                     DiskType::kPlayer1,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kPlayer2,
                                                     DiskType::kPlayer2,
                                                     DiskType::kPlayer1,
                                                     DiskType::kPlayer2,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kPlayer1,
                                                     DiskType::kPlayer1,
                                                     DiskType::kPlayer1,
                                                     DiskType::kPlayer2,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kPlayer2,
                                                     DiskType::kPlayer2,
                                                     DiskType::kPlayer2,
                                                     DiskType::kPlayer2,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty}};
    Board student;
    InitBoard(student);  // NOLINT
    CopyBoard(solution, student.board);

    REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer1));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kHorizontal));

    REQUIRE(CheckForWinner(student, DiskType::kPlayer2));
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kHorizontal));

    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kRightDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kRightDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kVertical));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kVertical));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kLeftDiag));
  };

  SECTION("[both][win][right]") {
    DiskType solution[kBoardHeight][kBoardWidth] = {{DiskType::kPlayer1,
                                                     DiskType::kPlayer2,
                                                     DiskType::kPlayer1,
                                                     DiskType::kPlayer2,
                                                     DiskType::kPlayer2,
                                                     DiskType::kPlayer2,
                                                     DiskType::kPlayer2},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer2,
                                                     DiskType::kPlayer1,
                                                     DiskType::kPlayer1,
                                                     DiskType::kPlayer1,
                                                     DiskType::kPlayer1},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty}

    };
    Board student;
    InitBoard(student);  // NOLINT
    CopyBoard(solution, student.board);

    REQUIRE(CheckForWinner(student, DiskType::kPlayer1));
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kHorizontal));

    REQUIRE(CheckForWinner(student, DiskType::kPlayer2));
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kHorizontal));

    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kRightDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kRightDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kVertical));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kVertical));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kLeftDiag));
  };

  SECTION("[both][win][left]") {
    DiskType solution[kBoardHeight][kBoardWidth] = {{DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kPlayer2,
                                                     DiskType::kPlayer2,
                                                     DiskType::kPlayer2,
                                                     DiskType::kPlayer2,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kPlayer1,
                                                     DiskType::kPlayer1,
                                                     DiskType::kPlayer1,
                                                     DiskType::kPlayer1,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty}};
    Board student;
    InitBoard(student);  // NOLINT
    CopyBoard(solution, student.board);

    REQUIRE(CheckForWinner(student, DiskType::kPlayer1));
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kHorizontal));

    REQUIRE(CheckForWinner(student, DiskType::kPlayer2));
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kHorizontal));

    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kRightDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kRightDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kVertical));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kVertical));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kLeftDiag));
  };
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Column Win", "[kVertical]") {
  SECTION("[player1][win][left]") {
    DiskType solution[kBoardHeight][kBoardWidth] = {{DiskType::kPlayer1,
                                                     DiskType::kPlayer1,
                                                     DiskType::kPlayer1,
                                                     DiskType::kPlayer2,
                                                     DiskType::kPlayer2,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kPlayer1,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kPlayer1,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kPlayer1,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty}};
    Board student;
    InitBoard(student);  // NOLINT
    CopyBoard(solution, student.board);

    REQUIRE(CheckForWinner(student, DiskType::kPlayer1));
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kVertical));

    REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer2));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kVertical));

    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kRightDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kRightDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kHorizontal));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kHorizontal));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kLeftDiag));
  };

  SECTION("[player1][win][right]") {
    DiskType solution[kBoardHeight][kBoardWidth] = {{DiskType::kPlayer1,
                                                     DiskType::kPlayer2,
                                                     DiskType::kPlayer2,
                                                     DiskType::kPlayer1,
                                                     DiskType::kPlayer2,
                                                     DiskType::kPlayer1,
                                                     DiskType::kPlayer1},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer1},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer1},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer1},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty}};
    Board student;
    InitBoard(student);  // NOLINT
    CopyBoard(solution, student.board);

    REQUIRE(CheckForWinner(student, DiskType::kPlayer1));
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kVertical));

    REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer2));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kVertical));

    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kRightDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kRightDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kHorizontal));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kHorizontal));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kLeftDiag));
  };

  SECTION("[player2][win][top-right]") {
    DiskType solution[kBoardHeight][kBoardWidth] = {{DiskType::kPlayer1,
                                                     DiskType::kPlayer2,
                                                     DiskType::kPlayer2,
                                                     DiskType::kPlayer1,
                                                     DiskType::kPlayer2,
                                                     DiskType::kPlayer1,
                                                     DiskType::kPlayer1},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer1},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer2},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer2},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer2},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer2}};
    Board student;
    InitBoard(student);  // NOLINT
    CopyBoard(solution, student.board);

    REQUIRE(CheckForWinner(student, DiskType::kPlayer2));
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kVertical));

    REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer1));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kVertical));

    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kRightDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kRightDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kHorizontal));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kHorizontal));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kLeftDiag));
  };

  SECTION("[player2][win][top-left]") {
    DiskType solution[kBoardHeight][kBoardWidth] = {{DiskType::kPlayer1,
                                                     DiskType::kPlayer2,
                                                     DiskType::kPlayer2,
                                                     DiskType::kPlayer1,
                                                     DiskType::kPlayer2,
                                                     DiskType::kPlayer1,
                                                     DiskType::kPlayer1},
                                                    {DiskType::kPlayer1,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer1},
                                                    {DiskType::kPlayer2,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer1},
                                                    {DiskType::kPlayer2,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kPlayer2,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kPlayer2,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty}};
    Board student;
    InitBoard(student);  // NOLINT
    CopyBoard(solution, student.board);

    REQUIRE(CheckForWinner(student, DiskType::kPlayer2));
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kVertical));

    REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer1));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kVertical));

    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kRightDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kRightDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kHorizontal));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kHorizontal));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kLeftDiag));
  };

  SECTION("bottom row", "[both][win][right]") {
    DiskType solution[kBoardHeight][kBoardWidth] = {{DiskType::kPlayer1,
                                                     DiskType::kPlayer2,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer1,
                                                     DiskType::kPlayer2},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer1,
                                                     DiskType::kPlayer2},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer1,
                                                     DiskType::kPlayer2},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer1,
                                                     DiskType::kPlayer2},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty}};
    Board student;
    InitBoard(student);  // NOLINT
    CopyBoard(solution, student.board);

    REQUIRE(CheckForWinner(student, DiskType::kPlayer1));
    REQUIRE(CheckForWinner(student, DiskType::kPlayer2));

    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kVertical));
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kVertical));

    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kRightDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kRightDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kHorizontal));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kHorizontal));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kLeftDiag));
  };

  SECTION("top row", "[both][win][left]") {
    DiskType solution[kBoardHeight][kBoardWidth] = {{DiskType::kPlayer1,
                                                     DiskType::kPlayer2,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer1,
                                                     DiskType::kPlayer2},
                                                    {DiskType::kPlayer2,
                                                     DiskType::kPlayer1,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer1,
                                                     DiskType::kPlayer2},
                                                    {DiskType::kPlayer1,
                                                     DiskType::kPlayer2,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer2,
                                                     DiskType::kPlayer1},
                                                    {DiskType::kPlayer1,
                                                     DiskType::kPlayer2,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer1,
                                                     DiskType::kPlayer2},
                                                    {DiskType::kPlayer1,
                                                     DiskType::kPlayer2,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kPlayer1,
                                                     DiskType::kPlayer2,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty}};
    Board student;
    InitBoard(student);  // NOLINT
    CopyBoard(solution, student.board);

    REQUIRE(CheckForWinner(student, DiskType::kPlayer1));
    REQUIRE(CheckForWinner(student, DiskType::kPlayer2));
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kVertical));
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kVertical));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kRightDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kRightDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kHorizontal));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kHorizontal));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kLeftDiag));
  };
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Diagonal Win", "[kLeftDiagonal]") {
  SECTION("[player1][win][left]") {
    DiskType solution[kBoardHeight][kBoardWidth] = {{DiskType::kPlayer1,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kPlayer1,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer1,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer1,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty}};
    Board student;
    InitBoard(student);  // NOLINT
    CopyBoard(solution, student.board);

    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kRightDiag));
    REQUIRE(CheckForWinner(student, DiskType::kPlayer1));

    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kRightDiag));
    REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer2));

    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kLeftDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kHorizontal));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kHorizontal));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kVertical));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kVertical));
  };

  SECTION("[player1][win][right]") {
    DiskType solution[kBoardHeight][kBoardWidth] = {{DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer1,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer1,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer1,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer1},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty}};
    Board student;
    InitBoard(student);  // NOLINT
    CopyBoard(solution, student.board);

    REQUIRE(CheckForWinner(student, DiskType::kPlayer1));
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kRightDiag));

    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kRightDiag));
    REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer2));

    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kLeftDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kHorizontal));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kHorizontal));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kVertical));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kVertical));
  };

  SECTION("[player2][win][top-right]") {
    DiskType solution[kBoardHeight][kBoardWidth] = {{DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer2,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer2,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer2,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer2}};
    Board student;
    InitBoard(student);  // NOLINT
    CopyBoard(solution, student.board);

    REQUIRE(CheckForWinner(student, DiskType::kPlayer2));
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kRightDiag));

    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kRightDiag));
    REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer1));

    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kLeftDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kHorizontal));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kHorizontal));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kVertical));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kVertical));
  };

  SECTION("[player2][win][top-left]") {
    DiskType solution[kBoardHeight][kBoardWidth] = {{DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kPlayer2,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kPlayer2,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer2,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer2,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty}};
    Board student;
    InitBoard(student);  // NOLINT
    CopyBoard(solution, student.board);

    REQUIRE(CheckForWinner(student, DiskType::kPlayer2));
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kRightDiag));

    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kRightDiag));
    REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer1));

    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kLeftDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kHorizontal));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kHorizontal));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kVertical));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kVertical));
  };

  SECTION("bottom row", "[both][win][right]") {
    DiskType solution[kBoardHeight][kBoardWidth] = {{DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer1,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer2,
                                                     DiskType::kPlayer1,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer2,
                                                     DiskType::kPlayer1,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer2,
                                                     DiskType::kPlayer1},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer2},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty}};
    Board student;
    InitBoard(student);  // NOLINT
    CopyBoard(solution, student.board);

    REQUIRE(CheckForWinner(student, DiskType::kPlayer1));
    REQUIRE(CheckForWinner(student, DiskType::kPlayer2));
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kRightDiag));
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kRightDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kLeftDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kHorizontal));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kHorizontal));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kVertical));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kVertical));
  };

  SECTION("[both][win][left]") {
    DiskType solution[kBoardHeight][kBoardWidth] = {{DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kPlayer2,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kPlayer1,
                                                     DiskType::kPlayer2,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kPlayer1,
                                                     DiskType::kPlayer2,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer1,
                                                     DiskType::kPlayer2,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer1,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty}};
    Board student;
    InitBoard(student);  // NOLINT
    CopyBoard(solution, student.board);

    REQUIRE(CheckForWinner(student, DiskType::kPlayer1));
    REQUIRE(CheckForWinner(student, DiskType::kPlayer2));
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kRightDiag));
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kRightDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kLeftDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kHorizontal));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kHorizontal));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kVertical));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kVertical));
  };
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Diagonal Win Other", "[kRightDiagonal]") {
  SECTION("[player1][win][left]") {
    DiskType solution[kBoardHeight][kBoardWidth] = {{DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer1,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer1,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kPlayer1,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kPlayer1,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty}};
    Board student;
    InitBoard(student);  // NOLINT
    CopyBoard(solution, student.board);

    REQUIRE(CheckForWinner(student, DiskType::kPlayer1));
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kLeftDiag));

    REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer2));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kLeftDiag));

    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kRightDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kRightDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kHorizontal));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kHorizontal));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kVertical));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kVertical));
  };

  SECTION("[player1][win][right]") {
    DiskType solution[kBoardHeight][kBoardWidth] = {{DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer1,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer1},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer1,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer1,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer1,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty}};
    Board student;
    InitBoard(student);  // NOLINT
    CopyBoard(solution, student.board);

    REQUIRE(CheckForWinner(student, DiskType::kPlayer1));
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kLeftDiag));

    REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer2));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kLeftDiag));

    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kRightDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kRightDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kHorizontal));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kHorizontal));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kVertical));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kVertical));
  };

  SECTION("[player2][win][top-left]") {
    DiskType solution[kBoardHeight][kBoardWidth] = {{DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer2,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer2,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kPlayer2,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kPlayer2,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty}};
    Board student;
    InitBoard(student);  // NOLINT
    CopyBoard(solution, student.board);

    REQUIRE(CheckForWinner(student, DiskType::kPlayer2));
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kLeftDiag));

    REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer1));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kLeftDiag));

    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kRightDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kRightDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kHorizontal));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kHorizontal));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kVertical));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kVertical));
  };

  SECTION("[player2][win][top-right]") {
    DiskType solution[kBoardHeight][kBoardWidth] = {{DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer2},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer2,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer2,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer2,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty}};
    Board student;
    InitBoard(student);  // NOLINT
    CopyBoard(solution, student.board);

    REQUIRE(CheckForWinner(student, DiskType::kPlayer2));
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kLeftDiag));

    REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer1));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kLeftDiag));

    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kRightDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kRightDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kHorizontal));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kHorizontal));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kVertical));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kVertical));
  };

  SECTION("bottom row", "[both][win][right]") {
    DiskType solution[kBoardHeight][kBoardWidth] = {{DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer1},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer1,
                                                     DiskType::kPlayer2},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer1,
                                                     DiskType::kPlayer2,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer1,
                                                     DiskType::kPlayer2,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer2,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty}};
    Board student;
    InitBoard(student);  // NOLINT
    CopyBoard(solution, student.board);
    REQUIRE(CheckForWinner(student, DiskType::kPlayer1));
    REQUIRE(CheckForWinner(student, DiskType::kPlayer2));
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kLeftDiag));
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kRightDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kRightDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kHorizontal));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kHorizontal));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kVertical));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kVertical));
  };

  SECTION("top row", "[both][win][left]") {
    DiskType solution[kBoardHeight][kBoardWidth] = {{DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer2,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer2,
                                                     DiskType::kPlayer1,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kPlayer2,
                                                     DiskType::kPlayer1,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kPlayer2,
                                                     DiskType::kPlayer1,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kPlayer1,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty}};
    Board student;
    InitBoard(student);  // NOLINT
    CopyBoard(solution, student.board);
    REQUIRE(CheckForWinner(student, DiskType::kPlayer1));
    REQUIRE(CheckForWinner(student, DiskType::kPlayer2));
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kLeftDiag));
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kRightDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kRightDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kHorizontal));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kHorizontal));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kVertical));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kVertical));
  };
}

TEST_CASE("miscellaneous") {
  SECTION("nowin", "[square]") {
    DiskType solution[kBoardHeight][kBoardWidth] = {{DiskType::kPlayer1,
                                                     DiskType::kPlayer1,
                                                     DiskType::kPlayer1,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer2,
                                                     DiskType::kPlayer2,
                                                     DiskType::kPlayer2},
                                                    {DiskType::kPlayer1,
                                                     DiskType::kPlayer1,
                                                     DiskType::kPlayer1,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer2,
                                                     DiskType::kPlayer2,
                                                     DiskType::kPlayer2},
                                                    {DiskType::kPlayer1,
                                                     DiskType::kPlayer1,
                                                     DiskType::kPlayer1,
                                                     DiskType::kEmpty,
                                                     DiskType::kPlayer2,
                                                     DiskType::kPlayer2,
                                                     DiskType::kPlayer2},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty},
                                                    {DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty,
                                                     DiskType::kEmpty}};
    Board student;
    InitBoard(student);  // NOLINT
    CopyBoard(solution, student.board);
    REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer1));
    REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer2));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kHorizontal));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kHorizontal));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kVertical));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kVertical));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kLeftDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kRightDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kRightDiag));
  };
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
