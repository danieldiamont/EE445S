%FIR feedforward variable delay flanger effect

[guitar, fs] = audioread('./samples/sample5.wav');
Ts = 1/fs;
numSamples = length(guitar);
tmax = Ts * numSamples;

%effect parameters
R = 100;
R = round(R);
alpha = 1;
f0 = 2;

%variable delay B[n]
Bn = zeros(1, numSamples);
arg = 0:numSamples; arg = 2*pi*(f0/fs)*arg;
Bn = (R/2)*(1 - cos(arg));
Bn = round(Bn);

y = zeros(1, numSamples);
buffer = zeros(1, R + 1);
oldest = 0;


%feedforward filter
for i = 1:numSamples
    offset = R - Bn(i);
    buffer(oldest + 1) = guitar(i);
    oldest = oldest + 1;
    oldest = mod(oldest, R+1);
    offset = oldest + offset;
    offset = mod(offset, R+1);
    y(i) = guitar(i) + alpha*buffer(offset+1);
end

soundview(guitar,fs);
pause(tmax + 2)
soundview(y,fs);