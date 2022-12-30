#ifndef ELEVATION_DATASET_H
#define ELEVATION_DATASET_H

#include <cstdlib>  // for size_t
#include <limits>
#include <stdexcept>
#include <string>
#include <vector>

class ElevationDataset {
public:
  ElevationDataset(const std::string& filename, size_t width, size_t height);
  size_t Width() const { return width_; }
  size_t Height() const { return height_; }
  int MaxEle() const { return max_ele_; }
  int MinEle() const { return min_ele_; }
  int DatumAt(size_t row, size_t col) const {
    if (row < 0 || row >= height_ || col < 0 || col >= width_) {
      return std::numeric_limits<unsigned int>::max();
      // throw std::invalid_argument("wrong numbers");
    }
    return data_[row][col];
  }

  const std::vector<std::vector<int>>& GetData() const { return data_; }
  // write behavior declarations here; define in elevation_dataset.cc.
private:
  std::vector<std::vector<int>> data_;
  size_t width_;
  size_t height_;
  int max_ele_;
  int min_ele_;
  static const int kMin = std::numeric_limits<int>::min();
  static const int kMax = std::numeric_limits<int>::max();
};

#endif