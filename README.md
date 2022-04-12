# Max-SDK

The Traditional Max Software Development Kit contains the API (headers, source, libraries) for building external objects (plug-ins) in C or C++ for [Max](https://cycling74.com/products/max-features). It additionally includes documentation of the API, example projects, and CMake scripts for generating Xcode and Visual Studio project files.

The repository contains one submodule, [max-sdk-base](https://github.com/Cycling74/max-sdk-base), that provides the low-level bindings to the Max application and CMake scripts for creating your own projects.

## Building

0. Clone the *max-sdk* from Github or download the [latest release](https://github.com/Cycling74/max-sdk/releases/latest). If you clone it from Github, **you should clone it into Max's Packages folder**. If you clone it elsewhere you will need to make an alias to it in your Packages folder.
   The *Packages* folder can be found inside of your *Max 8* folder which is inside of your user's *Documents* folder.
   Make sure you clone recursively so that all sub-modules are properly initiated : `git clone https://github.com/Cycling74/max-sdk.git --recursive`
1. In the Terminal or Console app of your choice, change directories (cd) into the max-sdk folder you cloned/installed in step 0.
2. `mkdir build` to create a folder with your various build files
3. `cd build` to put yourself into that folder
4. Now you can generate the projects for your choosen build environment:

### Mac 

Run `cmake -G Xcode ..`

Next run `cmake --build .` or open the Xcode project from this "build" folder and use the GUI.

Note: you can add the `-j4` option where "4" is the number of cores to use.  This can help to speed up your builds, though sometimes the error output is interleaved in such a way as to make troubleshooting more difficult.

If you are running on a Mac M1 machine, you will likely see an error `cannot be loaded due to system security policy` when loading your externals in Max. To resolve this, you can ad-hoc codesign your external with `codesign --force --deep -s - myobject.mxo`.

### Windows

You can run `cmake --help` to get a list of the options available.  Assuming some version of Visual Studio 2019, the commands to generate the projects will look like this: 

`cmake -G "Visual Studio 16 2019" ..`

Or using Visual Studio 2017 it will look like this:

`cmake -G "Visual Studio 15 2017 Win64" ..`

Having generated the projects, you can now build by opening the .sln file in the build folder with the Visual Studio app (just double-click the .sln file) or you can build on the command line like this:

`cmake --build . --config Release`

## Max 8.2 SDK Update

With the 8.2 update several aspects of the Max-SDK were changed in order to support Apple silicon and CMake project generation. For details on this change and steps to get started with CMake please see the [8.2 update readme](https://github.com/Cycling74/max-sdk/blob/main/README-8.2-update.md) or the [Max 8.2 SDK Update Overview](https://www.youtube.com/watch?v=il5WblTBUgs) video.

## C++ API

If you are interested in using Modern C++ to write external objects, please take a look at the [Min DevKit](https://github.com/Cycling74/min-devkit).

## Testing

It is highly recommended that you test your code thoroughly. One option is use the [max-test](https://github.com/Cycling74/max-test) package.

## Support
 
For support, please use the developer forums at:
http://cycling74.com/forums/
