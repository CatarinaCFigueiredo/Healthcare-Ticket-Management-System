markdown
# 🏥 Healthcare Ticket System

![Language](https://img.shields.io/badge/language-C-blue?style=flat-square)
![Build](https://img.shields.io/badge/build-Makefile-green?style=flat-square)
![Platform](https://img.shields.io/badge/platform-Linux%20%7C%20macOS%20%7C%20WSL-lightgrey?style=flat-square)
![Status](https://img.shields.io/badge/status-complete-brightgreen?style=flat-square)

> A console-based ticket management system for a healthcare service point, developed in C.

---

## 📋 Overview

This project simulates a ticketing system used in a healthcare environment. It manages the creation and handling of tickets for different types of appointments, applying validation rules and service constraints to ensure correct ticket processing.

The system was designed with a focus on **structured programming**, **input validation**, **modular organization**, and clear **business logic implementation**.

---

## ✨ Features

- 🎫 Generate tickets for scheduled and urgent appointments
- 🔢 Sequential and automatic ticket numbering
- 🕐 Registration of ticket creation date and time
- ✅ Input validation and business rule enforcement
- 🚨 Daily limit control for urgent appointment tickets
- 📁 Modular code organization using a header file
- 🔧 Compilation support through a Makefile

---

## 🗂️ Project Structure

```text
healthcare-ticket-system/
├── ticketsystem.c    # Main source file
├── ticketsystem.h    # Header file with declarations
├── Makefile          # Compilation rules
├── README.md         # Project documentation
└── .gitignore        # Git ignored files
```

---

## ⚙️ Requirements

Make sure you have the following installed before compiling:

- **GCC** 9.0+
- **GNU Make** 4.0+
- **OS:** Linux, macOS, or WSL (Windows Subsystem for Linux)

---

## 🚀 Getting Started

### Compile

```bash
make
```

This will generate the executable `ticketsystem` in the project root.

### Run

```bash
./ticketsystem
```

### Clean

To remove compiled files and the executable:

```bash
make clean
```

---

## 💻 Example Output

```
========================================
       HEALTHCARE TICKET SYSTEM
========================================
 [1] Scheduled Appointment
 [2] Urgent Appointment
 [0] Exit
----------------------------------------
Select an option: 1

Ticket generated successfully!
  Type   : Scheduled Appointment
  Number : A001
  Date   : 08/05/2026 at 09:32
========================================
```

---

## 🛠️ Technologies Used

| Technology | Purpose |
|---|---|
| C | Core programming language |
| GCC | Compilation |
| Makefile | Build automation |
| Git | Version control |

---

## 🔮 Future Improvements

- [ ] Split source into multiple `.c` files for better modularity
- [ ] Add persistent data storage using files
- [ ] Improve the terminal UI (e.g., with `ncurses`)
- [ ] Add unit tests
- [ ] Generate detailed daily reports and statistics
- [ ] Refactor for improved scalability

---

## 👩‍💻 Author

Developed by **Catarina Figueiredo**

[![GitHub](https://img.shields.io/badge/GitHub-profile-181717?style=flat-square&logo=github)](https://github.com/)
[![LinkedIn](https://img.shields.io/badge/LinkedIn-profile-0A66C2?style=flat-square&logo=linkedin)](https://linkedin.com/)
