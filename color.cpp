// vim: tw=60

#include <fstream>
#include <iostream>
#include <map>
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

Color getColor(const std::map<std::string, Color>& colors,
               const std::string& color) {
  return colors.at(color);
}

int main() {
  // Goal: read the database, then ask user for color names.
  // If the user enters a valid name, print the color.
  // Continue til the user says quit.

  // Read the database.
  std::ifstream f("colors.txt");
  std::map<std::string, Color> colors;
  while (true) {
    std::string name;
    Color color;
    f >> name >> color;
    colors[name] = color;
    if (!f) break;
  }

  while (true) {
    std::string input;
    std::cout << "Enter a color name, or type quit: ";
    std::cin >> input;
    if (input == "quit") break;
    Color color = getColor(colors, input);
    std::cout << color << std::endl;
  }
}