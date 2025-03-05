ToDo:
NumberUtils should be a Number class that is its own library.
Turn static libraries into dynamic libraries (this will require having postbuildcmds).
In some shape or form we need to reduce the decoupling such that I can get real threaded builds.
I believe our Error class should use exceptions instead, but in such a way that doesn't halt the program.
FIXME UnaPlus is not digit independent
