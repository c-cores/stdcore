Core
====

A library of core structures

I got fed up with the inability to extend the functionality of the standard libraries and their clumsy API for algorithms. Over the years, I've been creating these structures for various projects and now I've pulled them together into one place.

They aren't exactly well tested because they've been constantly evolving, but they do the job.

This library provides two primary containers: a linked list structure called list, and a dynamically allocated array structure called array. The containers are designed so that insertion and deletion are actually handled by the iterator, however there are also functions for insertion and deletion in the main structure that references back to these iterators. Algorithms are applied on what is called a bound which consists of two iterators: one that points to the first value in the container, and one that points to the last value in the container. However, these algorithms are templated in such a way that you can just call the algorithm on the container as a whole and it will automatically grab the bound.
As an extension of list, a very minimal map container is also provided, and as an extension of array a string implementation is also provided.

This also provides a cleaner file interface and extends it to the standard input, output, and error file streams. Lastly, there is a very strange reference implementation that happens to be useful for a particular matrix implementation.

