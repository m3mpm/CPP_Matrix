#include "cpp_matrix.h"

/*--- private method ---*/
void Matrix::memory_allocat() {
  _matrix = new double*[_rows];
  for (int i = 0; i < _rows; i++) {
    _matrix[i] = new double[_cols]();
  }
}

void Matrix::memory_free() {
  for (int i = 0; i < _rows; i++) {
    delete[] _matrix[i];
  }
  delete[] _matrix;
}

void Matrix::copy_elemets(const Matrix& other) {
  for (int i = 0; i < other._rows; i++) {
    for (int j = 0; j < other._cols; j++) {
      this->_matrix[i][j] = other._matrix[i][j];
    }
  }
}

/*--- private method end ---*/

/*--- constructor & destructor ---*/
Matrix::Matrix() {
  _rows = _cols = 0;
  _matrix = nullptr;
}

Matrix::Matrix(int rows, int cols) {
  if (rows < 1 || cols < 1) throw std::invalid_argument("Incorrect arguments!");
  _rows = rows;
  _cols = cols;
  memory_allocat();
}

Matrix::Matrix(const Matrix& other)
    : Matrix(other._rows, other._cols) {
  copy_elemets(other);
}

Matrix::Matrix(Matrix&& other) : Matrix() {
  this->_rows = other._rows;
  this->_cols = other._cols;
  this->_matrix = other._matrix;
  other._matrix = nullptr;
}

/* destructor */
Matrix::~Matrix() {
  if (_matrix) {
    memory_free();
  }
  this->_rows = 0;
  this->_cols = 0;
}

/*--- constructor & destructor end ---*/

/* set & get */

int Matrix::get_rows() { return _rows; }

void Matrix::set_rows(int new_rows) {
  if (new_rows < 1) throw std::invalid_argument("Incorrect number");
  Matrix tmp(new_rows, _cols);
  for (int i = 0; i < tmp._rows; i++) {
    for (int j = 0; j < tmp._cols; j++) {
      if (i < _rows) {
        tmp._matrix[i][j] = _matrix[i][j];
      }
    }
  }
  *this = tmp;
}

int Matrix::get_cols() { return _cols; }

void Matrix::set_cols(int new_cols) {
  if (new_cols < 1) throw std::invalid_argument("Incorrect number");
  Matrix tmp(_rows, new_cols);
  for (int i = 0; i < tmp._rows; i++) {
    for (int j = 0; j < tmp._cols; j++) {
      if (j < _cols) {
        tmp._matrix[i][j] = _matrix[i][j];
      }
    }
  }
  *this = tmp;
}

/* set & get end*/

/*--- public methods ---*/
bool Matrix::eq_matrix(const Matrix& other) {
  bool result = false;
  if (this->_rows == other._rows && this->_cols == other._cols) {
    result = true;
    for (int i = 0; i < other._rows; i++) {
      for (int j = 0; j < other._cols; j++) {
        if (fabs(this->_matrix[i][j] - other._matrix[i][j]) >= EPS) {
          result = false;
          break;
        }
      }
      if (!result) {
        break;
      }
    }
  }
  return result;
}

void Matrix::sum_matrix(const Matrix& other) {
  if (_rows != other._rows || _cols != other._cols)
    throw std::invalid_argument("Can't sum matrixs. Different matrixs' size");
  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < _cols; j++) {
      _matrix[i][j] += other._matrix[i][j];
    }
  }
}

void Matrix::sub_matrix(const Matrix& other) {
  if (_rows != other._rows || _cols != other._cols)
    throw std::invalid_argument("Can't sub matrixs. Different matrixs' size");
  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < _cols; j++) {
      _matrix[i][j] -= other._matrix[i][j];
    }
  }
}

void Matrix::mul_number(const double num) {
  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < _cols; j++) {
      _matrix[i][j] *= num;
    }
  }
}

void Matrix::mul_matrix(const Matrix& other) {
  if (_cols != other._rows)
    throw std::invalid_argument(
        "Can't mul matrixs. Number of columns aren't equal to number of rows!");
  Matrix res(_rows, other._cols);
  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < other._cols; j++) {
      for (int p = 0; p < _cols; p++) {
        res._matrix[i][j] += _matrix[i][p] * other._matrix[p][j];
      }
    }
  }
  *this = res;
}

Matrix Matrix::transpose() {
  Matrix res(_cols, _rows);
  for (int i = 0; i < _cols; i++) {
    for (int j = 0; j < _rows; j++) {
      res._matrix[i][j] = _matrix[j][i];
    }
  }
  return res;
}

Matrix Matrix::get_minor_matrix(int row, int col) {
  Matrix m(_rows - 1, _cols - 1);
  int x = 0, y = 0;
  for (int i = 0; i < this->_rows; i++) {
    for (int j = 0; j < this->_cols; j++) {
      if (i != row && j != col) {
        m._matrix[x][y] = _matrix[i][j];
        y += 1;
      }
    }
    if (y == m._cols) {
      x += 1;
      y = 0;
    }
  }
  return m;
}

double Matrix::determinant() {
  if (_rows != _cols) throw std::invalid_argument("The matrix is not square!");
  double determinant = 0.0;
  if (_cols == 1) {
    determinant = _matrix[0][0];
  } else if (_cols == 2) {
    determinant =
        ((_matrix[0][0] * _matrix[1][1]) - (_matrix[0][1] * _matrix[1][0]));
  } else {
    int i = 0;
    for (int j = 0; j < _cols; j++) {
      Matrix minor_matrix = get_minor_matrix(i, j);
      determinant +=
          _matrix[i][j] * pow(-1, i + j + 2) * minor_matrix.determinant();
    }
  }
  return determinant;
}

Matrix Matrix::calc_complements() {
  if (_rows != _cols) throw std::invalid_argument("The matrix is not square!");
  Matrix complements(_rows, _cols);
  if (_cols == 1) {
    complements._matrix[0][0] = 1;
  } else {
    for (int i = 0; i < _rows; i++) {
      for (int j = 0; j < _cols; j++) {
        Matrix minor_matrix = get_minor_matrix(i, j);
        complements._matrix[i][j] =
            pow(-1, i + j + 2) * minor_matrix.determinant();
      }
    }
  }
  return complements;
}

Matrix Matrix::inverse_matrix() {
  if (_rows != _cols) throw std::invalid_argument("The matrix is not square!");
  double determinant_result = this->determinant();
  if (determinant_result == 0.0) {
    throw std::invalid_argument("Matrix's determinant is zero, aborted!");
  }
  Matrix complements(this->calc_complements());
  Matrix transpose_complements = complements.transpose();
  transpose_complements.mul_number(1.0 / determinant_result);
  return transpose_complements;
}

/*--- public methods end ---*/

/* Operators */
Matrix& Matrix::operator=(Matrix& other) {
  bool is_same = false;
  if (this == &other) is_same = true;
  if (!is_same) {
    if (this->_matrix) {
      memory_free();
    }
    this->_rows = other._rows;
    this->_cols = other._cols;
    memory_allocat();
    copy_elemets(other);
  }
  return *this;
}

bool Matrix::operator==(const Matrix& other) {
  return this->eq_matrix(other);
}

Matrix Matrix::operator+(const Matrix& other) {
  Matrix result(*this);
  result.sum_matrix(other);
  return result;
}

Matrix Matrix::operator-(const Matrix& other) {
  Matrix result(*this);
  result.sub_matrix(other);
  return result;
}

Matrix Matrix::operator*(const Matrix& other) {
  Matrix result(*this);
  result.mul_matrix(other);
  return result;
}

Matrix& Matrix::operator+=(const Matrix& other) {
  this->sum_matrix(other);
  return *this;
}

Matrix& Matrix::operator-=(const Matrix& other) {
  this->sub_matrix(other);
  return *this;
}

Matrix& Matrix::operator*=(const Matrix& other) {
  this->mul_matrix(other);
  return *this;
}

double& Matrix::operator()(int i, int j) {
  if ((i < 0 || i >= _rows) || (j < 0 || j >= _cols)) {
    throw std::invalid_argument("Incorrect arguments");
  }
  return this->_matrix[i][j];
}

Matrix Matrix::operator*(const double num) {
  Matrix result(*this);
  result.mul_number(num);
  return result;
}

Matrix& Matrix::operator*=(const double num) {
  this->mul_number(num);
  return *this;
}

Matrix operator*(const double num, const Matrix& other) {
  Matrix result(other);
  result.mul_number(num);
  return result;
}

/* Operators end */

/*--- helper methods ---*/
void Matrix::fill_matrix_eq() {
  double new_value = 1.0;
  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < _cols; j++) {
      _matrix[i][j] = new_value;
      new_value += 1.0;
    }
  }
}

void Matrix::print_matrix() {
  std::cout << "print this " << this << std::endl;
  std::cout << "print memory " << this->_matrix << std::endl;
  std::cout << "_rows = " << _rows << std::endl;
  std::cout << "_cols = " << _cols << std::endl;
  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < _cols; j++) {
      if (j == _cols - 1) {
        std::cout << _matrix[i][j] << std::endl;
      } else {
        std::cout << _matrix[i][j] << " ";
      }
    }
  }
}

/*--- helper methods end ---*/
