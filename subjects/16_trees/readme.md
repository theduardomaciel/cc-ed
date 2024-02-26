# Trees

### The structure of Trees

- At most one predecessor but many successors
- Root has no predecessor
- Every position except the root has exactly one predecessor
- Every position except the root has the root as a (perhaps not immediate) predecessor

### Definitions

Let T be a tree, and let n and m be nodes of T...

1. n and m are `siblings` if they have the same parent
2. A node is a `leaf` of T if it has no children
3. A node is an `internal node` if it is not a leaf
4. An `edge` of T connects two nodes (parent and child)
5. A `path` in T is a collection of edges that join two nodes; the `length` of a path consists of the number of edges in the path
6. The height of a node is the length of the longest path from the node to a leaf
7. The depth of a node is the length of the path from that node to the root
8. The height of a tree T is the height of the root, namely, the length of the longest path from the root to a leaf
9. A subtree S, of T rooted at n is a tree that is made from T by considering n to be the root of S and including all S descendants of n

## Binary Tree

### Definition

A binary tree consists of either:

- Nothing at all (empty tree) or
- A node (called root) of the binary tree along with a leI subtree and a right subtree, both of which are binary trees

Each node can have the following degrees:

- Zero (no children)
- One
- Two

### Strictly Binary Tree

Is a tree in which every node other than the leaves has two children. Each node has degree zero or two

### Complete Binary Tree

If all leaves of a strictly binary tree are at the same depth
