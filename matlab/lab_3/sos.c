/* sos.c                                    */
/* SOS filter coefficients                  */
/* exported from MATLAB using sos_dump2c.m  */
/* order is {b0, b1, b2, -a1, -a2}          */


#include "sos.h"

float SOS[SOS_SIZE][5] = {
{           1,            0,           -1,      1.28028,    -0.657254}, /* SOS[0] */
{           1,            0,           -1,    -0.513935,    -0.530466}, /* SOS[1] */
{           1,            0,           -1,     0.369184,    -0.131652}, /* SOS[2] */
};
