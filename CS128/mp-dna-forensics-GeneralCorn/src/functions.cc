#include "functions.hpp"

#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::string DnaAnalysis(std::ifstream& dna_data, std::string& Strand) {
  std::string line;
  std::vector<std::vector<std::string>> identifier;
  std::vector<int> counts;

  // initialize 2d vector representing the dna file lines
  for (std::string line; std::getline(dna_data, line); line = "") {
    identifier.push_back(utilities::GetSubstrs(line, ','));
  }

  unsigned int itsize = identifier.size();
  unsigned int subsize = identifier[0].size();

  std::vector<std::vector<int>> comparison(itsize - 1,
                                           std::vector<int>(subsize - 1));

  for (unsigned int i = 1; i < subsize; i++) {
    int temp = LongStrCount(Strand, identifier[0][i]);
    counts.push_back(temp);
  }

  for (unsigned int i = 1; i < itsize; i++) {
    for (unsigned int j = 1; j < subsize; j++) {
      comparison[i - 1][j - 1] = std::stoi(identifier[i][j]);
    }
  }

  for (unsigned int i = 0; i < comparison.size(); i++) {
    for (unsigned int j = 0; j < comparison[0].size(); j++) {
      if (comparison[i] == counts) {
        return identifier[i + 1][0];
      }
    }
  }

  dna_data.close();

  return "no match";
}

int LongStrCount(std::string& Strand, std::string& str) {
  unsigned int tl = str.length();
  int max = 0, count = 0;
  for (unsigned int j = 0; j <= Strand.length() - tl;) {
    std::string s = Strand.substr(j, tl);
    if (s == str) {
      count++;
      j = j + tl;
    } else {
      max = (count > max) ? count : max;
      count = 0;
      j++;
    }
  }
  max = (count > max) ? count : max;

  return max;
}
