#include "grayscale_image.hpp"

#include <cmath>
#include <cstdlib>
#include <fstream>
#include <stdexcept>
#include <vector>

// std::round((elevation_point - min_ele) / (max_ele - min_ele) * 255)

GrayscaleImage::GrayscaleImage(const ElevationDataset& dataset):
    width_(dataset.Width()), height_(dataset.Height()) {
  int min_ele = dataset.MinEle(), max_ele = dataset.MaxEle();
  for (unsigned int i = 0; i < dataset.GetData().size(); ++i) {
    std::vector<Color> rowcolors;
    for (unsigned int j = 0; j < width_; ++j) {
      int currentele = dataset.DatumAt(i, j);
      int cv = 0;
      if (max_ele == min_ele)
        cv = 0;
      else
        cv = std::round((double)(currentele - min_ele) / (max_ele - min_ele) *
                        kMaxColorValue);
      Color tempcolor(cv, cv, cv);
      rowcolors.push_back(tempcolor);
    }
    image_.push_back(rowcolors);
  }
}

GrayscaleImage::GrayscaleImage(const std::string& filename,
                               size_t width,
                               size_t height):
    width_(width), height_(height) {
  ElevationDataset dataset(filename, width, height);
  int min_ele = dataset.MinEle(), max_ele = dataset.MaxEle();
  for (unsigned int i = 0; i < dataset.GetData().size(); ++i) {
    std::vector<Color> rowcolors;
    for (unsigned int j = 0; j < width_; ++j) {
      int currentele = dataset.DatumAt(i, j);
      int cv = 0;
      if (max_ele == min_ele)
        cv = 0;
      else
        cv = std::round((double)(currentele - min_ele) / (max_ele - min_ele) *
                        kMaxColorValue);
      Color tempcolor(cv, cv, cv);
      rowcolors.push_back(tempcolor);
    }
    image_.push_back(rowcolors);
  }
}

void GrayscaleImage::ToPpm(const std::string& name) const {
  std::ofstream gsppm{name};
  if (!gsppm.is_open()) throw std::runtime_error("ppm output not opened");
  gsppm << "P3\n";
  gsppm << width_ << " " << height_ << "\n";
  gsppm << kMaxColorValue << "\n";
  for (unsigned int i = 0; i < height_; ++i) {
    for (unsigned int j = 0; j < width_; ++j) {
      gsppm << image_[i][j].Red() << " " << image_[i][j].Green() << " "
            << image_[i][j].Blue() << " ";
    }
    gsppm << "\n";
  }
}
