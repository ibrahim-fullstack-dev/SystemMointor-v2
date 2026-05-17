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

## 3. System Design

- The project utilizes a decoupled 3-Tier Architecture to ensure strict Separation of Concerns and seamless long-term scalability:

1. The Agent Layer (C++): A lightweight background service (Daemon) running natively on the host machine (Linux/Windows). It interfaces directly with the kernel (e.g., reading the /proc filesystem on Linux) to fetch hardware metrics safely and efficiently.

2. The Gateway/Backend Layer (NestJS & TypeScript): A centralized data broker that orchestrates incoming socket connections from hundreds of agents, sanitizes the payloads, and broadcasts them to authorized clients.

3. The Presentation Layer (Next.js & Tailwind CSS): A responsive, dashboard frontend that receives live data pipelines and maps them onto fluid, reactive time-series charts.

## 4. Architure Decision

- Why C++ for the Agent? To achieve maximum execution performance and near-zero memory footprint. C++ allows direct, low-level OS API calls and system file reads without the heavy overhead of runtime environments like Node.js or Python.

- Why WebSockets over HTTP REST? Monitoring requires frequent updates (intervals $\le 1$ second). Continuous HTTP polling creates a massive network overhead due to constant TCP handshake cycles. WebSockets establish a single, persistent, bi-directional pipe with near-zero latency overhead.

- Why NestJS for the Backend? It provides a highly structured, scalable architecture that natively enforces OOP principles and SOLID design, offering robust, built-in WebSocket gateway modules

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
