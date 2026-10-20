#include "Knight.h"
#include <cmath>

namespace Chess
{
  bool Knight::legal_move_shape(const Position& start, const Position& end) const {
    int x_difference = abs(start.first-end.first);
    int y_difference = abs(start.second-end.second);
    if ((x_difference == 2 && y_difference == 1) || (x_difference == 1 && y_difference == 2)) {
      return true;
    }
    return false;
  }
}