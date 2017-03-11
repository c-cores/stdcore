# The Standard Core

Welcome to the Standard Core. This is a library for standard containers and their associated algorithms.

For thorough documentation, check out the [wiki](https://github.com/nbingham1/stdcore/wiki).

# Why does this exist?

I've been working with C++ for over a decade at this point. Every now and then, I would need to do something that the C++ Standard Library couldn't do. So I would make the necessary thing and move on. After a while, I noticed that I had managed to implement a full standard library scattered throughout my code base. So, I pulled it all together into a library, and well... here we are.

## Why should I care?

Quite by accident, this library is an interesting case study of a different programming paradigm. I make no claims that this code is optimized, verified, secured, or stabilized. It is provided as is with no guarantee and no promises. However, the resulting API is simple, clean, and expressive. So let's get started.

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

This library differs from the C++ Standard Library on a few key paradigms. It is these paradigms that make this library unique.

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
cout << "arr = " << arr << endl << endl;

cout << "arr.at(5).pop(3) = " << arr.at(5).pop(3) << endl;
cout << "arr = " << arr << endl << endl;

cout << "arr.at(2).push(3)" << endl;
arr.at(2).push(3);
cout << "arr = " << arr << endl << endl;

cout << "arr.at(3).append(range<int>(2, 8))" << endl;
arr.at(3).append(range<int>(2, 8));
cout << "arr = " << arr << endl << endl;

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
cout << "arr = " << arr << endl << endl;

slice<range<array<int>::iterator> > slc = arr.sub(2, 6);
cout << "slc = " << slc << endl << endl;

cout << "slc[1] = 100" << endl;
slc[1] = 100;
cout << "slc = " << slc << endl;
cout << "arr = " << arr << endl << endl;

slice<array<array<int>::iterator> > slc2 = array<int>::values(4, 2, 5, 0, 1).sample(arr);
cout << "slc2 = " << slc2 << endl << endl;

cout << "slc2[1] = 200" << endl;
slc2[1] = 200;
cout << "slc2 = " << slc2 << endl;
cout << "arr = " << arr << endl;
cout << "slc = " << slc << endl;
```

```
arr = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}

slc = {2, 3, 4, 5}

slc[1] = 100
slc = {2, 100, 4, 5}
arr = {0, 1, 2, 100, 4, 5, 6, 7, 8, 9}

slc2 = {2, 5, 0, 1}

slc2[1] = 200
slc2 = {2, 200, 0, 1}
arr = {0, 1, 2, 100, 4, 200, 6, 7, 8, 9}
slc = {2, 100, 4, 200}
```

## Simplicity Breeds Sanity

All algorithmic functions like sort, unique, reverse, etc can be run either in place or on a copy of the container in line.

```c++
array<int> arr = array<int>::values(10, 2, 6, 3, 2, 7, 3, 7, 5, 1, 0);
cout << "arr = " << arr << endl << endl;

cout << "sort_quick(arr) = " << sort_quick(arr) << endl;
cout << "arr = " << arr << endl << endl;

cout << "sort_quick_inplace(arr)" << endl;
sort_quick_inplace(arr);
cout << "arr = " << arr << endl;
```

```
arr = {2, 6, 3, 2, 7, 3, 7, 5, 1, 0}

sort_quick(arr) = {0, 1, 2, 2, 3, 3, 5, 6, 7, 7}
arr = {2, 6, 3, 2, 7, 3, 7, 5, 1, 0}

sort_quick_inplace(arr)
arr = {0, 1, 2, 2, 3, 3, 5, 6, 7, 7}
```

## Logging Hastens Deforestation

Finally, there are multiple stream interfaces provided for different logging purposes and its easy to create more.

```c++
ascii_stream cself(stdout, "\n", "Look at me", true);
cout << "Hello World!" << endl;
cnote << "World is asleep." << endl;
cwarn << "Do not wake world." << endl;
cerr << "World awoken." << endl;
cfate << "World floats away." << endl;
cself << "SPACE!" << endl;
```

```
Hello World!
note: World is asleep.
warning: Do not wake world.
error: World awoken.
example.cpp:13: fatal: World floats away.
example.cpp:14: Look at me: SPACE!
``` 
