% generate 200 random bits using round and rand
bits = round(rand(1,200));

% map to bpsk amplitudes
bpsk = bits;
bpsk(bpsk == 0) = -1;

%% simulation of block diagram
sps = 20; % 20 samples per symbol
beta = 1;
span = 8;
h = rcosdesign(beta, span, sps);
h = h ./ 0.2847096;

fvtool(h, 'Analysis', 'impulse');
title('Impulse Response Raised Cosine (beta = 1)');

upsample_bpsk = upsample(bpsk,20);
upsample_bpsk = upsample_bpsk(81:length(upsample_bpsk));

upsample_conv_bpsk = conv(h,upsample_bpsk);


upsample_conv_bpsk=upsample_conv_bpsk(81:length(upsample_conv_bpsk)-80);
plot(upsample_conv_bpsk);
title('Upsampled BPSK Convolved With Raised Cosine (beta = 1)');
ylabel('Voltage');
xlabel('Samples');
hold on
plot(upsample_bpsk);
hold off


%% repeat simulation with beta = 0.125

beta_1 = 0.125;
h_1 = rcosdesign(beta_1, span, sps);
h_1 = h_1 ./ 0.2317986;
fvtool(h_1, 'Analysis', 'impulse');
title('Impulse Response Raised Cosine (beta = 0.125)');

upsample_conv_bpsk_1 = conv(h_1, upsample_bpsk);
upsample_conv_bpsk_1=upsample_conv_bpsk_1(81:length(upsample_conv_bpsk_1)-80);
plot(upsample_conv_bpsk_1);
title('Upsampled BPSK Convolved With Raised Cosine (beta = 0.125)');
ylabel('Voltage');
xlabel('Samples');
hold on
plot(upsample_bpsk);
hold off