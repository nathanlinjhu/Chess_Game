#include <cassert>
#include <string>
#include "Exceptions.h"
#include "Game.h"

namespace Chess
{
	/////////////////////////////////////
	// DO NOT MODIFY THIS FUNCTION!!!! //
	/////////////////////////////////////
	Game::Game() : is_white_turn(true) {
		// Add the pawns
		for (int i = 0; i < 8; i++) {
			board.add_piece(Position('A' + i, '1' + 1), 'P');
			board.add_piece(Position('A' + i, '1' + 6), 'p');
		}

		// Add the rooks
		board.add_piece(Position( 'A'+0 , '1'+0 ) , 'R' );
		board.add_piece(Position( 'A'+7 , '1'+0 ) , 'R' );
		board.add_piece(Position( 'A'+0 , '1'+7 ) , 'r' );
		board.add_piece(Position( 'A'+7 , '1'+7 ) , 'r' );

		// Add the knights
		board.add_piece(Position( 'A'+1 , '1'+0 ) , 'N' );
		board.add_piece(Position( 'A'+6 , '1'+0 ) , 'N' );
		board.add_piece(Position( 'A'+1 , '1'+7 ) , 'n' );
		board.add_piece(Position( 'A'+6 , '1'+7 ) , 'n' );

		// Add the bishops
		board.add_piece(Position( 'A'+2 , '1'+0 ) , 'B' );
		board.add_piece(Position( 'A'+5 , '1'+0 ) , 'B' );
		board.add_piece(Position( 'A'+2 , '1'+7 ) , 'b' );
		board.add_piece(Position( 'A'+5 , '1'+7 ) , 'b' );

		// Add the kings and queens
		board.add_piece(Position( 'A'+3 , '1'+0 ) , 'Q' );
		board.add_piece(Position( 'A'+4 , '1'+0 ) , 'K' );
		board.add_piece(Position( 'A'+3 , '1'+7 ) , 'q' );
		board.add_piece(Position( 'A'+4 , '1'+7 ) , 'k' );
	}


	bool Game::is_path_clear(const Position& start, const Position& end) const {
    	int col_step = 0, row_step = 0; // initially assume no movement
		// calculate the total distance between the start and end positions in both dimensions
    	int col_diff = end.first - start.first; 
    	int row_diff = end.second - start.second;

		// figure out horizontal and vertical step directions 
    	if (col_diff != 0) {
        	if (col_diff > 0) {
            	col_step = 1; // move right
        	} else {
            	col_step = -1; // move left 
        	}
    	}

		// figure out vertical step direction
		if (row_diff != 0) {
			if (row_diff > 0) {
				row_step = 1; // move up
			} else {
				row_step = -1; // nove down
			 }
			}

		char c = start.first + col_step;
		char r = start.second + row_step;

		// go through square by square towards the end and stop right before the end
		while (Position(c, r) != end) {
//Beginning of using AI assistance
			// checks if there is a piece in the way
			// if yes, path is blocked and return false
			if (board(Position(c, r)) != nullptr) return false;
			c += col_step;
			r += row_step;
// End of using AI assistance
		}
		// if we made it here, path is clear and return true
		return true;
	}


	void Game::make_move(const Position& start, const Position& end) { //Reference function const Piece* Board::operator()(const Position& position) const {
		if (start.first < 'A'|| start.first > 'H' || start.second < '1' || start.second > '8') { //make sure start is on the board
			throw Exception("start position is not on board");
    	}
		if (end.first < 'A'|| end.first > 'H' || end.second < '1' || end.second > '8') { //make sure end is on the board
			throw Exception("end position is not on board");
    	}
	
		
		const Piece* piece = board(start);
		if (!piece) {
			throw Exception("no piece at start position");
		}

		if (piece->is_white() != is_white_turn) { //Make sure it is the correct turn
			throw Exception("piece color and turn do not match");
		}

		const Piece* capture_piece = board(end);
		bool can_capture = (capture_piece != nullptr);

		if(can_capture) {
			if (piece->legal_capture_shape(start,end) == false) {
				throw Exception("illegal capture shape");
			}
		} else {
			if(piece->legal_move_shape(start,end) == false) {
				throw Exception("illegal move shape");
			}
		}
		
		if (can_capture && capture_piece->is_white() == is_white_turn) {
			throw Exception("cannot capture own piece");
		}

		int x_difference = abs(end.first-start.first);
		int y_difference = abs(end.second-start.second);
		if (x_difference == 0 || y_difference == 0 || x_difference == y_difference) {
			if (!is_path_clear(start, end)) {
				throw Exception("path is not clear");
			}
		}


	
		Game sim = *this; // sim move on copy of game.

		// Free any captured piece on the destination, then remove the mapping
		if (sim.board.occ.count(end)) {
			delete sim.board.occ[end];
			sim.board.occ.erase(end);
		}
		// Free the moving piece from the start square on the copy
		delete sim.board.occ[start];
		sim.board.occ.erase(start);

		// Place a fresh piece of the same type on the end square
		sim.board.add_piece(end, piece->to_ascii());

		if (sim.in_check(is_white_turn)) {
			throw Exception("move exposes check");
		}		


		char piece_char = piece->to_ascii(); //make move in real board and grab info
   		bool pawn_is_white = piece->is_white();

		if (board.occ.count(end)){ //delete capture piece on destination
			delete board.occ[end];

			board.occ.erase(end);
    	}

		delete board.occ[start]; //delete moving peiece from start
    	board.occ.erase(start);

		bool is_pawn = (piece_char == 'p' || piece_char == 'P');
    	bool is_promotion = (pawn_is_white && end.second == '8')||(!pawn_is_white && end.second == '1');		
		
		if (is_pawn && is_promotion) {		
			if (pawn_is_white) {
				board.add_piece(end,'Q');
			} else {
				board.add_piece(end,'q');
			}	
		} else {
			board.add_piece(end, piece_char); //nomarl move (keep same piece type)
		}

		is_white_turn = !is_white_turn;
	}

	bool Game::in_check(const bool& white) const {
		Position king_location('A','1');
		bool king_found = false;
		for (Board::iterator it = board.begin(); it != board.end(); ++it) {
			Position current_location = *it;
			const Piece* p = board(current_location);
			if (p && p->is_white() == white) {
				if(p->to_ascii() == 'K' || p->to_ascii() == 'k') {
					king_location = current_location;
					king_found = true;
					break;
				}
			}
		}
		if (!king_found) {return false;}

		for (Board::iterator it = board.begin(); it != board.end(); ++it) {
			Position current_square = *it;
			const Piece* p= board(current_square);
			if (p && p->is_white() != white) { //Checks color
				int x_difference = abs(current_square.first-king_location.first);
				int y_difference = abs(current_square.second-king_location.second);
				if (p->legal_capture_shape(current_square,king_location)) {

					if (x_difference == 0 || y_difference == 0 || x_difference == y_difference) {
						if (!is_path_clear(current_square,king_location)) continue;
					}
					return true;
				}

				}
			}
			return false;	
}


bool Game::in_mate(const bool& white) const {
	if (!in_check(white)) {return false;}
	
	for (Board::iterator it = board.begin(); it != board.end(); ++it) { //Iterate through the board
		Position curr_pos = *it;
		const Piece* p = board(curr_pos);
		if (!p || p->is_white() != white) {continue;}

		for (char col = 'A'; col <= 'H'; col++) { //Check every square on the board to see if it can help us avoid checkmate
			for (char row = '1'; row <= '8'; row++) {
				Position destination{col,row};
				if (curr_pos == destination) {continue;}

				const Piece* end_p = board(destination);
				bool is_capture = (end_p != nullptr);

				if (is_capture) {
					if (end_p->is_white() == white) {continue;}
					if (!p->legal_capture_shape(curr_pos,destination)) {continue;}
				} else { //This block is important as if it is not a capture, but is a legal move we continue through to see if it can help us avoid checkmate
					if (!p->legal_move_shape(curr_pos,destination)) {continue;}
				}
				int x_difference = abs(curr_pos.first-destination.first);
				int y_difference = abs(curr_pos.second-destination.second);
				if (x_difference == 0 || y_difference == 0 || x_difference == y_difference) {
					if (!is_path_clear(curr_pos,destination)) {continue;}
				}

				//Now that we checked to see if we could potentially make a move to help us avoid checkmate, we simulate this using similar logic as in make_move
				Game sim = *this;
                if (sim.board.occ.count(destination)) { //if piece at destination, delete it on copy
                    delete sim.board.occ[destination];
                    sim.board.occ.erase(destination);
                }

                delete sim.board.occ[curr_pos]; //delete moving piece
                sim.board.occ.erase(curr_pos);

                sim.board.add_piece(destination, p->to_ascii());//new piece at destination

                if (!sim.in_check(white)){
					return false;
				} 
							
			}
		}	
	}
	return true;

}




bool Game::in_stalemate(const bool& white) const {
    // first condition: player is not in check 
    if (in_check(white)) return false;

    // second condition: player has no legal moves
	// iterate through the board and find pieces of the correct color
    for (Board::iterator it = board.begin(); it != board.end(); ++it) {
        Position curr_pos = *it;
        const Piece* p = board(curr_pos);
        if (!p || p->is_white() != white) continue;

        for (char col = 'A'; col <= 'H'; col++) {
            for (char row = '1'; row <= '8'; row++) {
                Position destination{col, row};
                if (curr_pos == destination) continue;

                const Piece* end_p = board(destination);
                bool is_capture = (end_p != nullptr);

                if (is_capture) {
                    if (end_p->is_white() == white) continue;
                    if (!p->legal_capture_shape(curr_pos, destination)) continue;
                } else {
                    if (!p->legal_move_shape(curr_pos, destination)) continue;
                }

                int x_difference = abs(curr_pos.first - destination.first);
                int y_difference = abs(curr_pos.second - destination.second);
                if (x_difference == 0 || y_difference == 0 || x_difference == y_difference) {
                    if (!is_path_clear(curr_pos, destination)) continue;
                }

                // Simulate the move on a copy so the real board stays untouched
                Game sim = *this;

                if (sim.board.occ.count(destination)) {
                    delete sim.board.occ[destination];
                    sim.board.occ.erase(destination);
                }
                delete sim.board.occ[curr_pos];
                sim.board.occ.erase(curr_pos);
                sim.board.add_piece(destination,p->to_ascii());

                // found a legal move, not stalemate
                if (!sim.in_check(white)) return false;
            }
        }
    }
    // no legal moves found, result is stalemate
    return true;

	}

    // Return the total material point value of the designated player
    int Game::point_value(const bool& white) const {
		int total = 0;
    	for (Board::iterator it = board.begin(); it != board.end(); ++it) {
        	const Piece* piece = board(*it);
        	if (piece && piece->is_white() == white) {
            	switch (piece->to_ascii()) {
                	case 'P': case 'p':
						total += 1; 
						break;
                	case 'N': case 'n':
						total += 3;
						break;
                	case 'B': case 'b':
						total += 3;
						break;
                	case 'R': case 'r':
						total += 5;
						break;
                	case 'Q': case 'q':
						total += 9;
						break;
                	default:
						total += 0;
						break;
            }
        }
    }
    return total;
    }


    std::istream& operator>> (std::istream& is, Game& game) {
		game.board.clear(); //wipe current board for fresh start
		try {
		for (char i = '8'; i>='1'; i--){ //read row from 8 -> 1
			std::string line;

			if(!std::getline(is, line)){ //full line from onput stream
				throw Exception("failed to read board row");
			}
			if(line.size()<8){//less then 8 char
				throw Exception("row too few characters");
			}
			
			for (char j = 'A'; j<='H';j++){ //read col from A-> H
				char piece_designator = line [j-'A'];
				if(piece_designator!= '-'){
					game.board.add_piece(Position(j,i), piece_designator);
				}
			}
		}

		std::string turn_line; //whose turn is it
		if(!std::getline(is, turn_line)){
			throw Exception("failed to read turn indicator");
		}
		if(turn_line.empty()){
			throw Exception("missing turn indicator");
		}
		
		char turn = turn_line[0]; 

		if(turn == 'w'){
			game.is_white_turn = true;
		} 
		else if (turn =='b')
		{
			game.is_white_turn = false;
		}
		else 
		{
			throw Exception("invalid turn indicator");
		}
	} catch (const Exception& e) {
		game.board.clear();
		throw;
	}
		return is;
	}

    /////////////////////////////////////
    // DO NOT MODIFY THIS FUNCTION!!!! //
    /////////////////////////////////////
	std::ostream& operator<< (std::ostream& os, const Game& game) {
		// Write the board out and then either the character 'w' or the character 'b',
		// depending on whose turn it is
		return os << game.board << (game.turn_white() ? 'w' : 'b');
	}
}
