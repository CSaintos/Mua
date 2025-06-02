ToDo:
- NumberUtils should be a Number class that is its own library.
- I believe our Error class should use exceptions instead, but in such a way that doesn't halt the program.
- FIXME UnaPlus is not digit independent
- We can still further decouple the project (probably need to do some research on Dependency Inversion)
- On MacOS release, make sure to allow permissions on each lib and exe.
- On Both MacOS and Linux, add the -rpath option during linking. 
