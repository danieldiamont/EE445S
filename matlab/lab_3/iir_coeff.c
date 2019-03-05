/* coeff.c                             */
/* IIR filter coefficients             */
/* exported by MATLAB using IIR_dump2C */
/* Michael G. Morrow - 2000, 2013      */


#include "coeff.h"

float B[N] = {
    0.108499,	/* B[0] */
           0,	/* B[1] */
   -0.325498,	/* B[2] */
           0,	/* B[3] */
    0.325498,	/* B[4] */
           0,	/* B[5] */
   -0.108499,	/* B[6] */
};

float A[N] = {
           1,	/* A[0] */
    -1.13553,	/* A[1] */
    0.944316,	/* A[2] */
   -0.637821,	/* A[3] */
    0.544417,	/* A[4] */
   -0.173657,	/* A[5] */
   0.0459008,	/* A[6] */
};
