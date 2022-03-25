/**
* @ author : junyeong heo
*
\brief
** These functions are the data structure API
** of the high-speed insertion array.
** The time complexity of the stack insertion algorithm of
** the existing array is O(n), but this array is O(1).
*/

#include "fast_array.h"

// math api
float gaussian_random(float average, float stdev)
{
	float v1, v2, s, temp;

	do {
		v1 = 2 * ((float)rand() / RAND_MAX) - 1;      // range = [-1.0, 1.0]
		v2 = 2 * ((float)rand() / RAND_MAX) - 1;      // range = [-1.0, 1.0]
		s = v1 * v1 + v2 * v2;
	} while (s >= 1 || s == 0);

	s = sqrt((-2 * log(s)) / s);

	temp = v1 * s;
	temp = (stdev * temp) + average;

	return temp;
}

// Functions Implementation
/******************************************************************************
**                          FUNCTION IMPLEMENTAION
**                          UTIL FUNCTIONS of ARRAY
*******************************************************************************/
void zeros(dtype* arr, const size_t size)
{
	int i; for (i = 0; i < size; i++) arr[i] = 0;
}
void zeros_pidx(dtype* arr, const size_t size, pIdx idx)
{
	int i; for (i = idx; i < idx + size; i++) arr[i] = 0;
}
void ones(dtype* arr, const size_t size)
{
	int i; for (i = 0; i < size; i++) arr[i] = 1;
}
void ones_pidx(dtype* arr, const size_t size, pIdx idx)
{
	int i; for (i = idx; i < idx + size; i++) arr[i] = 1;
}
void rands(dtype* arr, const size_t size, float average, float stdev)
{
	int i; for (i = 0; i < size; i++) arr[i] = gaussian_random(average, stdev);
}
void rands_pidx(dtype* arr, const size_t size, float average, float stdev, pIdx idx)
{
	int i; for (i = idx; i < idx + size; i++) arr[i] = gaussian_random(average, stdev);
}
void sin_(dtype* arr, const size_t size, float f0, float fs, float phase)
{
	int i; for (i = 0; i < size; i++) arr[i] = (dtype)sin(PI2 * (f0 / fs) * i + DEG2RAD(phase));
}
void sin_pidx(dtype* arr, const size_t size, float f0, float fs, float phase, pIdx idx)
{
	int i; for (i = idx; i < idx + size; i++) arr[i] = (dtype)sin(PI2 * (f0 / fs) * i + DEG2RAD(phase));
}
void cos_(dtype* arr, const size_t size, float f0, float fs, float phase)
{
	int i; for (i = 0; i < size; i++) arr[i] = (dtype)cos(PI2 * (f0 / fs) * i + DEG2RAD(phase));
}
void cos_pidx(dtype* arr, const size_t size, float f0, float fs, float phase, pIdx idx)
{
	int i; for (i = idx; i < idx + size; i++) arr[i] = (dtype)cos(PI2 * (f0 / fs) * i + DEG2RAD(phase));
}
void scaling(dtype* arr, const size_t size, dtype scailing_factor)
{
	int i; for (i = 0; i < size; i++) arr[i] *= scailing_factor;
}
void scaling_pidx(dtype* arr, const size_t size, dtype scailing_factor, pIdx idx)
{
	int i; for (i = idx; i < idx + size; i++) arr[i] *= scailing_factor;
}

/******************************************************************************
**                          FUNCTION IMPLEMENTAION
**                          FAST SIGNAL GENERATION
*******************************************************************************/
void fast_sin(dtype* arr, const size_t size, float f0, float fs)
{
	/*
	% init
		a1 = fnd_amp * cos(2 * pi * fnd_freq * (1 / sampling_rate));
		b0 = fnd_amp * sin(2 * pi * fnd_freq * (1 / sampling_rate));

		qn1 = 1; qn2 = 0;

		for n = 1 : length(t),
			cos_signal(n) = qn1 - a1 * qn2; % data push
			sin_signal(n) = b0 * qn2;

		qn0 = 2 * a1 * qn1 - qn2; % q(n) = a1 * qn(n - 1) - q(n - 2)
		qn2 = qn1;
		qn1 = qn0;
	end
	*/
	dtype a1 = cos(PI2 * f0 / fs), b0 = sin(PI2 * f0 / fs);
	dtype qn0, qn1 = 1, qn2 = 0;
	int i;

	for (i = 0; i < size; i++)
	{
		qn0 = 2 * a1 * qn1 - qn2;
		qn2 = qn1;
		qn1 = qn0;

		arr[i] = b0 * qn2;
	}

	return;
}
void fast_cos(dtype* arr, const size_t size, float f0, float fs)
{
	/*
	% init
		a1 = fnd_amp * cos(2 * pi * fnd_freq * (1 / sampling_rate));
		b0 = fnd_amp * sin(2 * pi * fnd_freq * (1 / sampling_rate));

		qn1 = 1; qn2 = 0;

		for n = 1 : length(t),
			cos_signal(n) = qn1 - a1 * qn2; % data push
			sin_signal(n) = b0 * qn2;

		qn0 = 2 * a1 * qn1 - qn2; % q(n) = a1 * qn(n - 1) - q(n - 2)
		qn2 = qn1;
		qn1 = qn0;
	end
	*/

	dtype a1 = cos(PI2 * f0 / fs), b0 = sin(PI2 * f0 / fs);
	dtype qn0, qn1 = 1, qn2 = 0;
	int i;

	for (i = 0; i < size; i++)
	{
		qn0 = 2 * a1 * qn1 - qn2;
		qn2 = qn1;
		qn1 = qn0;

		arr[i] = qn1 - a1 * qn2;
	}

	return;
}
void fast_sin_pidx(dtype* arr, const size_t size, float f0, float fs, pIdx idx)
{
	/*
	% init
		a1 = fnd_amp * cos(2 * pi * fnd_freq * (1 / sampling_rate));
		b0 = fnd_amp * sin(2 * pi * fnd_freq * (1 / sampling_rate));

		qn1 = 1; qn2 = 0;

		for n = 1 : length(t),
			cos_signal(n) = qn1 - a1 * qn2; % data push
			sin_signal(n) = b0 * qn2;

		qn0 = 2 * a1 * qn1 - qn2; % q(n) = a1 * qn(n - 1) - q(n - 2)
		qn2 = qn1;
		qn1 = qn0;
	end
	*/
	dtype a1 = cos(PI2 * f0 / fs), b0 = sin(PI2 * f0 / fs);
	dtype qn0, qn1 = 1, qn2 = 0;
	int i;

	for (i = idx; i < idx + size; i++)
	{
		qn0 = 2 * a1 * qn1 - qn2;
		qn2 = qn1;
		qn1 = qn0;

		arr[i] = b0 * qn2;
	}

	return;
}
void fast_cos_pidx(dtype* arr, const size_t size, float f0, float fs, pIdx idx)
{
	/*
	% init
		a1 = fnd_amp * cos(2 * pi * fnd_freq * (1 / sampling_rate));
		b0 = fnd_amp * sin(2 * pi * fnd_freq * (1 / sampling_rate));

		qn1 = 1; qn2 = 0;

		for n = 1 : length(t),
			cos_signal(n) = qn1 - a1 * qn2; % data push
			sin_signal(n) = b0 * qn2;

		qn0 = 2 * a1 * qn1 - qn2; % q(n) = a1 * qn(n - 1) - q(n - 2)
		qn2 = qn1;
		qn1 = qn0;
	end
	*/

	dtype a1 = cos(PI2 * f0 / fs), b0 = sin(PI2 * f0 / fs);
	dtype qn0, qn1 = 1, qn2 = 0;
	int i;
	for (i = idx; i < size + idx; i++)
	{
		qn0 = 2 * a1 * qn1 - qn2;
		qn2 = qn1;
		qn1 = qn0;

		arr[i] = qn1 - a1 * qn2;
	}
	return;
}
/******************************************************************************
**                          FUNCTION IMPLEMENTAION
**                          DOT PRODUCTS
*******************************************************************************/
dtype dot_product(dtype* a, dtype* b, pIdx size)
{
	dtype sum = 0; int i;
	for (i = 0; i < size; i++)  sum += a[i] * b[i];
	return sum;
}
dtype dot_product_pidx(dtype* arr1, dtype* arr2, const size_t size, pIdx ptr_idx)
{
	dtype sum = 0; int i;
	for (i = ptr_idx; i < ptr_idx + size; i++) sum += arr1[i] * arr2[i];
	return sum;
}
dtype dot_product_pidx_debug(dtype* arr1, dtype* arr2, const size_t size, pIdx ptr_idx)
{
	dtype sum = 0; int i;
	for (i = ptr_idx; i < ptr_idx + size; i++)
	{
		sum += arr1[i] * arr2[i];
		printf("arr[%d] = %.4f * arr2[%d]= %.4f = %.4f \n", i, arr1[i], i, arr2[i], sum);
	}
	return sum;
}
dtype dot_product_dpidx(dtype* arr1, dtype* arr2, const  size_t size, pIdx ptr_idx1, pIdx ptr_idx2)
{
	dtype sum = 0; int i, j;
	for (i = ptr_idx1, j = ptr_idx2; i < ptr_idx1 + size; i++, j++) sum += arr1[i] * arr2[j];
	return sum;
}
dtype dot_product_dpidx_debug(dtype* arr1, dtype* arr2, const size_t size, pIdx ptr_idx1, pIdx ptr_idx2)
{
	dtype sum = 0; int i, j;
	for (i = ptr_idx1, j = ptr_idx2; i < ptr_idx1 + size; i++, j++)
	{
		sum += arr1[i] * arr2[j];
		printf("arr[%d] = %.4f * arr2[%d]= %.4f = %.4f \n", i, arr1[i], i, arr2[j], sum);
	}
	return sum;
}
dtype dot_product4(dtype* arr1, dtype* arr2, const size_t size, pIdx ptr_idx1, pIdx ptr_idx2)
{
	dtype sum = 0; int i, j;
	for (i = ptr_idx1, j = ptr_idx2; i < ptr_idx1 + size; i++, j++) sum += arr2[i] * arr1[j];
	return sum;
}

/******************************************************************************
**                          FUNCTION IMPLEMENTAION
**                          PRINT ARRAY
*******************************************************************************/
void print_arr1d(dtype* arr, const size_t size, type_t data_type)
{
	/*
	* Arguments
	- r : Pointer to output array of autocorrelation of length audocor_len.
	- x : Pointer to input array of length nx+nr. Input data must be padded with nr consecutive zeros at the beginning.
	- autocor_len : Length of autocorrelation vector
	- lag : Length of lag

	Description
	-	This routine performs the autocorrelation of the input array x.
		It is assumed that the length of the input array, x, is a multiple of 2
		and the length of the output array, r, is a multiple of 4.
		The assembly routine computes 4 output samples at a time.
		It is assumed that input vector x is padded with nr no of zeros in the beginning.
	*/

	char* fn = NULL;
	int i;

	// data type
	if (!(strcmp(data_type, "int") && strcmp(data_type, "int32") && strcmp(data_type, "signed int") && strcmp(data_type, "signed int32")))
		fn = "%d ";

	else if (!(strcmp(data_type, "uint") && strcmp(data_type, "uint32") && strcmp(data_type, "unsigned int") && strcmp(data_type, "unsigned int32")))
		fn = "%u ";

	else if (!(strcmp(data_type, "short") && strcmp(data_type, "int16") && strcmp(data_type, "signed short") && strcmp(data_type, "signed int16")))
		fn = "%d ";

	else if (!(strcmp(data_type, "ushort") && strcmp(data_type, "uint16") && strcmp(data_type, "unsigned short") && strcmp(data_type, "unsigned int16")))
		fn = "%u ";

	else if (!(strcmp(data_type, "float") && strcmp(data_type, "float32") && strcmp(data_type, "signed float") && strcmp(data_type, "signed float32")))
		fn = "%.3f ";

	else if (!(strcmp(data_type, "double") && strcmp(data_type, "float64") && strcmp(data_type, "signed double") && strcmp(data_type, "signed float64")))
		fn = "%.4lf ";

	else
	{
		fprintf(stderr, "error : \"(%s)\" is Unsuppored data type \n", data_type);
		return;
	}

	for (i = 0; i < size; i++) fprintf(stdout, fn, arr[i]);
	printf("\n");

	return;
}

void print_arr1d_pidx(dtype* arr, const size_t size, type_t data_type, pIdx ptr_idx)
{
	char* fn = NULL;
	int i;

	// data type
	if (!(strcmp(data_type, "int") && strcmp(data_type, "int32") && strcmp(data_type, "signed int") && strcmp(data_type, "signed int32")))
		fn = "%d ";

	else if (!(strcmp(data_type, "uint") && strcmp(data_type, "uint32") && strcmp(data_type, "unsigned int") && strcmp(data_type, "unsigned int32")))
		fn = "%u ";

	else if (!(strcmp(data_type, "short") && strcmp(data_type, "int16") && strcmp(data_type, "signed short") && strcmp(data_type, "signed int16")))
		fn = "%d ";

	else if (!(strcmp(data_type, "ushort") && strcmp(data_type, "uint16") && strcmp(data_type, "unsigned short") && strcmp(data_type, "unsigned int16")))
		fn = "%u ";

	else if (!(strcmp(data_type, "float") && strcmp(data_type, "float32") && strcmp(data_type, "signed float") && strcmp(data_type, "signed float32")))
		fn = "%.3f ";

	else if (!(strcmp(data_type, "double") && strcmp(data_type, "float64") && strcmp(data_type, "signed double") && strcmp(data_type, "signed float64")))
		fn = "%.4lf ";

	else
	{
		fprintf(stderr, "error : \"(%s)\" is Unsuppored data type \n", data_type);
		return;
	}

	for (i = ptr_idx; i < ptr_idx + size; i++) fprintf(stdout, fn, arr[i]);
	printf("\n");

	return;
}

/******************************************************************************
**                          FUNCTION IMPLEMENTAION
**                          ADAPTIVE ALGORITHM
*******************************************************************************/
dtype least_mean_square(dtype* x, dtype* h, dtype* desired, dtype* y, dtype adapt_rate, dtype error,
	const int n_coeffecients, const int n_output_samples)
{
	/*
	* Arguments
	- x : Pointer to input samples
	- h : Pointer to the coefficient array
	- desired : Pointer to the desired output array
	- y : Pointer to filtered output array
	- adapt_rate : Adaptation rate error Initial error (mu)
	- n_coeffocients : Number of coefficients
	- n_output_samples : Number of output samples

	Description
	-	The least_mean_square implements an LMS adaptive filter.
		Given an actual input signal and a desired input signal,
		the filter produces an output signal, the final coefficient values,
		and returns the final output error signal.
	*/

	int i, j;
	dtype sum = 0.0f;
	for (i = 0; i < n_output_samples; i++)
	{
		for (j = 0; j < n_coeffecients; j++) h[j] = h[j] + (adapt_rate * error * x[i + j - 1]); // w(n+1) = w(n) + \mu*x(n)*e(n)
		sum = 0.0f;
		for (j = 0; j < n_coeffecients; j++) sum += h[j] * x[i + j];
		y[i] = sum;
		error = desired[i] - sum;
		printf("error : %f \n", error);
	}
	return error;
}

dtype fast_least_mean_square(dtype* x, dtype* h, dtype* desired, dtype* y, dtype adapt_rate, dtype error,
	const int n_coeffecients, const int n_output_samples, pIdx x_idx, pIdx h_idx, pIdx d_idx, pIdx y_idx)
{
	/*
	* Arguments
	- x : Pointer to input samples
	- h : Pointer to the coefficient array
	- desired : Pointer to the desired output array
	- y : Pointer to filtered output array
	- adapt_rate : Adaptation rate error Initial error
	- n_coeffocients : Number of coefficients
	- n_output_samples : Number of output samples
	- x_idx : Index of fast array x
	- h_idx : Index of fast array h
	- d_idx : Index of fast array d
	- y_idx : Index of fast array y

	Description
	-	The least_mean_square implements an LMS adaptive filter.
		Given an actual input signal and a desired input signal,
		the filter produces an output signal, the final coefficient values,
		and returns the final output error signal.
	*/

	int i, j;
	dtype sum = 0.0f;
	for (i = y_idx; i < n_output_samples + y_idx; i++)
	{
		for (j = h_idx; j < n_coeffecients + h_idx; j++) h[j] = h[j] + (adapt_rate * error * x[i + j - 1]); // w(n+1) = w(n) + \mu*x(n)*e(n)
		for (j = h_idx; j < n_coeffecients + h_idx; j++) sum += h[j] * x[i + j];
		y[i] = sum;
		error = desired[i] - sum;
	}
	return error;
}

/******************************************************************************
**                          FUNCTION IMPLEMENTAION
**                          OPEARTION
*******************************************************************************/
void autocor(dtype* __restrict r, const dtype* __restrict x, const int autocor_len, const int lag)
{
	/*
	* Arguments
	- r : Pointer to output array of autocorrelation of length audocor_len.
	- x : Pointer to input array of length nx+nr. Input data must be padded with nr consecutive zeros at the beginning.
	- autocor_len : Length of autocorrelation vector
	- lag : Length of lag

	Description
	-	This routine performs the autocorrelation of the input array x.
		It is assumed that the length of the input array, x, is a multiple of 2
		and the length of the output array, r, is a multiple of 4.
		The assembly routine computes 4 output samples at a time.
		It is assumed that input vector x is padded with nr no of zeros in the beginning.
	*/

	int i, k;
	dtype sum;
	for (i = 0; i < lag; i++)
	{
		sum = 0;
		for (k = lag; k < autocor_len + lag; k++) sum += x[k] * x[k - i];
		r[i] = sum;
	}
}

void fast_autocor(dtype* __restrict r, const dtype* __restrict x, const int autocor_len, const int lag, pIdx r_idx, pIdx x_idx)
{
	/*
	* Arguments
	- r : Pointer to output array of autocorrelation of length audocor_len.
	- x : Pointer to input array of length nx+nr. Input data must be padded with nr consecutive zeros at the beginning.
	- autocor_len : Length of autocorrelation vector
	- lag : Length of lag

	Description
	-	This routine performs the autocorrelation of the input array x.
		It is assumed that the length of the input array, x, is a multiple of 2
		and the length of the output array, r, is a multiple of 4.
		The assembly routine computes 4 output samples at a time.
		It is assumed that input vector x is padded with nr no of zeros in the beginning.
	*/
	int i, k;
	dtype sum;
	for (i = 0; i < lag; i++)
	{
		sum = 0;
		for (k = lag; k < autocor_len + lag; k++) sum += x[k] * x[k - i];
		r[i] = sum;
	}
}

dtype fir_filtering(dtype* x1, dtype* x2, const size_t size)
{
	/*
	* Arguments
	- x1 : Input array 1
	- x2 : Input array 2
	- size : Length of x1, x2 array

	Description
	-	This routine performs the fir filtering of the input array x1 and x2
	*/

	dtype sum = 0; int i;
	for (i = 0; i < size; i++)  sum += x1[i] * x2[i];
	return sum;
}

dtype fast_fir_filtering(dtype* x1, dtype* x2, const size_t size, pIdx idx)
{
	/*
	* Arguments
	- x1 : Input fast array 1
	- x2 : Input fast array 2
	- size : Length of x1, x2 array

	Description
	-	This routine performs the fir filtering of the input array x1 and x2
		using fast array
	*/

	dtype sum = 0; int i;
	for (i = idx; i < idx + size; i++)  sum += x1[i] * x2[i];
	return sum;
}

dtype fast_fir_filtering_dpidx(dtype* x1, dtype* x2, const  size_t size, pIdx idx1, pIdx idx2)
{
	/*
	* Arguments
	- x1 : Input fast array 1
	- x2 : Input fast array 2
	- size : Length of x1, x2 array
	- idx1 : Pointer index of x1
	- idx2 : pointer index of x2

	Description
	-	This routine performs the fir filtering of the input array x1 and x2
		using fast array

	Equation
	-	result = x1(idx1)*x2(idx2) + x1(idx1 + 1)*x2(idx2 + 1) + ... + x1(idx1 + L - 1)*x2(idx2 + L - 1)
	*/
	dtype sum = 0; int i, j;
	for (i = idx1, j = idx2; i < idx1 + size; i++, j++) sum += x1[i] * x2[j];
	return sum;
}

/******************************************************************************
**                          FUNCTION IMPLEMENTAION
**                          FFT(FAST FOURIER TRANSFORM)
*******************************************************************************/
