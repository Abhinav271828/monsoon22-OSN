---
title: Operating Systems and Networks (CS3.301)
subtitle: |
          | Monsoon 2022, IIIT Hyderabad
          | 30 August, Tuesday (Lecture 8)
author: Taught by Prof. P Krishna Reddy
---

# Process Concepts (contd.)
## Scheduling
CPU scheduling is the basis of multiprogrammed OSs. All computer resources are scheduled before use.

When one process has to wait for I/O, the OS takes CPU away from it and gives it to another process. Thus process execution consists of a cycle of computation and I/O; the distribution in which this happens for a certain process is a major factor in the scheduling algorithm.

Usually, I/O-bound processes tend to have a large number of short-duration (2-4 ms) CPU bursts, and much fewer long CPU bursts. Conversely, CPU-bound processes has longer CPU bursts.