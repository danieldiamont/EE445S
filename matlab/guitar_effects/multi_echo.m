%IIR feedback multi echo

[guitar, fs] = audioread('./samples/sample3.wav');
Ts = 1/fs;
numSamples = length(guitar);
tmax = Ts * numSamples;

N = 512;
B = [1];
alpha = 0.8;
R = 50;
R = round(R);
A = [1 zeros(1,R-2) alpha];

%IIR filter
[H,W] = freqz(B, A, N);

subplot(2,1,1), plot(W, abs(H))
xlabel('radians'); ylabel('amplitude');
subplot(2,1,2), plot(W, angle(H));
xlabel('radians'); ylabel('angle');

%output signal
y = filter(B, A, guitar);

soundview(guitar,fs);
pause(tmax + 3)
soundview(y,fs);