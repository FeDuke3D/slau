#include "matrix.h"

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <stdexcept>

Matrix::Matrix() {}

Matrix::Matrix(const Matrix& other) { *this = other; }

Matrix::Matrix(Matrix&& other) { *this = std::move(other); }

Matrix::~Matrix() {}

void Matrix::ReadFile(const std::string& file_name) {
  m_data.clear();
  std::ifstream stream(file_name);
  if (!stream) throw std::invalid_argument("cant open file");

  while (!stream.eof()) {
    std::vector<std::string> line;
    while (stream.peek() != '\n' && !stream.eof()) {
      std::string word;
      stream >> word;
      line.push_back(word);
    }
    if (stream.peek() == '\n') stream.get();
    if (line.size() > 0) {
      Resize(get_rows() + 1, std::max((unsigned)line.size(), get_cols()));
      unsigned cur_row{get_rows()};
      for (unsigned i{}; i < get_cols(); i++)
        At(cur_row - 1, i) = std::stod(line[i]);
    }
  }
  stream.close();
}

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

double Matrix::Determinant() {
  if (get_cols() != get_rows())
    throw std::invalid_argument(
        "trying to calculate determinant for a non square matrix");
  if (get_rows() == 0)
    throw std::invalid_argument(
        "trying to calculate determinant for an incorrect matrix");

  double res{};
  if (get_rows() == 1) {
    res = m_data[0][0];
  } else {
    for (int i{}; i < get_cols(); i++) {
      res += pow(-1, i) * m_data[0][i] * MinorElem(0, i);
    }
  }
  return res;
}

double Matrix::MinorElem(unsigned row, unsigned col) {
  return ReduxMx(row, col).Determinant();
}

Matrix Matrix::ReduxMx(unsigned row, unsigned col) {
  Matrix res;
  res.Resize(get_rows() - 1, get_cols() - 1);
  for (int i{}, isrc{}; i < res.get_rows(); i++, isrc++) {
    if (isrc == row) isrc++;
    for (int j{}, jsrc{}; j < res.get_cols(); j++, jsrc++) {
      if (jsrc == col) jsrc++;
      res[i][j] = m_data[isrc][jsrc];
    }
  }
  return res;
}
