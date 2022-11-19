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

## Chapter 6: CPU Scheduling
CPU scheduling is essential to multiprogrammed OSs.

### 6.1 Basic Concepts
The objective of multiprogramming is to maximise CPU utilisation by having some process running at all times.

#### CPU-I/O Burst Cycle
One property of processes is necessary for the success of CPU scheduling – the fact that they consist of a cycle of CPU execution and I/O wait, and alternate between these states. An interval during which the CPU is used is called a *CPU burst*; there tend to be very few long CPU bursts and large number of short ones.

#### CPU Scheduler
The *short-term scheduler*, or CPU scheduler, selects a process from among the processes in memory and allocates the CPU to it. The processes (more accurately, their PCBs) in memory therefore form a queue, but not necessarily a FIFO one.

#### Preemptive Scheduling
CPU-scheduling decisions may take place when a process switches to or from the running state, or when it terminates.

If a process terminates or goes from running to waiting, then the scheduler *must* select a new process for execution; there is no choice in these situations. This is *nonpreemptive* or *cooperative* scheduling.

*Preemptive scheduling* is more advanced, and requires some special hardware (like a timer) to be implemented. However, it can result in race conditions when several processes share data (see Chapter 5). Preemption also affects the design of the kernel.

#### Dispatcher
The dispatcher is a module that gives control of the CPU to the process selected by the STS. This involves:

* switching context
* switching to user mode
* jumping to the proper location in the user program

The dispatcher should be as fast as possible. The interval between the stopping of one process and the starting of another is called the *dispatch latency*.

### 6.2 Scheduling Criteria
The potential criteria to be considered during scheduling are:

* CPU utilisation: It should range from 40% to 90% in a real system.
* Throughput
* Turnaround time: This is the sum of the periods spent waiting to get into memory, waiting in the ready queue, executing on the CPU and doing I/O.
* Waiting time
* Response time: This is the time from the submission of the request until the first repsonse is produced.

In most cases, we optimise average of a quantity across all users. However, we may wish to optimise the maximum or minimum instead.

### 6.3 Scheduling Algorithms
#### First-Come First-Served Scheduling
FCFS is the simplest CPU-scheduling algorithm, where the ready queue is implemented as a normal FIFO queue.

The average waiting time under an FCFS policy is generally not minimal and may vary substantially.  
Furthermore, it causes a *convoy effect*, where a large number of processes wait for one big process to finish a CPU burst.

This algorithm is nonpreemptive, and therefore unsuitable for time-sharing systems.

#### Shortest-Job-First Scheduling
The SJF algorithm associates with each process the length of its next CPU burst.

This algorithm is provably optimal – it gives the minimum average waiting time for any given set of processes. However, the difficulty lies in identifying the length of the next burst. While this is given by the user in the case of the LTS, the CPU scheduler needs to predict it; it usually takes an exponential average of the previous CPU bursts. In other words, we predict
$$\tau_{n+1} = \alpha t_n + (1 - \alpha) \tau_n,$$
where $\alpha$ is a parameter that controls the relative weight of history in the prediction. We can understand its behaviour better by writing it as
$$\begin{split}
\tau_{n+1} &= \alpha t_n + (1-\alpha)\alpha t_{n-1} + \cdots + (1-\alpha)^{n+1} \tau_0 \\
&= \sum_{i=0}^n (1-\alpha)^i \alpha t_{n-i}.
\end{split}$$

The SJF policy can be preemptive or nonpreemptive, depending on its treatment of processes arriving in the ready queue while a previous process is still executing. Preemptive SJF scheduling is sometimes called *shortest-remaining-time-first* scheduling.

#### Priority Scheduling
Priority scheduling is a generalised form of SJF – processes are associated with *priorities*, which determine the order in which the CPU is allocated to them. These priorities can be defined internally (memory requirements, number of open files, etc.) or externally (importance, funds, etc.).

As with SJF, priority scheduling can be preemptive or nonpreemptive.

A major problem with priority-scheduling algorithms is *indefinite blocking*, or *starvation*, where a low-priority process may be continually blocked by a stream of high-priority processes. This is fixed by *aging*, *i.e.*, increasing the priority of processes that have been waiting in the system.

#### Round-Robin Scheduling
The round-robin scheduling algorithm, specifically designed for time-sharing systems, is similar to FCFS but preemptive. A *time quantum* or *time slice* is defined, and the scheduler goes around the ready queue (which is a circular queue), allocating the CPU to each process for [up to] one quantum. No process is allocated more than one quantum in a row, unless it is the only runnable process.  
The upper bound on the waiting time is $(n-1)q$ units.

Typically, deciding the time quantum is a tradeoff between waiting time and CPU utilisation – a large time quantum leads to a large waiting time but less context-switching time. A general heuristic is that 80% of the CPU bursts should be shorter than $q$.

#### Multilevel Queue Scheduling
If processes are easily classified into different groups (*e.g.*, foreground and background), a multilevel queue scheduling algorithm can be used. Each queue in such a system has its own algorithm, and there is a common algorithm for scheduling among queues (usually fixed-priority preemptive scheduling or time-slicing).

An example of a multilevel queue scheduling algorithm is one with five queues:

* System processes
* Interactive processes
* Interactive editing processes
* Batch processes
* Student processes

#### Multilevel Feedback Queue Scheduling
This is a modification of multilevel queue scheduling that allows a process to move between queues. Higher-priority processes that do not complete in their allocated time can be shifted to the tail of lower-priority queues. This automatically gives highest priority to processes with shorter CPU bursts.

A multilevel feedback queue scheduler is generally defined by the following parameters:

* the number of queues
* the scheduling algorithm for each queue
* the upgrade criterion
* the downgrade criterion
* the method to determine which queue receives a new process

### 6.4 Thread Scheduling
Here, we consider scheduling issues for both user-level and kernel-level threads.

#### Contention Scope
User-level and kernel-level threads may be distinguished by how they are scheduled.

On many-to-one and many-to-many systems, the thread library schedules user threads to run on an available LWP – this is called *process-contention scope* or PCS, (since competition for the CPU takes place among threads of a single process). On the other hand, the kernel schedules (kernel-level) threads onto the CPU using *system-contention scope* (SCS).

PCS is typically done according to priority, which in the case of user-level threads is set by the programmer. It is usually preemptive, however.

#### Pthread Scheduling
[p. 301-2]

### 6.5 Multiple-Processor Scheduling
The availability of multiple CPUs makes *load sharing* possible, but brings with it increased complexity. We will consider some issues in the case where the processors are all identical in terms of functionality (SMP).

#### Approaches to Multiple-Processor Scheduling
Multiple-processor scheduling may be *asymmetric* (one master server handling all system activities and scheduling decision) or *symmetric* (each processor is self-scheduling).

In the case of symmetric multiprocessing (SMP), the processors may have their own ready queues or there may be a common ready queue.

#### Processor Affinity
If a process has been running on a certain processor, the cache of that processor is populated with that process's data. If the process now migrates to another processor, the data must be invalidated from one cache and repopulated in another, which is an expensive operation – thus most systems try to avoid migrating processes. This is called *processor affinity*.

Affinity may be *soft* (there is no guarantee about process migration) or *hard* (a process specifies a subset of processors on which it may run).

#### Load Balancing
Load balancing attempts to keep the workload evenly distributed across processors in an SMP system; it is typically necessary, however, only in systems where each processor has its own private ready queue (which is the more common kind of SMP).

Load balancing may be done via *push migration* or *pull migration*. Push migration involves a specific task periodically checking the load on each processor, and redistributing processes accordinly. Pull migration entails each processor pulling waiting tasks from busier ones when it is idle. These two approaches, however, are often implemented in parallel.

#### Multicore Processors
A single chip may include several processor cores; this saves time and power. This may complicate scheduling issues. For example, a processor may need to shift to another thread when the running thread has a memory stall – thus, multiple hardware threads are assigned to a single core, each appearing as a logical processor to the OS.

Multithreading on a processor core may be *coarse-* (a thread executes until a long-latency event) or *fine-grained* (the processor switches between threads at every instruction cycle).

Note that multicore multithreading involves two levels of scheduling – each hardware thread deciding which software thread to run, and each core deciding which hardware thread to run.

### 6.6 Real-Time CPU Scheduling
A real-time system may be *soft* or *hard* – a soft real-time system gives no guarantee when a critical process will be run, while a hard real-time system has stricter requirements.

#### Minimising Latency
Real-time systems tend to be event-driven. The time period between an event occurring and being serviced is called the *event latency*.

There are two main types of latencies affecting RTSs – *interrupt latency* (where the event involved is an interupt) and *dispatch latency* (the time taken to stop a process and start another).  
Interrupt latency is the sum of the times taken to complete the current instruction, determine the type of interrupt, save the state of the process, and call the ISR. Interrupt latency must be bounded in the case of hard RTSs; furthermore, interrupts cannot be kept disabled for too long.  
Dispatch latency has two components: preemption of the running process, and release of resources by low-priority processes.

#### Priority-Based Scheduling
Since an RTS needs to respond to new processes immediately, it must support a priority-based algorithm with preemption. However, this only satisfies the requirements for a soft real-time system; hard real-time systems need to ensure that deadline constraints, etc., are met. We will consider some algorithms meeting these needs (rate-monotonic scheduling, earliest-deadline-first scheduling, and proportional share scheduling).

Processes being submitted to the scheduler are assumed to be periodic, requiring the CPU at intervals of $p$ units, during which it has a fixed processing time $t$ and a deadline $d$. These quantities are related as $0 \leq t \leq d \leq p$. The rate of the process is defined as $\frac1p$.

A process may need to announce its deadline requests to the scheduler; then the scheduler uses an *admission-control algorithm* to admit it with a guarantee of completion, or reject it if it is impossible.

#### Rate-Monotonic Scheduling
This algorithm schedules periodic tasks using a static priority policy with preemption. Each task is assigned a priority that depends inversely on its period – thus tasks that require the CPU more often have higher priority.

Rate-monotonic scheduling is optimal, in the sense that if it cannot schedule a set of processes, no other (static-priority) algorithm can. However, it imposes an upper limit on CPU utilisation, equal to $n \cdot (2^\frac1n - 1)$ for $n$ processes. This is asymptotically equal to about 69%.

#### Earliest-Deadline-First Scheduling
This algorithm *dynamically* assigns priorities according to the deadline; when a process becomes runnable, it must announce its deadline requirements to the system, and then priorities are adjusted to reflect the change.

This algorithm does not constrain processes to be periodic, or to require a constant amount of CPU time per burst – they only need to announce their deadlines when they become runnable. If we ignore practical overheads like context switching and interrupt handling, it makes 100% CPU utilisation possible.

#### Proportional Share Scheduling
A scheduler implementing proportional share scheduling partitions a total of $T$ shares among all processes, and uses an admission-control policy to guarantee that a task receives its share.

#### POSIX Real-Time Scheduling

### 6.7 Operating-System Examples
#### Example: Linux Scheduler
#### Example: Windows Scheduling
#### Example: Solaris Scheduling

### 6.8 Algorithm Evaluation
We can use several criteria to evaluate algorithms, like CPU utilisation or throughput. We will consider the various evaluation methods we can use.

#### Deterministic Modelling
This method is a type of *analytic evalution* (using a formula to evaluate the performance of a given algorithm on a given workload). It is simple and fast, and produces exact numbers; however, it requires exact numbers for input.

#### Queueing Models
We can measure and approximate the distributions of CPU and I/O bursts, and of arrival times, of processes. From these distributions we can calculate the average throughput, utilisation, waiting time, etc. This is called *queuing-network analysis*.

Let $n$ be the average queue length, $W$ the average waiting time, and $\lambda$ the average arrival rate. These quantities are related as $n = \lambda W$ (Little's formula).

Queuing analysis, however, can only handle a limited number of algorithms and distributions, and can become unmanageably complex. Simplicity of these models generally comes at the cost of accuracy and realistic assumptions.

#### Simulations
We can use RNGs set to imitate observed probability distributions. *Trace tapes* can also be used to record sequences of actual events and drive simulations.

#### Implementation

### 6.9 Summary

## Chapter 7: Deadlocks
A deadlock is a situation in which a process, having entered the waiting state, is unable to leave it.

### 7.1 System Model
The resources an OS has to distribute among the processes may be partitioned into a number of types, each containing identical instances (for example, CPU cycles, files, etc.). A process requesting an instance of a resource type can be allocated *any* instance of it.

In order to use a resource, a process must first request it and release it afterwards. The request and release of resources may be system calls – a system table records the status (free or allocated) of each resource. Each resource has a queue of processes waiting for it.

A set of processes is deadlocked when every process in the set is waiting for an event that can only be caused by another process in the set (usually resource acquisition or release).

### 7.2 Deadlock Characterisation
#### Necessary Conditions
The following four conditions are needed for a deadlock to arise in a system:

* Mutual exclusion: At least one resource mus be nonshareable (if one process requests it while another is holding it, the requesting process is delayed).
* Hold and wait: A process must be holding some resources and waiting to acquire some others.
* No preemption: Resources cannot be released by processes other than the one holding them.
* Circular wait: A set $\{P_0, \dots, P_n\}$ of processes must be such that $P_i$ is waiting for a resource held by $P_{(i+1) \mod n}$.

#### Resource-Allocation Graph
The resource-allocation graph describes the state of resources in the system. The vertices represent the processes and resources, and edges denote requests (going from processes to resources) and allocations or assignments (going from resources to processes).  
It can be shown that if there is a deadlock in the system, then there is a cycle in the graph (but the converse does not hold).

The presence of a cycle is always a necessary condition for a deadlock. It is also sufficient in the case where each resource type has exactly one instance.

### 7.3 Methods for Handling Deadlocks
The deadlock problem can, in general, be handled by

* ensuring deadlocks never occur (prevention or avoidance)
* allowing them to occur, but enabling the system to detect and recover from them
* ignoring them

*Deadlock prevention* provides a way to ensure that at least one of the four conditions for a deadlock cannot hold – thus it constrains the requests that can be made for resources.  
*Deadlock avoidance* needs the OS to have a priori information about the maximum resources a process can request.

A deadlock can arise if neither prevention nor avoidance is implemented. Such systems can detect and recover from deadlocks when they do occur.

### 7.4 Deadlock Prevention
#### Mutual Exclusion
We cannot deny this condition, since some resources are intrinsically nonshareable.

#### Hold and Wait
This requires us to guarantee that a process requesting a resource not hold any other resources – thus all the resources it needs should be allocated to it before it begins execution.

Another protocol allows a process to request resources only when it has none (*i.e.*, it has released all the resources previously allocated to it).

Both these protocols have two disadvantages – resource utilisation is low, and starvation is possible.

#### No Preemption
This condition can be negated by preempting all resources being held by a process that cannot be assigned its remaining needs. The process is resumed when it can be assigned all the resources it requires.

#### Circular Wait
One way to ensure that a circular wait never occurs is to impose a total ordering of resource types and to require processes to request them in that order. Formally, given a function $F : R \to \mathbb{N}$, we enforce that a process can request $R_j$ after $R_i$ iff $F(R_j) \geq (R_i)$. Further, if several instances of one type are needed, a single request must be issued.

In an application program, we can accomplish this by ordering synchronisation objects like mutexes and locks.

### 7.5 Deadlock Avoidance
We have seen that deadlock prevention can lead to low device utilisation and reduced throughput. Deadlock avoidance can be implemented by requiring extra information about resources being requested, *e.g.*, the order in which the resources will be requested.

The simplest model for this approach requries the maximum number of resources of each type that each process needs. The algorithm then dynamically examines the resource-allocation state to avoid a circular-wait situation.

#### Safe State
A state is safe if the system can allocate resources to each process in some order, while avoiding a deadlock. Formally, a system is in a safe state if the processes can be arranged in a *safe sequence* $\langle P_1, \dots, P_n \rangle$, where each $P_i$'s requests can be satisfied with the resources currently available *and* those held by all $P_{j < i}$.

An OS can avoid a deadlock as long as the system is safe; if the system is in an unsafe state, the behaviour of the process determines the occurrence of deadlocks. We now design algorithms to ensure that the system never enters an unsafe state.

Note that this may lower resource utilisation, since a process may have to wait for a resource that is, in fact, available.

#### Resource-Allocation-Graph Algorithm
If each resource type has only one instance, we can use a modification of the graph described earlier, adding a type of edge called a *claim edge* (indicating that a process may request a resource in the future). The resources must now be claimed a priori.

Now, a request is granted only if converting the request edge to an assignment edge does not create a cycle in the graph. The presence of a cycle means that the system is in an unsafe state.

#### Banker's Algorithm
The above algorithm only works in the case where each resource type has only one instance. For the more general case, we use the following algorithm.

When a new process enters the system, it declares the maximum number of instances of each resource type it needs. The algorithm maintains a vector `available[i]` (recording how many instances of $R_i$ are available), and matrices `max[i][j]` (recording the maximum demand by $P_i$ of $R_j$), `allocation[i][j]` (recording the allocation of $R_j$ to $P_i$), and `need[i][j]` (recording how much more of $R_j$ $P_i$ might need).

Now, we use the following algorithm to check if a system is in a safe state.  
We initialise `work = available` and `finish = repeat n false`. For each `i`, if `finish[i] == false` and `need[i] ≤ work`, then set `finish[i] = true` and `work += allocation[i]`. If `finish = repeat n true` now, the system is in a safe state.

We then use the following algorithm to check if a request can be granted. Let `request[i]` be the request vector for process $P$; now, if `request[i] ≤ need[i]` and `request[i] ≤ available`, then "pretend" to allocate resources:
```
available -= request[i]
allocation[i] += request[i]
need[i] -= request[i]
```
and check if the resulting state is safe. If it is, proceed; else, $P_i$ must wait.

### 7.6 Deadlock Detection
Note here that a detect-and-recovery scheme entails an overhead comprising not only the runtime costs of maintaining the necessary information but also the losses involved in recovery,

#### Single Instance of Each Resource Type
We use a variant of the resource-allocation graph called the *wait-for* graph, which has nodes only for processes and where an edge from $P_i$ to $P_j$ means that $P_i$ is waiting for $P_j$ to release some resource. A deadlock has occurred if the wait-for graph has a cycle; the system thus needs to examine this graph periodically.

#### Several Instances of a Resource Type
The algorithm for detecting deadlocks in this case is very similar to the banker's algorithm; the only difference is that `finish[i]` is initialised to `true` if `allocation[i] == 0`, and we check for `request[i] ≤ work` at each step. At the end, any process for which `finish[i] == false` is deadlocked.

We reclaim the resources of $P_i$ when we know that `request[i] ≤ work`, since we know it is not involved in a deadlock, and we assume that it will not request any more resources later (if it does, the algorithm will detect it then).

#### Detection-Algorithm Usage
When we should invoke the deadlock detection algorithm depends on how often a deadlock is likely to occur, and how many processes will be affected by it when it happens.

If deadlocks occur frequently, the algorithm should be invoked frequently.

Since deadlocks only occur when a process makes a request that cannot be granted immediately, we can run the algorithm only when this happens.

### 7.7 Recovery from Deadlock
One option for deadlock recovery is to allow the (human) operator to deal with it manually; if we wish to recover automatically, we can either abort one or more processes or preempt some resources from the deadlocked processes.

#### Process Termination
We can either abort all processes (this is very expensive and may cause processes to lose progress), or abort them one by one until the cycle is eliminated (this causes considerable overhead).

If we go with partial termination, we are faced with the policy decision of which process is to be terminated first. Many factors influence this, like priority, runtime, resource usage, resource requirement, and so on.

#### Resource Preemption
There are three main issues to be addressed in this approach:

* Selecting a victim: A process to take resources from has to be selected, as in process termination. The decision in this case involves many of the same factors.
* Rollback: What do we do with a process whose resources have been preempted? It needs to be rolled back to a previous safe state, but it is usually simpler to roll it all the way back.
* Starvation: The same process may always be picked as a victim, leading to starvation; the most common solution is to consider the number of rollbacks suffered so far in deciding which process to roll back.

### 7.8 Summary

# Part Three
## Chapter 8: Main Memory
We have seen that throughput and responsiveness can be increased by sharing the CPU among several processes, but this requires keeping all these processes in memory.

### 8.1 Background
We can here ignore how a program generates a memory address – we only care about the final sequence of addresses that a program generates.

#### Basic Hardware
Main memory and processor registers are the only form of general-purpose storage for the CPU. No machine instructions work with disk instructions.

Registers are typically accessed in one cycle; main memory access may require the processor to stall. To avoid long gaps, we use caches between the processor and the main memory.

The hardware compares every address generated with the base and limit registers to determine if it is valid. These registers can be loaded only by the OS, since only it operates in kernel mode.

#### Address Binding
We have seen that processes being executed need their code to be in main memory. All such processes waiting in main memory form the *input queue*.

A user program starts with the addresses being referenced symbolically. Typically, the addresses are then bound to relative addresses by the compiler, and then to absolute addresses by the linker.  
However, it may in fact happen at any stage. If the compiler does not know where the program is, it must generate relocatable code; if the program can be moved around during execution, then binding must be delayed even further.

#### Logical vs. Physical Address Space
Compile- or load-time binding usually generates identical physical and logical addresses, but runtime binding generates distinct ones. The mapping between the two spaces is carried out by the MMU; there are many methods to do this.

The user program never sees the physical addresses; it deals only with virtal addresses.

#### Dynamic Loading
If the entire program has to be in the main memory for execution, this places a limit on its size. *Dynamic loading*, on the other hand, loads a routine only when it is to be called; they are otherwise kept on disk in a relocatable format.

#### Dynamic Linking and Shared Libraries
*Dynamically linked libraries* are those that are linked to programs only during runtime. Some OSs support *static linking* also, however.

A *stub* is included in the image for each library-routine reference, which indicates how to loacte the actual routine.

This is useful especially when the library is updated.

### 8.2 Swapping
A process can temporarily be *swapped* to a backing store and brought back to memory for execution.

#### Standard Swapping
The backing store is usually a fast disk, large enough to accommdate copies of all users' memory images. The system maintains a *ready queue* for the processes in the backing store that are ready to run. The dispatcher brings them to main memory to be run.

The context-switch time overhead, however, is fairly high, being proportional to the amount of memory being swapped.  
It also complicates I/O occurring from user memory. Either processes with such pending I/O should never be swapped, or the OS buffer should take care of such conflicts.

#### Swapping on Mobile Systems

### 8.3 Contiguous Memory Allocation
Contiguous memory allocation is an early method to allocate main memory efficiently. Each process is held in a single section of memory contiguous to the next process's.

#### Memory Protection
For memory protection, we use the values of the base (or relocation) and limit registers as described before. This scheme allows the OS to change its size dynamically.

#### Memory Allocation
The *multiple-programming* method of allocating memory is to divide it into several partitions of fixed size, each of which can contain one process. However, this is no longer in use.

A variation of this is the *variable-partition* scheme, which keeps a table indicating the free and occupied parts of memory. Processes are allocated memory some time after entering the system, and are then loaded into memory. In general, the available memory blocks form a set of holes of various sizes, and the OS searches for a hole big enough for the incoming process.  
The *dynamic storage-allocation problem* concerns how to satisfy a request of size $n$ from a list of free holes. It can be solved by the following strategies:

* First fit – Allocate the first hole that is big enough. Generally faster.
* Best fit – Allocate the smallest hole that is beg enough.
* Worst fit – Allocate the largest hole. Bad.

#### Fragmentation
The first-fit and best-fit strategies suffer from external fragmentation – when the total memory space is enough to satisfy a request, but the space is non-contiguous. The 50% rule is a statistical observation that if $N$ blocks are allocated, $\fracN2$ will be unusable.

One solution to this is *compaction* – shuffle the memory contents to place all free memory together. This may not always be possible, unless addresses are dynamically relocated. Even if it is possible, it may be costly.

Segmentation and paging are two other solutions to this; they both allow the logical address space of the process to map to a noncontiguous physical space.

Internal fragmentation is another problem – since memory is allocated in fixed blocks, a process may get more than it requested.

### 8.4 Segmentation
Segmentation provides a way for the hardware to map the programmer's view to the physical view.

#### Basic Method
To the programmer, the memory consists of memory segments like "the stack", "the math library", and so on. Segmentation supports this view.

The logical address space consists of segments, each of which has a name and a length. The addresses specify both the segment name (for simplicity, usually a number) and the offset within the segment. A typical C compiler would have separate segments for the code, global variables, the heap, the stacks, and the standard C library.

#### Segmentation Hardware
The mapping from the segment view to the physical space is carried out by a *segment table*, a list of records with a *segment base* and *segment limit* each.

### 8.5 Paging
Paging is another memory-management scheme that provides the same advantage as segmentation, but unlike it avoids external fragmentation and the need for compaction. It also solves the problem of fitting memory chunks on the backing store, which cannot be compacted.

#### Basic Method
Physical memory is broken into blocks called *frames*, while logical memory is broken into blocks of the same size called *pages*. The backing store is broken into chunks that are the size of a cluster of frames.

When a process is to be executed, its pages are loaded into any available memory frames from their source.  
Every address contains a page number $p$ and a page offset $d$. $p$ indexes into a page table to get the base address of the corresponding page, which is combined with $d$ to find the physical address.

Note that paging does not avoid internal fragmentation. We can guess that it averages to half a frame per process, which suggests that frame size should be small, but the overhead of page table entries is reduced for larger pages.

The *frame table* stores which frames are allocated and available and other such information.

#### Hardware Support
Older OSs used dedicated registers to hold the page table, but modern systems use page tables of millions of entries. They keep the table in main memory, with a page-table base register pointing to it.  
However, this means that two memory accesses are needed for a single retrieval. This is avoided by using a *translation look-aside buffer*, which is a high-speed associative memory. It stores a few page-table entries, and when a TLB miss occurs, the retrieved entry is added to it. Some entries are *wired down* in the TLB, like those for kernel code.

Some TLBs store *address-space identifiers* as well, which are names for processes that provide address-space protection for them. TLBs that do not use ASIDs need to be flushed with every context switch.

The effective access time, as in the case of caches, is determined by weighing different possible access times with the hit ratio.

#### Protection
Each frame has protection bits associated with it, usually kept in the page table.

#### Shared Pages
If the code for an application that many users are using is *reentrant*, or *pure* (non-self-modifying), it can be shared among them instead of having separate copies of it.

### 8.6 Structure of the Page Table
#### Hierarchical Paging
The page table is usually too large for the address spaces of modern computers. This is fixed by using a two-level paging algorithm – the page table itself is paged.

However, the multiple memory accesses inherent in this method make it prohibitive.

#### Hashed Page Tables
A hashed page table is a map from virtual page numbers to a linked list of elements with a common hash value.

A variation of this scheme uses *clustered page tables*, which stores several pages in a single entry of a hash table (???).

#### Inverted Page Tables
Usually, page tables map from virtual addresses to physical addresses. This, however, itself takes up a lot of physical space. We solve this problem with an *inverted page table*, which has an entry for each physical frame storing its virtual address and information about the process that owns it.

While this reduces the amount of space required, it increases lookup time. It also makes the implementation of shared memory more difficult.

#### Oracle SPARC Solaris

### 8.7 Example: Intel 32- and 64-Bit Architectures

### 8.8 Example: ARM Architecture

### 8.9 Summary

## Chapter 9: Virtual Memory
Virtual memory allows systems to execute processes without loading them completely into memory. This has the advantage of both abstracting main memory, and of allowing programs to be larger than virtual memory.

### 9.1 Background
Memory-management algorithms are required because the instructions being executed need to be in physical memory. While dynamic loading can help to ease this, it requires extra overhead on the part of the programmer.

This, however, limits the size of the program to the size of physical memory. This is a big restriction – the ability to execute a memory that is not completely in memory has a lot of benefits:

* The users could program for an larger virtual address space rather than a smaller physical one.
* Many programs could be run simultaneously.
* Less I/O would be needed to load or swap user programs.

Virtual memory is the basis for this – it separates logical memory from physical memory, providing programmers with a large virtual memory. The virtual address space of a process is the view of the memory space as seen by that process.

The virtual address space is organised into sections for the code, the data, the heap and the stack. The heap and stack grow towards each other (upwards and downwards respectively), and the space between them is mapped to physical space only as needed. This gap is called a *hole* – address spaces with holes are called *sparse*. Sparsity allows for dynamic linking of libraries and other objects.

Virtual memory also allows or files and memory to be shared between processes, with the following benefits:

* System libraries can be shared by several processes.
* Regions of memory can be shared between processes.
* Pages can be shared during process creation by `fork()`ing, which speeds up process creation.

### 9.2 Demand Paging
Consider the circumstances in which an executable is loaded into memory. The entire program may be loaded at execution time, but this may not be required; alternatively, we may load pages only as they are needed. This is called *demand paging*.

A demand-paging system is similar to a paging system with swapping, although calling a system that moves pages into a system cannot be called a swapper – it only manipulates pages, not processes. The pager in such systems is *lazy* – it does not move a page into memory unless it will be needed.

#### Basic Concepts
When a process is swapped in, the pager only brings in those pages which it guesses will be used before the process is swapped out.  

We need to distinguish between (logical) pages that are in memory and those that are on disk – we use a single-bit field in the page table to indicate whether a page is valid and in memory or not.  
Now, if a program tries to access a page not in memory, it causes a *page fault*, which triggers a check for whether or not the reference was valid. If it was, we bring the required page in by finding a free frame and allocating it, and modifying the relevant entries in the process and page tables. Then the instruction that was interrupted is rerun.  
If the system starts with no pages in memory, it follows a *pure demand paging* scheme – only the necessary pages are brought into memory.

In theory, it is possible for programs to access several new pages in a single instruction, which would have unacceptable impacts on performance; however, in practice, programs tend to have *locality of reference*, which results in reasonable performance.

There is similar hardware support for demand paging as for paging and swapping – a page table (with a valid-invalid bit or protection bits) and a secondary memory (or *swap space*).

Restarting interrupted instructions poses some problems, however – consider the case where an instruction may modify several different locations. One way to avoid this is to try to access both ends of both blocks before starting the instruction.

#### Performance of Demand Paging
Consider the *effective access time* in a demand-paged system. If $p$ is the probability of a page fault, then this is equal to $(1-p) \times \text{(memory access time)} + p \times \text{(page fault time)}$.

The page fault time has three major components – servicing the interrupt, reading in the page, and restarting the process. Of these, the first and third can be reduced to an overhead of the order of 1-100 microseconds each; the page-swich time is the RDS, taking about 8 milliseconds. Given a memory access time of 200 nanoseconds, this gives us an effective access time of approximately $200 + 7,999,800p$.  
For a performance degrade of less than 10%, then, we need $p < 2.5 \cdot 10^{-6}$. Thus, less than one memory access out of nearly 400,000 should result in a page-fault.

The handling of swap space is another consideration in demand-paged systems.  
Since swap space I/O is faster than filesystem I/O, a system can achieve better throughput by copying a file image into the swap space at process startup and then exclusively paging between memory and the swap space.  
Alternatively, it may initially page in from disk but replace the page in the swap space after paging out.  
Some systems carry out demand paging of binary files, which are non-modifiable and so can be overwritten instead of being paged out. Swap space is still, however, used for *anonymous memory* (pages not associated with a file), like the stack and heap.

### 9.3 Copy-on-Write
Process creation using the `fork()` syscall may bypass the need for demand paging by using a technique similar to page sharing – this optimised process creation and minimises page allocation to the new process.

Since children processes frequently call `exec()` immediately after creation, duplicating the parent's address space is unnecessary in these cases. A technique called *copy-on-write* allows the parent and child to initially share the same pages (marked as copy-on-write pages), which are duplicated only if either process modifies them. Pages that cannot be modified, however, remain shared by the processes.

Many OSs maintain a pool of free pages for such allocations. This is done by a scheme called *zero-fill-on-demand* – pages are zeroed out before allocating.

### 9.4 Page Replacement
We can increase our degree of multiprogramming by *over-allocating* memory. This, however, may lead to a situation where page is to be allocated but there are no free frames – this can be solved by either reducing the degree of multiprogramming (by swapping out a process) or page replacement.

#### Basic Page Replacement
If no frame is free, we can free one that is not being currently used and use it. However, note that this requires two operations – a page out and a page in – which leads to an overhead. We can reduce this overhead by using a *modify bit* or *dirty bit*, which indicates whether a page has been modified or not.

Thus, we now require a frame-allocation algorithm and a page-replacement algorithm. Page-replacement algorithms are evaluated by simulating their performance on a string of memory references.

#### FIFO Page Replacement
A FIFO replacement algorithm records the time when a page is brought into memory (or maintains a queue of all pages in memory) and replaces the most recently paged in one.

This algorithm illustrates *Belady's anomaly* in some cases – the number of page faults increases with the number of allocated frames.

#### Optimal Page Replacement
The optimal page replacement algorithm simply consists of replacing the page that will not be used for the longest period of time – this guarantees the lowest possible page-fault rate.

#### LRU Page Replacement
This algorithm is effectively the opposite of the FIFO algorithm – the *least recently used* page is replaced. This can be implemented by recording the time of paging in (by copying the contents of a clock) or with a stack; however, both of these add a lot to the memory overhead.

This algorithm, and optimal replacement, do not suffer from Belady's anomaly – they belong to a class called *stack algorithms*, for which it can be shown that the set of pages in memory for $n$ frames is a subset of those that would be in memory with $n+1$ frames.

#### LRU-Approximation Page Replacement
Some systems provide a *reference bit* for each page, which is set when the page is referenced.

##### Additional-Reference-Bits Algorithm
We can store additional bits – say eight – for each page, and record the values at regular intervals. The page with the lowest value stored in these is then the LRU page.

##### Second-Chance Algorithm
The second-chance algorithm replaces the most recently used page *with a cleared reference bit*. If the MRU page has a set reference bit, it is cleared before checking the next one.  
This can be implemented by a circular queue, with a pointer that clears bits as it advances..

##### Enhanced Second-Chance Algorithm
We can consider the reference and modify bits as an ordered pair, which gives us the following possibilities:

* $(0,0)$ – neither used nor modified; best page to replace
* $(0,1)$ – not used but modified; will have to be paged out
* $(1,0)$ – recently used but clean; will probably be used again
* $(0,0)$ – both

#### Counting-Based Page Replacement
This is a class of algorithms that maintains a count of references for each page. For example, we may have least frequently used (LFU) or most frequently used (MFU) page replacement; however, neither of these is common and they are not close to optimal.

#### Page-Buffering Algorithms
These algorithms are augmentations of page-replacement algorithms – for example, we may read a page into a free frame before writing out a victim page, which allows the process to start again as soon as possible.

We may also maintain a list of modified pages, which can be rewritten to disk when the paging device is idle (thus making them clean again).

We could also record which page was in each frame, and continue to access it even after it has been paged out (if that frame was not reused).

#### Applications and Page Replacement

### 9.5 Allocation of Frames
We need to decide how to allocate free frames among processes.

#### Minimum Number of Frames
We must allocate a minimum number of frames to all processes, for reasons of performance. This number is defined by the computer architecture.

#### Allocation Algorithms
One simple way is to allocate an equal share of frames to each process; this is called *equal allocation*.

However, processes require different amounts of memory; we solve this with *proportional allocation*, where the number of pages is decided according to the size of the process.

Note that neither of these algorithms take priority into account.

#### Global versus Local Allocation
Page-replacement algorithms are classified into two categories – those that allow a replacement frame to be selected from the set of all frames (*global replacement*), and those that require it to be from the replacing process's set (*local replacement*).

Global replacement has the disadvantage that it makes throughput and runtime non-deterministic, but local replacement algorithms hinder a process by preventing it from accessing less used pages.

#### Non-Uniform Memory Access
Many systems have memory that has lower access time in certain regions than in others – these are called *non-uniform memory access* (NUMA) systems. These systems are especially susceptible to changes in the location of page frames – page frames should be stored in locations "closer" to the CPU for higher throughput.

### 9.6 Thrashing
When a process does not have enough frames, it ends up faulting repeatedly, and replacing and bringing back pages with high frequency. This is called *thrashing*.

#### Cause of Thrashing
Thrashing causes CPU utilisation to decrease, which results in increased multiprogramming, which then causes even more page faults and increased thrashing.

This effect can be limited by using local replacement or priority replacement, but these do not entirely solve the problem. We need to know how many frames a process needs – one approach to this question is defined by the *locality model*, which posits that a process moves from locality to locality as it executes. Localities are defined by the program's structure and the data structures it uses.

#### Working-Set Model
The working-set model is based on the locality principle – a parameter $\Delta$, the *working-set window*, defines the *working set*, which is the most recent $\Delta$ page references. The working set is updated every timestep.

The most important property of the working set is its size. Let $D$ be the total demand for frames; then
$$D = \sum_\text{processes} \text{working-set size}.$$
If $D > m$, the total number of available frames, thrashing will occur.

The OS, then, allocates frames to each process according to the working-set size, and initiates or suspends processes according to the demand.

The working-set model is approximated by a fixed-interval timer interrupt and a reference bit.

#### Page-Fault Frequency
Some strategies make use of page-fault frequency (PFF) – they allocate frames if it is high, and remove frames if it is low.

#### Concluding Remarks

### 9.7 Memory-Mapped Files
*Memory mapping* a file consists of using virtual memory techniqes to treat file I/O as routine memory accesses. This allows a part of the virtual address space to be logically associated with the file.

#### Basic Mechanism
Disk blocks are mapped to pages in memory, which are then handled by ordinary demand paging. This then reduces file manipulation to simple memory access, which is much faster.  
Note that writes to memory-mapped files are not necessarily synchronised to disk updates.

Multiple processes may map the same file concurrently, and all updates are seen by all processes sharing the file.

#### Shared Memory in the Windows API

#### Memory-Mapped I/O
We have seen that I/O controllers include registers to hold commands and data, which special I/O instructions access. Many architectures provide *memory mapped I/O* – ranges of memory addresses are mapped to device registers, which can be read and written to.

Memory mapped I/O is appropriate for devices with fast response times, like video controllers, but also for the serial and parallel ports that connect devices to a computer. The CPU transfers a byte to the port, sets a control bit, and waits; when the control bit is cleared, the process is repeated. The control bit may be polled (*programmed I/O*) or it may interrupt the system on being cleared (*interrupt-driven I/O*).

### 9.8 Allocating Kernel Memory
When a user process requests memory, pages are allocated from a list of pages maintained by the kernel, which is populated by page replacement algorithms, and contains free pages from throughout memory.

Kernel memory, however, is allocated from a different pool. This is because kernel memory usage is especially prone to fragmentation, and because it sometimes requires contiguous pages.

We consider two strategies for managing free memory for kernel processes.

#### Buddy System
Under this system, memory is allocated from a fixed-size segment consisting of contiguous pages. The allocator satisfies requests in units sized as powers of two, with rounding up. At allocation time, each memory segment is divided into two buddies until the appropriate size is found. Adjacent buddies can be quickly combined into larger segments using *coalescing*.

However, this system can lead to high fragmentation.

#### Slab Allocation
A *slab* consists of one or more continguous pages, and a *cache* consists of one or more slabs. Each kernel data structure has a single cache, populated with objects of that data structure's type.

The slab allocator first attempts to satisfy a request with a free object in a partial slab (which contains some free objects); if none exists, a free object is assigned from an empty slab; if none exists, a new slab is allocated.

The slab allocator has two main benefits:

* Fragmentation does not cause any wastage.
* Memory requests can be satisfied quickly.

### 9.9 Other Considerations
Aside from the selection of a replacement algorithm and an allocation policy, there are a number of considerations in a paging system.

#### Prepaging
Prepaging involves trying to reduce the high level of initial paging that processes have – the strategy is to bring into memory at one time all the pages that will be needed.

#### Page Size
Page sizes range from $2^{12}$ to $2^{22}$ bytes. A smaller page size increases the size of the page table, but utilises memory better and has a smaller transfer time.  
Smaller page size also improves *resolution*, which makes for better locality.

#### TLB Reach
The TLB reach refers to the amount of memory accessible from the TLB. It should be big enough for the working set of a process.  
It can be increased by increasing the page size, or, alternatively, by providing multiple page sizes.

#### Inverted Page Tables
Inverted page tables reduce the amount of memory required to store the mapping from physical to virtual memory, but no longer contains complete information.

#### Program Structure
Careful selection of data structures and programming structures can increase locality. The compiler and loader can also have a significant effect on paging; for example, the loader can place routines completely within single pages.

#### I/O Interlock and Page Locking
Some pages sometimes need to be *locked* in memory, *e.g.*, when I/O is done to or from virtual memory (to prevent the I/O-accessed location from being paged out while the process is waiting).

There are two solutions to this – never execute I/O in user memory (only to system memory), or to allow pages to be locked into memory. The latter involves associating a lock bit to each frame, which determines whether or not it can be selected for replacement.

Lock bits are used in various situations:

* The kernel code may be locked into memory.
* A database process may pin page into memory.
* We may want to avoid the replacement of a page that was newly brought in (but whose process has been swapped out).

### 9.10 Operating-System Examples

### 9.11 Summary

# Part Four
## Chapter 10: Mass-Storage Structure
The file system consists mainly of three parts – secondary storage, a user interface, and the algorithms and data structures used to implement this interface.

### 10.1 Overview of Mass-Storage Structure
#### Magnetic Disks
The bulk of secondary storage for modern systems is formed by magnetic disks. They are composed of platters, each of which has a flat circular shape and is covered with a magnetic material on both surfaces.  
A read-write head moves above each surface, attached to an arm (common to all heads). The surface is divided into tracks, subdivided into sectors. The set of all tracks at one (radial) position makes up a cylinder.

The *positioning time* for moving a head to the desired locatino consists of the *seek time* plus the *rotational latency*.

A disk drive is attached to a computer by an I/O bus, and the data transfers are carried out by *controllers* (a *host controller* on the computer end and a *disk controller* on the disk end). Disk controllers usually have a built-in cache.

#### Solid-State Disks
An SSD is a nonvolatile memory that is used like a hard drive. They are more reliable than traditional ones, as they have no moving parts and have no latency. However, they are more expensive, have less capacity, and have shorter life spans.

Their speed means that the standard bus interface becomes the RDS in throughput.

#### Magnetic Tapes
Magnetic tapes are relatively permanent and have high capacity, but have slow access times. They are mainly used for backup.  
The tape is kept on a spool and wound or unwound past a read-write head. This increases positioning time, but actual data transfer happens at comparable speeds.

### 10.2 Disk Structure
Modern disk drives are addressed as large one-dimensional arrays of logical blocks (which are the smallest unit of transfer), usually about 512 bytes. These blocks are mapped to sectors of disk sequentially, from the outermost to the innermost tracks.

The translation from an array index to an old-style disk address is difficult for two reasons – first, some sectors may be defective, and another is that the density of data may not be uniform (in *constant angular velocity* (CAV) systems).

### 10.3 Disk Attachment
Computers can access disk storage via *host-attached storage* (I/O ports) or *network-attached storage* (a remote host in a distributed file system).

#### Host-Attached Storage
Local I/O ports use several technologies. Typical desktop PCs use an architecture called IDE or ATA (at most two drives per I/O bus), while high-end workstations use more sophisticated I/O architectures like fibre channel.

Storage devices suitable for this approach are hard disk drives, RAID arrays, and CD, DVD and tape drives.

#### Network-Attached Storage
A NAS device is a special-purpose storage system that is accessed remotely over a data network. They are accessed via a RPC interface.

#### Storage-Area Network
Storage I/O operations consume bandwidth on a data network – this is a disadavantage of NAS systems. A SAN is a private network dedicated to connecting servers and storage units.

### 10.4 Disk Scheduling
The efficient use of disk drives depends on reducing the access time (the seek time and the rotational latency) and increasing disk bandwidth. These can both be achieved by managing the order in which disk I/O requests are serviced.

Pending I/O requests are placed on a queue, and the system needs to choose which request to service when the device is free. Disk-scheduling algorithms are used to make this choice.

#### FCFS Scheduling
This algorithm is fair, but does not provide the fastest service. It may involve a lot of swinging between locations on the disk, which increases average access time.

#### SSTF Scheduling
The *shortest-seek-time-first algorithm* is based on the assumption that the requests closest to the current head position should be serviced first. This method, like SJF scheduling, can cause starvation of some requests.

#### SCAN Scheduling
The disk arm in this algorithm starts at one end and moves towards the other, servicing requests as it proceeds. It reverses direction at the end of a pass.

#### C-SCAN Scheduling
*Circular SCAN* is a variant of SCAN designed to provide a more uniform wait time; the head returns to the beginning of the disk without servicing any requests on the way back.

#### LOOK Scheduling
This is a modification of SCAN scheduling where the head only goes until the last request in either direction.

#### Selection of a Disk-Scheduling Algorithm
SSTF is common since it increases performance over FCFS; SCAN and C-SCAN perform better if there is a heavy load on the disk.  

The file allocation method has a great impact on the requests for disk service – contiguously allocated files generate requests with high locality, while linked or indexed files will require greater head movement.  
Similarly, where the directories and index blocks are stored makes a considerable difference.

Modern disks, however, have a high rotational latency as well as high seek time, and do not disclose the location of the physical blocks; this means that scheduling must be performed by the controller hardware of the disk drive. The additional responsibility that the OS has of managing operations like paging, though, makes this a hard choice.

### 10.5 Disk Management
#### Disk Formatting
The division of a magnetic disk into sectors is called *physical* or *low-level* formatting; this fills the disk with a special data structure for each sector, which consists of a header, a trailer (which have information for the controller, like the sector number and an ECC) and a data area.

The OS then partitions a disk into cylinders, and creates a file system (*logical formatting*; initial file-system data structures are stored on disk).  
For efficiency, blocks are grouped into larger chunks, called *clusters*, which are used for file I/O. This ensures that file I/O has more sequential-access characteristics and less random-access characteristics.

#### Boot Block
The initial bootstrap program, which finds the kernel on disk, loads it, and jumps to the initial address, is stored in ROM. It cannot, however, be changed without changing the ROM hardware, so many systems have a bootstrap loader program in the boot ROM, which is easier to change. The bootstrap program itself is stored in the *boot blocks* on disk.

#### Bad Blocks
One or more sectors in the disk may be defective or damaged. This can be handled by flagging bad blocks during formatting, or maintaining a list of bad blocks that gets updated during operation. Sectors may also be kept in spare to sub in for bad blocks.

### 10.6 Swap-Space Management
Swap-space management is another low-level task of the OS.

#### Swap-Space Use
Different OSs use swap space differently; for example, it may hold an entire process image (with code and data) or pages pushed out of main memory.

#### Swap-Space Location
Swap space can be taken from the normal filesystem, or have its own disk partition. If it is a large file within the file system, it can be manipulated by normal file-system routines, although this is inefficient.

A *raw partition* can be used for swap space, which is handled by a separate swap-space storage manager. This uses algorithms optimised for speed rather than storage efficiency – thus it may, for instance, cause some degree of internal fragmentation. This creates a fixed amount of swap space, however.

#### Swap-Space Management: An Example

### 10.7 RAID Structure
Computer systems can have many disks attached, which allows for improvements in the rate of data transfer and the reliability of storage. A variety of techniques, called *redundant arrays of independent disks*, is used to address these issues.

#### Improvement of Reliability via Redundancy
When we have more disks, there is a higher chance that one of them fails. We fix this problem by storing redundant information in the disks.

The simplest way to do this is to duplicate every disk (*mirroring*). However, power failures can damage both volumes simultaneously; therefore, some systems add a solid-state NVRAM cache to the array, which is protected from power failures.

#### Improvement in Performance via Parallelism
Multiple disks can improve the transfer rate by *data striping*. In its simplest form, the bits of each byte are split across multiple disks. This is *bit-level striping*; we may also implement *block-level* or *byte-level* striping.

This form of parallelism has two main goals – increase the throughput of batches of small accesses, and reduce the response time of large accesses.

#### RAID Levels
There are a number of schemes to provide redundancy at lower cost – these are classified according to RAID levels.

* **Level 0 (block-level striping).**
* **Level 1 (disk mirroring).**
* **Level 2 (memory-style error-correcting-code).** Parity bits stored in extra disks.
* **Level 3 (bit-interleaved parity).** More efficient usage of parity bits over level 2. Less overhead and more parallelism than level 1. Fewer I/Os per second and higher parity computation overhead.
* **Level 4 (block-interleaved parity).** Slow data transfer but parallelism.
* **Level 5 (block-interleaved distributed parity).** Spreads data and parity among all disks; for each block, one disk stores parity and rest store data.
* **Level 6 (P + Q redundancy).** Reed-Solomon code instead of parity.
* **Level 0+1/1+0.** Performance + reliability. Expensive.

*Snapshots* and *replication* may also be implemented alongside RAID, for higher reliability. *Hot spares* may also be used.

#### Selecting a RAID Level
Rebuild performance is a common metric in evaluating RAID levels. It is easiest for level 1, and may take hours for level 5.

Level 0 is used in applications where loss is not critical.  
Level 1 is used in applications that require high reliability with fast recovery.  
Level 0+1 and 1+0 are used where performance and reliability are both important. However, level 5 is preferred for large volumes of data.

#### Extensions
RAID concepts have been generalised to other storage devices and to other areas like data broadcast (data is split, augmented with ECCs, and then transmitted).

#### Problems with RAID
RAID does not protect against hardware and software errors. File corruptions, for example, are handled by checksums in some file systems.

RAID implementations also tend to be inflexible, in matters of space availability. Even if enough hardware is available, the volume manager may not allow for changes in volume size.

### 10.8 Stable-Storage Implementation
For implementing stable storage, we need to write data to multiple storage devices with independent failure modes. We also need to ensure that the disks are never inconsistent at any point, and that failures do not affect even recovery.

A disk write may be successful, a partial failure, or a total failure.  
In order to carry out recovery, the system must maintain two physical blocks per logical block – both are written to sequentially, and the write is declared complete only after both operations are successful.  
During recovery, each pair of blocks is examined. If both are the same, no further action is necessary; if one contains a detectable error, it is replaced with the contents of the other; if they differ in content but have no error, replace the first block with the second.

Many storage arrays add an NVRAM cache because synchronous I/O is slow.

### 10.9 Summary

## Chapter 11: File-System Interface
The file system consists of a collection of files and a directory structure that provides information about the files.

### 11.1 File Concept

### 11.2 Access Methods

### 11.3 Directory and Disk Structure

### 11.4 File-System Mounting

### 11.5 File Sharing

### 11.6 Protection

### 11.7 Summary