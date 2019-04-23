sps = 20; % 20 samples per symbol
beta = 0.8;
span = 4; % symbol periods
h = rcosdesign(beta, span, sps);
h = h ./ 0.2725555;

fvtool(h, 'Analysis', 'impulse');
title('Impulse Response Raised Cosine (beta = 0.8)');

addpath('C:\Users\daniel\workspace_DSP\code\chapter_03\matlab\matlabExport');

FIR_dump2c('coeff','pulse',h,length(h));