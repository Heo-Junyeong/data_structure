/**
* @ author : junyeong heo
* 
*/

#include "fast_array.h"

#define LENGTH 10000
#define LENGTH2 ((2) * (LENGTH))

#define ITERATION 1000000

#define ORDER 1

#define __DEBUG2__
#ifdef __DEBUG2__

int main(void)
{
	/* local variables for push routine */
	dtype push_a[LENGTH] = { 0, }; // normal array
	dtype push_b[LENGTH] = { 0, };
	dtype push_c[LENGTH2] = { 0, }; // fast array needs twice as much memory

	clock_t start[3], end[3];
	pIdx ptr_idx = 0;

	const int n_samples = LENGTH / 100;

	/* local variables for lms routine */
	dtype lms_x[LENGTH];	// input signal
	dtype lms_h[ORDER];	// filter weight
	dtype lms_y[LENGTH]; // filter output
	dtype lms_d[LENGTH]; // desired input
	dtype lms_e = 0; // error signal

	/* variables for iteration */
	int i, j, k;
/******************************************************************************
**                          FAST ARRAY DEMO 1
**                          PUSH ROUTINE
*******************************************************************************/

	printf("I'm Alive!! :)\n");
	start[0] = clock();
	for (i = 0; i < ITERATION; i++)
	{
		fa_push_(push_a, LENGTH, (dtype)(i * 0.01));
	}
	end[0] = clock();

	printf("I'm Alive!! :)\n");
	start[1] = clock();
	for (i = 0; i < ITERATION; i++)
	{
		fa_push(push_b, LENGTH, (dtype)(i * 0.01));
	}
	end[1] = clock();

	printf("I'm Alive!! :)\n");
	start[2] = clock();
	for (i = 0; i < ITERATION; i++)
	{
		fa_fast_push_shift(push_c, LENGTH, ptr_idx, (dtype)(i * 0.01));
	}
	end[2] = clock();
	
	printf("I'm Alive!! :)\n");
	printf("comparsion of push algorithm time\n1. using for %d ms\n2. using memmove : %d ms\n3. using pIdx : %d ms\n",
		end[0]-start[0], end[1]- start[1], end[2]-start[2]);

	printf("Result test sample 1 : "); print_arrf(push_a, n_samples);
	printf("Result test sample 2 : "); print_arrf(push_b, n_samples);
	printf("Result test sample 3 : "); print_arrf_vect(push_c, n_samples, ptr_idx);

/******************************************************************************
**                          FAST ARRAY DEMO 2
**                          ADF ROUTINE
*******************************************************************************/
	
	float f0 = 880, fs = 8000, phase = 0;
	i = 2;

	cos_(lms_d, LENGTH, 880, 8000, 0);
	sin_(lms_x, LENGTH, 880, 8000, 0);
	zeros(lms_y, LENGTH);
	zeros(lms_h, ORDER);

	fa_lms(lms_x, lms_h, lms_d, lms_y, 0.01, lms_e, ORDER, LENGTH);

}
#endif