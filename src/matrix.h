#ifndef SRC_MATRIX_H_
#define SRC_MATRIX_H_

#include <vector>

class Matrix {
 public:
  Matrix();
  Matrix(const Matrix& other);
  Matrix(Matrix&& other);
  ~Matrix();

  Matrix& operator=(const Matrix& other);
  Matrix& operator=(Matrix&& other);

  void Resize(unsigned rows, unsigned cols);
  double& At(unsigned row, unsigned col);
  std::vector<double>& operator[](unsigned row);

  unsigned get_rows();
  unsigned get_cols();

 private:
  std::vector<std::vector<double>> m_data;
};

#endif  // SRC_MATRIX_H_
