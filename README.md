# IOTAID.EXE

IOTAID is a cross-platform text adventure engine written in C and LUA.
It mainly targets MS DOS via the [DJGPP development suite](http://www.delorie.com/djgpp/) but also aims to be compatible with POSIX and Windows targets (mostly for ease of debugging).

## Requirements

- A C compiler (DJGPP on MS DOS, possibly MSVC on Windows)
- [LUA 5.2](www.lua.org)

## Compiling

### MS DOS / DOSBox

After getting a working DJGPP environment working (will explain in more detail in the future) just write "make" when inside the IOTAID folder.

### Windows

Get yourself a static lua 5.2 .lib file (compile it, it's not hard) and fix the VC15 solution paths (as it will have mine). Then just compile.

### Linux / FreeBSD / *nix

"make". Executable will have the ".exe" extension. I'll fix that later.

## Platform specific bits

Most of the project should be completely portable across platforms, currently the only platform specific bit is the terminal management.

- **MS DOS:** term_dos.c
- **POSIX:** term_posix.c
- **Windows:** term_win32.c

## A 100% reason to remember the name!

IOTAID is a magic word from italian text adventure ["Avventura nel Castello"](http://www.erix.it/retro/storia_cast.html) by [Enrico Colombini](https://it.wikipedia.org/wiki/Enrico_Colombini).
It's a clever word play on the word IDIOTA (Idiot) and the game is what inspired this engine.