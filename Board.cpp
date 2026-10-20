#include <iostream>
#include <utility>
#include <map>
#ifndef _WIN32
#include "Terminal.h"
#endif // !_WIN32
#include "Board.h"
#include "CreatePiece.h"
#include "Exceptions.h"

namespace Chess
{
  /////////////////////////////////////
  // DO NOT MODIFY THIS FUNCTION!!!! //
  /////////////////////////////////////
  Board::Board(){}

  Board::~Board() {
    clear();
  }

  void Board::clear() {
    for(std::map<Position, Piece*>::iterator it = occ.begin();it != occ.end(); ++it) {
      delete it->second; //free heap mem
    }
    occ.clear();
  }

  Board::Board(const Board& other){ //deep copy create new piece matche piece on board
    for (std::map <Position, Piece*>::const_iterator it = other.occ.begin();it != other.occ.end();++it){
      char designator = it->second->to_ascii();
      occ[it->first] = create_piece(designator);
    }
  }

  Board& Board::operator=(const Board& other)
  {
    if (this ==&other){ //avoi self assigment
        return *this;
    }

    clear(); //delete existign pieces
    for (std::map<Position, Piece*>::const_iterator it = other.occ.begin();it != other.occ.end();++it) {
      occ[it->first] = create_piece(it->second->to_ascii()); //matching piece on board
    }
    return *this;
  }


  const Piece* Board::operator()(const Position& position) const { //This functions returns a pointer to the piece present at that square
    std::map<Position,Piece*>::const_iterator it = occ.find(position);
    if (it==occ.end()){
      return nullptr; //not found
    }
    return it->second; //found
  }
  
  void Board::add_piece(const Position& position, const char& piece_designator) {
   Piece *p = create_piece(piece_designator); //valid designator
    if(!p){
      throw Exception("invalid designator");
    }

    char col = position.first; //validate pos
    char row = position.second;

    if(col <'A'||col > 'H'||row < '1'||row > '8') {
      delete p;
      throw Exception("invalid position");
    }

    if(occ.count(position)) { //validate occupied or not
      delete p;
      throw Exception("position is occupied");
    }
    
    occ[position] = p; //add piece to board if valid
  }

  void Board::display() const { //UI fo the board
    std::cout << "   ";
    for(char c = 'A';c <= 'H'; c++) { //header (A B C D E F G H)
      std::cout << c<< " " ;
    }
    std::cout << "\n";
    for(char r='8';r>='1';r--){ //row loop
      std::cout << r <<" ";
      for(char c='A';c<='H';c++){// col loop
        int col_index = c - 'A';
        int row_index = r - '1';
        bool light = ((col_index)+(row_index))%2; //light when (col index + row index) is odd
        if(light){
          Terminal::color_all(true, Terminal::BLACK, Terminal::WHITE);
        } 
        else {
          Terminal::color_all(true, Terminal::WHITE, Terminal::BLACK);
        }

        const Piece* piece = (*this)(Position(c,r));//piece or empty square
        if(piece){
          std::cout << piece->to_unicode() << " " ; //print piece unicode symb
        } 
        
        else {
          std::cout << "  ";// empty square
        }

        Terminal::set_default();
      }
      std::cout<<" "<<r<<"\n";
    }
    std::cout << "   "; //footer
    for (char i = 'A'; i<= 'H'; i++){
      std::cout<<i<< " ";
    }
    std::cout << "\n";

  }

  bool Board::has_valid_kings() const { //There are two kings
    int white_king_count = 0;
    int black_king_count = 0;
    for (std::map<std::pair<char, char>, Piece*>::const_iterator it = occ.begin();
	       it != occ.end();
	       ++it) {
      if (it->second) {
	      switch (it->second->to_ascii()) {
	      case 'K':
	        white_king_count++;
	        break;
	      case 'k':
	        black_king_count++;
	        break;
	      }
      }
    }
    return (white_king_count == 1) && (black_king_count == 1);
  }

  /////////////////////////////////////
  // DO NOT MODIFY THIS FUNCTION!!!! //
  /////////////////////////////////////
  std::ostream& operator<<(std::ostream& os, const Board& board) {
    for(char r = '8'; r >= '1'; r--) {
      for(char c = 'A'; c <= 'H'; c++) {
	      const Piece* piece = board(Position(c, r));
	      if (piece) {
	        os << piece->to_ascii();
	      } else {
	        os << '-';
	      }
      }
      os << std::endl;
    }
    return os;
  }
}
