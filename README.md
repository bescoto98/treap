> Brenda Escoto; 
> escot105@mail.chapman.edu

Files:
  - main.cpp
  - Treap.cpp
  - Treap.h
  

Resources:
  R. Seidel, C. Aragon. “Randomized Search Trees.” (1989)
  
  https://www.geeksforgeeks.org/treap-set-2-implementation-of-search-and-delete/
  

> General information about to implement the operations for the data structure.

Final project called for the implementation of a non-trivial algorithm. 

A treap is a data structure that is formed from the union of a binary search tree and a max-heap Cartesian tree. Each node has a value that follows the rule of one of these structures, which leads to the overall structure being more balanced than either of them on their own. Functions preformed by the structure in order to access a node, insert a node, or remove a node follow the general procedures of a binary search tree, with heap priority violations being fixed by one or more rotations along the “branch” of a treap. Treaps are useful data structures for cases when the data inserted into the structure has a high chance of not being random, a case in which the performance of a binary search tree would degrade. 
