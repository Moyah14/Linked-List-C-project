# Linked List (C++)

A minimal CMake-based C++ project implementing a singly linked list with insert/delete/display and simple tests in `main`.

## Build (Windows PowerShell, MSVC)

```powershell
# From the project root containing CMakeLists.txt
mkdir build
cd build
cmake -S .. -B .
cmake --build . --config Release
# Run
.\Release\LinkedList.exe
```

## Build (MinGW or Clang on Windows)

```powershell
mkdir build
cd build
cmake -G "MinGW Makefiles" -S .. -B .
cmake --build . --config Release
# Run
.\LinkedList.exe
```

## Source layout

- `src/main.cpp`: Linked list implementation and three test sets
- `CMakeLists.txt`: Build configuration

## Notes

- Requires CMake 3.20+ and a C++20 compiler.
- Edit `main.cpp` to add more tests or integrate into a larger project.
