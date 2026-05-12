# Max-SDK

The Max Software Development Kit (SDK) contains the headers, source, and
libraries for building external objects (plug-ins) in C or C++ for
[Max](https://cycling74.com/products/max-features). It additionally includes
documentation of the API, example projects, and CMake scripts for generating
Xcode and Visual Studio project files.

The Max SDK depends on [max-sdk-base](https://github.com/Cycling74/max-sdk-base),
which provides thelow-level bindings to the Max application and CMake scripts
for creating your own projects. This dependency is fetched automatically by
CMake.

## Building

Pre-requisites:
  - CMake version >= 3.25
  - Xcode (macOS) or Visual Studio (Windows)
  - Clone or download `max-sdk` from GitHub and put it in your Max Package
    folder or somewhere on Max's [search path](https://docs.cycling74.com/userguide/search_path/).

### 1. Create a build directory to store build artifacts and IDE files

```shell
# From inside the `max-sdk` directory, create and enter a build directory
mkdir build
cd build
```

### 2. Generate the projects

You can run `cmake --help` to get a list of generators available for your
platform. On macOS, the typical choice is Xcode, and on Windows, it is usually
Visual Studio.

Then, run the CMake generation step to configure your build.

On macOS:
```shell
cmake -G Xcode ..
```

Note: you can add the `-j4` option to `cmake` where "4" is the number of cores
to use. This can help to speed up your builds, though sometimes the error
output is interleaved in such a way as to make troubleshooting more difficult.

On Windows:
```shell
cmake -G "Visual Studio 17 2022" ..
```

### 3. Build the projects

You can open the IDE projects and build from Xcode/Visual Studio interface.

Alternatively, you can build from the command line, passing `cmake` the path to
the `/build` directory after `--build`.

Debug:
```shell
cmake --build . --config Debug
```

Release:
```shell
cmake --build . --config Release
```

Note: If you are running on a Mac with Apple silicon, you may see an error
`cannot be loaded due to system security policy` when loading your externals in
Max. To resolve this, you can ad-hoc codesign your external with
`codesign --force --deep -s - myobject.mxo`.


## Max 8.2 SDK Update

With the 8.2 update several aspects of the Max-SDK were changed in order to
support Apple silicon and CMake project generation. For details on this change
and steps to get started with CMake please see the
[8.2 update readme](https://github.com/Cycling74/max-sdk/blob/main/README-8.2-update.md) or
the [Max 8.2 SDK Update Overview](https://www.youtube.com/watch?v=il5WblTBUgs)
video.

## C++ API

If you are interested in using Modern C++ to write external objects, please
take a look at the [Min DevKit](https://github.com/Cycling74/min-devkit).

## Testing

It is highly recommended that you test your code thoroughly. One option is use
the [max-test](https://github.com/Cycling74/max-test) package.

## Support
 
For support, please use the developer forums at:
http://cycling74.com/forums/
