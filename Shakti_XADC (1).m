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
