# cmake-library
Template of CMake files to build a static or shared library under Windows and Linux

## Use cases

The goal of this template is to support the worst case.

There is a main library: `library`

Then two libraries depend on `library`: `library2`, `library3`.

And a final library `library4` that depends on `library2` and `library3`. It's a diamond dependency.

After, a simple executable `extern` is linked with `library4`.

![class diagram](doc/diagram.png)

## CMakeLists.txt

All interesting data in this POC are in CMakeLists.txt files in `library` folder. The other folders are just a clone of this folder to show that everything is well configured for the worst scenario.

You need to know the basics of CMake. The whole [official tutorial](https://cmake.org/cmake/help/latest/guide/tutorial/index.html) is perfect.

The content in C++ source files is very simple.

To know how to build this example, simply follow instruction in `.github\workflows\cmake.yml` file.

## Typical problems

When using shared library, you need to define symbol `library_Export` when building library and undefining it when linking the library. It's automatically done when calling `add_library` in `SHARED` mode.

Under Windows with shared library, you need to copy all libraries in the same folder than the executable. `TARGET_RUNTIME_DLLS` generator-expression will help.

Diamond dependency doesn't look to be a problem with this example.

Don't explicitly (on user side) depends on library when linking `library2` or `library3`. But you need to explicitly do it in `Config.cmake` file.