---
title: Operating Systems and Networks (CS3.301)
subtitle: |
          | Monsoon 2022, IIIT Hyderabad
          | 12 August, Friday (Lecture 4)
author: Taught by Prof. P Krishna Reddy
---

# Different Kinds of Systems
Multiprocessor systems, also known as parallel systems or tightly coupled systems, have a lot of advantages as compared to single-processor systems. For example,

* increased throughput
* economy of scale
* increased reliability (graceful degradation)

The development of multiprocessor systems, however, presents a number of difficulties. For example, a multiprocessor environment must provide cache coherency in hardware so that *all CPUs* have the most recent value of a variable in their cache.

A multiprocessor system may be *symmetric* or *asymmetric*. In symmetric multiprocessing, all processors perform the same functions, whereas in asymmetric multiprocessing, each processor is assigned a certain task.

A similar notion is that of *clustered systems*, which are like multiprocessor systems but involve several systems working together. Clustered systems may also be symmetric or asymmetric.

# Operating System Interface
An operating system must provide a number of basic services, such as

* user interface: this may be CLI, GUI, etc.
* program execution
* I/O operations
* filesystem manipulation
* communication
* error detection