#include "seam_carver.hpp"

// implement the rest of SeamCarver's functions her
int SeamCarver::GetEnergy(int row, int col) const {
  const int kMax = 1e9;
  if (row < 0 || row >= height_ || col < 0 || col >= width_) {
    return kMax;
  }

  int top = row - 1;
  int left = col - 1;
  if (row == 0) top = image_.GetHeight() - 1;
  if (col == 0) left = image_.GetWidth() - 1;

  Pixel row_top = image_.GetPixel(top, col);
  Pixel row_bottom = image_.GetPixel((row + 1) % image_.GetHeight(), col);

  Pixel col_left = image_.GetPixel(row, left);
  Pixel col_right = image_.GetPixel(row, (col + 1) % image_.GetWidth());

  return Pow(row_top.GetRed() - row_bottom.GetRed()) +
         Pow(row_top.GetGreen() - row_bottom.GetGreen()) +
         Pow(row_top.GetBlue() - row_bottom.GetBlue()) +
         Pow(col_left.GetRed() - col_right.GetRed()) +
         Pow(col_left.GetGreen() - col_right.GetGreen()) +
         Pow(col_left.GetBlue() - col_right.GetBlue());
}

// simplify use of array

int* SeamCarver::GetVerticalSeam() const {
  int** energy = new int*[height_];
  for (int row = 0; row < height_; ++row) energy[row] = new int[width_];
  for (int row = 0; row < height_; ++row)
    for (int col = 0; col < width_; ++col)
      energy[row][col] = GetEnergy(row, col);
  for (int row = height_ - 2; row >= 0; --row)
    for (int col = 0; col < width_; ++col) {
      int left = 0, right = 0, middle = 0;
      if ((col - 1) < 0)
        left = kMax;
      else
        left = energy[row + 1][col - 1];
      if ((col + 1) >= width_)
        right = kMax;
      else
        right = energy[row + 1][col + 1];
      middle = energy[row + 1][col];
      energy[row][col] += std::min({left, right, middle});
    }
  int* seam = new int[height_];
  int starting = width_ - 1;
  for (int col = width_ - 1; col >= 0; --col)
    if (energy[0][col] <= energy[0][starting]) starting = col;
  seam[0] = starting;
  int ind = starting;
  for (int row = 1; row < height_; ++row) {
    int curr = energy[row][ind];
    int temp = ind;
    if ((ind - 1) >= 0 && energy[row][ind - 1] < curr) {
      curr = energy[row][ind - 1];
      temp = ind - 1;
    }
    if ((ind + 1) < width_ && energy[row][ind + 1] < curr) {
      curr = energy[row][ind + 1];
      temp = ind + 1;
    }
    if ((ind - 1) >= 0 && (ind + 1) < width_ && curr > energy[row][ind + 1] &&
        energy[row][ind + 1] == energy[row][ind - 1]) {
      curr = energy[row][ind - 1];
      temp = ind - 1;
    }
    ind = temp;
    seam[row] = ind;
  }
  for (int row = 0; row < height_; ++row) delete[] energy[row];
  delete[] energy;
  return seam;
}

int* SeamCarver::GetHorizontalSeam() const {
  int** energy = new int*[height_];
  for (int row = 0; row < height_; ++row) energy[row] = new int[width_];
  for (int row = 0; row < height_; ++row)
    for (int col = 0; col < width_; ++col)
      energy[row][col] = GetEnergy(row, col);
  for (int col = width_ - 2; col >= 0; --col)
    for (int row = 0; row < height_; ++row) {
      int top = 0, bottom = 0, middle = 0;
      if ((row - 1) < 0)
        top = kMax;
      else
        top = energy[row - 1][col + 1];
      if ((row + 1) >= height_)
        bottom = kMax;
      else
        bottom = energy[row + 1][col + 1];
      middle = energy[row][col + 1];
      energy[row][col] += std::min({top, middle, bottom});
    }
  int* seam = new int[width_];
  int starting = height_ - 1;
  for (int row = height_ - 1; row >= 0; --row)
    if (energy[row][0] <= energy[starting][0]) starting = row;
  seam[0] = starting;
  int ind = starting;
  for (int col = 1; col < width_; ++col) {
    int curr = energy[ind][col];
    int temp = ind;
    if ((ind - 1) >= 0 && energy[ind - 1][col] < curr) {
      curr = energy[ind - 1][col];
      temp = ind - 1;
    }
    if ((ind + 1) < height_ && energy[ind + 1][col] < curr) {
      curr = energy[ind + 1][col];
      temp = ind + 1;
    }
    if ((ind - 1) >= 0 && (ind + 1) < height_ && curr > energy[ind + 1][col] &&
        energy[ind + 1][col] == energy[ind - 1][col]) {
      curr = energy[ind - 1][col];
      temp = ind - 1;
    }
    ind = temp;
    seam[col] = ind;
  }
  for (int row = 0; row < height_; ++row) delete[] energy[row];
  delete[] energy;
  return seam;
}

void SeamCarver::RemoveVerticalSeam() {
  int* seam = GetVerticalSeam();
  image_.RemoveVert(seam);
  delete[] seam;
  width_--;
  seam = nullptr;
}

void SeamCarver::RemoveHorizontalSeam() {
  int* seam = GetHorizontalSeam();
  image_.RemoveHoriz(seam);
  delete[] seam;
  height_--;
  seam = nullptr;
}

/////////////////////////////////////////
// given functions below, DO NOT MODIFY //
SeamCarver::SeamCarver(const ImagePPM& image): image_(image) {
  height_ = image.GetHeight();
  width_ = image.GetWidth();
}

void SeamCarver::SetImage(const ImagePPM& image) {
  image_ = image;
  width_ = image.GetWidth();
  height_ = image.GetHeight();
}
