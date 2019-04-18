/* coeff.c                             */
/* IIR filter coefficients             */
/* exported by MATLAB using IIR_dump2C */
/* Michael G. Morrow - 2000, 2013      */


#include "coeff.h"

float B[N] = {
    0.245237,	/* B[0] */
    0.245237,	/* B[1] */
           0,	/* B[2] */
};

float A[N] = {
           1,	/* A[0] */
   -0.509525,	/* A[1] */
           0,	/* A[2] */
};
