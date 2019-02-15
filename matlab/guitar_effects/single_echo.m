%FIR feedforward single echo

[guitar, fs] = audioread('./samples/sample3.wav');
Ts = 1/fs;
numSamples = length(guitar);
tmax = Ts * numSamples;

N = 512;
A = [1];
alpha = 1;
R = 50;
R = round(R);
B = [1 zeros(1,R-2) alpha];

%FIR filter
[H,W] = freqz(B, A, N);

subplot(2,1,1), plot(W, abs(H))
xlabel('radians'); ylabel('amplitude')
subplot(2,1,2), plot(W, angle(H));
xlabel('radians'); ylabel('angle')

%output signal
y = filter(B, A, guitar);

soundview(guitar,fs);
pause(tmax + 3)
soundview(y,fs);