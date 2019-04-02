/* coeff.c                             */
/* FIR filter coefficients              */
/* exported by MATLAB using FIR_dump2c  */
/* Michael G. Morrow - 2000, 2003       */


#include "coeff.h"

float B[N+1] = {
-0.003921568366,	/* h[0] */
-0.003825033996,	/* h[1] */
-0.003338079470,	/* h[2] */
-0.002488927901,	/* h[3] */
-0.001343318439,	/* h[4] */
0.000000000000,	/* h[5] */
0.001417249008,	/* h[6] */
0.002770480831,	/* h[7] */
0.003920415490,	/* h[8] */
0.004740113900,	/* h[9] */
0.005128204786,	/* h[10] */
0.005020357120,	/* h[11] */
0.004397787239,	/* h[12] */
0.003291807869,	/* h[13] */
0.001783750714,	/* h[14] */
0.000000000000,	/* h[15] */
-0.001897672401,	/* h[16] */
-0.003725819049,	/* h[17] */
-0.005295999872,	/* h[18] */
-0.006433011721,	/* h[19] */
-0.006993006527,	/* h[20] */
-0.006879748646,	/* h[21] */
-0.006057329593,	/* h[22] */
-0.004557887819,	/* h[23] */
-0.002483260799,	/* h[24] */
0.000000000000,	/* h[25] */
0.002672232565,	/* h[26] */
0.005278243652,	/* h[27] */
0.007549616839,	/* h[28] */
0.009229973339,	/* h[29] */
0.010101009428,	/* h[30] */
0.010006907122,	/* h[31] */
0.008874692194,	/* h[32] */
0.006728310590,	/* h[33] */
0.003694607530,	/* h[34] */
-0.000000000000,	/* h[35] */
-0.004042608239,	/* h[36] */
-0.008056266627,	/* h[37] */
-0.011630490806,	/* h[38] */
-0.014357736306,	/* h[39] */
-0.015873014815,	/* h[40] */
-0.015893323076,	/* h[41] */
-0.014253293524,	/* h[42] */
-0.010933504708,	/* h[43] */
-0.006078225291,	/* h[44] */
0.000000000000,	/* h[45] */
0.006830613921,	/* h[46] */
0.013810742789,	/* h[47] */
0.020245669180,	/* h[48] */
0.025402148848,	/* h[49] */
0.028571426666,	/* h[50] */
0.029137758973,	/* h[51] */
0.026647461806,	/* h[52] */
0.020873054443,	/* h[53] */
0.011867011282,	/* h[54] */
-0.000000000000,	/* h[55] */
-0.014020733837,	/* h[56] */
-0.029156012555,	/* h[57] */
-0.044064103510,	/* h[58] */
-0.057154834909,	/* h[59] */
-0.066666662222,	/* h[60] */
-0.070763128935,	/* h[61] */
-0.067643556893,	/* h[62] */
-0.055661478514,	/* h[63] */
-0.033443395430,	/* h[64] */
0.000000000000,	/* h[65] */
0.045177920142,	/* h[66] */
0.102046043941,	/* h[67] */
0.169961542108,	/* h[68] */
0.247670951272,	/* h[69] */
0.333333311109,	/* h[70] */
0.424578773609,	/* h[71] */
0.518600602843,	/* h[72] */
0.612276263649,	/* h[73] */
0.702311304026,	/* h[74] */
0.785398111032,	/* h[75] */
0.858380482699,	/* h[76] */
0.918414395473,	/* h[77] */
0.963115405279,	/* h[78] */
0.990683805088,	/* h[79] */
0.999999933326,	/* h[80] */
0.990683805088,	/* h[81] */
0.963115405279,	/* h[82] */
0.918414395473,	/* h[83] */
0.858380482699,	/* h[84] */
0.785398111032,	/* h[85] */
0.702311304026,	/* h[86] */
0.612276263649,	/* h[87] */
0.518600602843,	/* h[88] */
0.424578773609,	/* h[89] */
0.333333311109,	/* h[90] */
0.247670951272,	/* h[91] */
0.169961542108,	/* h[92] */
0.102046043941,	/* h[93] */
0.045177920142,	/* h[94] */
0.000000000000,	/* h[95] */
-0.033443395430,	/* h[96] */
-0.055661478514,	/* h[97] */
-0.067643556893,	/* h[98] */
-0.070763128935,	/* h[99] */
-0.066666662222,	/* h[100] */
-0.057154834909,	/* h[101] */
-0.044064103510,	/* h[102] */
-0.029156012555,	/* h[103] */
-0.014020733837,	/* h[104] */
-0.000000000000,	/* h[105] */
0.011867011282,	/* h[106] */
0.020873054443,	/* h[107] */
0.026647461806,	/* h[108] */
0.029137758973,	/* h[109] */
0.028571426666,	/* h[110] */
0.025402148848,	/* h[111] */
0.020245669180,	/* h[112] */
0.013810742789,	/* h[113] */
0.006830613921,	/* h[114] */
0.000000000000,	/* h[115] */
-0.006078225291,	/* h[116] */
-0.010933504708,	/* h[117] */
-0.014253293524,	/* h[118] */
-0.015893323076,	/* h[119] */
-0.015873014815,	/* h[120] */
-0.014357736306,	/* h[121] */
-0.011630490806,	/* h[122] */
-0.008056266627,	/* h[123] */
-0.004042608239,	/* h[124] */
-0.000000000000,	/* h[125] */
0.003694607530,	/* h[126] */
0.006728310590,	/* h[127] */
0.008874692194,	/* h[128] */
0.010006907122,	/* h[129] */
0.010101009428,	/* h[130] */
0.009229973339,	/* h[131] */
0.007549616839,	/* h[132] */
0.005278243652,	/* h[133] */
0.002672232565,	/* h[134] */
0.000000000000,	/* h[135] */
-0.002483260799,	/* h[136] */
-0.004557887819,	/* h[137] */
-0.006057329593,	/* h[138] */
-0.006879748646,	/* h[139] */
-0.006993006527,	/* h[140] */
-0.006433011721,	/* h[141] */
-0.005295999872,	/* h[142] */
-0.003725819049,	/* h[143] */
-0.001897672401,	/* h[144] */
0.000000000000,	/* h[145] */
0.001783750714,	/* h[146] */
0.003291807869,	/* h[147] */
0.004397787239,	/* h[148] */
0.005020357120,	/* h[149] */
0.005128204786,	/* h[150] */
0.004740113900,	/* h[151] */
0.003920415490,	/* h[152] */
0.002770480831,	/* h[153] */
0.001417249008,	/* h[154] */
0.000000000000,	/* h[155] */
-0.001343318439,	/* h[156] */
-0.002488927901,	/* h[157] */
-0.003338079470,	/* h[158] */
-0.003825033996,	/* h[159] */
-0.003921568366,	/* h[160] */
};
