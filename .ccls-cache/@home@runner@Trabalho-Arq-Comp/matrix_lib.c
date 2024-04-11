#include "matrix_lib.h"
#include "timer.h"
#include <immintrin.h>
#include <stdio.h>
#include <stdlib.h>

int scalar_matrix_mult(float scalar_value, struct matrix *matrix) {
  if (matrix == NULL || matrix->rows == NULL) {
    return 0; // Error: matriz ou seus valores não estão alocados
  }

  unsigned long int total_elements = matrix->height * matrix->width;
  unsigned long int i;

  // Vetorizador AVX para otimização de desempenho
  __m256 scalar = _mm256_set1_ps(scalar_value);

  // Processamento da matriz em blocos de 8 elementos (tamanho de m256)
  for (i = 0; i < total_elements; i += 8) {
    __m256 matrix_values = _mm256_loadu_ps(&(matrix->rows[i]));
    matrix_values = _mm256_mul_ps(matrix_values, scalar);
    _mm256_storeu_ps(&(matrix->rows[i]), matrix_values);
  }

  return 1; // Sucesso
}

int matrix_matrix_mult(struct matrix *a, struct matrix *b, struct matrix *c) {
  return 0;
}