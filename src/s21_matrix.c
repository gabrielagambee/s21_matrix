#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int status = OK;
  if (rows <= 0 || columns <= 0 || result == NULL) {
    status = INCORRECT_MATRIX;
  }
  if (status == OK) {
    result->rows = rows;
    result->columns = columns;
    result->matrix = (double **)malloc(rows * sizeof(double *));
    if (result->matrix == NULL) {
      status = INCORRECT_MATRIX;
    } else {
      for (int i = 0; i < rows && status == OK; i++) {
        result->matrix[i] = (double *)malloc(columns * sizeof(double));
        if (result->matrix[i] == NULL) {
          status = INCORRECT_MATRIX;
        }
      }
    }
  }
  return status;
}

void s21_init_matrix(matrix_t *result) {  // Инициализация элементов матрицы
  double k = 0.0;
  for (int i = 0; i < result->rows; i++) {
    for (int j = 0; j < result->columns; j++) {
      result->matrix[i][j] = ++k;
    }
  }
}

// void s21_print_matrix(matrix_t *result) {
//   for (int i = 0; i < result->rows; i++) {
//     for (int j = 0; j < result->columns; j++) {
//       printf("%3.0lf ", result->matrix[i][j]);
//     }
//     printf("\n");
//   }
// }

void s21_remove_matrix(matrix_t *A) {
  if (A && A->matrix) {
    for (int x = 0; x < A->rows; x += 1) {
      free(A->matrix[x]);
    }
    free(A->matrix);
    A->matrix = NULL;
    A->columns = 0;
    A->rows = 0;
  }
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int rows_result = 0;
  int columns_result = 0;
  rows_result = A->columns;
  columns_result = A->rows;
  int status = s21_create_matrix(rows_result, columns_result, result);
  if (status == OK) {
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        result->matrix[i][j] = A->matrix[j][i];
      }
    }
  }
  return status;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int status = OK;
  if (s21_is_correct_matrix(A) == INCORRECT_MATRIX ||
      s21_is_correct_matrix(B) == INCORRECT_MATRIX || result == NULL) {
    status = INCORRECT_MATRIX;
  } else if (A->columns != B->columns || A->rows != B->rows) {
    status = CALCULATION_ERROR;
  } else {
    status = s21_create_matrix(A->rows, A->columns, result);
    if (status == OK) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
        }
      }
    }
  }
  return status;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int status = OK;
  if (s21_is_correct_matrix(A) == INCORRECT_MATRIX ||
      s21_is_correct_matrix(B) == INCORRECT_MATRIX || result == NULL) {
    status = INCORRECT_MATRIX;
  } else if (A->columns != B->columns || A->rows != B->rows) {
    status = CALCULATION_ERROR;
  } else {
    status = s21_create_matrix(
        A->rows, A->columns, result);  // <-- вот эта строка добавляет создание
    if (status == OK) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
        }
      }
    }
  }
  return status;
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int status = SUCCESS;
  if (s21_is_correct_matrix(A) == INCORRECT_MATRIX ||
      s21_is_correct_matrix(B) == INCORRECT_MATRIX) {
    status = INCORRECT_MATRIX;
  }
  if (A->columns != B->columns || A->rows != B->rows) {
    status = FAILURE;
  }
  if (status == SUCCESS) {
    for (int x = 0; x < A->rows; x += 1) {
      for (int y = 0; y < A->columns; y += 1) {
        if (fabs(A->matrix[x][y] - B->matrix[x][y]) > 1e-07) {
          status = FAILURE;
        }
      }
    }
  }
  return status;
}

int s21_is_correct_matrix(matrix_t *A) {
  int status = OK;
  if (A == NULL || A->matrix == NULL || A->rows <= 0 || A->columns <= 0) {
    status = INCORRECT_MATRIX;
  }
  return status;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int status = s21_is_correct_matrix(A);
  if (status == OK) {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  }
  return status;
}

int s21_is_good_for_mult(matrix_t *A, matrix_t *B) {
  int status = FAILURE;
  if (A->columns == B->rows) {
    status = SUCCESS;
  }
  return status;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int status = OK;
  if (s21_is_good_for_mult(A, B) == FAILURE) {
    status = CALCULATION_ERROR;
  } else {
    status = s21_create_matrix(A->rows, B->columns, result);
    if (status == OK) {
      for (int i = 0; i < result->rows; i++) {
        for (int j = 0; j < result->columns; j++) {
          result->matrix[i][j] = 0.0;
          int common_dim = A->columns;
          for (int k = 0; k < common_dim; k++) {
            result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
          }
        }
      }
    }
  }
  return status;
}

void s21_create_minor_matrix(matrix_t *src, int row_skip, int col_skip,
                             matrix_t *ptr_minor_matrix) {
  s21_create_matrix(src->rows - 1, src->columns - 1, ptr_minor_matrix);

  // заполняем минорную матрицу
  for (int src_i = 0, minor_i = 0; src_i < src->rows; src_i++) {
    // перебор строк за исключением указанной строки
    if (src_i != row_skip) {
      for (int src_j = 0, minor_j = 0; src_j < src->columns; src_j++) {
        // перебор столбцов за исключением указанного столбца
        if (src_j != col_skip) {
          ptr_minor_matrix->matrix[minor_i][minor_j] =
              src->matrix[src_i][src_j];
          minor_j++;
        }
      }
      minor_i++;
    }
  }
}

int s21_determinant(matrix_t *A, double *result) {
  int status = s21_is_correct_matrix(A);
  if (A->rows != A->columns) {
    status = CALCULATION_ERROR;
  }
  if (status == OK) {
    if (A->rows == 1) {
      *result = A->matrix[0][0];
    } else if (A->rows == 2) {
      *result =
          A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
    } else {
      *result = 0.0;
      for (int sign = 1, x = 0; x < A->columns; x += 1, sign *= -1) {
        matrix_t minor = {0};
        s21_create_minor_matrix(A, 0, x, &minor);
        double minor_det = 0.0;
        s21_determinant(&minor, &minor_det);  // рекурсия
        *result += sign * A->matrix[0][x] * minor_det;
        s21_remove_matrix(&minor);
      }
    }
  }
  return status;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int status = s21_is_correct_matrix(A);
  if (A->rows != A->columns) {
    status = CALCULATION_ERROR;
  }
  if (status == OK) {
    status = s21_create_matrix(A->rows, A->columns, result);
    if (A->rows == 1) {
      result->matrix[0][0] = 1;
    } else {
      for (int sign = 0, i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          matrix_t minor = {0};
          double det_min = 0.0;
          s21_create_minor_matrix(A, i, j, &minor);
          sign = ((i + j) % 2 == 0) ? 1 : (-1);
          s21_determinant(&minor, &det_min);
          result->matrix[i][j] = sign * det_min;
          s21_remove_matrix(&minor);
        }
      }
    }
  }
  return status;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  // запустить функцию детерминанта и присвоить статус
  double det = 0.0;
  int status = s21_determinant(A, &det);
  // если статус ок, то
  if (status == OK) {
    if (det) {
      // если детерминант не нулевой, то находим матрицу алгебраических
      // дополнений
      matrix_t alg_dop = {0};
      matrix_t alg_dop_trans = {0};
      s21_calc_complements(A, &alg_dop);
      // транспонируем матрицу алгебраических дополнений
      s21_transpose(&alg_dop, &alg_dop_trans);
      // вводим пееременную коэффициент obr_det = 1 / det
      int obr_dop = 1 / det;	
      // умножаем матрицу алг дополнений на коэффициент функцией умножения
      s21_mult_number(&alg_dop_trans, obr_dop, result);
    } else {
      status = CALCULATION_ERROR;
    }
  }
  return status;
}
