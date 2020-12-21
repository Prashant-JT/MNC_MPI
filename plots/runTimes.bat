@echo off
:: Bucle con fin/Contador
for /L %%b in (256,128,896) do (
mpiexec -n %%b practica7_1.exe
)
pause