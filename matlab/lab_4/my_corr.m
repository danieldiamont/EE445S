pn = [1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0];
sc = [0, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1];

pn(pn == 0) = -1;
sc(sc == 0) = -1;

tmp1 = [pn pn];
tmp2 = [sc sc];

s1 = fft(tmp1);
pn_corr = ifft(s1.*conj(s1))/length(tmp1);

s2 = fft(tmp2);
sc_corr = ifft(s2.*conj(s2)/length(tmp2));

plot(pn_corr);
title('PN circular autocorrelation');
xlabel('chip offset');
ylabel('R');
saveas(gcf, '../../report/lab_report_4/img/pn_corr.png');

figure;
plot(sc_corr);
title('scrambled circular autocorrelation');
xlabel('chip offset');
ylabel('R');
saveas(gcf, '../../report/lab_report_4/img/sc_corr.png');
