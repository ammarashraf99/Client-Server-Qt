# Client-Server-Qt

## Overview

This project is a **client–server application** written in **C++ using Qt 6**.
The server listens on a TCP socket and accepts textual commands from clients to perform
file-system related operations such as creating, reading, writing, listing, and deleting files.

The server is designed to be **modular, extensible, and thread-safe**, using well-known
object-oriented design patterns.

---

## Features

- TCP-based client–server communication
- One thread per client connection
- Command-based request handling
- Clean separation of networking, parsing, execution, and result handling
- Extensible command set
- Qt signals/slots and event-driven I/O

---

## Command Format

Requests sent to the server use the following format:

```
COMMAND arg1;arg2;arg3
```

### Examples:

```
AUTH admin,admin
CREATE test.txt
WRITE test.txt;Hello World
READ test.txt
LIST
DELETE test.txt
```

Arguments are separated using semicolons (`;`).

---

## Architecture Overview

The server follows a layered architecture:

	Client
	↓
	TCP Socket
	↓
	Connection Worker (Thread)
	↓
	Message Parser
	↓
	Command Factory
	↓
	Command Validation
	↓
	Command Execution
	↓
	Result Object
	↓
	TCP Response

Each client connection is handled in its own thread.

---

## Design Patterns Used

### 1. Command Pattern

Each request sent by the client is represented as a **Command object**.

- A common `Command` interface defines the contract.
- Each concrete command (`ReadCommand`, `WriteCommand`, `CreateCommand`, etc.)
  encapsulates its own validation and execution logic.
- The caller executes commands polymorphically without knowing their concrete type.

This makes the system easy to extend by adding new commands without modifying existing code.

---

### 2. Factory Method Pattern

A `CommandFactory` is responsible for creating the appropriate `Command` object
based on the parsed client request.

- The factory isolates command creation logic.
- The server depends only on the `Command` interface, not on concrete implementations.

This supports the Open/Closed Principle and keeps object creation centralized.

---

### 3. Result Object Pattern

All stages of request handling produce or modify a `Result` object.

- The `Result` object encapsulates:
  - success or failure state
  - error code
  - message or payload
- The final `Result` is serialized and written back to the client socket.

This provides consistent error handling and simplifies response generation.

---

### 4. Dispatcher Pattern

The server uses a Dispatcher (handleLine) to route incoming requests to the appropriate commands.

- Each client connection is handled by a connectionWorker.
- The worker:
  1. Reads raw data from the TCP socket
  2. Parses the request into a structured form
  3. Dispatches the request by invoking the CommandFactory
  4. Executes the resulting command
  5. Writes the result back to the client

The dispatcher decouples network I/O from business logic, ensuing clear separation of responsibilites.

---
### 5. Thread-per-Connection Pattern

The server uses a thread-per-connection concurrency model.

- Each incoming client connection spawns a dedicated worker thread.
- A ConnectionWorker object is moved to its own QThread.
- All socket I/O and command execution for that client occur within that thread.

This model:

- Simplifies concurrency by avoiding shared mutable state
- Keeps each client isolated
- Works well for moderate numbers of concurrent clients


## Building the Project

### Requirements

- Qt 6 (Core and Network modules)
- qmake
- make
- C++20-compatible compiler

---

### Build Server and Client

From the project root:

```bash
qmake
make
```

When you run, you need to be authenticated first in the connection.
You use

```
AUTH admin,admin
```

---

## Tests

There only one test for the parser in the core module.
Other tests will be implemented.

You need to install gtest for development to compile and run the test.

For Debian/Ubuntu

```bash
sudo apt install libgtest-dev
```

Make the test_script.h executable


```bash
cd ./Server/core/
chmod +x test_script.sh
```

Then run the test_parser executalbe.

```bash
./test_parser
```

