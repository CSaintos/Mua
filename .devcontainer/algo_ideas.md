## Extract Powers
- The purpose of the algorithm is to extract powers, and restructure the parse tree using those powers.
  - Perhaps the second part of the algorithm can be put into another method, for cohesion.
> asterisk and fslash nodes shall just be known as product nodes
> bin_plus and bin_minus nodes shall just be known as sum nodes
- Begins by taking in a product node.
- It must create a container (not sure what data structure it should be yet) for storing powers
- Must use a tree walking algorithm, or perhaps BFS/DFS algorithm, more thought on this later.
- It checks it's left and right children.
  - If the child is a value node, this is a power, store it in container.
  - If the child is a product node, then it must continue to walk the tree through this product node
  - If the child is a caret node, this is a power, store it in container.
  - If the child is a sum node. this is a dead end. do not store in container.
  - ... must see other nodes possible such as paren nodes
- After collecting all powers, it must sort them by type.
  - There are three categories of types of powers:
    - powers with the same base only
    - powers with the same exponent only
    - powers with both same base and same exponent
- After sorting through the container of powers, it must restructure the tree using the sorted container of powers to group together powers which are of the same type.

