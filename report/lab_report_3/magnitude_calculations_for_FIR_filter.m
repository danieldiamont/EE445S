sys = tf(Num, 1, 48000);

n = 1 : 1 : 24;

freqs = 1000 : 1000 : 24000;
h = freqz(Num, 1, freqs, 48000);
plot(freqs, abs(h));

abs_h = abs(h);