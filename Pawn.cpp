#include "Pawn.h"
#include <cmath>

namespace Chess
{
  bool Pawn::legal_move_shape(const Position& start, const Position& end) const {
     //Just do general move order (2 steps (or 1) on the first move and then 1 square after
     int direction;
     if (this->is_white()) {
      direction = 1;
     } else {
      direction = -1;
     }

     int y_difference = end.second - start.second; //No absolute value because pawn only moves forward
     int x_difference = end.first - start.first;
     
     if (x_difference != 0) {
      return false;
     }

     if (y_difference == direction) {
      return true;
     }

     if ((start.second == '2' || start.second == '7') && y_difference == 2 * direction) {
      return true;
  }
  return false;
}
    
  bool Pawn::legal_capture_shape(const Position& start, const Position& end) const {
    //Check diagonals for captures (only legal pawn capture)
    int direction;
     if (this->is_white()) {
      direction = 1;
     } else {
      direction = -1;
     }
    int x_difference = abs(end.first - start.first);
    int y_difference = end.second - start.second;
     return (x_difference == 1 && y_difference == direction);
  }
}
