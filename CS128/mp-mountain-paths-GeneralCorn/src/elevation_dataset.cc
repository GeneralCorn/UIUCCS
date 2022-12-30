#include "elevation_dataset.hpp"

#include <fstream>
#include <limits>
#include <stdexcept>
#include <vector>

ElevationDataset::ElevationDataset(const std::string& filename,
                                   size_t width,
                                   size_t height):
    width_(width), height_(height), max_ele_(kMin), min_ele_(kMax) {
  std::ifstream elevation{filename};
  if (!elevation.is_open()) throw std::runtime_error("file not opened");

  for (unsigned int i = 0; i < height; ++i) {
    std::vector<int> line;
    int ele = 0;
    for (unsigned int j = 0; j < width; ++j) {
      if (elevation.good()) {
        elevation >> ele;
        min_ele_ = std::min(min_ele_, ele);
        max_ele_ = std::max(max_ele_, ele);
        if (elevation.fail()) throw std::runtime_error("wrong input");
      } else {
        throw std::runtime_error("file corrupted");
      }
      line.push_back(ele);
    }
    data_.push_back(line);
  }

  int checktoomuch = 0;
  elevation >> checktoomuch;
  if (elevation.good())
    throw std::runtime_error("width/height value doesn't match file");
}
