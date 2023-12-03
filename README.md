# SDP_2023
Ocean Blue™'s submission for the 2023 OSU FEH Software Design Project

## Compilation Instructions
To compile this project, MinGW must have been installed using MSYS2 (as per the Visual Studio Code installation instructions in Carmen). Without this, you will be unable find windows API headers, link against Windows DLLs, or both.
As it relies on Windows APIs, this project can only be compiled and run on Windows. Finally, the provided Makefiles **_must_** be used to compile this project; trying to compile this repository's source code
using the default simulator template will produce errors.
If you are still unable to compile, a version without sound and which doesn't use Windows libraries can be found in the `silent` branch.

Once compiled, the resulting `game.exe` executable should be kept in the same parent directory as all the asset directories (images, sounds, and stats).
