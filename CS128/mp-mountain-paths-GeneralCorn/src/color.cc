#include "color.hpp"

#include <stdexcept>

Color::Color(int r, int g, int b): red_(r), green_(g), blue_(b) {
  static const int kMaxColor = 255;
  if (r < 0 || g < 0 || b < 0 || r > kMaxColor || g > kMaxColor ||
      b > kMaxColor) {
    throw std::runtime_error("invalid color");
  }
}

// do not modify
bool operator==(const Color& rhs, const Color& lhs) {
  return (rhs.Red() == lhs.Red() && rhs.Green() == lhs.Green() &&
          rhs.Blue() == lhs.Blue());
}