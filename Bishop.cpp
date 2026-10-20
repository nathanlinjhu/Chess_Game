#include "Bishop.h"
#include <cmath>


namespace Chess
{
  bool Bishop::legal_move_shape(const Position& start, const Position& end) const {
    int col_diff = abs(end.first - start.first);
    int row_diff = abs(end.second - start.second);

    if (col_diff == 0 && row_diff == 0) return false; // no move

    // Bishop can only move diagonally (taken from queen's diagonal move))
    return col_diff == row_diff;
  }
}
