#ifndef SRC_SLAU_H_
#define SRC_SLAU_H_

#include "matrix.h"

class Slau : private Matrix {
 public:
  Slau();
  explicit Slau(unsigned num);
  Slau(const Slau& other) : Matrix(other) {}
  Slau(Slau&& other) : Matrix(std::move(other)) {}
  ~Slau();

  Slau& operator=(const Slau& other);
  Slau& operator=(Slau&& other);

  void ReadFile(const std::string& file_name);
  std::vector<double> get_solution();

 private:
  const double kEps{1e-8};

  bool CheckSize();
  bool CheckDet();
  void SubtractRow(unsigned what, unsigned from, double coef);
  void MultRow(unsigned row, double coef);
  void ExpressVar(unsigned index);
  void ExpressAll();
};

#endif  // SRC_SLAU_H_