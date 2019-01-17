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

// If `color_name` is a recognized name in `colors`,
// returns a pointer to that color. Else returns nullptr.
//
// Remark: In modern C++, we usually use value semantics
// (i.e. return-by-value), references, or smart pointers
// (which call `delete` for us; we'll discuss it later this
// quarter) instead of plain C-style pointers. One
// reasonable use case for pointers is situations where you
// want to return a "maybe-reference", i.e., either a
// reference to an existing object or null (meaning no such
// object). That's why this function is returning a pointer.
const Color* getColor(
    const std::map<std::string, Color>& colors,
    const std::string& color_name) {
  auto iterator = colors.find(color_name);
  if (iterator == colors.end()) {
    // color_name wasn't found
    return nullptr;
  } else {
    // color_name was found. `iterator` points to a
    // key-value pair. Let's unpack that key-value pair:
    const std::string& key = iterator->first;
    const Color& value = iterator->second;
    // And return by pointer, using the address-of operator.
    return &value;
  }
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
    if (input == "quit" || std::cin.eof()) break;
    const Color *color = getColor(colors, input);
    if (color) {
      std::cout << *color << std::endl;
    } else {
      std::cout << "Error: no such color" << std::endl;
    }
  }
}
