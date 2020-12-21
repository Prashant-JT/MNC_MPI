clc;
clear;

thread2B = [0.002557, 0.002532];
thread4B = [0.002487, 0.002517, 0.002710, 0.002732];
thread8B = [0.002622, 0.002654, 0.002944, 0.0029329, 0.003098, 0.003058, 0.003274, 0.003313];

thread2PP = [0.001998, 0.002518];
thread4PP = [0.002561, 0.003294, 0.003326, 0.003362];
thread8PP = [0.002839, 0.003230, 0.003265, 0.003222, 0.003258, 0.003236, 0.003261, 0.003350];

subplot(1,2,1);
plot(thread2B);
hold on
plot(thread4B);
plot(thread8B);
title("Tiempo empleado según el número de procesos (Broadcast)");
xlabel("Número de hilos");
ylabel("Tiempo (segundos)");
legend('2 hilos','4 hilos', '8 hilos', 'Location', 'southeast');
hold off

subplot(1,2,2);
plot(thread2PP);
hold on
plot(thread4PP);
plot(thread8PP);
title("Tiempo empleado según el número de procesos (Punto a punto)");
xlabel("Número de hilos");
ylabel("Tiempo (segundos)");
legend('2 hilos','4 hilos', '8 hilos', 'Location', 'southeast');
hold off