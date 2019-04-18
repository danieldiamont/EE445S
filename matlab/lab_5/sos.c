/* sos.c                                    */
/* SOS filter coefficients                  */
/* exported from MATLAB using sos_dump2c.m  */
/* order is {b0, b1, b2, -a1, -a2}          */


#include "sos.h"

float sos[sos_SIZE][5] = {
{           1,            1,            0,     0.509525,           -0}, /* sos[0] */
};

float G[2] = {    0.2452, 1.0000    };