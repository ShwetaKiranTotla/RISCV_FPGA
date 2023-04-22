x_var_new=[0.000, 0.438, 0.830, 1.228, 1.620, 2.050, 2.446, 2.842 3.241];
x_th=[0    544   1030   1524   2011   2544   3036   3528   4023];
y_new=[0.000000 540 1028 1518 1999 2526 3010 3500 3995];
y_ch_2=[0 560 1035 1525 2009 2540 3030 4011];
x_theoretical_1=(((x_var_new)*4096)/3.3);
x_theoretical = cast(x_theoretical_1,"uint16");

plot(x_theoretical,x_theoretical)
hold on
plot(x_theoretical,y_new)
% hold on
% plot(x_var,y_var*1.1)
% y_adj=y_var*1.1;
legend('theoretical','practical')
title('Shakti XADC Precision Graph')
xlabel('Input Voltage from DC Power Supply') 
ylabel('XADC Output') 
grid on
hold off

%{Old Code
x_var=[0.000, 0.437, 0.830, 1.226, 1.618, 2.048, 2.443, 2.839];
y_var=[0.000, 0.399, 0.753, 1.111, 1.464, 1.851, 2.209, 2.564];
y_11=[0	0.4389	0.8283	1.2221	1.6104	2.0361	2.4299	2.8204];

y_theoretical=x_var;
plot(x_var,y_var)
hold on
plot(x_var,y_theoretical)
hold on
plot(x_var,y_var*1.1)
y_adj=y_var*1.1;
legend('theoretical','practical','adjusted')
grid on
%}
