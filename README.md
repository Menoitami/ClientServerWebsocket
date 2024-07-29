# WebSocket Client-Server Application

## Overview

This project consists of two programs: a client and a server. The client program uses two threads to process and send data to the server, while the server receives, processes, and prints the data to the console.

## Features

- **Client**:
  - Connects to a WebSocket server.
  - Uses two threads for data processing and sending.
  - Supports reconnection in case of connection loss.

- **Server**:
  - Accepts WebSocket connections from clients.
  - Processes received data.
  - Prints the processed data to the console.

## Getting Started

### Prerequisites

- C++17 or later
- Boost Libraries (Beast, Asio, etc.)
