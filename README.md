# Repository for Data Structures in C++

## Dynamic Array
**Dynamic array** is a variable size linear data structure.

### Features 
- Supports arithematic, relational and assignment operator
- Supports stream insertion operation
- Supports negative indexing (*`darry[-1]` returns value of last element.*)
- Throws ***out of bound errors***.


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
DArray<int> arry(4);
cout << arry << endl;    // [ 0, 0, 0, 0 ] 
```
