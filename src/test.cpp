#include "gtest/gtest.h"
#include "cpp_matrix.h"

TEST(ConstructorsTests, costr_default) {
  Matrix m;
  ASSERT_EQ(m.get_rows(), 0);
  ASSERT_EQ(m.get_cols(), 0);
}

TEST(MethodsTests_eq_matrix, eq_matrix_1) {
  Matrix m1(3, 3);
  Matrix m2(3, 3);
  m1.fill_matrix_eq();
  m2.fill_matrix_eq();
  ASSERT_TRUE(m1.eq_matrix(m2));
}

TEST(MethodsTests_eq_matrix, eq_matrix_2) {
  Matrix m1(3, 3);
  Matrix m2(2, 2);
  m1.fill_matrix_eq();
  m2.fill_matrix_eq();
  ASSERT_FALSE(m1.eq_matrix(m2));
}

TEST(MethodsTests_eq_matrix, eq_matrix_3) {
  Matrix m1(3, 3);
  Matrix m2;
  m1.fill_matrix_eq();
  ASSERT_FALSE(m1.eq_matrix(m2));
}

TEST(MethodsTests_eq_matrix, eq_matrix_4) {
  Matrix m1;
  Matrix m2;
  ASSERT_TRUE(m1.eq_matrix(m2));
}

TEST(MethodsTests_eq_matrix, eq_matrix_5) {
  Matrix m1;
  m1.fill_matrix_eq();
  ASSERT_TRUE(m1.eq_matrix(m1));
}

TEST(ConstructorsTests, constr_with_param_1) {
  Matrix m1(3, 3);
  Matrix m2(3, 3);
  ASSERT_TRUE(m1.eq_matrix(m2));
}

TEST(ConstructorsTests, costr_copy) {
  Matrix m1(3, 3);
  m1.fill_matrix_eq();
  Matrix m2(m1);
  ASSERT_TRUE(m1.eq_matrix(m2));
}

TEST(ConstructorsTests, costr_move) {
  Matrix m1(3, 3);
  Matrix m_res(m1);
  Matrix m2(std::move(m1));
  ASSERT_TRUE(m_res.eq_matrix(m2));
}

TEST(MethodsTests_sum_matrix, sum_matrix_1) {
  Matrix m1(3, 3);
  Matrix m2(3, 3);
  m2.fill_matrix_eq();
  m1.sum_matrix(m2);
  ASSERT_EQ(m1.eq_matrix(m2), true);
}

TEST(MethodsTests_sum_matrix, sum_matrix_2) {
  Matrix m1(3, 3);
  Matrix m2(3, 3);
  m1.fill_matrix_eq();
  m2.fill_matrix_eq();
  m2.sum_matrix(m1);
  m1.mul_number(2);
  ASSERT_EQ(m1.eq_matrix(m2), true);
}

TEST(MethodsTests_sub_matrix, sub_matrix_1) {
  Matrix m1(3, 3);
  Matrix m2(3, 3);
  m2.sub_matrix(m1);
  ASSERT_EQ(m1.eq_matrix(m2), true);
}

TEST(MethodsTests_sub_matrix, sub_matrix_2) {
  Matrix m1(3, 3);
  Matrix m2(3, 3);
  m1.fill_matrix_eq();
  m2.fill_matrix_eq();
  m2.sub_matrix(m1);
  Matrix m_res(3, 3);
  ASSERT_EQ(m_res.eq_matrix(m2), true);
}

TEST(MethodsTests_sub_matrix, sub_matrix_3) {
  Matrix m1(3, 3);
  Matrix m2(3, 3);
  m1.fill_matrix_eq();
  m2.fill_matrix_eq();
  m1.mul_number(2);
  m1.sub_matrix(m2);
  ASSERT_EQ(m1.eq_matrix(m2), true);
}

TEST(MethodsTests_mul_number, mul_number_1) {
  Matrix m1(3, 3);
  Matrix m2(3, 3);
  m1.mul_number(2);
  ASSERT_EQ(m2.eq_matrix(m1), true);
}

TEST(MethodsTests_mul_number, mul_number_2) {
  Matrix m1(10, 10);
  Matrix m2(10, 10);
  m1.fill_matrix_eq();
  m2.fill_matrix_eq();
  m2.sum_matrix(m1);
  m1.mul_number(2);
  ASSERT_EQ(m1.eq_matrix(m2), true);
}

TEST(MethodsTests_mul_matrix, mul_matrix_1) {
  Matrix m1(3, 3);
  Matrix m2(3, 1);
  m1.fill_matrix_eq();
  m2.fill_matrix_eq();
  m1.mul_matrix(m2);
  Matrix m_res(3, 1);
  m_res(0, 0) = 14.0;
  m_res(1, 0) = 32.0;
  m_res(2, 0) = 50.0;
  ASSERT_EQ(m1.eq_matrix(m_res), true);
}

TEST(MethodsTests_mul_matrix, mul_matrix_2) {
  Matrix m1(3, 3);
  Matrix m2(3, 3);
  m1.fill_matrix_eq();
  m2.fill_matrix_eq();
  m1.mul_matrix(m2);
  Matrix m_res(3, 3);
  m_res(0, 0) = 30.0;
  m_res(0, 1) = 36.0;
  m_res(0, 2) = 42.0;
  m_res(1, 0) = 66.0;
  m_res(1, 1) = 81.0;
  m_res(1, 2) = 96.0;
  m_res(2, 0) = 102.0;
  m_res(2, 1) = 126.0;
  m_res(2, 2) = 150.0;
  ASSERT_EQ(m1.eq_matrix(m_res), true);
}

TEST(MethodsTests_mul_matrix, mul_matrix_3) {
  Matrix m1(3, 3);
  Matrix m2(3, 3);
  m1.fill_matrix_eq();
  m2.fill_matrix_eq();
  m1.mul_matrix(m2);
  Matrix m_res(3, 3);
  m_res(0, 0) = 30.0;
  m_res(0, 1) = 36.0;
  m_res(0, 2) = 42.0;
  m_res(1, 0) = 66.0;
  m_res(1, 1) = 81.0;
  m_res(1, 2) = 96.0;
  m_res(2, 0) = 102.0;
  m_res(2, 1) = 126.0;
  m_res(2, 2) = 159.0;
  ASSERT_EQ(m1.eq_matrix(m_res), false);
}

TEST(MethodsTests_transpose, transpose_1) {
  Matrix m1(3, 3);
  m1.fill_matrix_eq();
  Matrix m2 = m1.transpose();
  Matrix m_res(3, 3);
  m_res(0, 0) = 1.0;
  m_res(0, 1) = 4.0;
  m_res(0, 2) = 7.0;
  m_res(1, 0) = 2.0;
  m_res(1, 1) = 5.0;
  m_res(1, 2) = 8.0;
  m_res(2, 0) = 3.0;
  m_res(2, 1) = 6.0;
  m_res(2, 2) = 9.0;
  ASSERT_EQ(m2.eq_matrix(m_res), true);
}

TEST(MethodsTests_determinant, determinant_1) {
  Matrix m1(3, 3);
  m1.fill_matrix_eq();
  ASSERT_EQ(m1.determinant(), 0);
}

TEST(MethodsTests_determinant, determinant_2) {
  Matrix m1(1, 1);
  m1(0, 0) = 10;
  ASSERT_EQ(m1.determinant(), 10);
}

TEST(MethodsTests_determinant, determinant_3) {
  Matrix m1(3, 3);
  m1.fill_matrix_eq();
  m1(0, 0) = 2;
  ASSERT_EQ(m1.determinant(), -3);
}

TEST(MethodsTests_calc_complements, calc_complements_1) {
  Matrix m1(1, 1);
  m1.fill_matrix_eq();
  m1(0, 0) = 2;
  Matrix m2 = m1.calc_complements();
  ASSERT_EQ(m2(0, 0), 1);
}

TEST(MethodsTests_calc_complements, calc_complements_2) {
  Matrix m1(2, 2);
  m1.fill_matrix_eq();
  Matrix m2 = m1.calc_complements();
  Matrix m_res(2, 2);
  m_res(0, 0) = 4.0;
  m_res(0, 1) = -3.0;
  m_res(1, 0) = -2.0;
  m_res(1, 1) = 1.0;
  ASSERT_EQ(m2.eq_matrix(m_res), true);
}

TEST(MethodsTests_calc_complements, calc_complements_3) {
  Matrix m1(3, 3);
  Matrix m2(3, 3);
  m1(0, 0) = 1.0;
  m1(0, 1) = 2.0;
  m1(0, 2) = 3.0;
  m1(1, 0) = 0.0;
  m1(1, 1) = 4.0;
  m1(1, 2) = 2.0;
  m1(2, 0) = 5.0;
  m1(2, 1) = 2.0;
  m1(2, 2) = 1.0;

  m2(0, 0) = 0.0;
  m2(0, 1) = 10.0;
  m2(0, 2) = -20.0;
  m2(1, 0) = 4.0;
  m2(1, 1) = -14.0;
  m2(1, 2) = 8.0;
  m2(2, 0) = -8.0;
  m2(2, 1) = -2.0;
  m2(2, 2) = 4.0;
  Matrix m_res = m1.calc_complements();
  ASSERT_EQ(m_res.eq_matrix(m2), true);
}

TEST(MethodsTests_inverse_matrix, inverse_matrix_1) {
  Matrix m1(3, 3);
  Matrix m2(3, 3);
  m1.fill_matrix_eq();
  m1(0, 0) = 2;

  m2(0, 0) = 1.0;
  m2(0, 1) = -2.0;
  m2(0, 2) = 1.0;
  m2(1, 0) = -2.0;
  m2(1, 1) = 1.0;
  m2(1, 2) = 0.0;
  m2(2, 0) = 1;
  m2(2, 1) = 2.0 / 3.0;
  m2(2, 2) = -2.0 / 3.0;
  Matrix m_res = m1.inverse_matrix();
  ASSERT_EQ(m_res.eq_matrix(m2), true);
}

TEST(MethodsTests_inverse_matrix, inverse_matrix_2) {
  Matrix m1(3, 3);
  Matrix m2(3, 3);
  m1(0, 0) = 1.0;
  m1(0, 1) = 2.0;
  m1(0, 2) = 3.0;
  m1(1, 0) = 0.0;
  m1(1, 1) = 4.0;
  m1(1, 2) = 2.0;
  m1(2, 0) = 5.0;
  m1(2, 1) = 2.0;
  m1(2, 2) = 1.0;

  m2(0, 0) = 0.0;
  m2(0, 1) = -0.1;
  m2(0, 2) = 0.2;
  m2(1, 0) = -0.25;
  m2(1, 1) = 0.35;
  m2(1, 2) = 0.05;
  m2(2, 0) = 0.5;
  m2(2, 1) = -0.2;
  m2(2, 2) = -0.1;
  Matrix m_res = m1.inverse_matrix();
  ASSERT_EQ(m_res.eq_matrix(m2), true);
}

TEST(GetTests_get_rows, get_rows_1) {
  Matrix m1(3, 2);
  ASSERT_EQ(m1.get_rows(), 3);
}

TEST(GetTests_get_cols, get_cols_1) {
  Matrix m1(3, 2);
  ASSERT_EQ(m1.get_cols(), 2);
}

TEST(MethodsTests_set_rows, set_rows_1) {
  Matrix m1(3, 3);
  m1.fill_matrix_eq();
  m1.set_rows(2);
  Matrix m_res(2, 3);
  m_res(0, 0) = 1.0;
  m_res(0, 1) = 2.0;
  m_res(0, 2) = 3.0;

  m_res(1, 0) = 4.0;
  m_res(1, 1) = 5.0;
  m_res(1, 2) = 6.0;
  ASSERT_EQ(m_res.eq_matrix(m1), true);
}

TEST(MethodsTests_set_rows, set_rows_2) {
  Matrix m1(3, 3);
  m1.fill_matrix_eq();
  m1.set_rows(4);
  Matrix m_res(4, 3);
  m_res(0, 0) = 1.0;
  m_res(0, 1) = 2.0;
  m_res(0, 2) = 3.0;

  m_res(1, 0) = 4.0;
  m_res(1, 1) = 5.0;
  m_res(1, 2) = 6.0;

  m_res(2, 0) = 7.0;
  m_res(2, 1) = 8.0;
  m_res(2, 2) = 9.0;

  m_res(3, 0) = 0.0;
  m_res(3, 1) = 0.0;
  m_res(3, 2) = 0.0;
  ASSERT_EQ(m_res.eq_matrix(m1), true);
}

TEST(MethodsTests_set_cols, set_cols_1) {
  Matrix m1(3, 3);
  m1.fill_matrix_eq();
  m1.set_cols(2);
  Matrix m_res(3, 2);
  m_res(0, 0) = 1.0;
  m_res(0, 1) = 2.0;

  m_res(1, 0) = 4.0;
  m_res(1, 1) = 5.0;

  m_res(2, 0) = 7.0;
  m_res(2, 1) = 8.0;
  ASSERT_EQ(m_res.eq_matrix(m1), true);
}

TEST(MethodsTests_set_cols, set_cols_2) {
  Matrix m1(3, 3);
  m1.fill_matrix_eq();
  m1.set_cols(4);
  Matrix m_res(3, 4);
  m_res(0, 0) = 1.0;
  m_res(0, 1) = 2.0;
  m_res(0, 2) = 3.0;
  m_res(0, 3) = 0.0;

  m_res(1, 0) = 4.0;
  m_res(1, 1) = 5.0;
  m_res(1, 2) = 6.0;
  m_res(1, 3) = 0.0;

  m_res(2, 0) = 7.0;
  m_res(2, 1) = 8.0;
  m_res(2, 2) = 9.0;
  m_res(2, 3) = 0.0;
  ASSERT_EQ(m_res.eq_matrix(m1), true);
}

TEST(OperatorsTests_assignment, operator_assignment_1) {
  Matrix m1(3, 3);
  m1.fill_matrix_eq();
  Matrix m2;
  m2 = m1;
  ASSERT_TRUE(m1.eq_matrix(m2));
}

TEST(OperatorsTests_assignment, operator_assignment_2) {
  Matrix m1(3, 3);
  m1.fill_matrix_eq();
  Matrix m2;
  m1 = m2;
  ASSERT_TRUE(m1.eq_matrix(m2));
}

TEST(OperatorsTests_assignment, operator_assignment_3) {
  Matrix m1(3, 3);
  m1.fill_matrix_eq();
  Matrix m2(4, 4);
  m2.fill_matrix_eq();
  m1 = m2;
  ASSERT_TRUE(m1.eq_matrix(m2));
}

TEST(OperatorsTests_assignment, operator_assignment_4) {
  Matrix m1(4, 1);
  m1.fill_matrix_eq();
  Matrix m2(3, 2);
  m2.fill_matrix_eq();
  m1 = m2;
  ASSERT_TRUE(m1.eq_matrix(m2));
}

TEST(OperatorsTests_equality, operator_equality_1) {
  Matrix m1(4, 1);
  m1.fill_matrix_eq();
  ASSERT_TRUE(m1 == m1);
}

TEST(OperatorsTests_equality, operator_equality_2) {
  Matrix m1(4, 1);
  m1.fill_matrix_eq();
  Matrix m2(3, 2);
  ASSERT_FALSE(m1 == m2);
}

TEST(OperatorsTests_equality, operator_equality_3) {
  Matrix m1(4, 1);
  Matrix m2(4, 1);
  m1.fill_matrix_eq();
  m2.fill_matrix_eq();
  ASSERT_TRUE(m1 == m2);
}

TEST(OperatorsTests_sum, operator_sum_1) {
  Matrix m1(3, 3);
  Matrix m2(3, 3);
  m1.fill_matrix_eq();
  m2.fill_matrix_eq();
  Matrix m_res = m1 + m2;
  m1.mul_number(2);
  ASSERT_TRUE(m_res == m1);
}

TEST(OperatorsTests_sub, operator_sub_1) {
  Matrix m1(3, 3);
  Matrix m2(3, 3);
  m1.fill_matrix_eq();
  m2.fill_matrix_eq();
  m1 *= 2;
  Matrix m_res = m1 - m2;
  ASSERT_TRUE(m_res.eq_matrix(m2));
}

TEST(OperatorsTests_mul_matrix, operator_mul_matrix_1) {
  Matrix m1(3, 3);
  Matrix m2(3, 1);
  m1.fill_matrix_eq();
  m2.fill_matrix_eq();
  Matrix m3 = m1 * m2;
  Matrix m_res(3, 1);
  m_res(0, 0) = 14.0;
  m_res(1, 0) = 32.0;
  m_res(2, 0) = 50.0;
  ASSERT_TRUE(m_res.eq_matrix(m3));
}

TEST(OperatorsTests_assignment_plus, operator_assignment_plus_1) {
  Matrix m1(3, 3);
  Matrix m2(3, 3);
  m1.fill_matrix_eq();
  m2.fill_matrix_eq();
  m1 *= 2;
  m2 += m2;
  ASSERT_TRUE(m1.eq_matrix(m2));
}

TEST(OperatorsTests_assignment_minus, operator_assignment_minus_1) {
  Matrix m1(3, 3);
  Matrix m2(3, 3);
  m1.fill_matrix_eq();
  m2.fill_matrix_eq();
  m1 *= 2;
  m1 -= m2;
  ASSERT_TRUE(m1.eq_matrix(m2));
}

TEST(OperatorsTests_assignment_mul_matrix, operator_assignment_mul_matrix_1) {
  Matrix m1(3, 3);
  m1.fill_matrix_eq();
  m1 *= m1;

  Matrix m_res(3, 3);
  m_res(0, 0) = 30.0;
  m_res(0, 1) = 36.0;
  m_res(0, 2) = 42.0;
  m_res(1, 0) = 66.0;
  m_res(1, 1) = 81.0;
  m_res(1, 2) = 96.0;
  m_res(2, 0) = 102.0;
  m_res(2, 1) = 126.0;
  m_res(2, 2) = 150.0;
  ASSERT_TRUE(m1.eq_matrix(m_res));
}

TEST(MethodsTests_operator_square, operator_square_1) {
  Matrix m1(3, 3);
  m1.fill_matrix_eq();
  m1(0, 0) = 2;
  ASSERT_EQ(m1(0, 0), 2);
}

TEST(MethodsTests_operator_mul, operator_mul_1) {
  Matrix m1(10, 10);
  Matrix m2(10, 10);
  m1.fill_matrix_eq();
  m2.fill_matrix_eq();
  Matrix m3 = m1 + m2;
  Matrix m4 = m1 * 2;
  ASSERT_TRUE(m3.eq_matrix(m4));
}

TEST(MethodsTests_operator_mul, operator_mul_2) {
  Matrix m1(10, 10);
  Matrix m2(10, 10);
  m1.fill_matrix_eq();
  m2.fill_matrix_eq();
  Matrix m3 = m1 + m2;
  Matrix m4 = 2 * m1;
  ASSERT_TRUE(m3.eq_matrix(m4));
}

TEST(MethodsTests_operator_mul, operator_mul_3) {
  Matrix m1(10, 10);
  m1.fill_matrix_eq();
  Matrix m2 = 2 * m1;
  m1 *= 2;
  ASSERT_TRUE(m1.eq_matrix(m2));
}
/*
TEST(ConstructorsTests, constr_with_param_throw) {
  EXPECT_THROW(Matrix m(0, 0), std::exception);
}

TEST(MethodsTests_sum_matrix, sum_matrix_throw) {
  Matrix m1(3, 3);
  Matrix m2(2, 2);
  EXPECT_THROW(m1.sum_matrix(m2), std::exception);
}

TEST(MethodsTests_sub_matrix, sub_matrix_throw) {
  Matrix m1(3, 3);
  Matrix m2(2, 2);
  m1.fill_matrix_eq();
  m2.fill_matrix_eq();
  EXPECT_THROW(m1.sub_matrix(m2), std::exception);
}

TEST(MethodsTests_mul_matrix, mul_matrix_throw) {
  Matrix m1(3, 3);
  Matrix m2(2, 3);
  m1.fill_matrix_eq();
  m2.fill_matrix_eq();
  EXPECT_THROW(m1.mul_matrix(m2), std::exception);
}

TEST(OperatorsTests_sum, operator_sum_throw) {
  Matrix m1(3, 3);
  Matrix m2(2, 2);
  m1.fill_matrix_eq();
  m2.fill_matrix_eq();
  EXPECT_THROW(Matrix m_res = m1 + m2, std::exception);
}

TEST(MethodsTests_determinant, determinant_throw) {
  Matrix m1(2, 3);
  m1.fill_matrix_eq();
  EXPECT_THROW(m1.determinant(), std::exception);
}

TEST(MethodsTests_calc_complements, calc_complements_throw) {
  Matrix m1(2, 3);
  m1.fill_matrix_eq();
  EXPECT_THROW(m1.calc_complements(), std::exception);
}

TEST(MethodsTests_inverse_matrix, inverse_matrix_throw) {
  Matrix m1(3, 3);
  m1.fill_matrix_eq();
  EXPECT_THROW(Matrix m_res = m1.inverse_matrix(), std::exception);
}

TEST(MethodsTests_set_rows, set_rows_throw) {
  Matrix m1(3, 3);
  EXPECT_THROW(m1.set_rows(0), std::exception);
}

TEST(MethodsTests_set_cols, set_cols_throw) {
  Matrix m1(3, 3);
  EXPECT_THROW(m1.set_cols(0), std::exception);
}

TEST(OperatorsTests_sub, operator_sub_throw) {
  Matrix m1(3, 3);
  Matrix m2(2, 2);
  m1.fill_matrix_eq();
  m2.fill_matrix_eq();
  EXPECT_THROW(Matrix m_res = m1 - m2, std::exception);
}

TEST(OperatorsTests_mul_matrix, operator_mul_matrix_throw) {
  Matrix m1(3, 3);
  Matrix m2(2, 3);
  m1.fill_matrix_eq();
  m2.fill_matrix_eq();
  EXPECT_THROW(Matrix m_res = m1 * m2, std::exception);
}

TEST(MethodsTests_operator_square, operator_square_2) {
  Matrix m1(3, 3);
  m1.fill_matrix_eq();
  EXPECT_THROW(m1(4, 0) = 2, std::exception);
}
*/
int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
