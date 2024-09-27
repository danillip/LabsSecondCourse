@echo off
chcp 65001 > nul

:menu
cls
echo 1. Подсчитать скрытые подкаталоги с рекурсией
echo 2. Подсчитать файлы Microsoft Word с выводом полного пути
echo 3. Выход

set /p choice=Выберите опцию (1, 2, или 3):

if "%choice%"=="1" (
    call :count_hidden_directories
) else if "%choice%"=="2" (
    call :count_word_files
) else if "%choice%"=="3" (
    exit /b
) else (
    echo Некорректный выбор. Попробуйте снова.
    pause
    goto :menu
)

:count_hidden_directories
setlocal enabledelayedexpansion

set "dir=%~dp0"
set "count=0"

set /p "choice=1. Использовать текущий путь (%dir%) или 2. Ввести свой путь: "

if "%choice%"=="1" (
    set "dir=%~dp0"
) else if "%choice%"=="2" (
    set /p "dir=Введите путь к каталогу: "
) else (
    echo Некорректный выбор. Попробуйте снова.
    pause
    goto :count_hidden_directories
)

for /r "%dir%" /d %%d in (*) do (
    dir /a:h "%%d" >nul 2>nul
    if !errorlevel! equ 0 (
        set /a count+=1
    )
)

echo Количество скрытых подкаталогов в %dir%: %count%
pause
goto :menu

:count_word_files
setlocal enabledelayedexpansion

set "dir=%~dp0"
set "count=0"

set /p "choice=1. Использовать текущий путь (%dir%) или 2. Ввести свой путь: "

if "%choice%"=="1" (
    set "dir=%~dp0"
) else if "%choice%"=="2" (
    set /p "dir=Введите путь к каталогу: "
) else (
    echo Некорректный выбор. Попробуйте снова.
    pause
    goto :count_word_files
)

for /r "%dir%" %%f in (*.doc *.docx) do (
    echo %%~ff
    set /a count+=1
)

echo Количество файлов Microsoft Word в %dir%: %count%
pause
goto :menu
