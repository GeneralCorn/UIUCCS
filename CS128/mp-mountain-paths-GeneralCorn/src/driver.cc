#include <cmath>
#include <iomanip>
#include <iostream>

#include "elevation_dataset.hpp"
#include "grayscale_image.hpp"
#include "path_image.hpp"

int main() {
  ElevationDataset eds("./example-data/ex_input_data/prompt_5w_2h.dat", 5, 2);
  for (auto x : eds.GetData()) {
    for (auto z : x) {
      std::cout << z << " ";
    }
    std::cout << std::endl;
  }
}
