// #include <SDL.h>
// #include <SDL_image.h>
// #include <SDL_ttf.h>
// #include <iostream>

// using namespace std;

// int main(int argc, char *argv[]) {
//   if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
//     cout << "not working" << endl;
//   else
//     cout << "working" << endl;
//   return 0;
// }
/*
-l[linalg]
=> Links to shared library or shared object - Specifically, it links to
linalg.dll on Windows, liblinalg.so (on Unix-like oses like Linux, BSD, AIX, …)
or linalg.dylib on MacOSX. -L[/path/to/shared-libraries]
=> Add search path to shared libraries, directory containing *.so, *.dll or
*.dlyb files such as libLinearAlgebra.so depending on the current operating
system. -I[/path/to/header-files] Add search path to header files (.h) or
(.hpp). -D[FLAG] or -D[FLAG]=VALUE Pass preprocessor flag #if FLAG … check this
out for more details :
https://caiorss.github.io/C-Cpp-No


tes/compiler-flags-options.html
*/