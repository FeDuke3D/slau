#include "matrix.h"

#include <stdexcept>

Matrix::Matrix() {}

Matrix::Matrix(const Matrix& other) { *this = other; }

Matrix::Matrix(Matrix&& other) { *this = std::move(other); }

Matrix::~Matrix() {}

Matrix& Matrix::operator=(const Matrix& other) {
  if (this != &other) m_data = other.m_data;
  return *this;
}

Matrix& Matrix::operator=(Matrix&& other) {
  if (this != &other) m_data = std::move(other.m_data);
  return *this;
}

void Matrix::Resize(unsigned rows, unsigned cols) {
  unsigned old_rows{get_rows()};
  if (rows != old_rows) m_data.resize(rows);
  if (cols != get_cols()) {
    for (auto& each : m_data) each.resize(cols);
  } else if (rows > old_rows) {
    for (unsigned i{old_rows}; i < rows; i++) {
      m_data[i].resize(cols);
    }
  }
}

double& Matrix::At(unsigned row, unsigned col) {
  if (row >= get_rows() || col >= get_cols())
    throw std::out_of_range("matrix index out of range");

  return m_data[row][col];
}

std::vector<double>& Matrix::operator[](unsigned row) {
  if (row >= get_rows()) throw std::out_of_range("matrix index out of range");

  return m_data[row];
}

unsigned Matrix::get_rows() { return m_data.size(); }

unsigned Matrix::get_cols() { return (get_rows()) ? m_data[0].size() : 0; }
