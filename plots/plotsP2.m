clc;
clear;

thread2 = [0.01921850, 0.01927100];
thread4 = [0.01901280, 0.01904500, 0.01901020, 0.01903960];
thread6 = [0.01940680, 0.01940920, 0.01943740, 0.01946060, 0.01944630, 0.01943530];
thread8 = [0.01902730, 0.01902420, 0.01976820, 0.01915440, 0.01906010, 0.01904000, 0.01902700, 0.02132020];
thread9 = [0.01911340, 0.01980700, 0.03241720, 0.01907870, 0.01912280, 0.01904030, 0.01904260, 0.02197330, 0.01915290];
thread10 = [0.01903860, 0.01900890, 0.01897300, 0.02082000, 0.03466640, 0.03464900, 0.01900940, 0.01905050, 0.01900470, 0.02077730];

figure(1)
plot(thread2);
hold on
plot(thread4);
plot(thread6);
plot(thread8);
plot(thread9);
plot(thread10);
title("Tiempo empleado según el número de procesos");
xlabel("Número de hilos");
ylabel("Tiempo (segundos)");
legend('2 hilos','4 hilos', '6 hilos', '8 hilos', '9 hilos', '10 hilos', 'Location', 'northeast');
hold off