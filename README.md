# Max-SDK

The Traditional Max Software Development Kit contains the API (headers, source, libraries) for building external objects (plug-ins) in C or C++ for [Max](https://cycling74.com/products/max-features). It additionally includes documentation of the API, example projects, and CMake scripts for generating Xcode and Visual Studio project files.

The SDK is structured as a Max package. Simply place the SDK in your `Max 8/Packages` folder to begin working.

The repository contains one submodule, [max-sdk-base](https://github.com/Cycling74/max-sdk-base), that provides the low-level bindings to the Max application and CMake scripts for creating your own projects.

## Max 8.2 SDK Update

With the 8.2 update several aspects of the Max-SDK were changed in order to support Apple silicon and CMake project generation. For details on this change and steps to get started with CMake please see the [8.2 update readme](https://github.com/Cycling74/max-sdk/blob/main/README-8.2-update.md) or the [Max 8.2 SDK Update Overview](https://www.youtube.com/watch?v=il5WblTBUgs) video.

## C++ API

If you are interested in using Modern C++ to write external objects, please take a look at the [Min DevKit](https://github.com/Cycling74/min-devkit).

## Testing

It is highly recommended that you test your code thoroughly. One option is use the [max-test](https://github.com/Cycling74/max-test) package.

## Support
 
For support, please use the developer forums at:
http://cycling74.com/forums/
