# Laboratory Work №1: Creating Classes in C++

## 📌 Overview
* **Topic:** Basic capabilities of C++ for creating and using classes.
* **Variant:** №41 — "Queue of Numbers".
* **Objective:** To implement a dynamic queue using a linked list structure without utilizing standard containers (STL).

## 🛠 Class Interface (`Queue`)
The class is designed with strict adherence to the provided guidelines:

### Data Members
* `head`: Pointer to the beginning of the queue.
* `tail`: Pointer to the end of the queue.
* `size`: Current number of elements.

### Key Methods
* **Constructors**: Default, parametric, copy, and move.
* **Destructor**: Ensures proper deallocation of dynamic memory.
* **Enqueue(int)**: Adds an element to the end of the queue.
* **Dequeue()**: Reads and removes the front element.
* **Peek()**: Reads the front element without removal.
* **IsEqual(Queue)**: Compares two queues for equality.
* **Print() / Input()**: Console I/O operations.

## ⚖️ Implementation Rules
* **Memory Management**: Manual allocation/deallocation via `new` and `delete`.
* **Encapsulation**: All data members are `private`.
* **Naming Convention**: Methods start with `Uppercase`, data members with `lowercase`.
* **No STL**: Only primitive types and custom `Node` structures are used.
