# Operator Overloading — Lab 2
**Discipline:** Object-Oriented Programming  
**Variant:** No. 25  
**Student:** Mykyta Kuzminov  
**Group:** ІТШІ-25-1

## Objective
Study of the features of operator overloading in C++.

## Tasks
Design and implement a "Sparse Vector in Multidimensional Space" class based on a dynamic linked list.

Class data: vector dimension, pointer to a dynamic linked list of non-zero vector coordinates.

Required operators:
- Addition and subtraction of vectors
- Multiplication of a vector by a scalar
- Dot product of two vectors
- Element access via `[]`
- Console input and output via `>>` and `<<`
- Equality and inequality comparison via `==` and `!=`
- Type conversion to `double*`
- Copy and move assignment operators

## Results

<img src="https://github.com/user-attachments/assets/300f0f3a-a2ed-41ff-9413-f22fe3e3cb11" />

*Figure 2.1 – Basic SparseVector tests*

<br>

<img src="https://github.com/user-attachments/assets/c81ce70f-d9e3-4141-b3ad-7ccd72fbf1b5" />

*Figure 2.2 – Basic SparseVector tests*

<br>

<img src="https://github.com/user-attachments/assets/321d094e-a20f-474a-bda9-8b97b6f31565" />

*Figure 2.3 – Basic SparseVector tests*

## Conclusion
During this laboratory work, a SparseVector class was implemented with all required operators and constructors as defined in the task. A destructor was implemented to properly deallocate all nodes of the linked list. The sparse representation allows efficient storage of high-dimensional vectors where most coordinates are zero.
