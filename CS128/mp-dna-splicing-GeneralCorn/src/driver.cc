#include <iostream>

#include "dna_strand.hpp"
#include "node.hpp"

int main() {
  DNAstrand ds = DNAstrand();
  ds.Push('t');
  ds.Push('a');
  ds.Push('x');
  ds.Push('a');
  ds.Push('z');
  char pattern[] = "ta";
  DNAstrand splice = DNAstrand();
  splice.Push('t');
  splice.Push('g');
  splice.Push('a');

  ds.SpliceIn(pattern, splice);
  std::cout << std::endl;
  auto* temp = ds.Head();
  while (temp != nullptr) {
    std::cout << temp->data << std::endl;
    temp = temp->next;
  }
}
