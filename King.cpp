#include "King.h"
#include <cmath>

namespace Chess
{
  bool King::legal_move_shape(const Position& start, const Position& end) const {
    int x_difference = abs(end.first - start.first);
    int y_difference = abs(end.second - start.second);
    if (x_difference + y_difference == 0) {
      return false; //King can't move nowhere for a move
    }
    return (x_difference <= 1 && y_difference <= 1); //Allows for any movement for 1 tile
  }
}
