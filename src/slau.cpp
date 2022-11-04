#include "slau.h"

#include <stdexcept>
#include <cmath>

Slau::Slau() : Matrix() { Resize(1, 2); }

Slau::Slau(unsigned num) : Matrix() {
  if (num == 0) throw std::out_of_range("slau needs at least 1 variable");

  Resize(num, num + 1);
}

Slau::~Slau() {}

void Slau::ReadFile(const std::string& file_name) {
  Matrix::ReadFile(file_name);
  if (!CheckSize()) throw std::invalid_argument("incorrect size");
}

std::vector<double> Slau::get_solution() {
  std::vector<double> res{};
  if (CheckDet()) {
    unsigned last{get_cols() - 1};
    ExpressAll();
    for (unsigned i{}; i < get_rows(); i++) res.push_back(-At(i, last));
  }
  return res;
}

bool Slau::CheckSize() {
  return (get_cols() == get_rows() + 1);
}

bool Slau::CheckDet() {
  Matrix tmp{*this};
  tmp.Resize(get_rows(), get_rows());
  return tmp.Determinant();
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
  bool flag{};
  if (fabs(At(index, index)) < kEps) {
    flag = true;
    for (unsigned i{}; i < get_rows(); i++) {
      if (fabs(At(i, index)) > kEps) {
        SubtractRow(i, index, 2);
        flag = false;
        break;
      }
    }
  }

  if (flag) {
    for (unsigned i{}; i < get_cols(); i++) {
      if (i == index) {
        At(index, i) = 1;
      } else if (i == get_cols() - 1) {
        At(index, i) = NAN;
      } else {
        At(index, i) = 0;
      }
    }
  } else {
    MultRow(index, 1 / At(index, index));
    for (unsigned i{}; i < get_rows(); i++) {
      if (i != index) SubtractRow(index, i, At(i, index));
    }
  }
}

void Slau::ExpressAll() {
  for (int i{}; i < get_rows(); i++) ExpressVar(i);
}
