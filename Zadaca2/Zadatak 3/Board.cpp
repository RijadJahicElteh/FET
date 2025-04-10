#include "Board.hpp"
#include <iostream>
#include <fstream>

Board::Board() {
  board = std::vector<std::vector<int>>(SIZE, std::vector<int>(SIZE, 0));
  fixed = std::vector<std::vector<bool>>(SIZE, std::vector<bool>(SIZE, false));
}

bool Board::loadFromFile(const std::string& filename) {
  std::ifstream in(filename);
  if(!in.is_open()) {
    std::cout<<"Neispravan fajl\n";
    return false;
  }
  for(int i=0;i<SIZE;++i) {
    for(int j=0;j<SIZE;++j) {
      int value;
      in>>value;
      board[i][j] = value;
      fixed[i][j] = (value != 0);
    }
  }
    return true;
}
bool Board::isValid(int red, int kolona, int vrijednost) const {
  if(vrijednost == 0) return true;
  for(int j=0;j<SIZE;++j)
    if(j!=kolona && board[red][j] == vrijednost) return false;
  for(int i=0;i<SIZE;++i) 
    if(i!=red && board[i][kolona] == vrijednost) return false;
  int blockRed = (red/3) * 3;
  int blockKol = (kolona/3) * 3;
  for(int i=blockRed; i<blockRed + 3; ++i)
    for(int j=blockKol; j<blockKol +3; ++j)
      if((i!=red||j!=kolona) && board[i][j] == vrijednost)
        return false;
  return true;
}

bool Board::setValue(int red, int kolona, int vrijednost) {
  if (red<0 || red >= SIZE || kolona < 0 || kolona > SIZE) {
    std::cout<<"Neispravan unos"<<std::endl;
    return false;
  }
  if(fixed[red][kolona]) {
    std::cout<<"Polje je fiksno!\n";
    return false;
  }
  if(vrijednost < 0 || vrijednost > 9) {
    std::cout<<"Neispravna vrijednost.\n";
    return false;
  }
  if(vrijednost != 0 && !isValid(red, kolona, vrijednost)) {
    std::cout<<"Vrijednost nije validna.\n";
    return false;
  }
  board[red][kolona] = vrijednost;
  return true;
}
bool Board::isFixed(int red, int kolona) const {
  return fixed[red][kolona];
}
bool Board::isConflict(int red, int kolona) const {
  int vrijednost = board[red][kolona];
  if(vrijednost == 0) return false;
  for(int j=0;j<SIZE;++j) 
    if(j!=kolona && board[red][j] == vrijednost) return true;
  for(int i=0;i<SIZE;++i)
    if(i!=red && board[i][kolona] == vrijednost) return true;
  int blockRed = (red/3)*3;
  int blockKol = (kolona/3)*3;
  for(int i=blockRed; i<blockRed +3; ++i) 
    for(int j=blockKol; j<blockKol +3; ++j)
      if((i!=red || j!= kolona) && board[i][j] == vrijednost)
        return true;
  return false;
}
void Board::print() const {
  for(int i=0;i<SIZE;++i) {
    if(i%3==0)
      std::cout<<"+---+---+---+---+---+---+---+---+---+\n";
  for(int j=0;j<SIZE;++j) {
    if(j%3==0) std::cout<<"|";
    int vrijednost = board[i][j];
    if(vrijednost == 0) {
      std::cout<<"   ";
    } else if (fixed[i][j]) {
      std::cout<<" "<<vrijednost<<" ";
    } else {
      if(isConflict(i,j)) {
        std::cout<<"*("<<vrijednost<<")";
      } else {
        std::cout<<"("<<vrijednost<<")";
      }
    }
  }
  std::cout<<"|\n";
  }
  std::cout<<"+---+---+---+---+---+---+---+---+---+\n";
}

