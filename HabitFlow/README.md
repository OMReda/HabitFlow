<h1 align="center">HabitFlow 🌱</h1>

<p align="center">
  <strong>A lightweight, blazing-fast terminal habit tracker written in C.</strong>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/language-C-blue.svg" alt="Language C">
  <img src="https://img.shields.io/badge/platform-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey.svg" alt="Platform">
  <img src="https://img.shields.io/badge/license-MIT-green.svg" alt="License MIT">
</p>

<hr>

## 📖 About

**HabitFlow** is a minimalist command-line interface (CLI) application designed to help you build and maintain positive habits directly from your terminal. Whether you're a developer living in the terminal or just someone who appreciates fast, distraction-free tools, HabitFlow provides everything you need to track your daily routines, maintain streaks, and visualize your progress.

## ✨ Features

- **⚡ Blazing Fast**: Written in pure C with zero heavy dependencies.
- **✅ Daily Check-Ins**: Quickly log your habits for the day.
- **🔥 Streak Tracking**: Motivation through numbers—track your current and longest streaks.
- **📊 Visual Statistics**: View your progress with colorful terminal charts and ASCII progress bars.
- **💾 Local Storage**: Your data stays yours, securely saved locally via binary files (`.dat`).
- **📁 CSV Export**: Export your habit data for external analysis or backup.
- **🎨 Beautiful UI**: Rich terminal output utilizing ANSI colors and emojis.

## 🚀 Getting Started

### Prerequisites
- A C compiler (e.g., `gcc`, `clang`)
- `make`

### Installation

1. **Clone the repository:**
   ```bash
   git clone https://github.com/yourusername/habitflow.git
   cd habitflow
   ```

2. **Build the project:**
   For Linux/macOS using Make:
   ```bash
   make
   ```
   For Windows using the provided batch script:
   ```cmd
   build.bat
   ```

## 💻 Usage

HabitFlow is incredibly simple to use from the command line.

**Basic Commands:**

```bash
# Add a new habit
./habitflow add "Read 20 pages"

# List all your current habits
./habitflow list

# Check-in for a habit (using its ID from the list)
./habitflow check 1

# View your statistics and progress bars
./habitflow stats

# Show the interactive dashboard
./habitflow dashboard

# Export your habit data to a CSV file
./habitflow export
```

## 📂 Project Structure

- `src/`: Core implementation files in C.
- `include/`: Header files defining the architecture (`habit.h`, `stats.h`, `storage.h`, `ui.h`).
- `data/`: Where your habits and logs are securely stored.

## 🤝 Contributing

Contributions are always welcome! Whether it's a bug report, a new feature idea, or a code contribution, feel free to open an issue or submit a Pull Request.

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## 📜 License

Distributed under the MIT License. See `LICENSE` for more information.

---
<p align="center">Made with ❤️ for the terminal</p>
