#ifndef SRC_CPP_MATRIX_H_
#define SRC_CPP_MATRIX_H_

#include <cmath>
#include <exception>
#include <iostream>

#define EPS 1e-7

class Matrix {
 private:
  int _rows, _cols;
  double** _matrix;

  void memory_allocat();
  void memory_free();
  void copy_elemets(const Matrix& other);
  Matrix get_minor_matrix(int row, int col);

 public:
  Matrix();                        // default constructor
  Matrix(int rows, int cols);      // constructor with rows,cols
  Matrix(const Matrix& other);  // constructor copy
  Matrix(Matrix&& other);       // consturctor transfer
  ~Matrix();                       // destructor

  /* setters & getters */
  int get_rows();
  void set_rows(int new_rows);
  int get_cols();
  void set_cols(int new_cols);

  /* Methods */
  bool eq_matrix(const Matrix& other);
  void sum_matrix(const Matrix& other);
  void sub_matrix(const Matrix& other);
  void mul_number(const double num);
  void mul_matrix(const Matrix& other);
  Matrix transpose();
  Matrix calc_complements();
  double determinant();
  Matrix inverse_matrix();

  /* Operators */
  Matrix& operator=(Matrix& other);
  bool operator==(const Matrix& other);
  Matrix operator+(const Matrix& other);
  Matrix operator-(const Matrix& other);
  Matrix operator*(const Matrix& other);
  Matrix& operator+=(const Matrix& other);
  Matrix& operator-=(const Matrix& other);
  Matrix& operator*=(const Matrix& other);
  double& operator()(int i, int j);

  Matrix operator*(const double num);
  Matrix& operator*=(const double num);
  friend Matrix operator*(const double num, const Matrix& other);

  /* helper methods */
  void fill_matrix_eq();
  void print_matrix();
};

#endif  // SRC_CPP_MATRIX_H_
