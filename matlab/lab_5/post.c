/* post.c                                   */
/* SOS filter coefficients                  */
/* exported from MATLAB using sos_dump2c.m  */
/* order is {b0, b1, b2, -a1, -a2}          */


#include "post.h"

float post[post_SIZE][5] = {
{           1,            0,           -1,      1.87293,    -0.969067}, /* post[0] */
};
