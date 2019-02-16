%feedforward tremolo effect

[guitar, fs] = audioread('./samples/sample3.wav');
Ts = 1/fs;
numSamples = length(guitar);
tmax = Ts * numSamples;

%effect parameters
alpha = 0.5;
f0 = 2;
N = fs/f0;

%variable delay B[n]
Bn = zeros(1, N);
arg = 0:N-1; arg = 2*pi*(f0/fs)*arg;
Bn = (1/2)*(1 - cos(arg));
scale = 1 - alpha;

y = zeros(1, numSamples);
bI = 0;

for i = 1:numSamples
    y(i) = scale*guitar(i)+ Bn(bI + 1)*alpha*guitar(i);
    bI = bI + 1;
    bI = mod(bI, N);
end

soundview(guitar,fs);
pause(tmax + 2)
soundview(y,fs);
