// vim: tw=60

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

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
  // Goal: read the database, then ask user for color names.
  // If the user enters a valid name, print the color.
  // Continue til the user says quit.

  // Read the database.
  std::ifstream f("colors.txt");
  std::vector<std::string> names;
  std::vector<Color> colors;
  while (true) {
    std::string name;
    Color color;
    f >> name >> color;
    names.push_back(name);
    colors.push_back(color);
    if (!f) break;
  }

  while (true) {
    std::string input;
    std::cout << "Enter a color name, or type quit: ";
    std::cin >> input;
    if (input == "quit") break;
    for (int i = 0; i < names.size(); i++) {
      if (names[i] == input) {
        std::cout << colors[i] << std::endl;
      }
    }
  }
}
