# Development Plan

| # | Task Name                                                            | Difficulty (1-5) | Dependencies | Owner | Due Date | Status |
|---|---|---|---|---|---|---|
| 1 | Header file design (Piece, Board, Game interfaces)                   | 3 | N/A | All | Apr 19 | Completed
| 2 | UML diagram                                                          | 2 | 1 | All | Apr 15 | Completed 
| 3 | Thin slice: minimal Board, Pawn, King, Game, main running end to end | 4 | 1 | All | Apr 20 | Completed
| 4 | Path helper functions (straight, diagonal clear path)                | 2 |1, 3|nlin18|Apr 21|Completed
| 5 | Queen.cpp implementation                                        | 2 | 1, 4 | nlin18 | Apr 22| Completed
| 6 | Bishop.cpp implementation                                       | 1 | 1, 4 | nlin18 | Apr 22 | Completed
| 7 | King.cpp full implementation (movement only)                         | 2 | 1, 3 | syu99 | Apr 23 | Completed
| 8 | Rook.cpp full implementation                                         | 1 | 1, 4 | nlin18 | Apr 22 | Completed |
| 9 | Knight.cpp full implementation                                       | 2 | 1 | syu99 | Apr 22 | Completed
| 10 | Pawn.cpp (movement, capture, promotion)                             | 4 | 1, 3 | syu99 | Apr 23 | Completed
| 11 | Board.cpp full: add_piece with exceptions                           | 2 | 1, 3 | xgao59 | Apr 21 | Completed
| 12 | Board::iterator nested class                                        | 3 | 1, 11 | xgao59 | Apr 22 | Completed
| 13 | Board::display with terminal colors                                 | 2 | 12 | xgao59 | Apr 23 | Completd
| 14 | File I/O: operator>> and operator<< for Board and Game              | 4 | 12 | xgao59 | Apr 24 | Completed
| 15 | Game::make_move full validation chain with exceptions               | 5 | 4-15 | All | Apr 25 | Completed
| 16 | Check, checkmate, stalemate detection                               | 5 | 16 | syu99 + nlin18 | Apr 25 | Completed
| 17 | point_value evaluation function                                     | 2 | 5-10 | nlin18 | Apr 25 | Completed
| 18 | main.cpp exception handling                                         | 2 | 15, 16 | All | Apr 25 | Completed
| 19 | Run sample files (mate_in_two, promotion_to_mate, stalemate)        | 2 | 16, 17, 18 | All | Apr 26 | Completed
| 20 | Valgrind pass and memory leak fixes                                 | 3 | All implementation | All | Apr 26 | Completed
| 21 | Code style cleanup (comments, header guards, no using in headers)   | 1 | All implementation | All | Apr 26 | Completed

