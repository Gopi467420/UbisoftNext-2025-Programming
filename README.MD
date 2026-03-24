# 🚀 Base Invaders – Custom 2D Game Engine (C++)

A custom-built **2D top-down game engine and gameplay prototype** developed in C++ as part of the **Ubisoft NEXT 2025–2026 Programming Challenge**.

This project focuses on building core engine systems from scratch using a **data-oriented and performance-driven approach**, without relying on existing game engines.

---



---

## 🎮 Game Overview

**Base Invaders** is a hybrid of **tower defense and survival gameplay**, where the player defends a central base against waves of enemies.

### Gameplay Features:
- Strategic positioning and crowd control  
- Multiple enemy types with unique behaviors  
- Upgrade and progression system  

---

## ⚙️ Core Systems & Architecture

The engine follows an **ECS-inspired architecture**:

### 🧩 Entity Structure
- `GObject` → Base class (ID, lifecycle, transform)  
- `Entity` → Gameplay abstraction  
- `EntityComponent` → Modular behaviors  

### 🔧 Components Implemented
- Movement Component  
- Health Component  
- Collision Component (Circle-based)  
- Shape/Rendering Component  

### 💡 Design Highlights
- Component-driven system (no rigid inheritance chains)  
- Clear separation of data and logic  
- Scalable and extensible architecture  

---

## 🚀 Performance & Memory Optimization

### 🔹 Object Pooling
Implemented custom pools for:
- Enemies  
- Projectiles  
- Gems  

### 🔹 Data-Oriented Design (SoA)
- Data stored in **separate contiguous arrays**:
  - Positions  
  - Directions  
  - Speeds  
  - Health  
- Improves cache locality and iteration performance  

### 🔹 Efficient Removal
- `aliveCount` + **swap-and-remove**  
- Constant time (O(1)) deletion  
- Keeps active data tightly packed  

### 🔹 Runtime Optimization
- No dynamic allocations during gameplay  
- Stable and predictable performance  

---

## 💥 Combat System

### 🔫 Ammo Types
- **Precision Ammo** → Single-target, high accuracy  
- **Spread Ammo** → Multi-shot for crowd control  
- **Explosive Ammo** → Area-of-effect damage  

### 💡 Design
- Shared projectile pool  
- Behavior controlled through data-driven logic  

---

## 👾 Enemy System

### Enemy Types
- **Swarm** → Fast, low health  
- **WallBreaker** → High damage  
- **Airborne** → Fast and durable  
- **Bomber** → High impact  

### Features
- Data-driven enemy stats  
- Shared behavior systems  
- Easy tuning and balancing  

---

## 🧠 AI, Movement & Physics

### 🔹 Movement System
- Centralized system for:
  - Direction  
  - Velocity  
  - Target-seeking  

### 🔹 AI Behavior
- Enemy separation logic  
- Avoids clustering  

### 🔹 Collision System
- Circle-based collision  
- Layer & mask filtering  
- Trigger vs collision support  

### 🔹 Physics Manager
- Collision detection  
- Event dispatch  
- Overlap resolution  

---

## 📦 Spatial Partitioning

Implemented **Grid-Based Spatial Partitioning (Grid Hashing)**:
- Divides world into cells  
- Reduces collision checks  
- Efficient neighbor queries  

---

## 🎥 Supporting Systems

### 🎥 Camera
- World ↔ Screen conversion  
- Zoom and pan  

### ⏱️ Wave System
- Timer-based spawning  
- Progressive difficulty  

### 🧩 UI / HUD
- Basic gameplay feedback  
- Layered rendering  

---

## ⚙️ Engine Flow

1. **Initialization**
   - Systems and pools initialized  
   - Entities created  

2. **Update Loop**
   - Movement updates  
   - Physics & collision processing  
   - Game logic updates  

3. **Rendering**
   - Entities rendered via camera  
   - UI rendered on top  

---

## 🛠️ Tech Stack

- **Language:** C++  
- **IDE:** Visual Studio  
- **Build System:** CMake  

---

## 💡 Key Learnings

- Data-oriented design improves performance  
- Object pooling removes runtime overhead  
- System-driven architecture scales better  
- Building from scratch deepens engine understanding  

---

## 📌 Future Improvements

- Hot-reload system  
- Advanced AI behaviors  
- Improved UI system  
- Additional gameplay mechanics  

---

## 👨‍💻 Author

**Gopi Velmurugan**  
- LinkedIn: https://www.linkedin.com/in/gopi-velmurugan-65249716a/  
- Email: gopiofficialca20@gmail.com  

---

