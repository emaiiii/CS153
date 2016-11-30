b 2: Memory Management

##### Handed out Monday, October 30th, 2016

##### Walkthrough due November 17th, 2016

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

In xv6, the VM system uses a simple two-level page table. If you do not remember the details, read [Section 20.3 of OS 3 easy Steps](http://pages.cs.wisc.edu/~remzi/OSTEP/vm-smalltables.pdf). However, you may find the description in Chapter 1 of the xv6 manual sufficient (and more relevant to the assignment). As it currently is structured, user code is loaded into the very first part of the address space. Thus, if you dereference a null pointer, you will not see an exception (as you might expect); rather, you will see whatever code is the first bit of code in the program that is running. Try it and see!

Thus, the first thing you might do is create a program that dereferences a null pointer. It is simple! See if you can do it. Then run it on Linux as well as xv6, to see the difference. 

You job here will be to figure out how xv6 sets up a page table. Thus, once again, this project is mostly understanding the code, and not writing very much. Look at how exec() works to better understand how address spaces get filled with code and in general initialized. that will get you most of the way.

You should also look at fork(), in particular the part where the address space of the child is created by copying the address space of the parent. What needs to change in there/

The rest of your task will be completed by looking through the code to figure out where there are checks or assumptions made about the address space. Think about what happens when you pass a parameter into the kernel (using a system call), for example; if passing a pointer, the kernel needs to be very careful with it, to ensure you haven't passed it a bad pointer. How does it do this now? Does this code need to change in order to work in your new version of xv6?

One last hint: you will have to look at the xv6 makefile as well. In there user programs are compiled so as to set their entry point (where the first instruction is) to 0. If you change xv6 to make the first page invalid, clearly the entry point will have to be somewhere else(e.g., the next page, or 0x1000). thus, something in the makefile will need to change to reflect as well.

You should be able to demonstrate what happens when user code tries to access a null pointer. If you do this part correctly, xv6 should trap and kill the process without too much trouble on your part.

###Part 3: Stack Rearrangement

The xv6 address space is currently set up like this:

```
code
stack (fixed-sized, one page)
heap (grows towards the high-end of the address space)
```

In this part of the xv6 project, you will rearrange the address space to look more like Linux:

```
code
heap(grows towards the high-end of the address space)
...(gap)
stack (at end of address space; grows backwards)
```

this will take a little work on your part. First, you will have to figure out where xv6 allocates and initializes the user stack; then, you will have to figure out how to change that to use a page at the high-end of the xv6 user address space, instead of one between the code and heap.

Some tricky parts: one thing you will have to be very careful with is how xv6 currently tracks the size of a process's address space (currently with the sz field in the proc struct). there are a number of places in the code where this is used (e.g., to check whether an argument passed into the kernel is valid; to copy the address space. We recommend keeping this field to track the size of the code and heap, but doing some other accounting to track the stack, and changing all relevant code (i.e., that used to deal with sz) to now work with your new accounting.

You should also be wary of growing your heap and overwriting your stack. In fact, you should always leave an unallocated (invalid) page between teh stack and heap.

The high end of the xv6 user address space is 640KB (see the USERTOP value defined in the xv6 code). Thus your stack page shoudl live at 636KB-640KB.

One final part of this project, which is challenging: automaticall growing the stack backwards when needed. Doing so would require you to see if a fault occured on the page above the stack and tehn, instead of killing the offending process, allocating a new page, mapping it into the address space, and continuing to run. Getting this to work will make you into a kernel boss, and also get you those last 10% of credit.

Bonus (5%): Write code to try and get the stack to grow into the heap. Were you able to? If not explain why.

##The Code

You may also find the following readings about xv6 useful: [xv6 book](https://pdos.csail.mit.edu/6.828/2011/xv6/book-rev6.pdf).

**Particularly useful for this project:** Chapter 1 + anything else about fork() and exec(), as well as virtual memory.

## Submission(s)

Like Lab1, there are two submissions, a walkthrough/design document and the final submission. The walkthrough tentatively consists of the following questions (may be subject to modifications until November 7th). Where an outline of an implementation is requested, you have to list all the major items clearly:

```
- read chapter 2 in the xv6 book. Briefly explain the operation of kvmalloc() and mappages() and Figure 2-2.
- What is the size of the virtual address space used in xv6?
- How does a virtual address get translated to a physical address?
- show where in the code we can figure out the location of the stack.
```
