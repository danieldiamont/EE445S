%use this script only after exporting FIR coefficients to the workspace
%design using matlab filter design tool
%export matlab FIR coefficients

addpath('../../../code/chapter_03/matlab/matlabExport');

FIR_dump2c('coeff','B',Num,length(Num));
