@echo off
cd /d "%~dp0"

REM ===== clear results once =====
echo ==== experiment start ==== > results.txt

REM ===== category 1 =====
for %%i in (1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20) do (
    echo 0 10000 1 10000 %%i > input.txt
    .\h34136091_hw4.exe < input.txt >> results.txt
)

REM ===== category 2 =====
for %%i in (1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20) do (
    echo 0 10000 10000 30000 %%i > input.txt
    .\h34136091_hw4.exe < input.txt >> results.txt
)

REM ===== category 3 =====
for %%i in (1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20) do (
    echo 0 10000 1 30000 %%i > input.txt
    .\h34136091_hw4.exe < input.txt >> results.txt
)

REM ===== category 4 =====
for %%i in (1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20) do (
    echo 0 50000 1 50000 %%i > input.txt
    .\h34136091_hw4.exe < input.txt >> results.txt
)

REM ===== category 5 =====
for %%i in (1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20) do (
    echo 0 50000 20000 70000 %%i > input.txt
    .\h34136091_hw4.exe < input.txt >> results.txt
)

REM ===== category 6 =====
for %%i in (1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20) do (
    echo 0 50000 1 70000 %%i > input.txt
    .\h34136091_hw4.exe < input.txt >> results.txt
)

REM ===== category 7 =====
for %%i in (1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20) do (
    echo 0 100000 1 100000 %%i > input.txt
    .\h34136091_hw4.exe < input.txt >> results.txt
)

REM ===== category 8 =====
for %%i in (1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20) do (
    echo 0 100000 50000 150000 %%i > input.txt
    .\h34136091_hw4.exe < input.txt >> results.txt
)

REM ===== category 9 =====
for %%i in (1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20) do (
    echo 0 100000 1 150000 %%i > input.txt
    .\h34136091_hw4.exe < input.txt >> results.txt
)

echo.
echo ===== ALL EXPERIMENTS FINISHED =====
pause
