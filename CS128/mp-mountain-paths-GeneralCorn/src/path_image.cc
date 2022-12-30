#include "path_image.hpp"

#include <fstream>
#include <limits>
#include <stdexcept>
#include <vector>

PathImage::PathImage(const GrayscaleImage& image,
                     const ElevationDataset& dataset):
    width_(dataset.Width()), height_(dataset.Height()) {
  ////////STOREPATHS///////////
  for (unsigned int i = 0; i < height_; ++i) {
    Path temp = RowCalculator(dataset, i);
    paths_.push_back(temp);
  }

  const Color kRed(252, 25, 63);
  const Color kGreen(31, 253, 13);
  path_image_ = image.GetImage();
  Path initpath = paths_.at(0);
  for (const Path& curr : paths_) {
    if (curr.EleChange() < initpath.EleChange()) initpath = curr;
    for (unsigned int i = 0; i < curr.GetPath().size(); ++i) {
      path_image_[curr.GetPath()[i]][i] = kRed;
    }
  }
  for (unsigned int i = 0; i < path_image_[0].size(); ++i) {
    path_image_[initpath.GetPath()[i]][i] = kGreen;
  }
}

void PathImage::ToPpm(const std::string& name) const {
  std::ofstream pippm{name};
  pippm << "P3\n";
  pippm << width_ << " " << height_ << "\n";
  pippm << kMaxColorValue << "\n";
  for (unsigned int i = 0; i < height_; ++i) {
    for (unsigned int j = 0; j < width_; ++j) {
      pippm << path_image_[i][j].Red() << " " << path_image_[i][j].Green()
            << " " << path_image_[i][j].Blue() << " ";
    }
    pippm << "\n";
  }
}

////////////////HELPERFUNCTIONS/////////////////////////////
///////////////HELPERFUNCTIONS//////////////////////////////
///////////////HELPERFUNCTIONS//////////////////////////////

Path PathImage::RowCalculator(const ElevationDataset& dataset,
                              size_t starting_row) const {
  Path pathatrow(width_, starting_row);
  unsigned int forward = starting_row, top = 0, bottom = 0;
  int current = dataset.DatumAt(starting_row, 0);
  for (unsigned int col = 1; col < width_; ++col) {
    top = forward - 1;
    bottom = forward + 1;
    unsigned int forward_dist = abs((current - dataset.DatumAt(forward, col)));
    unsigned int bottom_dist = abs((current - dataset.DatumAt(bottom, col)));
    unsigned int top_dist = abs((current - dataset.DatumAt(top, col)));
    if ((forward_dist <= bottom_dist && forward_dist <= top_dist)) {
      current = dataset.DatumAt(forward, col);
      pathatrow.SetLoc(col, forward);
      pathatrow.IncEleChange(forward_dist);
    } else if (top_dist == bottom_dist ||
               (bottom_dist < top_dist && bottom_dist < forward_dist)) {
      current = dataset.DatumAt(bottom, col);
      pathatrow.SetLoc(col, bottom);
      pathatrow.IncEleChange(bottom_dist);
      forward = bottom;
    } else {
      current = dataset.DatumAt(top, col);
      pathatrow.SetLoc(col, top);
      pathatrow.IncEleChange(top_dist);
      forward = top;
    }
  }
  return pathatrow;
}
