#include "slau.h"

#include <stdexcept>

Slau::Slau() { Resize(1, 2); }

explicit Slau::Slau(unsigned num) {
  if (num == 0) throw std::out_of_range("slau needs at least  variable");

  Resize(num, num + 1);
}

Slau::~Slau() {}

std::vector<double> Slau::get_solution() {
  std::vector<double> res{};
  unsigned last{get_cols() - 1};

  ExpressAll();
  for (unsigned i{}; i < get_rows(); i++) res.push_back(-At(i, last));
  return res;
}

void Slau::SubtractRow(unsigned what, unsigned from, double coef) {
  if (what >= get_rows() || from >= get_rows())
    throw std::out_of_range("index out of range");

  for (unsigned i{}; i < get_cols(); i++) At(from, i) -= At(what, i) * coef;
}

void Slau::MultRow(unsigned row, double coef) {
  if (row >= get_rows()) throw std::out_of_range("index out of range");

  for (auto& each : operator[](row)) each *= coef;
}

void Slau::ExpressVar(unsigned index) {
  MultRow(index, 1 / At(index, index));

  for (unsigned i{}; i < get_rows(); i++) {
    if (i != index) SubtractRow(index, i, At(i, index));
  }
}

void Slau::ExpressAll() {
  for (int i{}; i < get_rows(); i++) ExpressVar(i);
}
