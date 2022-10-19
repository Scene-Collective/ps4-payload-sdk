@echo off
rem PS4 Payload SDK libPS4 build script... for Windows!
rem written by nik...

setlocal EnableDelayedExpansion

rem set this to your C compiler toolchain executable
set CC=clang
rem set this to your ar toolchain executable
set AR=llvm-ar

rem usually you do not need to touch the rest of this:
set RDIR=libPS4
set ODIR=build
set SDIR=source
set IDIR=include
set CFLAGS=--target=x86_64-pc-freebsd12-elf -Wno-unused-command-line-argument -I"%IDIR%" -Os -std=c11 -ffunction-sections -fdata-sections -fno-builtin -nostartfiles -nostdlib -Wall -Wextra -masm=intel -march=btver2 -mtune=btver2 -m64 -mabi=sysv -mcmodel=small -fpie -fPIC
set TARGET=%RDIR%.a
set OBJS=


pushd %RDIR%

rem clean
rmdir /s /q %ODIR%
del /q /f %TARGET%
mkdir %ODIR%

rem do the build
for %%f in (%SDIR%\*.c %SDIR%\*.s) do (
	%CC% -c -o %ODIR%\%%~nf.o %%f %CFLAGS%
)

for %%f in (%ODIR%\*.o) do set OBJS=!OBJS! %%f

%AR% rcs %TARGET% %OBJS%

popd

echo Done
