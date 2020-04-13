# OS-assignments
Assignments for Operating System course in Athens University of Economics and Business


For convenience this project should run both on Windows, Mac and Linux based systems.

## Windows (Visual Studio)

Since pthreads are not available on windows, we use the pthread-win32 library.
Visual Studio is required (newer version should be supported, however development was done on VS 2015)

To create the projects run:

```bash
vendor/premake5.exe vs20xx
```

This should create the project files for Visual Studio. You can build it with Visual Studio.


## Linux/Mac/Windows(cygwin)

Uses the original pthread library

To create GNU make files run:
```bash
vendor/premake5_{your_os}_{your_architecture} gmake2
```

After the make files are created, run 
```bash
make
```
to build the project.

In order to build the optimized version run
```bash
make config=release
```

### Executable directory

The executable is in bin/{config}-{os}/
