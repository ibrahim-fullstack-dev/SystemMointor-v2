# 🖥️ System Monitor v2

## 📋 1. Requirements Analysis

### 🎯 (The What)

**System Monitor v2** is a next-generation infrastructure monitoring platform designed for real-time tracking of remote servers and personal computers. It provides users with a comprehensive, low-latency web dashboard to access, monitor, and audit system vitals securely from anywhere in the world.

- The system captures, processes, and visualizes the following critical telemetry metrics::

**⚡ CPU:** Per-core utilization, clock speed, and core temperatures.

**🧠 RAM:** Live memory allocation, swap space, and cache usage.

**🎮 GPU:** Graphics processor utilization and video memory (VRAM) consumption.

**🌐 Network:** Real-time upload/download bandwidth, network latency, and interface status.

**🔋 Battery:** Charge capacity, degradation/health status, and power consumption rates.

**⚙️ Processes:** A full inventory of active background processes with sorting options based on resource consumption.

### (The Why)

- In modern enterprise environments, companies manage hundreds of headless cloud servers. Manually inspecting these machines via SSH is highly inefficient.

* **❌ The Problem:**: Existing monitoring solutions are either incredibly resource-heavy—consuming the very server capacity they are meant to watch—or they lack true real-time, instantaneous updates.

* **✅ The Solution:** This system solves this by deploying a lightweight background daemon (Agent) written in C++ that consumes less than 1% of system resources. It streams data over an optimized protocol (WebSockets) to a centralized, reactive web dashboard.

## 🏗️ 2. System Design & Data Flow

To ensure the system remains clean, untangled, and modular (unlike monolithic v1 implementations), System Monitor v2 adopts an asymmetrical, event-driven architecture decoupled into three standalone subsystems.

### 🔄 End-to-End Data Pipeline

The live hardware telemetry flows through three distinct stages:

```text
[ Linux/windows Kernel /proc ]
       │
       ▼ (Direct File I/O - Native C++)
[ 1. System Monitor Agent ]
       │
       ▼ (Upstream Stream via Secure WebSockets - JSON Payload)
[ 2. NestJS Gateway Server ]
       │
       ▼ (Downstream Broadcast via WebSockets)
[ 3. Next.js Web Dashboard ]
```

## ⚖️ 3. Architecture Decisions (ADRs)

### 🧩 Decision 1: Utilizing C++ for the Host Agent

- **Context:** The agent must sample core hardware subsystems continuously (intervals ≤ 1s) without degrading the host's primary workload performance.
- **Informed Choice:** Native **C++17** was chosen over managed runtimes (Node.js/Python).
- **Impact:** Zero garbage collection (GC) pauses, deterministic memory footprint (under 15MB RAM allocation), and direct compiled execution of OS kernel APIs.

### 🔌 Decision 2: WebSockets (WSS) vs. HTTP REST for Telemetry Streaming

- **Context:** Transporting high-frequency time-series system states to the front-end dashboard.
- **Informed Choice:** **Persistent WebSockets (Bi-directional TCP)** instead of standard HTTP Pull/Polling.
- **Impact:** Eliminates the HTTP header overhead (saving megabytes of bandwidth over time) and achieves sub-second, live data updates in the browser UI.

### 🏗️ Decision 3: NestJS for the Backend Gateway

- **Context:** We need a robust server that handles hundreds of concurrent connections and scales smoothly.
- **Informed Choice:** **NestJS Framework (TypeScript)**.
- **Impact:** Enforces strict modular architecture, out-of-the-box WebSocket gateway architecture, and shares a highly intuitive learning curve with enterprise tools like ASP.NET.

## 5. Database Design

- To handle a continuous flow of data changing every second without degrading system performance, a Polyglot Persistence model is implemented:

1. Relational Data (PostgreSQL): Handles user accounts, subscription metrics, registered agents, access control tokens, and custom threshold configurations.

2. Time-Series Data (TimescaleDB / Redis Caching): Historical metrics (used to generate weekly/monthly diagnostic reports) are fed into TimescaleDB, while live telemetry uses Redis caching to prevent disk write bottlenecks.

## 6. Securtiy Planning

- Securing the telemetry stream is paramount, as the Agent reads highly sensitive host environment information:

1. ncryption: All data in transit between the Agent, Backend, and Browser is forced over encrypted protocols: WSS (Secure WebSockets) and HTTPS.

2. Authentication: Upon initialization, each Agent is issued a unique cryptographic API Token. The backend rejects any data packet that does not provide a valid token in the connection handshake.

3. Authorization (RBAC): Strict Role-Based Access Control isolates server views; users can only stream data from machines they explicitly own or have been granted access to.

## 7. Testing Strategy

- To maintain system stability before deployment to production environments:

1. Unit & Integration Testing (Backend): Powered by Jest to independently test data transformation pipes, guards, and access-control middleware.

2. Performance/Load Testing: Executed via k6 or Artillery to simulate 1,000 active agents concurrently streaming data, ensuring the backend gateway holds under high stress.

3. Memory Leak Detection (C++ Agent): Profiled using Valgrind to guarantee that the C++ daemon can run continuously for months without bleeding system memory.

## 8. Performance Optimization

- Performance Optimization
  Binary Payloads (Future Implementation): Migrating from string-based JSON to gRPC / Protocol Buffers. This will compress the network payload into a highly optimized binary format, reducing data transmission over the network by up to 70%.

- Dynamic Throttling: If no user is actively viewing a specific machine's dashboard, the backend signals the respective Agent to reduce its sampling rate from (1 second) to (60 seconds), saving server energy and network bandwidth.

## 9. Long-Term Maintenance

- Containerization: The entire architecture is configured to deploy via Docker. Docker Compose manages the backend, database, and caching layers identically across local environments and cloud providers (AWS, DigitalOcean).

- CI/CD Pipelines: Automated workflows configured with GitHub Actions to lint, test, and compile the frontend/backend applications and verify the C++ build script on every commit.

## 10. Building & Installing
