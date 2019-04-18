% m-PAm error probability
m = [2 4 8];
snr = 1 : 0.1 : 500;

p = zeros(length(m), length(snr));

for i=1:length(m)
    for j=1:length(snr)
    p(i,j) = 2 * (m(i) - 1)/m(i) * qfunc( sqrt( 3 / (m(i)^2 - 1) ) * snr(j) );
    end
end

hold on;
plot(20*log10(snr), 20*log10(p(1,:)));
plot(20*log10(snr), 20*log10(p(2,:)));
plot(20*log10(snr), 20*log10(p(3,:)));
legend('2-PAM','4-PAM', '8-PAM');
title('Probability of Error vs. Signal-to-Noise Ratio');
xlabel(' $$ log_{10}(\frac{P_s}{P_n}) $$ ', 'Interpreter', 'latex');
ylabel(' $$ P_e (dB) $$ ', 'Interpreter', 'latex');
hold off;