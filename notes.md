---
title: Operating System Concepts
author: |
        | Abraham Silberschatz
        | Peter Baer Galvin
        | Greg Gagne
---

# Part One
## Chapter 1: Introduction
An OS is a program that

* manages a computer's hardware
* provides a basis for application programs
* acts as an intermediary between the computer user and hardware

They are designed on a spectrum from convenience to efficiency, depending on their use case: mainframe OSs optimise hardware utilisation, while PC OSs support varied applications.

### 1.1 What Operating Systems Do
A computer system consists of:

* the hardware: the CPU, the memory and the I/O devices
* the application programs: these define the ways in which the hardware is utilised
* the OS: this controls the hardware and coordinates its use
* the users

Th OS only provides an environment for programs to do useful work.

#### User View
For PCs (consisting of a monitor, keyboard, mouse and a system), the OS is designed mainly for ease of use and partially for performance. No consideration is given to resource utilisation. They are optimised for the single-user experience.  
For mainframes or minicomputers, OSs maximise resource utilisation and sharing among multiple users.  
In workstations that are part of a larger network, the OS is designed to compromise between individual usability and resource utilisation.

#### System View
Based on its various functions, the OS can be seen as

* a resource allocator: the program most intimately involved with the hardware
* a control program: the program that manages the execution of other programs to prevent errors and improper use (especially w.r.t I/O devices)

#### Defining Operating Systems
Operating systems are very diverse, due to the diversity in computer design itself. They are therefore difficult to define precisely.  
In general, the operating system is a program that brings together the common functions of controlling and allocating resources. 

One common definition is that the OS is the *kernel*, or the program running at all times on the computer. Some OSs, however, also include *middleware* – a set of software frameworks that provide additional services to application developers (like database, multimedia and graphics support).

### 1.2 Computer System Organisation
#### Computer System Operation
A computer system has one or more CPUs, a number of device controllers, and a shared memory. The CPU(s) and the controllers can execute in parallel, with a memory controller synchronising memory access.

A computer has a bootstrap program in ROM or EEPROM, known as *firmware*. It locates and loads the kernel.  
The kernel then provides services to the system, along with certain system programs that run along with it (called *daemons*). The system then waits for an interrupt.

Interrupts may be triggered by the hardware (a signal on the shared bus) or software (a *system call*). This leads to the CPU transfering execution to the service routine for the interrupt, on completion of which the CPU resumes its computation.

To ensure speed, rather than a generic routine examining the interrupt type, the system has a table of pointers to specific interrupt routines (an *interrupt vector*) stored in low memory.

#### Storage Structure
–

#### I/O Structure
Each device is controlled by a device controller, which may be in charge of more than one device (like the SCSI controller). It maintains some local buffer storage and special-purpose registers, and is responsible for moving data between these buffers and the peripheral dvices.  
Typically, a device driver interfaces between the OS and the device controller.

First, the device driver informs the device controller what action is to be taken by loading certain registers within it. The device controller than transfers the data from the device to its buffer (or vice versa) and signals to the driver via an interrupt that the operation is complete (possibly with some return value). The OS then regains control of execution.

Interrupt-driven I/O may have a high overhead in the case of bulk data movement, which is avoided by *direct memory access* (DMA) – the interrupts are generated only once per block of data transferred between the memory and the controller's buffer, rather than once per byte. This frees up the CPU for other work.

Some systems use a switch architecture, where multiple components can communciate concurrently, rather than competing for time on a shared bus. This makes DMA more effective.

### 1.3 Computer System Architecture
#### Single-Processor Systems
A single-processor system consists of one main CPU executing a general-purpose instruction set, with a number of special-purpose processors for devices or I/O. The latter are managed by the OS, although they work autonomously.

#### Multiprocessor Systems
The (two or more) processors in such systems share the bus, clock, memory and peripheral devices. They have three main advantages:

* increased throughput: while there is an overhead in keeping the parts working in sync, in addition to contention for shared resources, there is still some gain from additional processors.
* economy of scale: the sharing of peripherals and storage means that multiprocessors systems are more cost-effective than multiple single-processor systems.
* increased reliability: the failure of one processor only leads to a slowdown rather than a shutdown; this is called *graceful degradation*. Some systems are even *fault tolerant* – they allow for the detection, diagnosis and correction of failures.

There are two main types of multiprocessor systems – *asymmetric* (each processor has a specific task) or *symmetric* (each processor performs all tasks).

Multiprocessing may increase the amount of memory available to the system, but also might cause it to change its model from uniform to non-uniform memory access.

Some systems have multiple *cores* on a single chip – these are faster than multi-chip systems. These cores may share caches or registers, or maintain them separately.

*Blade servers* are another type of system which have multiple processor, I/O and networking boards on the same chassis.

#### Clustered Systems
Multiple CPUs (nodes), when loosely coupled, form a clustered system. Each may be a single- or multiprocessor system. Generally, they tend to be linked via a LAN network, and share storage.

Clustering usually aims for high availability, by adding a level of redundancy. The systems can be asymmetric (where one machine is on standby mode) or symmetric.

Clusters can also provide high-performance computing environments through *parallelisation*.

### 1.4 Operating System Structure
One of the most important aspects of OSs is *multiprogramming*, which increases CPU utilisation by organising jobs so that the CPU always has one to execute.  
This happens by having all the jobs kept in a *job pool* on disk, of which some are allocated main memory. The CPU then picks a job from the set of jobs in memory and begins to execute it. When it needs to wait for some task to complete, it can be switched out for another job, and so on.

*Time sharing* or *multitasking* is a logical extension of this, in which the CPU executes multiple jobs by switching among them, but extremely frequently. This allows many users to share the computer.

The system must choose among jobs that are to be brought into main memory (*job scheduling*) and among jobs that are ready to be run (*CPU scheduling*). These jobs must also be limited in their ability to affect each other.

Lower response times are usually achieved by *swapping* (moving processes in and out of main memory), or *virtual memory*. Virtual memory allows for running programs that are larger than the physical memory, and also separates logical memory from physical memory.

The system must also provide a file system, a disk management system, a mechanism to protect resources from inappropriate use, and mechanisms for job synchronisation and communication.

### 1.5 Operating System Operations
Modern OSs are interrupt-driven; they wait for events, signalled by interrupts (or traps). Each interrupt has a corresponding interrupt service routine to deal with it.

#### Dual-Mode and Multimode Operation
OSs need to distinguish between the execution of system code and user-defined code. Hardware support is usually provided for this, in the form of *modes of operation*.

There are at least two modes: user mode and kernel mode. A *mode bit* in the hardware indicates the current mode.

The hardware boots up in kernel mode, followed by the loading of the OS. The user applications then start in user mode. Syscalls switch the mode to kernel mode to complete the relevant operation.

Dual-mode operation protects the OS from errant users, by designating some machine instructions as *privileged instructions* (for example, the instruction to switch to kernel mode).

This can be generalised to more than two modes; for example, in systems that support virtualisation, there is a separate mode for the VMM. Various kernel components may also have separate modes.

An attempt by a user program to perform an illegal instruction or access memory out of bounds is treated as an ordinary trap, which leads to termination and a memory dump.

#### Timer
A timer can interrupt the system after a fixed period, which allows the OS to regularly inspect the user program for infinite loops or other issues.

### 1.6 Process Management
A program in execution is called a process. However, a process may also be a system task (like sending output to an I/O device). Note that a program *by itself* is a passive entity, while a process is active.

A process needs certain resources, which are allocated to it at creation or during runtime. These resources are reclaimed by the OS at termination.

A single-threaded process has a PC (multithreaded processes have many) specifying the next instruction, and its execution must be sequential. At any time, at most one instruction is executed on behalf of a process.

Thus a process is a unit of work in a system. Some processes are OS processes, while some are user processes. These can execute concurrently. An OS has the following duties w.r.t process management:

* scheduling processes and threads on the CPUs
* creating and deleting processes
* suspending and resuming processes
* process synchronisation
* process communication

### 1.7 Memory Management
Main memory is a large array of bytes, which are quickly accessible and shared by the CPU and I/O devices. It stores the instructions of the executing process. It is the only large storage device directly accessible to the CPU.

Memory management is required as general-purpose computers have to keep several programs in memory. Various different schemes are used for memory management, and each one requires its own hardware support. The duties of the OS w.r.t memory management are:

* keeping track of which parts of memory are being used and by whom
* deciding which processes and data to move in and out of memory
* allocating and deallocating memory space

### 1.8 Storage Management
The logical unit of storage is the *file*. This is an abstraction away from the physical storage devices, and the OS carries out the mapping from files to physical media.

#### File System Management
A file is a collection of related information defined by its creator; typically, a file can represent a program or data. The OS manages mass storage media to control files, organises them into directories, and controls details of their access.  

The duties of the OS in this regard are:

* creation and deletion of files and directories
* manipulation of files and directories
* mapping from files to secondary storage
* backup of files to stable storage media

#### Mass Storage Management
Most programs are stored on disk until being loaded into memory. The OS is responsible for free space management, storage allocation and disk scheduling.

OSs may or may not be responsible for tertiary storage.

#### Caching
Cache management is an important design problem. Usually, the OS is in charge of transfer from disk to memory, while the hardware handles transfeer from cache to the CPU and registers.

Caching poses the problem of multiple copies of data in multitasking environments, to ensure that different processes accessing the same value access the most recently updated one. This issue is exacerbated by the multiple caches present in multiprocessor environments. This is called *cache coherency*.

#### I/O Systems
The I/O subsystem consists of various components: memory management, the device driver interface, and the drivers for specific devices.

### 1.9 Protection and Security
There are mechanisms to ensure that files, memory and other resources are manipulated only by processes with the appropriate authorisation from the OS. *Protection* is any mechanism to control this access.

*Security* consists of defending the system against external and internal attacks, which can be of several types. These may or may not be under the umbrella of the OS's functions.

### 1.10 Kernel Data Structures
* Lists, Stacks and Queues
* Trees
* Hash Functions and Maps
* Bitmaps

### 1.11 Computing Environments
* Traditional Computing
* Mobile Computing
* Distributed Systems
* Client-Server Computing
* Peer-to-Peer Computing
* Virtualisation
* Cloud Computing
* Real-Time Embedded Systems

### 1.12 Open-Source Operating Systems
* History
* Linux
* BSD Unix
* Solaris
* Open-Source Systems as Learning Tools

### 1.13 Summary

## Chapter 2: Operating System Structures
### 2.1 Operating System Services
An OS provides an environment for the execution of programs. It provides certain services to programs and their users; those falling in the latter class are:

* user interface: this may include a command-line interface, a batch interface, or a graphical user interface
* program execution
* I/O operations
* file system manipulation
* communications
* error detection

while those of the former type are:

* resource allocation
* accounting
* protection and security

### 2.2 User and Operating System Interface
#### Command Interpreters
An OS might include the command interpreter in the kernel, or treat it as a special program. If a system has multiple interpreters, they are known as *shells*.

A command interpreter may implement commands in two ways: it may include the code to perform the task itself (thus calling the command only jumps to another part of the shell's code itself), or it may use the command to identify a file to be executed without actually understanding it in any way.

#### Graphical User Interfaces

#### Choice of Interface

### 2.3 System Calls
System calls provide an interface to the services provided by the OS; they are usually available as routines written in C/C++, although some may be in assembly.

Programmers, however, frequently use an API rather than actual system calls. This ensures portability and abstracts away from detail. Most PLs provide a runtime support system with a syscall interface that forms the link between the API and the actual syscalls.

Syscalls may require parameters (for example, an input syscall would require the device from which data is to be read). There are three general methods for this:

* pass the parameters in registers
* pass the parameters in a block whose address is stored in a register
* push parameters on the stack

### 2.4 Types of System Calls
There are mainly six categories of syscalls: process control, file manipulation, device manipulation, information maintenance, communications and protection.

#### Process Control
A running program can halt its execution normally (`end()`) or abnormally (`abort()`). The latter causes an error trap followed by a memory dump, which can be examined by a debugger. In an interactive system, the command interpreter will continue with the next command; in a GUI, an error popup might be displayed; in a batch system, the command interpreter would terminate the whole job.

A process can `load()` and `execute()` another program. When the loaded program terminates, control may be returned to the existing program (which would require it to be saved). We can control its execution through `get_process_attributes()`, `set_process_attributes()`, and `terminate_process()`. We can also wait for them to finish using `wait_time()`.

Processes can share data by locking it, through `acquire_lock()` and `release_lock()`.

#### File Management
There are syscalls to `create()`, `delete()`, `open()`, `read()` from, `write()` to, `reposition()`, and `close()` files.

There is a corresponding set of operations for directories. We also have calls to manipulate file information, like `get_file_attributes()` and `set_file_attributes()`.

#### Device Management
The various resources available to the OS can be considered devices, some of which are phsyical while others are virtual. Most OSs provide syscalls to `request()` and `release()` devices (analogous to files). Similarly, we can `read()`, `write()` and `reposition()` them.

#### Information Maintenance
Many syscalls simply transfer information between the user program and the OS, like `time()`, `date()`, `dump()`, `get_process_attributes()`, `set_process_attributes()` and so on.

#### Communication
There are two main models of inter-process communication: message-passing and shared memory.

Message passing relies on the processes exchanging messages, either directly or through a common mailbox. A connection is first opened with the unique IDs of each process (obtained by `get_hostid()` and `get_processid()`). The recipient process (usually a special-purpose daemon) then accepts the connection, and messages are exchanged by `{read,write}_message()` calls.

Shared memory gives one process access to regions of memory owned by another process. They then exchange information in these areas. The processes themselves are responsible for ensuring they do not write simultaneously.

Message passing is useful for smaller amounts of data, and is easier to implement. Shared memory allows for greater speed and convenience, but protection and synchronisation pose issues.

#### Protection
The most common syscalls related to protection are `{get,set}_permission()`, and `{allow,deny}_user()`.

### 2.5 System Programs
System programs provide a convenient environment for program development and execution; some of these are simply interfaces to system calls, while some are more complex. They are usually related to file management, status information, file modification, PL support, program loading and execution, communications and bacground services.

### 2.6 Operating System Design and Implementation
#### Design Goals
The design of an OS is affected by the choice of hardware and the type of system (batch, time sharing, single- or multiuser, distributed, real-time or general purpose).

The requirements beyond this can be divided into *user goals* (convenience, reliability, safety, speed, etc.) and *system goals* (like ease of design, implementation and maintenance, and flexibility and efficiency).

#### Mechanisms and Policies
Mechanisms determine *how* to do something, while policies determine *what* is to be done. Policies are much more likely to change over time; thus a mechanism invariant under these changes is desirable.

#### Implementation
OSs can be written in assembly language, or HLLs, or a mixture of both (which is the most common). Code in HLLs is more compact, can be written faster, is easy to debug and understand, and more portable. There is slight loss in speed, but the optimisations performed by modern compilers make up for this.

### 2.7 Operating System Structure
#### Simple Structure
Many OSs, like MS-DOS, do not have well-defined structures. UNIX is layered to some extent.  
Such approaches are inconvenient, but have a distinct performance advantage in the avoidance of system call interface or kernel communication.

#### Layered Approach
Proper hardware support allows OSs to be broken into smaller pieces, which gives implementers also greater freedom.

The layered approach breaks the OS into a number of layers with distinct functionalities, from the hardware to the user interface. The main advantage of this approach is simplicity of construction and debugging.

Its major difficulty involves appropriately defining the layers; this entails careful planning. For example, the device driver for the backing store should be *below* the memory management routines, but may be above or below the CPU scheduler.  
It also tends to be less efficient due to the function call overhead.

#### Microkernels
A microkernel is simply a smaller kernel, which takes all nonessential components out of the kernel. Typically, microkernels provide minimal process and memory management and a communication facility (its main function).

This approach makes extending the OS easier, as the kernel does not tend to have to be modified.

#### Modules
In this approach, the kernel has a set of core components and takes in additional services via modules, during runtime or at boot time. Thus each kernel section has defined, protected interfaces. Since any module can call any other, there is more flexibility than in the case of layered systems.

#### Hybrid Systems

### 2.8 Operating System Debugging
#### Failure Analysis
This is done by the OS writing the error information to a *log file*, or taking a *core dump* in a file.  
A failure in the kernel is called a crash, which saves the memory state to a *crash dump*.

#### Performance Tuning

#### DTrace

### 2.9 Operating System Generation
Configuring a system for each specific computer site is called *system generation*. Information like what CPU is to be used, how the boot disk will be formatted, how much memory is available, what devices are available, and what OS options are desired, are used for this process.

### 2.10 System Boot
The process of starting the computer by loading the kernel is known as *booting*. In most systems, the *bootstrap program* or *bootstrap loader* locates the kernel, loads it, and starts its execution. Some PCs make this a two-step process.

When the CPU is reset, the instruction register is loaded with a predefined memory location, which is where the initial bootstrap program is.

# Part Two
## Chapter 3: Processes
The development of computers that allowed multiple programs to be loaded into memory and executed concurrently required firmer control and more compartmentalisation; these needs resulted in the notion of a *process*, a program in execution. In modern time-sharing systems, a process is the unit of work.

### 3.1 Process Concept
The activities executed by the CPU in a batch system are called *jobs*, while in a time-shared system they are called *user programs* or *tasks*. Even in a single-program system, the OS would need to support its internal activities as well.  
All these are similar, and are categorised together as *processes*.

#### The Process
A process is (informally) a program in execution, but it is more than the code of the program itself (the *text section*). It also includes

* the program counter
* the contents of the processor's registers
* the process *stack* (function parameters, return addresses, local variables)
* a *data section* (global variables)
* possibly a *heap* (memory dynamically allocated at runtime)

A program is a passive entity, while a process is an active entity. A program becomes a process when an executable file is loaded into memory. More than one process may be associated with a single program; processes may also spawn other processes as they run.

#### Process State
The state of a process changes as it executes, and is partly defined by the current activity of the process. The possible states are:

* *new* – being created
* *running* – being executed
* *waiting* – waiting for some event, like I/O or a signal
* *ready* – waiting for a processor
* *terminated* – completed execution

Only one process can be *running* on a processor at any instant, but several may be *ready* or *waiting*.

#### Process Control Block
Processes are replresented in the OS by a process control block or PCB. It contains the following information:

* the process state
* the program counter
* CPU registers
* CPU scheduling information (process priority, pointers to scheduling queues, etc.)
* memory management information (base and limit registers, page/segment tables)
* accounting information (amount of CPU and time used, time limits, process numbers, etc.)
* I/O status information (list of allocated I/O devices, open files, etc.)

[see p. 109]

#### Threads
We have only considered processes that perform a single thread of execution. Most modern OSs, however, all processes to perform more than one task at a time (this is especially beneficial on multicore systems).

### 3.2 Process Scheduling
The process scheduler has two main objectives – to have some process running at all times (multiprogramming) and to switch the CPU among processes frequently enough for multiple users to interact with the system (time-sharing). It selects an available process for execution on the CPU.

#### Scheduling Queues
When a process enters the system, it is put in the *job queue*, which has all the processes in the system; those that are ready to execute and residing in main memory are kept in the *ready queue* (these queues are generally linked lists).

If a process makes an I/O request during execution, it may need to wait – it then enters the *device queue*.

[see p. 111-2]

Process scheduling is commonly represented by *queueing diagrams*.

A new process is in the ready queue until it is *dispatched*. Now, it may

* issue an I/O request and be placed in the I/O queue
* create a new child process and wait for its termination
* be removed forcibly back to the ready queue as the result of an interrupt

#### Schedulers
The operating system needs to select processes from various queues for scheduling purposes; this is carried out by a scheduler. There are two main kinds of schedulers.  
The *long-term scheduler* or *job scheduler* selects processes from a pool on disk (or any mass-storage device) to load into memory, while the *short-term scheduler* or *CPU scheduler* selects from processes ready to execute to allocate the CPU to them.

The major difference between these is frequency – the CPU scheduler needs to select new processes frequently (often once every 100ms).  
The long-term scheduler, on the other hand, operates on the scale of minutes. To keep the degree of multiprogramming stable, the LTS needs to be invoked only on the departure of a process from the system.

The LTS should select a good mix of I/O-bound and CPU-bound processes. If all are I/O-bound, the ready queue will always be empty, but if all are CPU bound, the waiting queue will always be empty.

Some OSs may have minimal long-term scheduling (*e.g.*, placing all new processes in memory). The stability of these systems depends on a physical limitation or adjusting on the part of the user.

Some OSs may introduce an intermediate level of scheduling, called the *medium-term scheduler*. It relies on the idea that it can be advantageous to remove a process from active contention for the CPU, and reduce the degree of multiprogramming. The process can later be reintroduced and resumed (this is called *swapping*). This helps to improve the process mix or free up memory in case of unforeseen changes.

#### Context Switch
When an interrupt causes the OS to run a kernel routine, the system needs to save the current context of the process running on the CPU (in order to restore it afterwards). This context is represented in the PCB – it includes the register values, the process state, and the memory management information. The two operations involved are called a *state save* and a *state restore*. Performing the state save of one process and the state restore of another is called a *context switch*.

Context-switching time is pure overhead, and it varies depending on the OS.

### 3.3 Operations on Processes
#### Process Creation
A process can create new processes during the course of its execution, each of which may create others, and so on. Each process is typically identified by a unique pid.  
The `init` process, which always has a pid of 1, serves as the root parent process and can create user processes. For example, there may be processes to handle kernel tasks (`kthreadd`), users `ssh`ing into the system (`sshd`), and users logging into the system (`login`).

A child process may obtain its resources (time, memory, files, I/O) from the CPU directly, or it may be constrained to a subset of its parent's resources. This latter restriction prevents any process from creating too many child processes and overloading the system.  
The parent may also pass along input to the child process, in addition to resources.

There are two possibilities for the parent after creating a new child process – it may continue to execute concurrently, or it may wait until some or all of its children have terminated.  
Further, the child process may be a duplicate of the parent process, or it may be running a new program.

#### Process Termination
A process terminates when it finishes execution and asks the OS to delete it with the `exit()` syscall. It may return a status value to its parent process via `wait()`. The OS deallocates all resources.

A parent may terminate the execution of a child. This can happen in multiple circumstances:

* the child has exceeded its usage of some resources
* the task assigned to it is not needed
* the parent is exiting (if the OS does not allow a child to outlive its parent)

A process that has terminated, but whose parent has not called `wait()`, is a *zombie* process. All processes pass through this state, however briefly; the entry in the process table remains until the `wait()` call.  
If a parent terminates without calling `wait()`, the child process is an *orphan*. The `init` process is assigned as the new parent of such processes, and it periodically calls `wait()` to clean them up.

### 3.4 Interprocess Communication
Processes executing concurrently in the OS may be independent (unable to affect or be affected by other processes in the system), or cooperating. This distinction relies on whether or not the process shares data with other processes.

Some reasons for making process cooperation possible are:

* information sharing
* computation speedup (by breaking a task into parallelly running subtasks)
* modularity
* convenience (multitasking)

Interprocess communication (IPC) is carried out by one of two models – *shared memory* (a common region of memory is established between the processes) and *message passing* (messages are exchanged by the processes). The latter system is useful for smaller amounts of data, and easier to implement; however, the former is faster due to the lack of syscalls.

#### Shared-Memory Systems
Typically, a region of shared memory resides in the address space of the process creating it, and must be attached to the other processes involved. The restriction imposed by the OS on access to other processes' memory must be removed for these processes.  
The processes themselves decide the form and location of the data being transferred, and are responsible for syncing up writing and reading.

The *producer-consumer* problem is a common paradigm for cooperating processes, centred around one process giving out information that the other one needs (it is a useful abstraction for the client-server paradigm).

The shared-memory solution to this problem keeps available a buffer of items that can be filled by the producer and empties by the consumer, residing in a common region of memory. The producer and consumer must be synced to ensure that the consumer does not try to consume data that has not yet been produced.  
The buffer can be *unbounded* or *bounded* – in both cases, the consumer may have to wait, but only in the latter does the producer have to. [see p. 125-6]

#### Message-Passing Systems
Alternatively, the OS may provide the facility for cooperating processes to communicate with each other via message passing. This method does not require the processes to share the same address space, and is therefore useful in a distributed environment.

There are at least two operations in a message-passing facility – `send(msg)` and `receive(msg)`. The messages' size may be fixed or variable – the former restriction makes the system-level implementation straightforward but the programming difficult, while the latter simplifies programming but complicates the system-level implementation.

The logical implementation of the communication link between two processes passing messages to and fro may be done by various methods:

* direct or indirect communication
* synchronous or asynchronous communication
* automatic or explicit buffering

We will consider issues related to this method of communication.

##### Naming
Under direct communication, the processes name each other explicitly (this is a *symmetric* scheme). A link is associated with exactly two processes in this case. A variant of this is *asymmetric* – only the sender need name the recipient. This scheme is disadvantageous in its limited modularity.

Indirect communication allows processes to use *mailboxes* or *ports*, which, in the abstract, are objects that contain messages to be passed between processes. Here a link exists between processes sharing a certain mailbox, and this may be more than two; further, a pair of processes may share several mailboxes.  
Two processes may try to read a message sent by a third to a shared mailbox – this can be solved by restricting the mailbox to be shared by at most two processes, or the processes to not execute `receive()` simultaneously. Alternatively, the system can arbitrarily pick one of the processes to read the message.  
A mailbox may be owned by a process (which can then only read from it), in which case it disappears when that process terminates, or by the OS.

##### Synchronisation
Message passing may be *blocking* (or *synchronous*) or *nonblocking* (or *asynchronous*).  
A *blocking send* blocks the sender until the message is received, while a *nonblocking send* allows it to continue operation.  
A *blocking receive* blocks the recipient until a message is available, while a *nonblocking receive* provides it with either a valid message or a null.  

A situation where both the sender and recipient use blocking calls is called a *rendezvous*. This makes the solution to the producer-consumer problem trivial.

##### Buffering
Messages exchanged by communicating processes, directly or indirectly, reside in a temporary queue. This queue can be implemented in three ways:

* zero capacity: the sender must block until the recipient receives the message
* bounded capacity: the sender needs to block only if the queue is full, and can unblock once space is available in the queue
* unbounded capacity: the sender never blocks

The first kind of system is called a *no buffering system*, while the latter two cases are called *automatic buffering* systems.

### 3.5 Examples of IPC Systems
[p. 130-6]

### 3.6 Communication in Client-Server Systems
As well as the methods below (sockets, RPCs and pipes), shared memory and message passing can be used in client-server systems.

#### Sockets
A *socket* is an endpoint for communication, and a pair of communicating processes uses a pair of sockets. A socket is identified by an IP address and a port number.

A server waits for incoming client requests by listening to a specified port; once received, the server accepts a connection from the client socket. Specific services, like telnet, FTP and HTTP, listen to specific ports. Ports below 1024 are considered well-known and can be used for standard services; those above 1024 are assigned (uniquely) to client processes initiating requests.

A client and server on the same system can communicate through the *loopback* IP address `127.0.0.1`.

This paradigm is considered a low-level form of communication, since sockets only allow an unstructured stream of bytes to be exchanged.

#### Remote Procedure Calls
This paradigm is an abstraction of the procedure-call mechanism for use between two systems part of the same network. It is generally based on a message-passing system.

The messages exchanged in RPC communication are well-structured. Each is addressed to an RPC daemon listening to a port on the remote system, and contains an identifier with the function to be executed and its parameters. The output of this function is sent back to the requester in another message.

The RPC system hides the details of communication by providing one *stub* on the client side for each remote procedure, which locates the server port, *marshals* the parameters (converts them to transmittable form) and sending the message via message passing. A stub on the server side receives the message and invokes the procedure.

To avoid issues presented by discrepancies in data representation, many RPC systems define an *external data representation* (XDR), to and from which the data is converted during marshalling.  
RPCs can also fail or be re-executed due to network issues – this is avoided by ensuring that messages are acted on *exactly once*, which is accomplished by `ACK` messages acknowledging receipt and keeping track of the timestamps of messages.  
The client and server also need to know each other's ports to communicate. This is achieved by either fixing the port after compile time, or running a *matchmaker* daemon that provides the port number of the recipient to the sender.

#### Pipes
A pipe acts as a conduit for two processes to communicate. They are relatively simple, but have some limitations. There are four important parameters:

* is the communication bidirectional or unidirectional?
* if bidirectional, is it half-duplex or full-duplex?
* do the processes need to be related?
* can the pipes communicate across a network?

##### Ordinary Pipes
Ordinary pipes allow two processes to communicate in a standard producer-consumer fashion – they have a *read-end* and a *write-end*. They therefore allow only one-way communication between a parent process and its child.

##### Named Pipes
Named pipes are much more powerful, as they allow bidirectional communication between an arbitrary pair of processes. Several processes can use a named pipe for communication once it is created – it is not tied to any one pair.

## Chapter 4: Threads
Most modern OSs allow a process to contain multiple threads of control.

### 4.1 Overview
A thread is a basic unit of CPU utilisation. It consists of a thread ID, a program counter, a register set and a stack. It shares its code, data and resources with other threads of the same process.

A process with a single thread is called a traditional or *heavyweight* process.

#### Motivation
An application is typically implemented as a process with several threads of control. They may also need to leverage the processing capabilities of multicore systems, or perform several similar tasks.

Process creation is one method that was common before threads – a server runs as a single process and creates new processes to service requests it receives. However, this is time-consuming and resource-intensive.

RPC servers also tend to be multithreaded – they service each message they receive using a separate thread, allowing them to service several concurrent requests.

#### Benefits
There are four major kinds of benefits of multithreaded programming:

* responsiveness – an application can continue even if part of it is blocked or busy.
* resource sharing – threads share resources and memory by default.
* economy – creating and switching between processes is much more expensive that the corresponding operations on threads.
* scalability – multithreading exploits multicore systems.

### 4.2 Multicore Programming
Multithreaded programming provides a mechanism for more efficient use of multiple computing cores and improved concurrency.

*Parallelism* is a characteristic of systems that can perform more than one task simultaneously; *concurrency* is a characteristic of systems that support more than one task and allow all the make progress. It is therefore possible to have concurrency without parallelism.

Modern systems support more than one thread per core.

#### Programming Challenges
There are five main categories of challenges to multicore programming:

* identifying tasks – find areas that can be divided into separate tasks.
* balance – ensure that the tasks provide equally valuable work.
* data splitting
* data dependency
* testing and debugging

#### Types of Parallelism
There are two main types of parallelism – *data parallelism* and *class parallelism*. Data parallelism involves distributing subsets of the same data across cores and performing the same operation on all of them; task parallelism distributes threads across cores, each performing a unique task.

### 4.3 Multithreading Models
Threads may be supported as *user threads* (supported above the kernel without its support) or *kernel threads* (supported and managed directly by the OS).

#### Many-to-One Model
In this model, many user-level threads are mapped to one kernel thread. Thread management is done in user space, which is efficient. However, if a single thread makes a blocking system call, the entire process will block.  
This model is not popular due to its inability to take advantage of multiple cores.

#### One-to-One Model
Here, each user thread is mapped to one kernel thread, which provides more concurrency. Its only drawback is that overhead of creating a new kernel thread worsens the performance of applications – most systems implementing this model limit the number of threads a single application can create.

#### Many-to-Many Model
Here, a number of user-level threads is mapped to a smaller or equal number of kernel threads. The exact number of kernel threads may be specific to the application and the machine.

This model allows developers to create as many threads as necessary, while the corresponding kernel threads carry out true parallelism on a multiprocessor.

A variation of this model, the *two-level model*, allows for this mapping but also lets a user-level thread be bound to a single kernel thread.

### 4.4 Thread Libraries
There are two primary approaches to thread libraries – they can be implemented either in user space with no kernel support, or at the kernel level supported by the OS.

Threading may be synchronous (where the parent waits for all its children to die) or asynchronous (where the parent resumes execution without monitoring the child).

### 4.5 Implicit Threading
Implicit threading is the strategy of giving compilers and run-time libraries the responsibility of creating and managing threads. We will discuss some approaches towards this.

#### Thread Pools
We have seen that a web server can be designed to create a new thread every time it receives a request. There are two issues with this implementation – the time taken to create a thread is an overhead, and if unlimited threads are created, system resources can be exhausted.

One solution to the second problem is using a *thread pool*. The idea behind this is to create a number of threads at startup, and place them into a pool. When a server gets a request, it passes it to one of the available threads in the pool, or waits until one of them becomes free. This idea has the following advantages:

* The server need not wait to create a thread.
* The number of threads is limited.
* We can have different strategies for running the task (*e.g.* it could be run after a delay, or periodically).

The number of threads in the pool can be set based on factors like the number of CPUs, the amount of memory, and the expected number of requests. It may also be dynamically adjusted according to usage patterns.

#### OpenMP
OpenMP is a set of compiler directives that provides support for parallel programming in shared-memory environments. It identifies *parallel regions* (blocks of code that may run in parallel); developers insert directives into their code at these regions and they are then executed in parallel.

#### Grand Central Dispatch
GCD is a combination of extensions to C, an API and a runtime library that functions like OpenMP. It identifies *blocks* in C(++) code, marked by the syntax `^{ ... }`, which are self-contained units of work, and schedules them for execution by placing them in a dispatch queue. Blocks are assigned to available threads as they leave the queue.

There are two types of dispatch queues – *serial* and *concurrent*. Serial queues are depleted in FIFO order; the next block is not removed until the last one has finished execution. Each process has its own serial queue, called its *main queue*, but developers can create additional serial queues local to processes. They are useful for ensuring the sequential execution of tasks.

Concurrent queues are also depleted in FIFO order, but several blocks may be removed at a time to execute in parallel. There are three system-wide concurrent queues, distinguished according to priority – low, default, and high.

Internally, GCD's thread pool is composed of POSIX threads.

#### Other Approaches

### 4.6 Threading Issues
#### The `fork()` and `exec()` System Calls
Multithreading complicates the semantics of these syscalls. If one thread in a program calls `fork()`, does the new process duplicate all threads, or is the new process single-threaded? Some UNIX systems have two versions of `fork()` for each of these options.

The `exec()` system call typically replaces the entire process, including all the threads.

Which version of `fork()` to use depends on the application – if `exec()` is called immediately after forking, then duplicating all threads is unnecessary, but otherwise it is the better option.

#### Signal Handling
A signal may be synchronous or asynchronous, but all of them follow the same pattern – they are generated by the occurrence of a particular event and delivered to a process, and must be handled once delivered.  
When a signal is generated by an event external to a running process, it is received asynchronously.

It may be handled by either a default signal handler, or a user-defined signal handler. Handling a signal may mean anything from ignoring it altogether to terminating the program.

In the case of multithreaded programs, where should a signal be delivered? The options we have are to deliver it to the thread to which it applies, to deliver to every thread, to deliver it to certain threads, or to assign a specific thread to receive all signals.  
Which method we use depends on the type of signal generated – for example, synchronous signals need to be delivered to the thread causing the signal itself. Asynchronous signals, however, may have to be sent to all threads or only to some.

Some systems allow a thread to block some signals and accept others; thus a signal may be delivered only to the threads that will accept it. However, signals need to be handled only once, so they may be delivered only to the first thread that s not blocking it.

Windows simulates signals using *asynchronous procedure calls* or APCs, but this facility is more straightforward than the idea of signals.

#### Thread Cancellation
Sometimes, a thread needs to be terminated before it has completed – for example, if multiple threads are searching a database, all threads can be cancelled once one returns.

A thread to be cancelled is called the *target thread*. Cancellation may be *asynchronous* (one thread immediately terminates the target thread) or *deferred* (the target thread periodically checks if it should terminate).

The fact that resources have been allocated to a cancelled thread, and that it may be updating data shared with other threads, however, complicate this (especially in the case of asynchronous cancellation). The OS may not reclaim all resources from a cancelled thread.

#### Thread-Local Storage
While threads usually share the data of a process, in some cases, each thread might need its own copy of certain data. Such data is called *thread-local storage* or TLS.  
Most thread libraries support TLS.

#### Scheduler Activations
The many-to-many and two-level models described above necessitate communication between the kernel and the thread library. Many systems place an intermediate data structure between these levels, called a *lightweight process* or LWP.

For the user-level library, the LWP is a virtual processor on which a thread can be scheduled to be run. Each LWP is attached to a kernel thread, which the OS scheduled to run on physical processors. If a kernel thread blocks, so does the LWP, and in turn the user-level thread.  
Different applications may require any number of LWPs to run efficiently.

*Scheduler activation* is one scheme for communication between the user-thread library and the kernel. The kernel provides an application with a set of LWPs, on any of which the application can schedule a user thread. The kernel also informs the application of certain events, by a procedure called an *upcall*, which is handled by an upcall handler run on an LWP.  
For example, if an application thread is about to block, the kernel makes an upcall to the application informing it of this and allocating it a new LWP. This new LWP then saves the state of the blocking thread and the application gives up the LWP on which that thread is running. When the awaited event occurs, the kernel makes another upcall allowing the blocked thread to run again.

### 4.7 Operating-System Examples
#### Windows Threads

#### Linux Threads

### 4.8 Summary

## Chapter 5: Process Synchronisation
Cooperating processes can affect or be affected by other processes in the system. They can either directly share a logical address space or share data through files or messages. This, however, causes issues of data consistency.

### 5.1 Background
We have seen that processes can execute concurrently or in parallel, with the CPU switching among processes at any point. Additionally, multiple instruction streams can execute simultaneously on separate processing cores. However, concurrent or parallel execution can contribute to data integrity issues.  
We have seen the bounded buffer model for allowing processes to share memory – it allows at most $(\text{bufferSize} - 1)$ in the buffer at one time. To remedy this, we can use a variable `counter` to keep track of how many items are in the buffer. However, the concurrent execution of statements like `counter++` and `counter--` by different processes can lead to issues – this is called a *race condition*. To guard against this, we need to ensure that only one process ata time can manipulate a global variable – for this, we need to synchronise the processes in some way.

These situations occur frequently in OSs, as different parts of the system manipulate shared resources. Multithreading exacerbates this problem.

### 5.2 The Critical-Section Problem
Consider a system with $n$ processes $P_0, \dots, P_n$. Each process has a segment of code called a *critical section*, in which it may be changing variables, writing files, etc. An important feature of the system is that no two processes are operating in their critical section at the same time; the *critical-section problem* is to design a protocol that the processes can use to cooperate.

Each process must request permission to enter its critical section, which is implemented by code called the *entry section*. The critical section may then be followed by an *exit section*, and the rest of the code is the *remainder section*. A solution to the critical-section problem must satisfy the following requirements:

* *Mutual exclusion* – the basic requirement that no two processes can be executing in their CSs simultaneously.
* *Progress* – if no process is executing in its CS, then only processes not in their RSs can decide which will enter its CS next, and this decision cannot be postponed indefinitely.
* *Bounded waiting* – there is a limited number of times other processes can enter their CSs after a process has made a request to enter its CS and before the request is fulfilled.

The kernel code of a system is subject to several possible race conditions – for example, the file table, the memory allocation data structures, process lists, and so on.  
In OSs, there are two general approaches to handling CSs: *preemptive* and *nonpreemptive* kernels. A preemptive kernel allows a process to be preempted when in kernel mode, while a nonpreemtive kernel will run it until it exits kernel mode, blocks, or voluntarily gives up the CPU.

A nonpreemptive kernel is essentially free from race conditions, but preemptive kernels must be carefully designed to avoid them. Their advantages, however, lie in the fact that they may be more responsive (since processes cannot run for arbitrarily long), and are more suitable for real-time programming.

### 5.3 Peterson's Solution
This is a classic software-based solution to the critical-section problem. While there are no guarantees that it will work correctly on modern architectures, it provides a good algorithmic description of solving the problem.

Peterson's solution is restricted to two processes $P_0$ and $P_1$ that alternate execution between their CSs and RSs. It requires them to share two data items, an integer variable `turn` and a boolean array `flag[2]`.  
To enter the CS, $P_i$ first sets `flag[i] = true` and `turn = 1 - i` (asserting that $P_{1-i}$ can enter the CS if it wishes). If both attempt to set `turn` together, the value that lasts after the overwrite determines what will happen.  
After this, the process executes its CS while `(flag[1-i] && turn == j)`, and then sets `flag[i] = false`.

This can be proved to satisfy all three properties.

### 5.4 Synchronisation Hardware
All solutions we will now see that solves the critical-section problem are based on *locking* – protecting critical regions through the use of locks.

The CS problem can be solved in a single-processor environment by preventing interrupts while a shared variable is being modified. This is the approach taken by nonpreemptive kernels.  
However, this is not feasible in a multiprocessor environment, as message passing to the processes delays entry into CSs and decreases efficiency.

Many computer systems provide special hardware instructions, which we will abstract by the commands `test_and_set()` and `compare_and_swap()`. Both of these are *atomic* commands.  
`test_and_set()` sets a boolean variable to true and returns its previous value. It can be used to implement mutual exclusion by defining a variable `boolean lock = false` and waiting for it to be `true`.  
`compare_and_swap()` sets a variable to a new value if it has an expected previous value, which is then returned. It is a generalisation of `test_and_set()` and can be used in much the same way to implement mutual exclusion.

However, bounded-waiting is not satisfied by these algorithms. We can use a boolean array `waiting[n]` and variable `lock` to satisfy all requirements (p. 211).

### 5.5 Mutex Locks
Since hardware solutions are complicated and inaccessible to application programmers, there are software tools to solve the CS problem, the simplest of which is the *mutex lock*. A process must `acquire()` the lock before entering a CS, and can `release()` it once it exits. There is a boolean `available` that indicates if the lock is available or not; if it is not, the process is blocked until it is released.

The main disadvantage of this implementation is *busy waiting* – a process trying to enter its CS must loop continuously for the lock to be released (this type of lock is also called a *spinlock* for this reason).  
Their advantage, however, lies in the fact that no context switch is required. Thus they can be useful when locks are expected to be held for a short time.

### 5.6 Semaphores
A *semaphore* `S` is an integer variable that can only be accessed through `wait()` and `signal()`, both standard atomic operations – `wait()` loops until `S` rises above 0, and then decrements it; `signal()` increments it.

#### Semaphore Usage
A semaphore may be a *counting* or a *binary* semaphore (which behave like mutex locks). Counting semaphores cna be used to control access to a given resource with a finite number of instances – the semaphore value keeps track of the number of free resources. Semaphores can also be used to synchronise two processes.

#### Semaphore Implementation
`wait()` and `signal()` need to be modified to overcome the need for busy waiting. This can be done by letting a process block itself, rather than busy-wait, while waiting for the value to rise above 0. It can be placed into a waiting queue associated with the semaphore.

A blocked process should be restarted whenever `signal()` is executed, which is done by a `wakeup()` operation that places it in the reasy queue.

It is critical, however, that no two processes can execute `wait()` and `signal()` on the same semaphore together.

#### Deadlocks and Starvation
This implementation of a semaphore may result in a situation where two or more processes are waiting for an event that only one of them can cause (a `signal()` call). This is called a *deadlock*.

Another problem related to this is *indefinite blocking* or *starvation*, where processes wait indefinitely within the sempahore.

#### Priority Inversion
If a higher-priority process needs to read or modify kernel data that is being accessed by a lower-priority process, a scheduling challenge arises. For example, if a low-priority process $L$ is using a resource $R$ that higher-priority processes $M, H$ are waiting for, and $M$ preempts $L$, then $H$ must wait even longer for $R$. This problem is called *priority inversion*.

Typically, this is solved by implementing a priority-inheritance protocol. All processes accessing resources needed by a higher-priority process inherit this higher priority until they are done. In the example above, this prevents $M$ from preempting $L$, since it temporarily has the priority of $H$.

### 5.7 Classic Problems of Synchronisation
#### The Bounded-Buffer Problem
Suppose that the producer and consumer processes share three semaphores `mutex = 1`, `empty = n`, and `full = 0`, and an integer `n`. We assume that the pool consists of `n` buffers; the `mutex` semaphore excludes access to the buffer pool, while the `empty` and `full` semaphores count the number of empty and full buffers.

#### The Readers-Writers Problem
If a database is to be shared among several concurrent processes, there may be problems when a writer tries to access it along with some other process.

To avoid this, we require that writers have exclusive access to the database. This synchronisation problem is called the *readers-writers problem*. There are several variations of this problem – a waiting writer should not hold up waiting readers, and readers should not hold up a waiting writer. Clearly, a solution to either of these problems may result in starvation.

These problems have been generalised to provide *raeder-writer locks* on some systems. Acquiring a reader-writer lock requires specifying the mode of the lock, either `read` or `write`. These locks are most useful

* in applications where it is easy to identify which processes are readers or writers.
* in applications that have more readers than writers.

#### The Dining-Philosophers Problem
Consider five philosophers who spend their lives thinking and eating. These philosophers are seated around a circular table with five chairs, at the centre of which is a bowl of rice with five chopsticks.  
A philosopher tries to pick up two chopsticks when hungry, and eats when she has both at the same time.

This is an example of a large class of concurrency-control problems. It is a simple representation of the need to allocate several resources among several processes in a deadlock- and starvation-free manner.

One solution is to represent each chopstick with a semaphore. While this guarantees that no two neighbours eat simultaneously, it could create a deadlock – if all philosophers get hungry together and all grab the left chopstick, they will all be delayed forever. This can be solved by

* allowing $\leq 4$ philosophers to be seated at the table.
* allowing a philospher to pick up chopsticks only if both are available.
* using an asymmetric solution, *e.g.*, an odd-numbered philosopher first takes her left chopstick and then her right chopstick, and an even-numbered philosopher does the opposite.

### 5.8 Monitors
Using semaphores incorrectly can result in timing errors that are difficult to detect. Difficulties can arise if even a *single* process is not well-behaved:

* If a single process interchanges the order in which the `wait()` and `signal()` operations on the semaphore `mutex` are executed, then several processes may be executing in their critical sections simultaneously.
* If a process replaces a `signal()` call with a `wait()` call, then a deadlock will occur.
* If a process omits either of the calls, either mutual exclusion is violated or a deadlock will occur.

To deal with these, we have high-level language constructs, one of which is the *monitor* type.

#### Monitor Usage
The `monitor` construct ensures that only one process at a time is active within the monitor. However, it is not sufficient – additional synchronisation mechanisms are provided by the `condition` construct.

The `condition` structure can call its `wait()` and `signal()` methods to suspend and resume processes. When a process $P$ calls `signal()`, while another process $Q$ is suspended, one of two possibilities must occur:

* signal and wait – $P$ waits for $Q$ to leave the monitor or for another condition
* signal and continue – $Q$ waits for $P$ to leave the monitor or for another condition

#### Dining-Philosophers Solution Using Monitors

#### Implementing a Monitor Using Semaphores
Each monitor has a semaphore `mutex`, which must be `wait()`ed at entry and `signal()`ed at exit.

#### Resuming Processes Within a Monitor
How do we decide which of the suspended processes should be resumed on a `signal()` call? This can be implemented by the *conditional-wait* construct, where `wait()` is passed an argument called a *priority number* that is stored with the name of the process in the queue. The process with the smallest priority number is resumed on a `signal()` call.

However, this construct also requires the programmer to make use of the monitor construct correctly.

### 5.9 Synchronisation Examples
#### Synchronisation in Windows
#### Synchronisation in Linux
#### Synchronisation in Solaris
#### Synchronisation in Pthreads

### 5.10 Alternative Approaches
#### Transactional Memory
A memory transaction is a sequence of atomic memory read-write operations; only if all operations are complete is the transaction committed. This construct can act as an alternative to traditional locking methods.

This is beneficial as the transaction system is responsible for guaranteeing atomicity, rather than the developer. It also avoids deadlocks (since locks are not involved).

It can be implemented in either software or hardware.

#### OpenMP

#### Functional Programming Languages

### 5.11 Summary