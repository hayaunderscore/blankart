# SRB2Kart - Which DLLs do I need to bundle?

Updated 8/23/2020 (v1.3)

Here are the required DLLs, per build. For each architecture, copy all the binaries from these folders:

* libs\dll-binaries\[i686/x86_64]
* libs\SDL2\[i686/x86_64]...\bin
* libs\SDL2mixerX\[i686/x86_64]...\bin
* libs\libopenmpt\[x86/x86_64]...\bin\mingw

and don't forget to build r_opengl.dll for srb2dd.

## srb2kart, 32-bit

* libs\dll-binaries\i686\exchndl.dll
* libs\dll-binaries\i686\libgme.dll
* libs\dll-binaries\i686\discord-rpc.dll
* libs\dll-binaries\i686\mgwhelp.dll (depend for exchndl.dll)
* libs\SDL2\i686-w64-mingw32\bin\SDL2.dll
* libs\SDL2mixerX\i686-w64-mingw32\bin\*.dll (get everything)
* libs\libopenmpt\x86\bin\mingw\libopenmpt.dll

## srb2kart, 64-bit

* libs\dll-binaries\x86_64\libgme.dll
* libs\dll-binaries\x86_64\discord-rpc.dll
* libs\SDL2\x86_64-w64-mingw32\bin\SDL2.dll
<<<<<<< HEAD
* libs\SDL2mixerX\x86_64-w64-mingw32\bin\*.dll (get everything)
* libs\libopenmpt\x86_64\bin\mingw\libopenmpt.dll
* libs\libbacktrace\bin\x86_64\libbacktrace-0.dll
* libs\libbacktrace\bin\x86_64\libgcc_s_seh-1.dll
* libs\libbacktrace\bin\x86_64\libwinpthread-1.dll
=======
* libs\SDL2_mixer\x86_64-w64-mingw32\bin\*.dll (get everything)
* libs\libopenmpt\x86_64\bin\mingw\libopenmpt.dll
>>>>>>> 3b4187389 (make the thing compile, remove drmingw stuff from 64bit builds)
