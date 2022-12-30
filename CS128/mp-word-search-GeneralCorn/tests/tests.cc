// clang-format off
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//  Written By : Student Name                    Environment : ubuntu:bionic               //
//  Date ......: 2021/02/10                      Compiler ...: clang-10                    //
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
#include <string>
#include <vector>

#include "CharPositions.hpp"
#include "WordLocation.hpp"
#include "WordSearchSolver.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////

bool CompareStruct(WordLocation& a, WordLocation& b) {
  if (a.word == b.word) {
    std::vector<CharPositions> ac = a.char_positions;
    std::vector<CharPositions> bc = b.char_positions;

    if (ac.size() - bc.size() != 0) return false;

    for (unsigned int i = 0; i < ac.size(); i++) {
      CharPositions acp = ac[i];
      CharPositions bcp = bc[i];
      if (acp.character == bcp.character && acp.col == bcp.col &&
          acp.row == bcp.row) {
        return true;
      }
    }
  }
  return false;
}

TEST_CASE("RightDiag[square]") {
  SECTION("size - 3 letters") {
    std::string word = "fh";
    std::vector<std::vector<char>> puzzle{{'b', 'o', 'u', 'f', 'c'},
                                          {'c', 'r', 'o', 'e', 'h'},
                                          {'o', 'o', 'o', 'e', 'h'},
                                          {'o', 'o', 'u', 'o', 'h'},
                                          {'c', 'l', 'o', 'e', 'm'}};

    WordSearchSolver wss(puzzle);
    WordLocation general = wss.FindWord(word);
    WordLocation wl_v = wss.FindWord(word, CheckDirection::kVertical);
    WordLocation wl_h = wss.FindWord(word, CheckDirection::kHorizontal);
    WordLocation wl_l = wss.FindWord(word, CheckDirection::kLeftDiag);
    WordLocation wl_r = wss.FindWord(word, CheckDirection::kRightDiag);

    WordLocation ans = {
        word, std::vector<CharPositions>{{word[0], 0, 3}, {word[1], 1, 4}}};

    REQUIRE(CompareStruct(general, ans));
    REQUIRE(CompareStruct(wl_r, ans));
    REQUIRE_FALSE(CompareStruct(wl_l, ans));
    REQUIRE_FALSE(CompareStruct(wl_h, ans));
    REQUIRE_FALSE(CompareStruct(wl_v, ans));
  }

  SECTION("size - 2 letters") {
    std::string word = "ooo";
    std::vector<std::vector<char>> puzzle{{'b', 'o', 'u', 'f', 'h'},
                                          {'c', 'r', 'd', 'e', 'h'},
                                          {'o', 'o', 'x', 'e', 'h'},
                                          {'o', 'o', 'u', 'o', 'h'},
                                          {'c', 'l', 'o', 'e', 'm'}};

    WordSearchSolver wss(puzzle);
    WordLocation general = wss.FindWord(word);
    WordLocation wl_v = wss.FindWord(word, CheckDirection::kVertical);
    WordLocation wl_h = wss.FindWord(word, CheckDirection::kHorizontal);
    WordLocation wl_l = wss.FindWord(word, CheckDirection::kLeftDiag);
    WordLocation wl_r = wss.FindWord(word, CheckDirection::kRightDiag);

    WordLocation ans = {word,
                        std::vector<CharPositions>{
                            {word[0], 2, 0}, {word[1], 3, 1}, {word[2], 4, 2}}};

    REQUIRE(CompareStruct(general, ans));
    REQUIRE(CompareStruct(wl_r, ans));
    REQUIRE_FALSE(CompareStruct(wl_l, ans));
    REQUIRE_FALSE(CompareStruct(wl_h, ans));
    REQUIRE_FALSE(CompareStruct(wl_v, ans));
  }

  SECTION("size letters") {
    std::string word = "broom";
    std::vector<std::vector<char>> puzzle{{'b', 'o', 'u', 'f', 'h'},
                                          {'c', 'r', 'o', 'e', 'h'},
                                          {'o', 'o', 'o', 'e', 'h'},
                                          {'o', 'o', 'u', 'o', 'h'},
                                          {'c', 'l', 'o', 'e', 'm'}};

    WordSearchSolver wss(puzzle);
    WordLocation general = wss.FindWord(word);
    WordLocation wl_v = wss.FindWord(word, CheckDirection::kVertical);
    WordLocation wl_h = wss.FindWord(word, CheckDirection::kHorizontal);
    WordLocation wl_l = wss.FindWord(word, CheckDirection::kLeftDiag);
    WordLocation wl_r = wss.FindWord(word, CheckDirection::kRightDiag);

    WordLocation ans = {word,
                        std::vector<CharPositions>{{word[0], 0, 0},
                                                   {word[1], 1, 1},
                                                   {word[2], 2, 2},
                                                   {word[3], 3, 3},
                                                   {word[4], 4, 4}}};

    REQUIRE(CompareStruct(general, ans));
    REQUIRE(CompareStruct(wl_r, ans));
    REQUIRE_FALSE(CompareStruct(wl_l, ans));
    REQUIRE_FALSE(CompareStruct(wl_h, ans));
    REQUIRE_FALSE(CompareStruct(wl_v, ans));
  }
}

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

TEST_CASE("LeftDiag[square]") {
  SECTION("size - 3 letters") {
    std::string word = "he";
    std::vector<std::vector<char>> puzzle{{'b', 'o', 'u', 'f', 'h'},
                                          {'c', 'r', 'o', 'x', 'h'},
                                          {'o', 'o', 'o', 'x', 'h'},
                                          {'o', 'o', 'u', 'o', 'h'},
                                          {'c', 'l', 'o', 'e', 'm'}};

    WordSearchSolver wss(puzzle);
    WordLocation general = wss.FindWord(word);
    WordLocation wl_v = wss.FindWord(word, CheckDirection::kVertical);
    WordLocation wl_h = wss.FindWord(word, CheckDirection::kHorizontal);
    WordLocation wl_l = wss.FindWord(word, CheckDirection::kLeftDiag);
    WordLocation wl_r = wss.FindWord(word, CheckDirection::kRightDiag);

    WordLocation ans = {
        word, std::vector<CharPositions>{{word[0], 3, 4}, {word[1], 4, 3}}};

    REQUIRE(CompareStruct(general, ans));
    REQUIRE(CompareStruct(wl_l, ans));
    REQUIRE_FALSE(CompareStruct(wl_r, ans));
    REQUIRE_FALSE(CompareStruct(wl_h, ans));
    REQUIRE_FALSE(CompareStruct(wl_v, ans));
  }

  SECTION("size - 2 letters") {
    std::string word = "uro";
    std::vector<std::vector<char>> puzzle{{'b', 'o', 'u', 'f', 'h'},
                                          {'c', 'r', 'o', 'e', 'h'},
                                          {'o', 'o', 'o', 'e', 'h'},
                                          {'o', 'o', 'u', 'o', 'h'},
                                          {'c', 'l', 'o', 'e', 'm'}};

    WordSearchSolver wss(puzzle);
    WordLocation general = wss.FindWord(word);
    WordLocation wl_v = wss.FindWord(word, CheckDirection::kVertical);
    WordLocation wl_h = wss.FindWord(word, CheckDirection::kHorizontal);
    WordLocation wl_l = wss.FindWord(word, CheckDirection::kLeftDiag);
    WordLocation wl_r = wss.FindWord(word, CheckDirection::kRightDiag);

    WordLocation ans = {word,
                        std::vector<CharPositions>{
                            {word[0], 0, 2}, {word[1], 1, 1}, {word[2], 2, 0}}};

    REQUIRE(CompareStruct(general, ans));
    REQUIRE(CompareStruct(wl_l, ans));
    REQUIRE_FALSE(CompareStruct(wl_r, ans));
    REQUIRE_FALSE(CompareStruct(wl_h, ans));
    REQUIRE_FALSE(CompareStruct(wl_v, ans));
  }

  SECTION("size letter") {
    std::string word = "heooc";
    std::vector<std::vector<char>> puzzle{{'b', 'o', 'u', 'f', 'h'},
                                          {'c', 'r', 'o', 'e', 'h'},
                                          {'o', 'o', 'o', 'e', 'h'},
                                          {'o', 'o', 'u', 'o', 'h'},
                                          {'c', 'l', 'o', 'e', 'm'}};

    WordSearchSolver wss(puzzle);
    WordLocation general = wss.FindWord(word);
    WordLocation wl_v = wss.FindWord(word, CheckDirection::kVertical);
    WordLocation wl_h = wss.FindWord(word, CheckDirection::kHorizontal);
    WordLocation wl_l = wss.FindWord(word, CheckDirection::kLeftDiag);
    WordLocation wl_r = wss.FindWord(word, CheckDirection::kRightDiag);

    WordLocation ans = {word,
                        std::vector<CharPositions>{{word[0], 0, 4},
                                                   {word[1], 1, 3},
                                                   {word[2], 2, 2},
                                                   {word[3], 3, 1},
                                                   {word[4], 4, 0}}};

    REQUIRE(CompareStruct(general, ans));
    REQUIRE(CompareStruct(wl_l, ans));
    REQUIRE_FALSE(CompareStruct(wl_r, ans));
    REQUIRE_FALSE(CompareStruct(wl_h, ans));
    REQUIRE_FALSE(CompareStruct(wl_v, ans));
  }
}

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

TEST_CASE("Horizontal[square]") {
  SECTION("size - 3 letters") {
    std::string word = "bo";
    std::vector<std::vector<char>> puzzle{{'b', 'o', 'u', 'f', 'h'},
                                          {'c', 'r', 'o', 'e', 'h'},
                                          {'o', 'o', 'o', 'e', 'h'},
                                          {'o', 'o', 'u', 'o', 'h'},
                                          {'c', 'l', 'o', 'e', 'm'}};

    WordSearchSolver wss(puzzle);
    WordLocation general = wss.FindWord(word);
    WordLocation wl_v = wss.FindWord(word, CheckDirection::kVertical);
    WordLocation wl_h = wss.FindWord(word, CheckDirection::kHorizontal);
    WordLocation wl_l = wss.FindWord(word, CheckDirection::kLeftDiag);
    WordLocation wl_r = wss.FindWord(word, CheckDirection::kRightDiag);

    WordLocation ans = {
        word, std::vector<CharPositions>{{word[0], 0, 0}, {word[1], 0, 1}}};

    REQUIRE(CompareStruct(general, ans));
    REQUIRE(CompareStruct(wl_h, ans));
    REQUIRE_FALSE(CompareStruct(wl_r, ans));
    REQUIRE_FALSE(CompareStruct(wl_l, ans));
    REQUIRE_FALSE(CompareStruct(wl_v, ans));
  }

  SECTION("size - 2 letters") {
    std::string word = "oem";
    std::vector<std::vector<char>> puzzle{{'b', 'o', 'u', 'f', 'h'},
                                          {'c', 'r', 'o', 'e', 'h'},
                                          {'o', 'o', 'o', 'e', 'h'},
                                          {'o', 'o', 'u', 'o', 'h'},
                                          {'c', 'l', 'o', 'e', 'm'}};

    WordSearchSolver wss(puzzle);
    WordLocation general = wss.FindWord(word);
    WordLocation wl_v = wss.FindWord(word, CheckDirection::kVertical);
    WordLocation wl_h = wss.FindWord(word, CheckDirection::kHorizontal);
    WordLocation wl_l = wss.FindWord(word, CheckDirection::kLeftDiag);
    WordLocation wl_r = wss.FindWord(word, CheckDirection::kRightDiag);

    WordLocation ans = {word,
                        std::vector<CharPositions>{
                            {word[0], 4, 2}, {word[1], 4, 3}, {word[2], 4, 4}}};

    REQUIRE(CompareStruct(general, ans));
    REQUIRE(CompareStruct(wl_h, ans));
    REQUIRE_FALSE(CompareStruct(wl_r, ans));
    REQUIRE_FALSE(CompareStruct(wl_l, ans));
    REQUIRE_FALSE(CompareStruct(wl_v, ans));
  }

  SECTION("size letter") {
    std::string word = "oooeh";
    std::vector<std::vector<char>> puzzle{{'b', 'o', 'u', 'f', 'h'},
                                          {'c', 'r', 'o', 'e', 'h'},
                                          {'o', 'o', 'o', 'e', 'h'},
                                          {'o', 'o', 'u', 'o', 'h'},
                                          {'c', 'l', 'o', 'e', 'm'}};

    WordSearchSolver wss(puzzle);
    WordLocation general = wss.FindWord(word);
    WordLocation wl_v = wss.FindWord(word, CheckDirection::kVertical);
    WordLocation wl_h = wss.FindWord(word, CheckDirection::kHorizontal);
    WordLocation wl_l = wss.FindWord(word, CheckDirection::kLeftDiag);
    WordLocation wl_r = wss.FindWord(word, CheckDirection::kRightDiag);

    WordLocation ans = {word,
                        std::vector<CharPositions>{{word[0], 2, 0},
                                                   {word[1], 2, 1},
                                                   {word[2], 2, 2},
                                                   {word[3], 2, 3},
                                                   {word[4], 2, 4}}};

    REQUIRE(CompareStruct(general, ans));
    REQUIRE(CompareStruct(wl_h, ans));
    REQUIRE_FALSE(CompareStruct(wl_r, ans));
    REQUIRE_FALSE(CompareStruct(wl_l, ans));
    REQUIRE_FALSE(CompareStruct(wl_v, ans));
  }
}

//////////////////////////////////////////////////////////////////////

TEST_CASE("Vertical[square]") {
  SECTION("size - 3 letters") {
    std::string word = "hm";
    std::vector<std::vector<char>> puzzle{{'b', 'o', 'u', 'f', 'h'},
                                          {'c', 'r', 'o', 'e', 'h'},
                                          {'o', 'o', 'o', 'e', 'h'},
                                          {'o', 'o', 'u', 'o', 'h'},
                                          {'c', 'l', 'o', 'e', 'm'}};

    WordSearchSolver wss(puzzle);
    WordLocation general = wss.FindWord(word);
    WordLocation wl_v = wss.FindWord(word, CheckDirection::kVertical);
    WordLocation wl_h = wss.FindWord(word, CheckDirection::kHorizontal);
    WordLocation wl_l = wss.FindWord(word, CheckDirection::kLeftDiag);
    WordLocation wl_r = wss.FindWord(word, CheckDirection::kRightDiag);

    WordLocation ans = {
        word, std::vector<CharPositions>{{word[0], 3, 4}, {word[1], 4, 4}}};

    REQUIRE(CompareStruct(general, ans));
    REQUIRE(CompareStruct(wl_v, ans));
    REQUIRE_FALSE(CompareStruct(wl_r, ans));
    REQUIRE_FALSE(CompareStruct(wl_l, ans));
    REQUIRE_FALSE(CompareStruct(wl_h, ans));
  }

  SECTION("size - 2 letters") {
    std::string word = "bco";
    std::vector<std::vector<char>> puzzle{{'b', 'o', 'u', 'f', 'h'},
                                          {'c', 'r', 'o', 'e', 'h'},
                                          {'o', 'o', 'o', 'e', 'h'},
                                          {'o', 'o', 'u', 'o', 'h'},
                                          {'c', 'l', 'o', 'e', 'm'}};

    WordSearchSolver wss(puzzle);
    WordLocation general = wss.FindWord(word);
    WordLocation wl_v = wss.FindWord(word, CheckDirection::kVertical);
    WordLocation wl_h = wss.FindWord(word, CheckDirection::kHorizontal);
    WordLocation wl_l = wss.FindWord(word, CheckDirection::kLeftDiag);
    WordLocation wl_r = wss.FindWord(word, CheckDirection::kRightDiag);

    WordLocation ans = {word,
                        std::vector<CharPositions>{
                            {word[0], 0, 0}, {word[1], 1, 0}, {word[2], 2, 0}}};

    REQUIRE(CompareStruct(general, ans));
    REQUIRE(CompareStruct(wl_v, ans));
    REQUIRE_FALSE(CompareStruct(wl_r, ans));
    REQUIRE_FALSE(CompareStruct(wl_l, ans));
    REQUIRE_FALSE(CompareStruct(wl_h, ans));
  }

  SECTION("size letter") {
    std::string word = "orool";
    std::vector<std::vector<char>> puzzle{{'b', 'o', 'u', 'f', 'h'},
                                          {'c', 'r', 'o', 'e', 'h'},
                                          {'o', 'o', 'o', 'e', 'h'},
                                          {'o', 'o', 'u', 'o', 'h'},
                                          {'c', 'l', 'o', 'e', 'm'}};

    WordSearchSolver wss(puzzle);
    WordLocation general = wss.FindWord(word);
    WordLocation wl_v = wss.FindWord(word, CheckDirection::kVertical);
    WordLocation wl_h = wss.FindWord(word, CheckDirection::kHorizontal);
    WordLocation wl_l = wss.FindWord(word, CheckDirection::kLeftDiag);
    WordLocation wl_r = wss.FindWord(word, CheckDirection::kRightDiag);

    WordLocation ans = {word,
                        std::vector<CharPositions>{{word[0], 0, 1},
                                                   {word[1], 1, 1},
                                                   {word[2], 2, 1},
                                                   {word[3], 3, 1},
                                                   {word[4], 4, 1}}};

    REQUIRE(CompareStruct(general, ans));
    REQUIRE(CompareStruct(wl_v, ans));
    REQUIRE_FALSE(CompareStruct(wl_r, ans));
    REQUIRE_FALSE(CompareStruct(wl_l, ans));
    REQUIRE_FALSE(CompareStruct(wl_h, ans));
  }
}

TEST_CASE("not found[square]") {
  std::string word = "study";
  std::vector<std::vector<char>> puzzle{{'b', 'o', 'u', 'f', 'h'},
                                        {'c', 'r', 'o', 'e', 'h'},
                                        {'o', 'o', 'o', 'e', 'h'},
                                        {'o', 'o', 'u', 'o', 'h'},
                                        {'c', 'l', 'o', 'e', 'm'}};

  WordSearchSolver wss(puzzle);
  WordLocation general = wss.FindWord(word);
  WordLocation wl_v = wss.FindWord(word, CheckDirection::kVertical);
  WordLocation wl_h = wss.FindWord(word, CheckDirection::kHorizontal);
  WordLocation wl_l = wss.FindWord(word, CheckDirection::kLeftDiag);
  WordLocation wl_r = wss.FindWord(word, CheckDirection::kRightDiag);

  WordLocation ans{};

  REQUIRE(general.word == ans.word);
  REQUIRE(wl_l.word == ans.word);
  REQUIRE(wl_r.word == ans.word);
  REQUIRE(wl_v.word == ans.word);
  REQUIRE(wl_h.word == ans.word);
  REQUIRE(general.char_positions.empty());
  REQUIRE(wl_l.char_positions.empty());
  REQUIRE(wl_r.char_positions.empty());
  REQUIRE(wl_v.char_positions.empty());
  REQUIRE(wl_h.char_positions.empty());
}

TEST_CASE("not found[rect]") {
  std::string word = "study";
  std::vector<std::vector<char>> puzzle{{'b', 'o', 'u', 'f', 'h', 'h', 'h'},
                                        {'c', 'r', 'o', 'e', 'h', 'h', 'h'},
                                        {'o', 'o', 'o', 'e', 'h', 'h', 'd'},
                                        {'o', 'o', 'u', 'o', 'h', 'h', 'x'},
                                        {'c', 'l', 'o', 'e', 'm', 'h', 'j'}};

  WordSearchSolver wss(puzzle);
  WordLocation general = wss.FindWord(word);
  WordLocation wl_v = wss.FindWord(word, CheckDirection::kVertical);
  WordLocation wl_h = wss.FindWord(word, CheckDirection::kHorizontal);
  WordLocation wl_l = wss.FindWord(word, CheckDirection::kLeftDiag);
  WordLocation wl_r = wss.FindWord(word, CheckDirection::kRightDiag);

  WordLocation ans{};

  REQUIRE(general.word == ans.word);
  REQUIRE(wl_l.word == ans.word);
  REQUIRE(wl_r.word == ans.word);
  REQUIRE(wl_v.word == ans.word);
  REQUIRE(wl_h.word == ans.word);
}

TEST_CASE("not found[rect2]") {
  std::string word = "stu";
  std::vector<std::vector<char>> puzzle{{'b', 'o', 'u'},
                                        {'c', 'r', 'o'},
                                        {'o', 'o', 'o'},
                                        {'o', 'o', 'u'},
                                        {'c', 'l', 'o'}};

  WordSearchSolver wss(puzzle);
  WordLocation general = wss.FindWord(word);
  WordLocation wl_v = wss.FindWord(word, CheckDirection::kVertical);
  WordLocation wl_h = wss.FindWord(word, CheckDirection::kHorizontal);
  WordLocation wl_l = wss.FindWord(word, CheckDirection::kLeftDiag);
  WordLocation wl_r = wss.FindWord(word, CheckDirection::kRightDiag);

  WordLocation ans{};

  REQUIRE(general.word == ans.word);
  REQUIRE(wl_l.word == ans.word);
  REQUIRE(wl_r.word == ans.word);
  REQUIRE(wl_v.word == ans.word);
  REQUIRE(wl_h.word == ans.word);
}

TEST_CASE("individual") {
  SECTION("right diag") {
    std::string word = "bro";
    std::vector<std::vector<char>> puzzle{{'b', 'o', 'u', 'f', 'h', 'h', 'h'},
                                          {'c', 'r', 'o', 'e', 'h', 'h', 'h'},
                                          {'o', 'o', 'o', 'e', 'h', 'h', 'd'},
                                          {'o', 'o', 'u', 'o', 'h', 'h', 'x'},
                                          {'c', 'l', 'o', 'e', 'm', 'h', 'j'}};

    WordSearchSolver wss(puzzle);
    WordLocation general = wss.FindWord(word);
    WordLocation wl_v = wss.FindWord(word, CheckDirection::kVertical);
    WordLocation wl_h = wss.FindWord(word, CheckDirection::kHorizontal);
    WordLocation wl_l = wss.FindWord(word, CheckDirection::kLeftDiag);
    WordLocation wl_r = wss.FindWord(word, CheckDirection::kRightDiag);

    WordLocation ans{};

    REQUIRE(general.word == "bro");
    REQUIRE(general.char_positions[0].character == 'b');
    REQUIRE(general.char_positions[1].character == 'r');
    REQUIRE(general.char_positions[2].character == 'o');

    REQUIRE(general.char_positions[0].row == 0);
    REQUIRE(general.char_positions[1].row == 1);
    REQUIRE(general.char_positions[2].row == 2);

    REQUIRE(general.char_positions[0].col == 0);
    REQUIRE(general.char_positions[1].col == 1);
    REQUIRE(general.char_positions[2].col == 2);

    REQUIRE(wl_l.word == ans.word);
    REQUIRE(wl_v.word == ans.word);
    REQUIRE(wl_h.word == ans.word);
    REQUIRE(wl_l.char_positions.empty());
    REQUIRE(wl_v.char_positions.empty());
    REQUIRE(wl_h.char_positions.empty());
  }
}

///////////////

TEST_CASE("rectangle") {
  SECTION("bottom right horizontal") {
    std::string word = "oemf";
    std::vector<std::vector<char>> puzzle{{'b', 'o', 'u', 'f', 'h', 'c'},
                                          {'c', 'r', 'o', 'e', 'h', 'd'},
                                          {'o', 'o', 'o', 'e', 'h', 'b'},
                                          {'o', 'o', 'u', 'o', 'h', 's'},
                                          {'c', 'l', 'o', 'e', 'm', 'f'}};

    WordSearchSolver wss(puzzle);
    WordLocation general = wss.FindWord(word);
    WordLocation wl_v = wss.FindWord(word, CheckDirection::kVertical);
    WordLocation wl_h = wss.FindWord(word, CheckDirection::kHorizontal);
    WordLocation wl_l = wss.FindWord(word, CheckDirection::kLeftDiag);
    WordLocation wl_r = wss.FindWord(word, CheckDirection::kRightDiag);

    WordLocation ans = {word,
                        std::vector<CharPositions>{{word[0], 4, 2},
                                                   {word[1], 4, 3},
                                                   {word[2], 4, 4},
                                                   {word[3], 4, 5}}};

    REQUIRE(CompareStruct(general, ans));
    REQUIRE(CompareStruct(wl_h, ans));
    REQUIRE_FALSE(CompareStruct(wl_r, ans));
    REQUIRE_FALSE(CompareStruct(wl_l, ans));
    REQUIRE_FALSE(CompareStruct(wl_v, ans));
  }

  SECTION("top right vertical") {}

  SECTION("bottom left right diag") {
    std::string word = "oso";
    std::vector<std::vector<char>> puzzle{{'b', 'o', 'u', 'f', 'h', 'b'},
                                          {'c', 'r', 'o', 'e', 'h', 'd'},
                                          {'o', 'o', 's', 'e', 'h', 'x'},
                                          {'o', 's', 'u', 'o', 'h', 'q'},
                                          {'c', 'l', 'o', 'e', 'm', 'z'}};

    WordSearchSolver wss(puzzle);
    WordLocation general = wss.FindWord(word);
    WordLocation wl_v = wss.FindWord(word, CheckDirection::kVertical);
    WordLocation wl_h = wss.FindWord(word, CheckDirection::kHorizontal);
    WordLocation wl_l = wss.FindWord(word, CheckDirection::kLeftDiag);
    WordLocation wl_r = wss.FindWord(word, CheckDirection::kRightDiag);

    WordLocation ans = {word,
                        std::vector<CharPositions>{
                            {word[0], 2, 0}, {word[1], 3, 1}, {word[2], 4, 2}}};

    REQUIRE(CompareStruct(general, ans));
    REQUIRE(CompareStruct(wl_r, ans));
    REQUIRE_FALSE(CompareStruct(wl_l, ans));
    REQUIRE_FALSE(CompareStruct(wl_v, ans));
    REQUIRE_FALSE(CompareStruct(wl_h, ans));
  }

  SECTION("bottom right left diag") {
    std::string word = "xhe";
    std::vector<std::vector<char>> puzzle{{'b', 'o', 'u', 'f', 'h', 'b'},
                                          {'c', 'r', 'o', 'e', 'h', 'd'},
                                          {'o', 'o', 'o', 'e', 'h', 'x'},
                                          {'o', 'o', 'u', 'o', 'h', 'q'},
                                          {'c', 'l', 'o', 'e', 'm', 'z'}};

    WordSearchSolver wss(puzzle);
    WordLocation general = wss.FindWord(word);
    WordLocation wl_v = wss.FindWord(word, CheckDirection::kVertical);
    WordLocation wl_h = wss.FindWord(word, CheckDirection::kHorizontal);
    WordLocation wl_l = wss.FindWord(word, CheckDirection::kLeftDiag);
    WordLocation wl_r = wss.FindWord(word, CheckDirection::kRightDiag);

    WordLocation ans = {word,
                        std::vector<CharPositions>{
                            {word[0], 2, 5}, {word[1], 3, 4}, {word[2], 4, 3}}};

    REQUIRE(CompareStruct(general, ans));
    REQUIRE(CompareStruct(wl_l, ans));
    REQUIRE_FALSE(CompareStruct(wl_r, ans));
    REQUIRE_FALSE(CompareStruct(wl_v, ans));
    REQUIRE_FALSE(CompareStruct(wl_h, ans));
  }
}
