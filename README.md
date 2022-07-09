# CitOLCCore

Download the toolchain.

```shell
$ wget https://raw.githubusercontent.com/leetal/ios-cmake/master/ios.toolchain.cmake
```

## Include settings ##

Since we are including a C++ library we need to add the include paths to the headers we are going to use. This is done in the consuming library via `XCode`. Typically by clicking the project -> Build Settings -> Header Search Paths. You should add the path to the Tolc generated header for both Debug and Release.

## Link settings ##

Since we are linking C++ code we need to add the link flag `-lc++`. This is done in the consuming library via `XCode`. Typically by clicking the project -> Build Settings -> Other Linker Flags. You should add the line `-lc++` for both Debug and Release.

If not the above:

```shell
Undefined symbols for architecture x86_64:
  "___cxa_begin_catch", referenced from:
  ___clang_call_terminate in libcitOLCCore.a(citOLCCore.o)
  "operator delete(void*)", referenced from:
  +[citOLCCore(f_citOLCCore_getOLC) getOLC:] in libcitOLCCore.a(citOLCCore_objc.o)
  "___gxx_personality_v0", referenced from:
  Tolc_::convertBaseStringToCpp(NSString*) in libcitOLCCore.a(citOLCCore_objc.o)
  +[citOLCCore(f_citOLCCore_getOLC) getOLC:] in libcitOLCCore.a(citOLCCore_objc.o)
  getOLC(std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> > const&) in libcitOLCCore.a(citOLCCore.o)
  "std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >::compare(unsigned long, unsigned long, char const*, unsigned long) const", referenced from:
  getOLC(std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> > const&) in libcitOLCCore.a(citOLCCore.o)
  "operator new(unsigned long)", referenced from:
  Tolc_::convertBaseStringToCpp(NSString*) in libcitOLCCore.a(citOLCCore_objc.o)
  "std::terminate()", referenced from:
  ___clang_call_terminate in libcitOLCCore.a(citOLCCore.o)
  "std::__1::__basic_string_common<true>::__throw_length_error() const", referenced from:
  Tolc_::convertBaseStringToCpp(NSString*) in libcitOLCCore.a(citOLCCore_objc.o)
ld: symbol(s) not found for architecture x86_64
clang: error: linker command failed with exit code 1 (use -v to see invocation)
```

### Linking static libraries ###

We have two static libraries: `citOLCCore` written in `C++` and its dependent library `citOLCCore_objc` written in `Objective-C`. If you just add `citOLCCore_objc` to your iOS app, you will get a link error like;

```shell
Undefined symbols for architecture x86_64:
  getOLC(std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> > const&)
```

Corresponding to the `C++` function

```cpp
std::string getOLC(std::string const &city);
```

It is of course available in the other static library:

```shell
$ nm --demangle build/citOLCCore.build/Release-iphonesimulator/citOLCCore.build/Objects-normal/x86_64/citOLCCore.o
...
0000000000000000 T getOLC(std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> > const&)
...
```

You can solve this by simply appending the two libraries with `libtool`:

```shell
$ libtool -static -o libcitOLCCore.a path/to/objc/libcitOLCCore.a path/to/cpp/libcitOLCCore.a
```

Then you have the combined `libcitOLCCore.a` that you can simply drag and drop in XCode.



