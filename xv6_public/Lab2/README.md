# Lab 2: Concurrency and Memory

##### Handed out Monday, October 30th, 2016

##### Walkthrough due November 15th, 2016

##### Due Thuesday December 1st, 2016


###Objectives

There are two components to this assignment:

```
- Understand virtual memory (Part 1)
- Make Simple modifications to the memory layout (Part 2 and Part 3)
```

### Part 1: Memory translation system call

####Overview

The goal of this part is to learn about the data structures used to manage virtual memory.

#### Details

Add system call v2p (int virtual, int physical) v2p takes a virtual address and returns a phydicaal address. v2p should return an error if the virtual address is not valid (e.g., out of range) or not mapped.

###Part 2: Null pointer dereference

#### Overview

In this part, you will be changing xv6 to support a feature available in virtually every modern OS: raising an exception when your program dereferences a null pointer. Sound simple? Well, there are a few tricky details.

#### Details

In xv6, the VM system uses a simple two-level page table. If you do not remember the details, read [http://pages.cs.wisc.edu/~remzi/OSTEP/vm-smalltables.pdf] (Section 20.3 of OS 3 easy steps). However, you may find the description in Chapter 1 of the xv6 manual sufficient (and more relevant to the assignment). AS it currently is structured, user code is loaded
