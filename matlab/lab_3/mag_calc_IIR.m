sys = tf(Num, Den, 48000);

freqs = 1000 : 1000 : 24000;
h = freqz(Num, Den, freqs, 48000);
plot(freqs, abs(h));
abs_h = abs(h);