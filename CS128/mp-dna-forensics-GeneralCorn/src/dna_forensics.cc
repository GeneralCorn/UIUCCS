#include <fstream>
#include <iostream>

#include "functions.hpp"
#include "utilities.hpp"

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " [input_file] [dna_sequence]"
              << std::endl;
    return 1;
  }

  std::string file = argv[1];
  std::ifstream dna_record{file};
  std::string dna_strand = argv[2];

  std::cout << DnaAnalysis(dna_record, dna_strand) << std::endl;

  return 0;
}