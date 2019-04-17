%lab 5 part 2

%source bits
bits = round(rand(1,2000));

%bpsk symbol mapping
symbols = bits;
symbols(symbols == 0) = -1;

%pulse shape
beta = 0.1;
span = 8;
sas = 20;
pulse_shape = rcosdesign(beta,span,sas,'normal');

%create waveform
w = upsample(symbols, 20);
x = conv(w,pulse_shape);
x = x(round(length(pulse_shape)/2):end - round(length(pulse_shape)/2));

figure;
plot(pulse_shape);

figure;
plot(x);

%reciever

%downsample
yrx = x(1:sas:end);

%scr
pre = filter(Pre_Num,Pre_Den,x);
figure;
plot(pre);
title('pre time')

figure;
freqz(pre)
title('pre freq');

sqr = pre.^2;
figure;
plot(sqr);
title('square time');

figure;
freqz(sqr);
title('square freq');

post_bandpass = filter(Band_Num,Band_Den, sqr);
figure;
plot(post_bandpass);
title('post time');

figure;
freqz(post_bandpass);
title('post freq');

%%

addpath('../../../code/appendix_e/MatlabExports');
sos_dump2c('post','post',post,1);
sos_dump2c('pre','pre',pre,1);










