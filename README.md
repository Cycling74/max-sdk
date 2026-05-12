# Max-SDK

The Max Software Development Kit (SDK) contains the headers, source, and
libraries for building external objects (plug-ins) in C or C++ for
[Max](https://cycling74.com/products/max-features). It additionally includes
documentation of the API, example projects, and CMake scripts for generating
Xcode and Visual Studio project files.

The Max SDK depends on [max-sdk-base](https://github.com/Cycling74/max-sdk-base),
which provides the low-level bindings to the Max application and CMake scripts
for creating your own projects. This dependency is fetched automatically by
CMake at configure time.

## CMake

The Max SDK uses [CMake](https://cmake.org) to generate Xcode and Visual Studio
project files. CMake replaced the `.xcodeproj` and `.sln` files that previously
shipped in the repo. The change was driven by the need to support Apple silicon
in Max 8.2. You still open Xcode or Visual Studio to build; CMake is the
one-time step that generates those project files. There is an
[overview video](https://www.youtube.com/watch?v=il5WblTBUgs) which walks through
the updates for supporting Max 8.2, and a [legacy guide](https://github.com/Cycling74/max-sdk/blob/3d808d9/README-8.2-update.md)
for those migrating from pre-8.2 projects.

### Building

Pre-requisites:
  - CMake version >= 3.25
  - Xcode (macOS) or Visual Studio (Windows)
  - Clone or download `max-sdk` from GitHub and put it in your Max Package
    folder or somewhere on Max's [search path](https://docs.cycling74.com/userguide/search_path/).

#### 1. Create a build directory to store build artifacts and IDE files

```shell
mkdir build
cd build
```

#### 2. Generate the projects

You can run `cmake --help` to get a list of generators available for your
platform. On macOS, the typical choice is Xcode, and on Windows, it is usually
Visual Studio.

On macOS:
```shell
cmake -G Xcode ..
```

> Note: you can add the `-j4` option to `cmake` where "4" is the number of
> cores to use. This can help to speed up your builds, though sometimes the
> error output is interleaved in such a way as to make troubleshooting more
> difficult.


On Windows:
```shell
cmake -G "Visual Studio 17 2022" ..
```

#### 3. Build the projects

You can open the IDE projects and build from the Xcode or Visual Studio
interface.

Alternatively, you can build from the command line, passing `cmake` the path to
the `/build` directory after `--build`.

```shell
cmake --build . --config Debug
cmake --build . --config Release
```

Note: If you are running on a Mac with Apple silicon, you may see an error
`cannot be loaded due to system security policy` when loading your externals in
Max. To resolve this, you can ad-hoc codesign your external with
`codesign --force --deep -s - myobject.mxo`.

### Writing an external's CMakeLists.txt

Each external has its own `CMakeLists.txt`. The minimal form looks like this:

```cmake
set_property(DIRECTORY PROPERTY max::external YES)
set_property(DIRECTORY PROPERTY max::glob ON)
project(myexternal)
```

- `max::external YES` tells the SDK build machinery to treat this directory as
  a Max external.
- `max::glob ON` automatically includes all `.c` and `.cpp` files in the
  directory as source files.
- `project(myexternal)` names the external and triggers target creation. The
  output will be `myexternal.mxo` (macOS) or `myexternal.mxe64` (Windows).

If you want explicit control over which files are compiled, omit `max::glob` and
list them yourself after `project()`:

```cmake
set_property(DIRECTORY PROPERTY max::external YES)
project(myexternal)

target_sources(myexternal PRIVATE myexternal.cpp helper.cpp)
```

After `project()`, the target named `${PROJECT_NAME}` exists and can be
customized with standard CMake commands such as `target_link_libraries`,
`target_include_directories`, and `target_compile_definitions`.

## C++ API

If you are interested in using Modern C++ to write external objects, please
take a look at the [Min DevKit](https://github.com/Cycling74/min-devkit).

## Testing

It is highly recommended that you test your code thoroughly. One option is use
the [max-test](https://github.com/Cycling74/max-test) package.

## Support
 
For support, please use the developer forums at:
http://cycling74.com/forums/
