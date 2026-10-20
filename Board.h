#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <map>
#include "Piece.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include "Mystery.h"

namespace Chess
{
  class Board {

		// Throughout, we will be accessing board positions using Position defined in Piece.h.
		// The assumption is that the first value is the column with values in
		// {'A','B','C','D','E','F','G','H'} (all caps)
		// and the second is the row, with values in {'1','2','3','4','5','6','7','8'}

	public:
		// Default constructor
		Board();

		~Board(); //destructor

		Board(const Board& other); //copy constructor, 4 deep copies

		Board& operator=(const Board& other); //assignment operator, 4 deep copies

		// Returns a const pointer to the piece at a prescribed location if it exists,
		// or nullptr if there is nothing there.
		const Piece* operator() (const Position& position) const;

		// Attempts to add a new piece with the specified designator, at the given position.
		// Throw exception for the following cases:
		// -- the designator is invalid, throw exception with error message "invalid designator"
		// -- the specified position is not on the board, throw exception with error message "invalid position"
		// -- if the specified position is occupied, throw exception with error message "position is occupied"
		void add_piece(const Position& position, const char& piece_designator); 

		void clear(); //nuke all pieces off board , free heap mem

		// Displays the board by printing it to stdout
		void display() const;

		// Returns true if the board has the right number of kings on it
		bool has_valid_kings() const;

		class iterator{//travrse every square of board (c A-H, r 1-8)
			public:
				iterator(char c, char r): col(c), row(r) {}

				Position operator*() const { return Position(col, row); }

				iterator& operator++() {
					if (col < 'H') {
						col++; //still more room
					} 
					
					else {
						col = 'A'; //end of row-> wrap around to A
						row++; //move down
					}
					return *this;
				}

				bool operator!=(const iterator& other) const {
					return ((col != other.col)|| (row != other.row));
				}
				
		
			private:
				char col;
				char row;
		};
		
		iterator begin() const { return iterator('A', '1'); } //return ite to A8
		iterator end() const { return iterator('A', '0'); } //return past the end ite 

		

	private:
		// The sparse map storing the pieces, keyed off locations
		std::map<Position, Piece*> occ;

		friend class Game;
        // Write the board state to an output stream
        friend std::ostream& operator<< (std::ostream& os, const Board& board);
	};	
}
#endif // BOARD_H
