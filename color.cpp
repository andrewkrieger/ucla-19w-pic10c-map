// vim: tw=60

#include <fstream>
#include <iostream>
#include <string>

struct Color {
  float r, g, b;
};

std::ostream& operator<<(std::ostream& os, struct Color c) {
  return os << '(' << c.r << ',' << c.g << ',' << c.b
            << ')';
}

std::istream& operator>>(std::istream& is,
                         struct Color& c) {
  return is >> c.r >> c.g >> c.b;
}

int main() {
  std::ifstream f("colors.txt");
  while (true) {
    std::string name;
    Color color;
    f >> name >> color;
    if (!f) break;
    std::cout << "Read color '" << name << "' = " << color
              << '\n';
  }
}
