ToDo:
- NumberUtils should be a Number class that is its own library.
- I believe our Error class should use exceptions instead, but in such a way that doesn't halt the program.
- FIXME UnaPlus is not digit independent
- We can still further decouple the project (probably need to do some research on Dependency Inversion)
- Replace node building move calls with methods for building nodes.
- Bugfix all issues in math.mua
- When setting context, its redundant to set the node's state context to itself passing in a pointer of itself.
