#include "WordSearchSolver.hpp"

#include <string>

WordSearchSolver::WordSearchSolver(
    const std::vector<std::vector<char>>& puzzle):
    puzzle_(puzzle) {
  puzzle_height_ = puzzle.size();
  puzzle_width_ = puzzle[0].size();
}

WordLocation WordSearchSolver::FindWord(const std::string& word) {
  WordLocation w1 =
      WordSearchSolver::Horizontal(word, puzzle_height_, puzzle_width_);
  WordLocation w2 =
      WordSearchSolver::Vertical(word, puzzle_height_, puzzle_width_);
  WordLocation w3 =
      WordSearchSolver::RightDiagonal(word, puzzle_height_, puzzle_width_);
  WordLocation w4 =
      WordSearchSolver::LeftDiagonal(word, puzzle_height_, puzzle_width_);

  if (!w1.word.empty() && !w1.char_positions.empty()) return w1;
  if (!w2.word.empty() && !w2.char_positions.empty()) return w2;
  if (!w3.word.empty() && !w3.char_positions.empty()) return w3;
  if (!w4.word.empty() && !w4.char_positions.empty()) return w4;

  return {};
}

WordLocation WordSearchSolver::FindWord(const std::string& word,
                                        CheckDirection direction) {
  switch (direction) {
  case CheckDirection::kHorizontal:
    return WordSearchSolver::Horizontal(word, puzzle_height_, puzzle_width_);
  case CheckDirection::kVertical:
    return WordSearchSolver::Vertical(word, puzzle_height_, puzzle_width_);
  case CheckDirection::kLeftDiag:
    return WordSearchSolver::LeftDiagonal(word, puzzle_height_, puzzle_width_);
  case CheckDirection::kRightDiag:
    return WordSearchSolver::RightDiagonal(word, puzzle_height_, puzzle_width_);
  }
}

WordLocation WordSearchSolver::LeftDiagonal(const std::string& word,
                                            size_t row,
                                            size_t col) {
  for (size_t i = 0; i < row - word.length() + 1; ++i) {
    for (size_t j = word.length() - 1; j < col; ++j) {
      std::string temp;
      std::vector<CharPositions> positions;
      for (size_t k = 0; k < word.length(); ++k) {
        temp += puzzle_[i + k][j - k];
        positions.push_back({puzzle_[i + k][j - k], i + k, j - k});
      }
      if (temp == word) return {temp, positions};
    }
  }
  return {};
}

//
WordLocation WordSearchSolver::RightDiagonal(const std::string& word,
                                             size_t row,
                                             size_t col) {
  for (size_t i = 0; i < row - word.length() + 1; ++i) {
    for (size_t j = 0; j < col - word.length() + 1; ++j) {
      std::string temp;
      std::vector<CharPositions> positions;
      for (size_t k = 0; k < word.length(); ++k) {
        temp += puzzle_[i + k][j + k];
        positions.push_back({puzzle_[i + k][j + k], i + k, j + k});
      }
      if (temp == word) return {temp, positions};
    }
  }
  return {};
}

WordLocation WordSearchSolver::Vertical(const std::string& word,
                                        size_t row,
                                        size_t col) {
  for (size_t i = 0; i < col; ++i) {
    std::string temp;
    std::vector<CharPositions> positions;
    for (size_t j = 0; j < row; ++j) temp.push_back(puzzle_[j][i]);

    auto pos = temp.find(word);
    if (pos != std::string::npos) {
      for (size_t ind = pos; ind < pos + word.length(); ++ind) {
        positions.push_back({temp[ind], ind, i});
      }
      return {word, positions};
    }
  }
  return {};
}

WordLocation WordSearchSolver::Horizontal(const std::string& word,
                                          size_t row,
                                          size_t col) {
  for (size_t i = 0; i < row; ++i) {
    std::string temp;
    std::vector<CharPositions> positions;
    for (size_t j = 0; j < col; ++j) temp.push_back(puzzle_[i][j]);
    auto pos = temp.find(word);
    if (pos != std::string::npos) {
      for (size_t ind = pos; ind < pos + word.length(); ++ind) {
        positions.push_back({temp[ind], i, ind});
      }
      return {word, positions};
    }
  }
  return {};
}

bool WordSearchSolver::LocationInBounds(size_t row, size_t col) const {
  return ((row < puzzle_height_) && (col < puzzle_width_));
}
