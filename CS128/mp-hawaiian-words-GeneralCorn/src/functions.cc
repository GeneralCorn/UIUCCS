#include "functions.hpp"

#include <cctype>
#include <iostream>
#include <map>
#include <string>
std::string HawaiianWords(const std::string& inputWord) {
  std::map<std::string, std::string> comb_map;
  std::map<char, std::string> vowel_map;
  std::string prnc, lower, valid = "aeioupkhl'mnw ";
  comb_map = {{"ai", "eye"},
              {"ae", "eye"},
              {"ao", "ow"},
              {"au", "ow"},
              {"ei", "ay"},
              {"eu", "eh"},
              {"iu", "ew"},
              {"oi", "oy"},
              {"ou", "ow"},
              {"ui", "ooey"}};
  vowel_map = {{'a', "ah"}, {'e', "eh"}, {'i', "ee"}, {'o', "oh"}, {'u', "oo"}};
  for (unsigned int i = 0; i < inputWord.length(); i++)
    lower.push_back(static_cast<char>(tolower(inputWord[i])));
  for (unsigned int i = 0; i < inputWord.length(); i++) {
    bool next =
        lower[i + 1] != ' ' && lower[i + 1] != '\'' && i != lower.length() - 1;
    if (valid.find(lower[i]) == std::string::npos)
      return inputWord +
             " contains a character not a part of the Hawaiian language.";
    if (comb_map.count(lower.substr(i, 2)) > 0) {
      prnc += comb_map.at(lower.substr(i, 2));
      if (next) prnc += '-';
      i += 1;
    } else if (vowel_map.count(lower[i]) > 0) {
      prnc += vowel_map.at(lower[i]);
      if (next) prnc += '-';
    } else if ((i > 0) && lower[i] == 'w' &&
               ((lower[i - 1] == 'i') || (lower[i - 1] == 'e'))) {
      prnc += 'v';
    } else {
      prnc += lower[i];
    }
  }
  return prnc;
}