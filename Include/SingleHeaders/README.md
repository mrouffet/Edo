# Edo Single Headers

_Edo Single Headers_ is a collection of [header-only](https://en.wikipedia.org/wiki/Header-only) files to be **easily** and **freely shared** and used across any projects.\
Each files are **individual** and can be **shared separately** of the others, however packing them together will allow cross-API use.

Following the [stb philosophy](https://github.com/nothings/stb), each library is composed of a **header part** by default, to be included anywhere to be used; and a **source part** to be declared into _exactly one_ C++ file to be compiled using the **library's macro** to be defined.

Example:
```cpp
// my_file1.hpp
#include <edo_debug.hpp>

// my_file2.hpp
#include <edo_debug.hpp>

// my_debug.cpp
#define EDO_DEBUG_IMPLEMENTATION
#include <edo_debug.hpp>
```


## edo_debug.hpp

_edo_debug.hpp_ offers simple, ready-to-use, and extensible tools for **logging** and **debugging** your application, such as:
- Log type
- [Log Levels](https://github.com/mrouffet/Edo/wiki/edo_debug.hpp#loglevel)
- [Log Channels](https://github.com/mrouffet/Edo/wiki/edo_debug.hpp#logchannel)
- [Output Stream interface](https://github.com/mrouffet/Edo/wiki/edo_debug.hpp#logstream) (extensible), with Console & File Stream already provided
- [Macros](https://github.com/mrouffet/Edo/wiki/edo_debug.hpp#macros) helper preprocessor to be used for easier integration

Links to the **official** [documentation](https://mrouffet.github.io/edo/edo_debug.hpp) and [wiki](https://github.com/mrouffet/Edo/wiki/edo_debug.hpp) for advanced details.

### Initialization
No initialization is required to have **simple** console logging, however, a **one-line** initialization will provide **advanced** console (colors) and file logging.\
```cpp
// No initialization

// OR

// Single-thread (thread-unsafe) logger.
// Console colors and file logging.
SA::Debug::InitDefaultLogger();
```
See [_Initialization_](https://github.com/mrouffet/Edo/wiki/edo_debug.hpp#initialization) for advanced implementation.

### EDO_LOG
Log **anything** converted as a string with default LogLevel, channel, and details.
```cpp
EDO_LOG(_str, _level = Normal, _channel = Default, _details = "");
```
Example:
```cpp
EDO_LOG("Hello, World!");
```
```
[18:44:14][0] {Normal - Default}   main.cpp:50 - int main()
Msg:    Hello, World!
```
See [_EDO_LOG_](https://github.com/mrouffet/Edo/wiki/edo_debug.hpp#edo_log) for more examples and advanced use.

### EDO_WARN / EDO_ERROR
Log a **warning**/**error** on **false predicate** with default channel and details.
```cpp
EDO_WARN(_pred, _channel = Default, _details = "", _postCmd);
EDO_ERROR(_pred, _channel = Default, _details = "", _postCmd);
```
Example:
```cpp
int myInt = 2;
EDO_WARN(myInt == 1, MyChannel, "myInt invalid: might cause issues");
EDO_ERROR(myInt == 1, MyChannel, "myInt invalid: possible crash");
```
```
[18:46:20][0] {Warning - MyChannel}        main.cpp:53 - int main()
Msg:    { myInt == 1 }  evaluated to false!
Dets:   myInt invalid: might cause issues

[18:46:20][0] {Error - MyChannel}        main.cpp:53 - int main()
Msg:    { myInt == 1 }  evaluated to false!
Dets:   myInt invalid: possible crash
```
See [_EDO_WARN_](https://github.com/mrouffet/Edo/wiki/edo_debug.hpp#edo_warn)/[_EDO_ERROR_](https://github.com/mrouffet/Edo/wiki/edo_debug.hpp#edo_error) for more examples and advanced use.

### EDO_ASSERT / EDO_THROW
**Assert** a log on **false predicate** with default channel and details.
```cpp
EDO_ASSERT(_pred, _channel = Default, _details = "", _postCmd);
EDO_THROW(_str, _channel = Default, _details = "");
```
Example:
```cpp
int myIndex = 7;
int minBound = 2;
int maxBound = 6;

SA_ASSERT((myIndex >= minBound && myIndex <= maxBound), MyTestChannel, "Access index out of bound!")
```
```
[18:49:22][0] {AssertFailure - MyTestChannel}      main.cpp:53 - int main()
Msg:    { (myIndex >= minBound && myIndex <= maxBound) }  evaluated to false!
Dets:   Access index out of bound!

terminate called after throwing an instance of 'edo::Log'
```
See [_EDO_ASSERT_](https://github.com/mrouffet/Edo/wiki/edo_debug.hpp#edo_assert)/[_EDO_THROW_](https://github.com/mrouffet/Edo/wiki/edo_debug.hpp#edo_throw) for more examples and advanced use.


## edo_maths.hpp


## edo_memory.hpp


## edo_event.hpp


## edo_thread.hpp


## edo_rhi.hpp


## edo_reflect.hpp



# Authors

**Maxime "mrouffet" ROUFFET** - main developer
