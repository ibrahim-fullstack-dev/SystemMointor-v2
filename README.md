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

```

```
