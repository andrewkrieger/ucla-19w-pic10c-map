// vim: tw=60

#include <cctype>
#include <fstream>
#include <iostream>
#include <string>

struct User {
  std::string username, password;
};

std::ostream& operator<<(std::ostream& os, const User& u) {
  return os << "<User '" << u.username
            << "' with password '" << u.password << "'";
}

std::istream& operator>>(std::istream& is, User& u) {
  is >> u.username;
  if (!is) return is;
  std::getline(is, u.password);
  size_t i = 0;
  while (i < u.password.size() &&
         std::isspace(u.password[i])) {
    i++;
  }
  // What is `i` here?
  u.password.erase(0, i);
  return is;
}

int main() {
  std::ifstream f("users.txt");
  while (true) {
    User user;
    if (!(f >> user)) break;
    std::cout << "Got: " << user << '\n';
  }
}
