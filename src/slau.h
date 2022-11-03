#ifndef SRC_SLAU_H_
#define SRC_SLAU_H_

#include "matrix.h"

class Slau : private Matrix {
 public:
  Slau();
  explicit Slau(unsigned num);
  ~Slau();

  std::vector<double> get_solution();

 private:
  const double kEps{1e-8};

  bool CheckDet();
  void SubtractRow(unsigned what, unsigned from, double coef);
  void MultRow(unsigned row, double coef);
  void ExpressVar(unsigned index);
  void ExpressAll();
};

#endif  // SRC_SLAU_H_