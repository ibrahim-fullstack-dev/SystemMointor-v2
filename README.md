# 🖥️ System Monitor v2

**System Monitor v2** is a next-generation infrastructure monitoring platform designed for real-time tracking of remote servers and personal computers. It provides users with a comprehensive, low-latency web dashboard to access, monitor, and audit system vitals securely, alongside remote reverse control from anywhere in the world.

## 📋 1. Requirements Analysis

**🎯 1.1 (The What)**

- It is a production line consisting of three main parts:

1. Agent (written in C++): A lightweight background daemon running on the host machine or server. Its sole function is to directly interact with the OS kernel to fetch data from hardware components.

2. Backend (written NestJS): A centralized intermediary server. It receives the live telemetry data from the C++ Agent and broadcasts it to the internet immediately. It also receives remote commands from the dashboard and securely routes them back to the target device.

3. Frontend (written in React): A responsive web application accessible from any device globally (computer or phone). It visualizes hardware info on live charts and provides a secure command interface containing control buttons (e.g., an emergency shut down button, kill process etc...).

**💡1.2 (The Why)**

- ❌ The Problem: While many monitoring tools exist, they often suffer from poor user experience, delayed alerts, and an inability to take action. System Monitor v2 was built to solve these exact user frustrations by focusing on three core motivations:

- ✅ The Solutions:

1. **Universal Accessibility & Ease of Use:** System administrators shouldn't be tethered to complex VPN setups, local networks, or intimidating terminal screens just to check their hardware. This project democratizes server management by providing a sleek, responsive web dashboard. A user can securely monitor their entire infrastructure from a laptop, tablet, or smartphone anywhere in the world with zero friction.

2. **Active Device Protection (From Passive to Reactive):** Most monitoring platforms are strictly "passive"—they only send an email alert when a server is already overheating or crashing. This system transitions to "active" protection by acting as a two-way control center. If an administrator spots a critical spike on the dashboard, they don't need to waste time logging into the server manually; they can instantly push a reverse command (like an emergency SHUTDOWN) directly from the browser to save the hardware before catastrophic damage occurs.

3. **Peace of Mind Through Instant Visibility:** Traditional monitoring setups rely on delayed polling (e.g., refreshing data every 1 to 5 minutes), leaving IT teams blind to sudden traffic spikes or memory leaks between those intervals. By streaming true, sub-second live telemetry, this project gives engineers absolute peace of mind. They can trust that they are seeing the exact, live pulse of their machines the very millisecond a change happens.

## 🏗️ 2. System Design & Data Flow

- Design overall solution and how components work together:

**🔄 2.1 End-to-End Data Pipeline**

The live hardware telemetry flows through three distinct stages:

```text
       ┌─────────────────────────────────────────────────────────┐
       │ Operating System Service Manager (Windows SCM / systemd)│
       └───────────────────────────┬─────────────────────────────┘
                                   │ (Spawns, Monitors & Controls Lifecycle)
                                   ▼
┌────────────────────────────────────────────────────────────────────────┐
│                      1. C++ SYSTEM MONITOR AGENT                       │
│                                                                        │
│   ┌────────────────────────────────────────────────────────────────┐   │
│   │                    Data Access Layer (DAL)                     │   │
│   │          [WindowsMetricsReader / LinuxMetricsReader]           │   │
│   └──────────────────────────────▲─────────────────────────────────┘   │
│                                  │ (Reads System Vitals)               │
│                                  ▼                                     │
│                 [ Hardware / OS Kernel /proc ]                         │
│                                  ▲                                     │
│                                  │ (Executes Remote Commands)          │
│   ┌──────────────────────────────▼─────────────────────────────────┐   │
│   │                  Business Logic Layer (BLL)                    │   │
│   │                       [MonitoringLogic]                        │   │
│   │    ⚙️ Runs inside an interruptible Background Thread           |   |
│   │    ⚙️ Condition Variable Loop (3-Second Smart Wakeup Timer)    |   |
│   └──────────────────────────────▲─────────────────────────────────┘   │
│                                  │ (Encapsulates Data / Decodes Commands)
│                                  ▼                                     │
│   ┌────────────────────────────────────────────────────────────────┐   │
│   │                    Network / Gateway Layer                     │   │
│   │                       [WebSocketClient]                        │   │
│   └──────────────────────────────▲─────────────────────────────────┘   │
└──────────────────────────────────┼─────────────────────────────────────┘
                                   │
                                   │ 🔄 Full-Duplex WebSockets Link
                                   │    ▲ Upstream: Continuous Telemetry (JSON)
                                   │    ▼ Downstream: Reverse Remote Commands
                                   │
┌──────────────────────────────────▼─────────────────────────────────────┐
│                       2. NestJS GATEWAY SERVER                         │
│                                                                        │
│    • Manages active device connections & maps unique Socket IDs.       │
│    • Ingests live streams from Agent and immediately broadcasts them.  │
│    • Securely routes reverse control JSON frames back to the target.   │
└──────────────────────────────────┬─────────────────────────────────────┘
                                   │
                                   │ 🔄 Full-Duplex WebSockets Link
                                   │    ▲ Upstream: Live Dashboard Rendering
                                   │    ▼ Downstream: User Control Input Action
                                   │
┌──────────────────────────────────▼─────────────────────────────────────┐
│                        3. REACT WEB DASHBOARD                          │
│                                                                        │
│    • Renders live telemetry on responsive, low-latency charts.         │
│    • Implements clean memory buffering to prevent browser crashes.     │
│    • UI Command Grid: Direct action triggers (e.g., Force Shutdown).   │
└────────────────────────────────────────────────────────────────────────┘
```

**📝 2.2 Structural Breakdown & Component Descriptions:**

1. C++ SYSTEM MONITOR AGENT

```text
📁 SystemMonitorAgent/
│
├── 📄 CMakeLists.txt
├── 📄 config.json
|
├── 📁 include/                          # 🎯 All Headers Files (.hpp)
│   ├── 📁 config/
│   ├── 📁 enums/
│   ├── 📁 models/                       # Pure Containers
│   │   ├── 📁 raw/                      # OS Raw Models
│   │   └── 📁 dto/                      # Clean DTOs
│   ├── 📁 interfaces/                   # Pure Inrefaces.
│   │   └── 📁 processors/
│   ├── 📁 readers/                      # DAL Headers.
│   │   ├── 📁 hardware/
│   │   └── 📁 network/
│   └──📁 processors/                   # BL Headers.
│       ├── 📁 core/
│       ├── 📁 hardware/
|       └── 📁 network/
├── 📁 src/                              # 🎯 Implementation Source Files (.cpp)
│   ├── 📁 config/
│   ├── 📁 readers/
│   │   ├── 📁 windows/
│   │   └── 📁 linux/
│   ├──📁 processors/
│   |   ├── 📁 core/
│   |   ├── 📁 hardware/
|   |   └── 📁 network/
|   └── 📄 main.cpp
├── 📁 platforms/                             # OS Background Service Wrappers
│   ├── 📁 windows/
│   └── 📁 linux/
├── 📁 build/
└── 📁 tests/                                 # Automated Test Target Suites
    ├── 📁 unit/
    └── 📁 integration/
```

## ⚖️ 3. Architecture Decisions (ADRs)

### 🧩 3.1 Agent Project Decisions

#### Decision 1: C++ Native Target vs. Managed Worker Templates

- ❌ **The Problem:** Built-in IDE templates (like C# Worker Service / other languages) require heavy runtimes, consuming 30–50 MB of RAM idle with unpredictable Garbage Collection (GC) spikes.

- ✅ **The Solution:** A native executable project manually configured via CMake using compiled .cpp/.hpp files.

- 🚀 **The Impact:** Direct interaction with OS Kernel APIs (Windows API / Linux /proc), a tiny 2–5 MB RAM footprint, zero runtime dependencies, and < 1% CPU overhead.

#### 🔌 Decision 2: WebSockets (WSS) vs. HTTP REST Polling

- ❌ **The Problem:** Traditional HTTP REST polling creates immense network overhead by constantly opening/closing connections and repeating bulky text headers.

- ✅ **The Solution:** A single, persistent Bi-directional WebSocket (TCP) connection.

- 🚀 **The Impact:** Eliminates HTTP header waste, slashes bandwidth consumption, and achieves true sub-second, full-duplex telemetry and remote control.

#### 🚀 Decision 3: Data-Oriented Programming (DOP) vs. Classic Polymorphic OOP

- ❌ **The Problem:** Traditional Object-Oriented patterns bundle data with behavior into heavy objects. Spreading an array of polymorphic Core objects or pointer-chasing collections across RAM causes massive CPU Cache Misses and VTable runtime overhead, causing the background agent to run slow and experience "Cache Stalls" while waiting for RAM.

- ✅ **The Solution:** A strict Data-Oriented Design (DOD) approach utilizing Structures of Arrays (SoA) layout inside the Data Access Layer loops. We strip virtual inheritance and dynamic allocations from fast polling routines, keeping all raw telemetry numbers sequentially aligned in flat contiguous memory blocks (std::vector or raw buffers).

- 🚀 **The Impact:** Radical reduction in execution time due to maximum Spatial and Temporal Cache Locality. A single 64-byte CPU cache line pull automatically fetches up to 8 core metrics at once, enabling the compiler to effortlessly use SIMD Vectorization (Single Instruction, Multiple Data) to process massive system telemetry loops concurrently while staying safely below the strict < 1% CPU target.

### 🧩 3.2 Backend Project Decisions

#### 🏗️ Decision 1: NestJS for the Backend Server Gateway

- ❌ **The Problem:** Raw Node.js/Express servers lack structural enforcement, leading to unmaintainable code as real-time features grow.

- ✅ **The Solution:** NestJS Framework (TypeScript) utilizing native Dependency Injection.

- 🚀 **The Impact:** It bridges the gap between high-speed asynchronous networking and strict engineering architecture, isolates the streaming engine (agent-gateway) from the health checks (background-tracker), and scales effortlessly.

### 🧩 3.2 Frontend Project Decisions

#### 🎨 Decision 1: React SPA (Vite) vs. Next.js Framework

- ❌ **The Problem:** Next.js introduces Server-Side Rendering (SSR) overhead, which is completely unnecessary for an internal, private real-time app with no SEO requirements.

- ✅ **The Solution:** A pure client-side React Single Page Application (SPA) bundled with Vite.

- 🚀 **The Impact:** Zero server-side state overhead; the browser downloads static assets once and dedicates 100% of its focus to painting live WebSocket data charts at 60 FPS.

## 🗄️ 4. Database Design (Polyglot Persistence)

To handle continuous telemetry streams without causing disk I/O bottlenecks, System Monitor v2 splits its data layer into two distinct storage paradigms:

```text
                           ┌───────────────────────────┐
                           │   NestJS Backend Server   │
                           └─────────────┬─────────────┘
                                         │
                 ┌───────────────────────┴───────────────────────┐
                 ▼ (Relational / ACID)                           ▼ (Time-Series / High Ingestion)
     ┌───────────────────────┐                       ┌───────────────────────┐
     │   PostgreSQL Engine   │                       │   TimescaleDB/Redis   │
     └───────────────────────┘                       └───────────────────────┘
     - User Profiles                                 - CPU/RAM Metrics Log
     - Device Registration                           - Historical Analytics
     - API Tokens & RBAC                             - Alert Threshold Logs

```

## 🔒 6. Security Planning

Securing the telemetry data pipeline is a top priority, as the C++ Agent reads highly sensitive host environment metrics. The security architecture is designed to balance robust protection with zero infrastructure cost, utilizing free open-source tools.

### 🌐 6.1 Data Transit & Environment Adaptation (Encryption)

- **Development Environment (Cost-Free Localhost):** During development and local testing, the system operates securely over standard `http://localhost` and `ws://localhost`. Modern web browsers natively treat localhost as a secure context, allowing full feature development without purchasing SSL certificates.
- **Production Environment (Automated Free Encryption):** When deployed to the cloud, the data stream is automatically upgraded to **HTTPS** and **WSS (Secure WebSockets)**. This is achieved at zero cost by utilizing **Let's Encrypt** (automated, free SSL/TLS certificates) or **Cloudflare's Free Tier** proxy, ensuring all high-frequency hardware metrics are fully encrypted in transit against man-in-the-middle (MITM) attacks.

### 🔑 6.2 Telemetry Ingress Validation (Authentication)

- **Cryptographic API Tokens:** Upon initial setup, each registered target machine is issued a unique, long-lived API Token.
- **Secure Connection Handshake:** When the C++ Agent initiates a dynamic WebSocket connection to the NestJS gateway, it must pass this token within the connection headers. The backend instantly validates the token against a hashed record in the PostgreSQL database. If the token is missing or invalid, the backend terminates the socket connection within 3 seconds to prevent unauthorized resource consumption.

### 🛡️ 6.3 Multitenancy & Data Isolation (Authorization)

- **Role-Based Access Control (RBAC):** Users are bounded by strict roles managed via NestJS Guards (`ADMIN`, `SERVER_OWNER`, `VIEWER`).
- **Targeted Socket Rooms:** The backend server strictly forbids public or global broadcasting of telemetry payloads. When an Agent connects, the NestJS gateway assigns that data stream to an isolated, private socket room linked exclusively to the device owner's ID. A user can only subscribe to data streams from machines they explicitly own or have been granted permission to audit.

## 🧪 7. Testing Strategy

To maintain absolute system stability, prevent regressions, and guarantee high availability before deploying to production environments, System Monitor v2 implements a multi-tiered, responsive verification framework.

### 📦 7.1 Testing Framework Architecture

- **🧩 Tier 1: Unit & Integration Testing**
  - **Target Subsystem:** Backend Gateway (`NestJS`)
  - **Tools Employed:** `Jest` / `Supertest`
  - **Core Objective:** Verify data transformation pipes, custom validation guards, and RBAC middleware isolation logic under isolated environments.

- **🏋️ Tier 2: Performance & Load Testing**
  - **Target Subsystem:** Infrastructure Gateway Cluster
  - **Tools Employed:** `k6` / `Artillery`
  - **Core Objective:** Simulate 1,000+ concurrent live C++ agents streaming high-frequency payloads to stress-test memory limits and connection thresholds.

- **🔍 Tier 3: Low-Level Memory Profiling**
  - **Target Subsystem:** Telemetry Agent (`C++`)
  - **Tools Employed:** `Valgrind` / `Dr. Memory`
  - **Core Objective:** Intercept runtime pointer assignments to detect dynamic memory leaks ($0\text{ B}$ target leak rate) during long-term daemon execution cycles.

---

### ⚙️ 7.2 Testing Implementations

- **🧩 Backend Integrity (Jest):** Automated tests isolate the NestJS controllers and WebSocket gateways. We mock the database connection to test how the server reacts to invalid tokens, expired sessions, and malformed JSON payloads from the network.
- **🏋️ Stress and Concurrency (k6):** We execute virtual user scripts that mimic thousands of active machines spinning up and opening WebSocket pipelines simultaneously. The goal is to measure server CPU/RAM exhaustion spikes and fine-tune socket room allocation thresholds.
- **🔍 Low-Level Safety (Valgrind):** Since C++ lacks automatic garbage collection, dynamic memory allocated on the heap (via `new` or raw pointers) must be explicitly freed. The C++ Agent is run through Valgrind memory checkers for hours under simulated load to guarantee zero memory leaks ($0\text{ B}$ leak rate), ensuring it can run continuously for months on client servers.

## ⚡ 8. Performance Optimization

To ensure the telemetry platform can scale to accommodate thousands of concurrent infrastructure nodes without experiencing hardware degradation or excessive network congestion, System Monitor v2 integrates advanced optimization architectures.

### 🌐 8.1 Data Serialization Migration (Future Implementation)

- **The Paradigm Shift:** Migrating upstream and downstream telemetry payloads from verbose, string-based **JSON** formats to strongly-typed **gRPC / Protocol Buffers (Protobuf)**.
- **The Impact:** JSON sends raw text keys (like `"cpu_utilization": 45`) repeatedly every second, which wastes network packets. Protocol Buffers serialize this data into an immutable, highly compressed binary format. This transition reduces network serialization payload overhead by **up to 70%**, minimizing packet fragmentation and significantly lowering network bandwidth costs.

- **Architectural Readiness (Future-Proof Design):** Thanks to the **Dependency Inversion Principle (SOLID)** enforced in the current architecture, the Business Logic Layer (`Processors`) is completely decoupled from the Network Layer via the `WebClientProvider` abstract interface. Transitioning to Protobuf/gRPC in the future will require **zero changes** to the hardware-reading logic. We will simply plug in a new `ProtobufWebSocketClient` implementation that inherits from `WebClientProvider`, leaving the core engine untouched

### ⏱️ 8.2 Event-Driven Dynamic Throttling (Resource Conservation)

- **The Paradigm Shift:** Implementing a reactive feedback loop between the NestJS gateway and the remote C++ Agents using an active client detection algorithm.
- **The Impact:** If the NestJS server detects that no authorized administrator is currently viewing a specific machine's web dashboard, it emits a background signaling event back to that machine's respective C++ Agent. Upon reception, the Agent dynamically toggles its internal loop hardware sampling rate from high-frequency mode (**1 second**) to economy sleep mode (**60 seconds**). This preserves host CPU idle cycles, saves client server battery/energy, and avoids flooding the central gateway with unread telemetry logs.

## 📦 9. Long-Term Maintenance & DevOps Pipeline

To guarantee that System Monitor v2 can be consistently deployed, scaled, and maintained across disparate environments without configuration drift or human error, the codebase incorporates production-ready DevOps automation.

### 🐳 9.1 Multi-Container Orchestration (Containerization)

- **The Architecture:** The platform is decoupled and containerized utilizing **Docker** and orchestrated via **Docker Compose**.
- **The Impact:** It packages the NestJS server, PostgreSQL engine, and Redis caching layer into isolated, identical runtime environments (Containers). This completely eliminates the infamous _"it works on my machine"_ bug. Whether you boot the platform on a local computer or deploy it to cloud infrastructures like **AWS EC2** or **DigitalOcean Droplets**, the system runs identically, reducing infrastructure configuration overhead to a single command: `docker-compose up -d`.

### 🚀 9.2 Automated Workflows (CI/CD Pipelines)

- **The Architecture:** Continuous Integration and Continuous Deployment (CI/CD) pipelines managed dynamically via **GitHub Actions**.
- **The Impact:** Every time you push code or open a Pull Request, automated cloud runners wake up to audit your repository:
  1.  **Linting & Styling:** Enforces code cleanliness standards on the NestJS and Next.js applications.
  2.  **Automated Testing:** Executes the entire `Jest` test suite to catch regressions before they hit production.
  3.  **Cross-Platform Compilation:** Automatically runs the C++ compiler toolchain (`g++` / `clang`) on clean Linux environments to verify that the core System Agent compiles flawlessly without syntax or pointer initialization bugs.

## 10. Building & Installing

```
# Setup steps will be defined here
```
