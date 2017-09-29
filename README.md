# Indexer

Assignment 3: by Paulo Garcia and Roel Ronquillo

Objective:
Given a file with a list of words, Count the occurances within other files, if they appear at all, inside a given directory.

Design:
Indexer is made up of two types of linked list structures. The first linked-list structure contains words
sorted in alphabetical order. The second list structure is one of a file structure, that contains a file name
and a sorted list of words that are contained within the file.

The indexer works by traversing the first list of all the words, and counting the occurrences in every file
node within the second list. If the word is found, the indexer will print out the number of occurrences of
the particular word in the file.
