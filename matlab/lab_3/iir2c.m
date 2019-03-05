%use this script only after exporting FIR coefficients to the workspace
%design using matlab filter design tool
%export matlab FIR coefficients

addpath('../../../445S/code/appendix_e/MatlabExports');

IIR_dump2C('coeff','B', Num, 'A', Den, length(Den));

sos_dump2c('sos','SOS',SOS,3);