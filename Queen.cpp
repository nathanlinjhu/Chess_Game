#include "Queen.h"
#include <cmath>


namespace Chess
{
  bool Queen::legal_move_shape(const Position& start, const Position& end) const {
    int col_diff = abs(end.first - start.first);
    int row_diff = abs(end.second - start.second);


    if (col_diff == 0 && row_diff == 0) return false; // no move

    // Horizontal or vertical (acts like the rook)
    if (col_diff == 0 || row_diff == 0) return true;

    // Diagonal (acts like the bishop)
    if (col_diff == row_diff) return true;

    return false;
  }
}
