/* pre.c                                    */
/* SOS filter coefficients                  */
/* exported from MATLAB using sos_dump2c.m  */
/* order is {b0, b1, b2, -a1, -a2}          */


#include "pre.h"

float pre[pre_SIZE][5] = {
{           1,            0,           -1,      1.96004,    -0.984414}, /* pre[0] */
};
