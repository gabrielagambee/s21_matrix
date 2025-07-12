#include "s21_matrix.h"

#include <check.h>

START_TEST(test_create_matrix_1) {
  matrix_t A;
  int status = s21_create_matrix(1, 1, &A);
  ck_assert_int_eq(status, OK);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_create_matrix_2) {
  matrix_t A;
  int status = s21_create_matrix(100, 100, &A);
  ck_assert_int_eq(status, OK);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_create_matrix_3) {
  matrix_t A;
  int status = s21_create_matrix(0, 0, &A);
  ck_assert_int_eq(status, INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_remove_matrix) {
  matrix_t A;
  int status = s21_create_matrix(1, 1, &A);
  s21_remove_matrix(&A);
  ck_assert_ptr_null(A.matrix);
  ck_assert_int_eq(A.rows, 0);
  ck_assert_int_eq(A.columns, 0);
  ck_assert_int_eq(status, OK);
}
END_TEST

START_TEST(test_eq_matrix_1) {
  matrix_t A;
  matrix_t B;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(2, 3, &B);
  s21_init_matrix(&A);
  s21_init_matrix(&B);
  int status = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(status, SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_eq_matrix_2) {
  matrix_t A;
  matrix_t B;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(2, 3, &B);
  s21_init_matrix(&A);
  s21_init_matrix(&B);
  A.matrix[0][0] = 25;
  int status = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(status, FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_eq_matrix_3) {
  matrix_t A;
  matrix_t B;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(2, 3, &B);
  s21_init_matrix(&A);
  s21_init_matrix(&B);
  A.matrix[0][0] = 1.123456789;
  B.matrix[0][0] = 1.123456689;
  int status = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(status, FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_eq_matrix_4) {
  matrix_t A;
  matrix_t B;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(2, 3, &B);
  s21_init_matrix(&A);
  s21_init_matrix(&B);
  int status = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(status, FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_eq_matrix_5) {
  matrix_t A;
  matrix_t B;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(2, 3, &B);
  s21_init_matrix(&A);
  s21_init_matrix(&B);
  A.matrix[0][0] = 1.123456789;
  B.matrix[0][0] = 1.123456777;
  int status = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(status, SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_eq_matrix_6) {
  matrix_t A;
  matrix_t B;
  s21_create_matrix(0, 0, &A);
  s21_create_matrix(2, 3, &B);
  int status = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(status, FAILURE);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_sum_matrix_1) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  matrix_t D;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  s21_create_matrix(2, 2, &C);
  s21_create_matrix(2, 2, &D);
  s21_init_matrix(&A);
  s21_init_matrix(&B);
  s21_sum_matrix(&A, &B, &C);
  D.matrix[0][0] = 2;
  D.matrix[0][1] = 4;
  D.matrix[1][0] = 6;
  D.matrix[1][1] = 8;
  int status = s21_eq_matrix(&C, &D);
  ck_assert_int_eq(status, SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&D);
}
END_TEST

START_TEST(test_sum_matrix_2) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(4, 4, &B);
  s21_create_matrix(4, 4, &C);
  s21_init_matrix(&A);
  s21_init_matrix(&B);

  int status = s21_sum_matrix(&A, &B, &C);
  ck_assert_int_eq(status, CALCULATION_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(test_sum_matrix_3) {
  matrix_t *A = NULL, *B = NULL, result;

  int status = s21_sum_matrix(A, B, &result);

  ck_assert_int_eq(status, INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_sub_matrix_1) {
  matrix_t A, B, C = {0}, D;

  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  s21_create_matrix(2, 2, &D);

  s21_init_matrix(&A);
  s21_init_matrix(&B);

  s21_sub_matrix(&A, &B, &C);

  D.matrix[0][0] = 0;
  D.matrix[0][1] = 0;
  D.matrix[1][0] = 0;
  D.matrix[1][1] = 0;

  int status = s21_eq_matrix(&C, &D);
  ck_assert_int_eq(status, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&D);
}
END_TEST

// Тест: Ошибка при невозможности создать результирующую матрицу
START_TEST(test_sum_matrix_result_create_fail_4) {
  matrix_t A, B;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  // Передаем некорректный указатель для result
  int status = s21_sum_matrix(&A, &B, NULL);
  ck_assert_int_eq(status, INCORRECT_MATRIX);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_sub_matrix_2) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(4, 4, &B);
  s21_create_matrix(4, 4, &C);
  s21_init_matrix(&A);
  s21_init_matrix(&B);

  int status = s21_sub_matrix(&A, &B, &C);
  ck_assert_int_eq(status, CALCULATION_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(test_sub_matrix_incorrect_data) {
  matrix_t *A = NULL, *B = NULL, result;
  s21_create_matrix(2, 2, &result);

  int status = s21_sub_matrix(A, B, &result);

  ck_assert_int_eq(status, INCORRECT_MATRIX);

  s21_remove_matrix(&result);
}

START_TEST(test_transpose_matrix) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(3, 2, &C);
  s21_init_matrix(&A);
  s21_transpose(&A, &B);
  C.matrix[0][0] = 1;
  C.matrix[1][0] = 2;
  C.matrix[2][0] = 3;
  C.matrix[0][1] = 4;
  C.matrix[1][1] = 5;
  C.matrix[2][1] = 6;
  int status = s21_eq_matrix(&B, &C);
  ck_assert_int_eq(status, SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(test_mult_number_1) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(2, 3, &C);
  s21_init_matrix(&A);
  s21_mult_number(&A, 2, &B);
  C.matrix[0][0] = 2;
  C.matrix[0][1] = 4;
  C.matrix[0][2] = 6;
  C.matrix[1][0] = 8;
  C.matrix[1][1] = 10;
  C.matrix[1][2] = 12;
  int status = s21_eq_matrix(&B, &C);
  ck_assert_int_eq(status, SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(test_mult_number_2) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(2, 3, &C);
  s21_init_matrix(&A);
  s21_mult_number(&A, -2, &B);
  C.matrix[0][0] = -2;
  C.matrix[0][1] = -4;
  C.matrix[0][2] = -6;
  C.matrix[1][0] = -8;
  C.matrix[1][1] = -10;
  C.matrix[1][2] = -12;
  int status = s21_eq_matrix(&B, &C);
  ck_assert_int_eq(status, SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(test_mult_number_3) {
  matrix_t A = {0};
  matrix_t B = {0};
  s21_create_matrix(2, 0, &A);
  int status = s21_mult_number(&A, 2, &B);
  ck_assert_int_eq(status, INCORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_mult_matrix_1) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(3, 2, &B);
  int status = s21_mult_matrix(&A, &B, &C);
  ck_assert_int_eq(status, OK);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(test_mult_matrix_2) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};
  s21_create_matrix(5, 3, &A);
  s21_create_matrix(4, 2, &B);
  int status = s21_mult_matrix(&A, &B, &C);
  ck_assert_int_eq(status, CALCULATION_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(test_determinant_1) {
  matrix_t A = {0};
  double det = 0.0;
  s21_create_matrix(3, 2, &A);
  int status = s21_determinant(&A, &det);
  ck_assert_int_eq(status, CALCULATION_ERROR);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_2) {
  matrix_t A = {0};
  double det = 0.0;
  s21_create_matrix(2, 2, &A);
  s21_init_matrix(&A);
  int status = s21_determinant(&A, &det);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(det, -2);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_3) {
  matrix_t A = {0};
  double det = 0.0;
  s21_create_matrix(3, 3, &A);
  s21_init_matrix(&A);
  int status = s21_determinant(&A, &det);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(det, 0);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_4) {
  matrix_t A = {0};
  double det = 0.0;
  s21_create_matrix(1, 1, &A);
  s21_init_matrix(&A);
  int status = s21_determinant(&A, &det);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(det, A.matrix[0][0]);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_5) {
  matrix_t A = {0};
  double det = 0.0;
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 25.2344;
  int status = s21_determinant(&A, &det);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(det, A.matrix[0][0]);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_inverse_1) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};

  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &C);

  A.matrix[0][0] = 2;
  A.matrix[0][1] = 5;
  A.matrix[0][2] = 7;
  A.matrix[1][0] = 6;
  A.matrix[1][1] = 3;
  A.matrix[1][2] = 4;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = -2;
  A.matrix[2][2] = -3;

  C.matrix[0][0] = 1;
  C.matrix[0][1] = -1;
  C.matrix[0][2] = 1;
  C.matrix[1][0] = -38;
  C.matrix[1][1] = 41;
  C.matrix[1][2] = -34;
  C.matrix[2][0] = 27;
  C.matrix[2][1] = -29;
  C.matrix[2][2] = 24;

  int status = s21_inverse_matrix(&A, &B);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(s21_eq_matrix(&B, &C), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(test_inverse_2) {
  matrix_t A = {0};
  matrix_t B = {0};
  s21_create_matrix(3, 2, &A);
  int status = s21_inverse_matrix(&A, &B);
  ck_assert_int_eq(status, CALCULATION_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_inverse_3) {
  matrix_t A = {0};
  matrix_t B = {0};
  s21_create_matrix(3, 3, &A);
  s21_init_matrix(&A);
  int status = s21_inverse_matrix(&A, &B);
  ck_assert_int_eq(status, CALCULATION_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_complement_1) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};

  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &C);

  A.matrix[0][0] = 2;
  A.matrix[0][1] = 5;
  A.matrix[0][2] = 7;
  A.matrix[1][0] = 6;
  A.matrix[1][1] = 3;
  A.matrix[1][2] = 4;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = -2;
  A.matrix[2][2] = -3;

  C.matrix[0][0] = -1;
  C.matrix[0][1] = 38;
  C.matrix[0][2] = -27;
  C.matrix[1][0] = 1;
  C.matrix[1][1] = -41;
  C.matrix[1][2] = 29;
  C.matrix[2][0] = -1;
  C.matrix[2][1] = 34;
  C.matrix[2][2] = -24;

  int status = s21_calc_complements(&A, &B);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(s21_eq_matrix(&B, &C), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(test_complement_2) {
  matrix_t A = {0};
  matrix_t B = {0};
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 25;
  int status = s21_calc_complements(&A, &B);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(B.matrix[0][0], 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_complement_3) {
  matrix_t A = {0};
  matrix_t B = {0};
  s21_create_matrix(1, 2, &A);
  int status = s21_calc_complements(&A, &B);
  ck_assert_int_eq(status, CALCULATION_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

Suite *create_suite(void) {
  Suite *suite_s21_matrix;
  TCase *tc_core_s21_matrix;
  suite_s21_matrix = suite_create("Suite_of_test_s21_matrix");
  tc_core_s21_matrix = tcase_create("Core_of_test_s21_matrix");

  tcase_add_test(tc_core_s21_matrix, test_create_matrix_1);
  tcase_add_test(tc_core_s21_matrix, test_create_matrix_2);
  tcase_add_test(tc_core_s21_matrix, test_create_matrix_3);
  tcase_add_test(tc_core_s21_matrix, test_remove_matrix);
  tcase_add_test(tc_core_s21_matrix, test_eq_matrix_1);
  tcase_add_test(tc_core_s21_matrix, test_eq_matrix_2);
  tcase_add_test(tc_core_s21_matrix, test_eq_matrix_3);
  tcase_add_test(tc_core_s21_matrix, test_eq_matrix_4);
  tcase_add_test(tc_core_s21_matrix, test_eq_matrix_5);
  tcase_add_test(tc_core_s21_matrix, test_eq_matrix_6);
  tcase_add_test(tc_core_s21_matrix, test_sum_matrix_1);
  tcase_add_test(tc_core_s21_matrix, test_sum_matrix_2);
  tcase_add_test(tc_core_s21_matrix, test_sum_matrix_3);
  tcase_add_test(tc_core_s21_matrix, test_sum_matrix_result_create_fail_4);
  tcase_add_test(tc_core_s21_matrix, test_sub_matrix_1);
  tcase_add_test(tc_core_s21_matrix, test_sub_matrix_2);
  tcase_add_test(tc_core_s21_matrix, test_sub_matrix_incorrect_data);
  tcase_add_test(tc_core_s21_matrix, test_transpose_matrix);
  tcase_add_test(tc_core_s21_matrix, test_mult_number_1);
  tcase_add_test(tc_core_s21_matrix, test_mult_number_2);
  tcase_add_test(tc_core_s21_matrix, test_mult_number_3);
  tcase_add_test(tc_core_s21_matrix, test_mult_matrix_1);
  tcase_add_test(tc_core_s21_matrix, test_mult_matrix_2);
  tcase_add_test(tc_core_s21_matrix, test_determinant_1);
  tcase_add_test(tc_core_s21_matrix, test_determinant_2);
  tcase_add_test(tc_core_s21_matrix, test_determinant_3);
  tcase_add_test(tc_core_s21_matrix, test_determinant_4);
  tcase_add_test(tc_core_s21_matrix, test_determinant_5);
  tcase_add_test(tc_core_s21_matrix, test_inverse_1);
  tcase_add_test(tc_core_s21_matrix, test_inverse_2);
  tcase_add_test(tc_core_s21_matrix, test_inverse_3);
  tcase_add_test(tc_core_s21_matrix, test_complement_1);
  tcase_add_test(tc_core_s21_matrix, test_complement_2);
  tcase_add_test(tc_core_s21_matrix, test_complement_3);

  /*сюда добавляем тест кейсы
   *
   * tcase_add_test(tc_core_s21_matrix, test_name);
   *
   */
  suite_add_tcase(suite_s21_matrix, tc_core_s21_matrix);
  return suite_s21_matrix;
}

int main(void) {
  int failed_counter;
  Suite *suite = create_suite();
  SRunner *suite_runner = srunner_create(suite);

  srunner_run_all(suite_runner, CK_NORMAL);
  failed_counter = srunner_ntests_failed(suite_runner);
  srunner_free(suite_runner);

  return (failed_counter == 0 ? 0 : 1);
}