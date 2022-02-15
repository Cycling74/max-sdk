# SDK 8.2 update readme

## Relevant Repositories
- [max-sdk-base](https://github.com/Cycling74/max-sdk-base)
- [max-sdk](https://github.com/Cycling74/max-sdk)
- [min-api](https://github.com/Cycling74/min-api)
- [min-devkit](https://github.com/Cycling74/min-devkit)

## Motivations

-   Apple silicon external development support
    -   Allow third-parties to compile externals which run natively on Apple silicon

-   CMake support in **max-sdk**
    -   Modernize build system and remove platform-specific projects

-   Integration of base headers and libs in **min-api** and **max-sdk**
    -   Eliminate the divergence in base headers when developing in Min vs. the traditional Max SDK


## Technical Changes

### Restructuring of submodules

-   A new **max-sdk-base** repo containing minimally required headers, libs, and CMake scripts
    -   **max-sdk** has **max-sdk-base** as a submodule
    -   **min-api** replaces **max-api** with **max-sdk-base**

-   Branch renaming of **max-sdk**, **min-api**, **min-devkit** (master --> main)

### CMake support in Max SDK

-   Xcode and Visual Studio project files have been removed from the repo.
-   CMake is required to generate project files on any platform (see below).

### Base headers and libs changes

-  **max-sdk-base** support for C++ namespaces and replacement of some defines with enums (may be of interest to developers looking for better C++ compatibility without requiring the use of Min, and will serve as the replacement for **max-api** in that regard)

## How to Update

Requirements:

-   CMake (\>=3.19)

A [video](https://www.youtube.com/watch?v=il5WblTBUgs) walk-through is also available.

### 1. Switch submodule branches from master to main

To switch branches from master to main from the command line:
```
git branch -m master main
git fetch origin
git branch -u origin/main main
git remote set-head origin -a
```


### 2. Update all submodules

`git submodule update --init --recursive` (since these are newly added submodules the `--init` flag is required)

When updating **min-api**, the old submodules may or may not get removed. If not, simply remove either **max-api** and/or **max-sdk** folders from inside the **min-api** folder.

### 3. Using CMake to generate projects

Install CMake if it's not already on your computer. On macOS, we recommend Homebrew: [https://brew.sh/](https://brew.sh/index_de). On Windows, either download from <http://cmake.org>, or install it as part of your Terminal environment (such as `mingw64` or the Git bash console).

Navigate to your SDK folder in the Terminal e.g.:
```
cd ~/max-sdk
```

Make a directory called build and navigate to that directory

```
mkdir build && cd build
```

Build the projects on Mac:

```
cmake -G Xcode ..
```

*Note:* If you are running on a Mac M1 machine, you will likely see an error `cannot be loaded due to system security policy` when loading your externals in Max. To resolve this, you can ad-hoc codesign your external with `codesign --force --deep -s - myobject.mxo`.


Build the projects on Windows (adjust for your version of Visual Studio, or omit for default):

```
cmake -G "Visual Studio 16 2019" ..
```


Open the generated project files and build from your IDE.


## How to Support Apple Silicon

Requirements:

-   Xcode 12 and MacOS \>= 10.15 (Catalina)

To support Apple silicon in your projects, simply add the following line to your base CMakeLists.txt file:

```
set(CMAKE_OSX_ARCHITECTURES x86_64;arm64)
```

Alternatively use the following CMake flag:

```
cmake "-DCMAKE_OSX_ARCHITECTURES=x86_64;arm64"
```

This will build Fat externals, supporting both Intel and Apple silicon machines.

For support, please use the developer forums at: <http://cycling74.com/forums/>.
