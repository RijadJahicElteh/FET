#include <vector>
#include <string>

class Board {
  private:
    static const int SIZE = 9;
    std::vector<std::vector<int>> board;
    std::vector<std::vector<bool>> fixed;

  public:
    Board();
    bool loadFromFile(const std::string& filename);
    void print() const;
    bool isValid(int red, int kolona, int vrijednost) const;
    bool setValue(int red, int kolona, int vrijednost);
    bool isFixed(int red, int kolona) const;
    bool isConflict(int red, int kolona) const;
};
