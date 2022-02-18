#pragma once

#ifndef __FAST_ARRAY_H__
#define __FAST_ARRAY_H__

#include "common.h"

typedef float dtype; // for general programming
typedef int pIdx; // pointer index


/******************************************************************************
**                          FUNCTION DEFINITIONS
**                          COMMON
*******************************************************************************/
void zeros(dtype* arr, const size_t size);
void zeros_pidx(dtype* arr, const size_t size, pIdx idx);
void ones(dtype* arr, const size_t size);
void ones_pidx(dtype* arr, const size_t size, pIdx idx);
void rands(dtype* arr, const size_t size, float average, float stdev);
void rands_pidx(dtype* arr, const size_t size, float average, float stdev, pIdx idx);
void sin_(dtype* arr, const size_t size, float f0, float fs, float phase);
void sin_pidx(dtype* arr, const size_t size, float f0, float fs, float phase, pIdx idx);
void cos_(dtype* arr, const size_t size, float f0, float fs, float phase);
void cos_pidx(dtype* arr, const size_t size, float f0, float fs, float phase, pIdx idx);

/******************************************************************************
**                          FUNCTION DEFINITIONS
**                          PUSH
*******************************************************************************/
#define push_using_for(vector, length, target) for (int j = length - 1; j > 0; j--) vector[j] = vector[j - 1]; vector[0] = target;
#define push_using_memmove(vector, length, target) memmove(vector + 1, vector, sizeof(dtype) * (length-1)); vector[0] = target;
#define push_using_pidx(ptr, size, ptr_idx, target) \
if(--ptr_idx < 0) ptr_idx = size - 1; ptr[ptr_idx] = target; ptr[ptr_idx + size] = target
	//fast insert

#define push_using_pidx_no_shift(ptr, size, ptr_idx, target) \
if(ptr_idx < 0) ptr_idx = size - 1; ptr[ptr_idx] = target; ptr[ptr_idx + size] = target
	// not use pointer index decrese

/* wrapper function : push */
#define fa_push_ push_using_for
#define fa_push push_using_memmove
#define fa_fast_push_shift push_using_pidx
#define fa_fast_push push_using_pidx_no_shift

/******************************************************************************
**                          FUNCTION DEFINITIONS
**                          CDOT
*******************************************************************************/
dtype dot_product(dtype * a, dtype * b, pIdx size);
dtype dot_product_pidx(dtype* arr1, dtype* arr2, const size_t size, pIdx ptr_idx);
dtype dot_product_pidx_debug(dtype* arr1, dtype* arr2, const size_t size, pIdx ptr_idx);
dtype dot_product_dpidx(dtype* arr1, dtype* arr2, const size_t size, pIdx ptr_idx1, pIdx ptr_idx2);
dtype dot_product_dpidx_debug(dtype* arr1, dtype* arr2, const size_t size, pIdx ptr_idx1, pIdx ptr_idx2);
dtype dot_product4(dtype* arr1, dtype* arr2, const size_t size, pIdx ptr_idx1, pIdx ptr_idx2);

/* wrapper function : cdot */
#define fa_cdot dot_product
#define fa_fast_cdot dot_product_dpidx

/******************************************************************************
**                          FUNCTION DEFINITIONS
**                          ADAPTIVE ALGORITHM
*******************************************************************************/
dtype least_mean_square(dtype * x, dtype * h, dtype * desired, dtype * y, dtype adapt_rate, dtype error,
	int n_coeffecients, int n_output_samples);
dtype fast_least_mean_square(dtype * x, dtype * h, dtype * desired, dtype * y, dtype adapt_rate, dtype error,
	const int n_coeffecients, const int n_output_samples, pIdx x_idx, pIdx h_idx, pIdx d_idx, pIdx y_idx);

/* wrapper function : lms */
#define fa_lms least_mean_square
#define fa_fast_lms fast_least_mean_sqaure

/******************************************************************************
**                          FUNCTION DEFINITIONS
**                          OPERATION
*******************************************************************************/
void autocor(dtype * __restrict r, const dtype * __restrict x, int autocor_len, int lag);
void fast_autocor(dtype * __restrict r, const dtype * __restrict x, int autocor_len, int lag, pIdx r_idx, pIdx x_idx);

/* wrapper function : cor */
#define fa_autocor autocor
#define fa_fast_autocor fast_autocor

/******************************************************************************
**                          FUNCTION DEFINITIONS
**                          PRINT ARRAY
*******************************************************************************/
void print_arrf_vect(dtype * ptr, const size_t size, pIdx ptr_idx);
void print_arrs_vect(short* ptr, const size_t size, pIdx ptr_idx);
void print_arrf(dtype * arr, const size_t size);
void print_arrs(short* arr, const size_t size);

#endif