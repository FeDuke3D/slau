#include <iostream>

#include "slau.h"

int main(int argc, char** argv) {
  if (argc > 1) {
    for (int i{1}; i < argc; i++) {
      std::cout << argv[i] << ":\n";
      try {
        Slau A;
        A.ReadFile(argv[i]);
        auto sol = A.get_solution();
        for (auto& each : sol) std::cout << each << std::endl;
      } catch (const std::exception& e) {
        std::cout << "error: " << e.what() << std::endl;
      }
    }
  } else {
    std::cout << "please, specify a file" << std::endl;
  }
}