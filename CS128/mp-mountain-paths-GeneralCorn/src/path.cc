#include "path.hpp"

#include <vector>

Path::Path(size_t length, size_t starting_row):
    length_(length), starting_row_(starting_row) {
  std::vector<size_t> temp(length_, starting_row);
  path_ = temp;
}