# Repository for Data Structures in C++

## Dynamic Array
**Dynamic array** is a variable size linear data structure.

### Features 
- Supports arithematic, relational and assignment operator
- Supports stream insertion operation
- Supports negative indexing (*`darry[-1]` returns value of last element.*)
- Throws ***out of bound errors***.
- Supports Iterators.


### Methods

| Name | Description |
| :-: | - |
| `push()` | Pushes an element at back of the array. |
| `pop()` | Pops the last elemnt out of array. |
| `extend()` | Push multiple elements at back using an array.|
| `length()` | Length of array. |
| `capacity()` | Capacity of array. |

### Example

```c++
DArray<int> arry(4), arry2(3, 99), arry3(arry2);
std::cout << arry << std::endl;    // [ 0, 0, 0, 0 ]
std::cout << arry2 << std::endl;    // [ 99, 99, 99 ]
std::cout << arry3 << std::endl;    // [ 99, 99, 99 ]
```

Negative Indexing:

```c++
DArray<int> arry(3);
arry[-1] = 42;
std::cout << arry << std::endl;  // [ 0, 0, 42 ]
```

Supports Iterators:

```c++
DArray<int> arry(5, 42);
for (auto itr = arry.begin(); itr != arry.end(); itr++) {
    *itr = 2;
}
for (auto e : arry) {
    std::cout << e << " "; 
}
// Output: 2 2 2 2 2
```