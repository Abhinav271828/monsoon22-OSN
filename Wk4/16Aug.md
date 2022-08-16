---
title: Operating Systems and Networks (CS3.301)
subtitle: |
          | Monsoon 2022, IIIT Hyderabad
          | 16 August, Tuesday (Lecture 5)
author: Taught by Prof. P Krishna Reddy
---

# System Design
## Mechanisms and Policies
The speicifcation and design of an OS is a highly creative task, and is guided by some principles. One important principle is the separation of *mechanism* (how things are to be done) and *policy* (what is to be done). For example, using a timer for CPU protection is a mechanism, but deciding how long the timer is set is a policy.  
Microkernal OSs implement only mechanisms, with policies provided at the user level.

## Implementation
Assembly can be used to implement OSs – its main advantage is its high speed. Higher-level languages are, however, easier to develop, understand and debug, and are therefore more popular (UNIX was written in C).

# Structure of OSs
After several refinements through the course of the development of OSs, a layered structure was developed. Early OSs, like MS-DOS, had some structure, but its levels of functionality are not well separated and it was not divided into modules. Application programs could call any programs below them, even up to the hardware drivers.

UNIX had limited structuring. It consisted of two parts – system programs and the kernel. The kernel consists of everything between the physical hardware and the syscall interface. System programs have access only to the kernel and *not* to the driver.

Thus, OSs are divided into *layers*, where the lowest layer is the hardware, and layers access layers below them via system calls.

The microkernel system structure is a special type of layered architecture in which communication takes place between user modules using message passing, and moves many functions from the kernel space to the user space. Such a system, while it is easier to extend and port, and more reliable and secure, also introduces the overhead of message passing. A typical microkernel only implements interprocess communication, memory management, and CPU scheduling; functionalities like file management and device drivers are moved to the user space.

# Virtual Machines
In general, application programs can view everything under them as the machine itself. This leads to the concept of virtual machines. The VM approach provides an interface identical to the underlying hardware; each process has access to such a VM. The physical resources of the machine are shared to create these VMs.  
CPU scheduling allows the CPU to be shared in a transparent way. Memory management is used to create a large virtual memory space to address.

Virtual machines are difficult to implement, as they need to provide a copy of the underlying machine. They typically run in user mode; they create a virtual user mode and virtual kernel mode for the guest processes.  
They also tend to be slower than actual machines.

# Process Concepts
A *process* is any program in execution on a system. It may be a system program or an application program. The notion of processes emerged to control the execution of programs.

The components of a process are

* the program to be executed (multiple processes may be associated with one program)
* the data on which it executes
* the resources it requires
* the status of execution (given by the program counter and the stack)

The information associated with a process (called the *process control block*) consists of

* its state (new, running, waiting, ready, or terminated)
* the PC
* CPU registers
* CPU scheduling information
* memory management information
* accounting information
* I/O status information

The process control block is stored in the stack.