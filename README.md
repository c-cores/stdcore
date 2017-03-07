# The Standard Core

Welcome to the Standard Core. This is a library for standard containers and their associated algorithms. It was created in response to perceived shortcomings of the C++ Standard Library's API. I make no claims that this code is optimized, verified, secured, or stabilized. It is provided as is with no guarantee and no promises. However, it is simpler, cleaner, and more expressive. So let's get started.

# Linking

Lets start with a basic program which will include the array header. Every header in this library is found in the `std` directory. Every structure and function are contained within the `core` namespace.

```c++
#include <std/array.h>

using namespace core;

int main()
{
    return 0;
}
```

This can be compiled with the following command.

```
g++ example.cpp -Ipath/to/include -Lpath/to/lib -lstdcore -o example
```

# Paradigms

This library differs from the C++ Standard Library on a few key paradigms. It's these paradigms that make it this library unique.

## The Simple Things in Life

First, while the typical array, list, map, and string containers are still the center of the library, there are also dedicated containers for simpler data. This means fill, range, and sparse_range.

```c++
cout << "fill = " << fill<int>(7, 5) << endl;
cout << "range = " << range<int>(5, 15) << endl;
cout << "sparse_range = " << sparse_range<int>(5, 25, 2) << endl;
```

```
fill = {5, 5, 5, 5, 5, 5, 5}
range = {5, 6, 7, 8, 9, 10, 11, 12, 13, 14}
sparse_range = {5, 7, 9, 11, 13, 15, 17, 19, 21, 23}
```

## Power to the Iterator

Second, iterators have full power to modify their base structure. This means that iterators can push, pop, drop, replace, append, and swap. These actions can still invalidate other iterators depending upon the container structure.

```c++
array<int> arr = range<int>(0, 10);
cout << "arr = " << arr << endl;
cout << "arr.at(5).pop(3) = " << arr.at(5).pop(3) << endl;
cout << "arr = " << arr << endl;
cout << "arr.at(2).push(3)" << endl;
arr.at(2).push(3);
cout << "arr = " << arr << endl;
cout << "arr.at(3).append(range<int>(2, 8))" << endl;
arr.at(3).append(range<int>(2, 8));
cout << "arr = " << arr << endl;
cout << "arr.at(4).replace(3, 10)" << endl;
arr.at(4).replace(3, 10);
cout << "arr = " << arr << endl;
```

```
arr = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}
arr.at(5).pop(3) = {5, 6, 7}
arr = {0, 1, 2, 3, 4, 8, 9}
arr.at(2).push(3)
arr = {0, 1, 3, 2, 3, 4, 8, 9}
arr.at(3).append(range<int>(2, 8))
arr = {0, 1, 3, 2, 3, 4, 5, 6, 7, 2, 3, 4, 8, 9}
arr.at(4).replace(3, 10)
arr = {0, 1, 3, 2, 10, 6, 7, 2, 3, 4, 8, 9}
```

## Slice and Dice

Third, this has a full implementation of slices. You can use any container to slice another container. These slices make the API significantly cleaner and easier to use while introducing very little run-time overhead. 

```c++
array<int> arr = range<int>(0, 10);
cout << "arr = " << arr << endl;
slice<range<array<int>::iterator> > slc = arr.sub(2, 6);
cout << "slc = " << slc << endl;
slc[1] = 100;
cout << "slc = " << slc << endl;
cout << "arr = " << arr << endl;
slice<array<array<int>::iterator> > slc2 = array<int>::values(4, 2, 5, 0, 1).sample(arr);
cout << "slc2 = " << slc2 << endl;
slc2[1] = 200;
cout << "slc2 = " << slc2 << endl;
cout << "arr = " << arr << endl;
cout << "slc = " << slc << endl;
```

```
arr = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}
slc = {2, 3, 4, 5}
slc = {2, 100, 4, 5}
arr = {0, 1, 2, 100, 4, 5, 6, 7, 8, 9}
slc2 = {2, 5, 0, 1}
slc2 = {2, 200, 0, 1}
arr = {0, 1, 2, 100, 4, 200, 6, 7, 8, 9}
slc = {2, 100, 4, 200}
```

## Simplicity Breeds Sanity

Finally, all algorithmic functions like sort, unique, reverse, etc can be run either in place or on a copy of the container in line.

```c++
array<int> arr = array<int>::values(10, 2, 6, 3, 2, 7, 3, 7, 5, 1, 0);
cout << "arr = " << arr << endl;
cout << "sort_quick(arr) = " << sort_quick(arr) << endl;
cout << "arr = " << arr << endl;
sort_quick_inplace(arr);
cout << "arr = " << arr << endl;
```

```
arr = {2, 6, 3, 2, 7, 3, 7, 5, 1, 0}
sort_quick(arr) = {0, 1, 2, 2, 3, 3, 5, 6, 7, 7}
arr = {2, 6, 3, 2, 7, 3, 7, 5, 1, 0}
arr = {0, 1, 2, 2, 3, 3, 5, 6, 7, 7}
```
