---
title: Operating Systems and Networks (CS3.301)
subtitle: |
          | Monsoon 2022, IIIT Hyderabad
          | 23 August, Tuesday (Lecture 7)
author: Taught by Prof. P Krishna Reddy
---

# Process Concepts (contd.)
## Inter-Process Communication
Processes may communicate via shared memory or message passing. Shared memory is fairly straightforward, but it has some issues – for example, if the recipient process is unable to read before the new messages are overwritten (too slow), or reads before the old message is overwritten (too fast). These problems are solved by the *producer-consumer* model, which uses a bounded buffer. This maintains an in-pointer (for the next position to write to) and an out-pointer (for the next position to read from).

Message-passing consists of sending and receiving messages through mailboxes. Two processes can communicate if they have a shared mailbox.

## Client-Server Communication
A socket is defined as an endpoint for communication in a network; a pair of processes communicating over a network employs a pair of sockets. Sockets are represented by a concatenation of the IP address and the port, separated by a colon, *e.g.*, `161.25.19.8:1625` refers to port `1625` on host `161.25.19.8`.  
Servers implementing specific services listen to certain ports. For example, the telnet and http servers listen to port 80 and the ftp server to port 21.

Procedure calls between processes on network systems are abstracted by *remote procedure calls*. Client processes have *stubs* associated with them on the client and the server machine; the client stub acts as a proxy for the actual procedure on the server, and the server stub uses these parameters to actually perform to procedure. These stubs locate the server and marshal the parameters.  
RPCs have many issues – the netwrok may run into errors, the procedure call may fail, and so on. Two ways to address this problem are *exactly-once* semantics, where the message is processed exactly once (this is difficult to implement), or *at-least-once* semantics, where the message is repeatedly sent until the server sends an `ack`.

## Pipes
Pipes act as a conduit for two processes to communicate. Ordinarily, they are unidirectional; one end is reserved for the producer process, and the other for the consumer process. It requires that the processes that are communicating have a parent-child relationship, and cannot be accessed by other processes.

## Multithreaded Programming
### Processes and Threads
A process has two characteristics – resource ownership (like virtual address spaces, I/O channels, main memory) and execution (which follows a *trace*). These two characteristics are independent.  
The unit of dispatching or execution is called a *thread*, while the unit of resource ownership is called a *process* or a *task*.

Multithreading is the ability of an OS to support multiple threads of execution in a single process.

Each of the threads in a process has its own execution state, control block, and stack. However, it shares memory and files with other threads that are in that process.  


Multithreading has many advantages:

* responsiveness: a program can run even if a part of it is blocked or performing a time-consuming operation.
* resource sharing
* economy: it is faster to create and terminate a thread than a process; threads are also faster to switch between and communicate.
* utilisation of multiprocessor architectures

Now, scheduling and dispatching occurs at the thread level. The main system calls associated with threads are:

* spawn: create a new thread
* block: wait for an event (this does not affect other threads in the process)
* unblock: resume after event
* finish: end execution

There are two types of threads: user-level and kernel-level. As the names suggest, the former are managed and scheduled by application programs, while the kernel handles the latter. The user-level threads are mapped to kernel-level threads – this may be a many-to-one, one-to-one, or many-to-many mapping.

### Issues
One major issue with multithreading is that the semantics of the `fork()` and `exec()` syscalls now change. If a single thread calls `fork()`, should the new process contain a single thread, or all the threads?

Sometimes a thread needs to be terminated before it completes, depending on the progress of the other threads in the process; a common example is searching a database.

Threads may also need their own individual copies of data in some cases; then data-sharing leads to problems.