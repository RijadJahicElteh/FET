#include "Board.hpp"
#include <iostream>

int main() {
  Board sudoku;
  if(!sudoku.loadFromFile("puzzle.txt")) return 1;

  while(true) {
    sudoku.print();
    int r, c, v;
    std::cout<<"Unesi red(1-9), kolonu(1-9), vrijednost(0 za brisanje): ";
    std::cin>>r>>c>>v;

    if(!sudoku.setValue(r-1,c-1,v)) {
      std::cout<<"Greska. Pokusaj ponovo\n";
    }
  }
  return 0;
}

