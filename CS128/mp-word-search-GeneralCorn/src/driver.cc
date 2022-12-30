#include <iostream>
#include <string>
#include <vector>

#include "WordSearchSolver.hpp"

int main() {
  std::string word = "brooim";
  std::vector<std::vector<char>> puzzle{{'b', 'o', 'u', 'f', 'h'},
                                        {'c', 'r', 'o', 'e', 'h'},
                                        {'o', 'o', 'o', 'e', 'h'},
                                        {'o', 'o', 'u', 'o', 'h'},
                                        {'c', 'l', 'o', 'e', 'm'}};

  // size_t row = puzzle.size();
  // size_t col = puzzle[0].size();

  WordSearchSolver wss(puzzle);

  /**
  WordLocation loc_h = wss.Horizontal(word, row, col);
  for (auto x : loc_h.char_positions) std::cout << x << std::endl;

  WordLocation loc_v = wss.Vertical(word, row, col);
  for (auto x : loc_v.char_positions) std::cout << x << std::endl;

  WordLocation loc_r = wss.RightDiagonal(word, row, col);
  for (auto x : loc_r.char_positions) std::cout << x << std::endl;

  WordLocation loc_l = wss.LeftDiagonal(word, row, col);
  for (auto x : loc_l.char_positions) std::cout << x << std::endl;
**/
  WordLocation empty{};
  WordLocation loc_r = wss.FindWord(word, CheckDirection::kRightDiag);

  if (loc_r.word == empty.word) {
    std::cout << "both are empty";
  }
}