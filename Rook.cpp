#include "Rook.h"

namespace Chess
{
  bool Rook::legal_move_shape(const Position& start, const Position& end) const {
    int col_diff = abs(end.first - start.first);
    int row_diff = abs(end.second - start.second);

    if (col_diff == 0 && row_diff == 0) return false; // no move
    // Rook can only move horizontally or vertically (taken from queen's horizontal/vertical move))
    return col_diff == 0 || row_diff == 0;
  }
}
