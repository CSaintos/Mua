ToDo:
- NumberUtils should be a Number class that is its own library.
- I believe our Error class should use exceptions instead, but in such a way that doesn't halt the program.
- FIXME UnaPlus is not digit independent
- We can still further decouple the project (probably need to do some research on Dependency Inversion)
- Bugfix all issues in math.mua
- Bugfix orphan nodes
  - lhs_node didn't have parent. Also, don't set node's parent to this->parent, and then use the parent to setNode when in current node, as that will cause a dangling pointer to the current class and therefore undefined results.
