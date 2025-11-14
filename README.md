# ClipSync Pro v2.0

**ClipSync Pro** is a high-performance, lightweight, and modern clipboard manager for Windows, built from the ground up with native C++ and the Qt 6 framework. It's designed for developers, writers, and power users who need a fast, reliable, and visually pleasing way to manage their copy-paste history.

---

## ✨ Features

*   **Unlimited Clipboard History**: Automatically saves every piece of text you copy.
*   **System Tray Integration**: Runs quietly in the background. Hiding the window no longer quits the application.
*   **Quick Access Menu**: Right-click the tray icon to quickly show/hide the window or quit the application.
*   **Sleek Dark UI**: A modern, professional dark theme that's easy on the eyes.
*   **Instant Search**: A case-insensitive live search bar to find any snippet in seconds.
*   **Lightweight & Fast**: Built with native C++ for minimal CPU and memory usage. It feels snappy and responsive.
*   **Self-Contained & Portable**: Saves history to a simple, human-readable `clipboard_history.json` file.
*   **Open Source**: The complete source code is available for you to inspect, modify, and learn from.

---

## 🚀 Getting Started

### Prerequisites

To build this project from source, you will need the following tools installed on your Windows machine:

1.  **A C++ Compiler**:
    *   **Visual Studio 2022** (or the standalone **Visual Studio Build Tools 2022**) with the "Desktop development with C++" workload installed.
2.  **The Qt 6 Framework**:
    *   **Qt 6.x** installed via the Qt Online Installer. The component for **MSVC 2022 64-bit** must be selected during installation.
3.  **CMake**:
    *   Version 3.16 or higher. Ensure it is added to your system's PATH during its installation.

### Building the Project (The Guaranteed Manual Way)

This project uses CMake for a simple and robust build process.

1.  **Clone the repository or download the source code.**
    ```bash
    git clone https://github.com/Chilluminati2/ClipSyncPro.git
    cd ClipSyncPro
    ```

2.  **Open the Developer Command Prompt.**
    This is the most important step. Open the Start Menu and launch the **"x64 Native Tools Command Prompt for VS 2022"**. This terminal has the necessary environment variables for the compiler.

3.  **Navigate to the project directory** within that command prompt.
    ```cmd
    cd C:\Path\To\Your\ClipSyncPro
    ```

4.  **Configure the project using CMake.**
    Run the following command. This only needs to be run once, or after cleaning the build folder.

    ```cmd
    cmake -B build -G "Visual Studio 17 2022" -DCMAKE_BUILD_TYPE=Release
    ```

5.  **Compile the application.**
    This command will build the optimized `ClipSyncPro.exe` file inside the `build/Release` directory.

    ```cmd
    cmake --build build --config Release
    ```

### Deploying the Application

After building, your `.exe` needs the Qt `.dll` files to run.

1.  **Navigate to the output directory** in your Developer Command Prompt.
    ```cmd
    cd build\Release
    ```
2.  **Run Qt's deployment tool.** This copies all necessary libraries.
    ```cmd
    windeployqt ClipSyncPro.exe
    ```
3.  **Manually copy assets.** Copy the `assets` and `res` folders from the main project directory into this `Release` folder.

You can now run `ClipSyncPro.exe` directly!

---

## 📦 Creating a Release

This repository includes a `release.bat` script to automate the entire build, packaging, and website deployment process.

**To use it:**
1.  Open the **"x64 Native Tools Command Prompt for VS 2022"**.
2.  Navigate to the `ClipSyncPro` project directory.
3.  Run the script:
    ```cmd
    release.bat
    ```
4.  Enter the new version number when prompted.

The script will automatically build the release version, create `.zip` packages for the application and source code, and update the project website.

---

## 🛠️ Project Structure

The codebase is organized with a clear separation of concerns:

*   `assets/`: Contains the application icon (`.ico`).
*   `src/core/`: The "brains" of the application (`ClipboardManager`).
*   `src/gui/`: All user interface code (`MainWindow`, `SystemTray`).
*   `src/res/`: Contains the Qt Style Sheet (`.qss`) for the dark theme.
*   `src/storage/`: The `HistoryManager` class for saving/loading the JSON history file.
*   `CMakeLists.txt`: The main build script for the project.
*   `win32_resource.rc`: The Windows-specific resource script to embed the icon into the `.exe` file itself.
*   `release.bat`: The automated script for creating distributable packages.

---

## 🤝 Contributing

Contributions and suggestions are always welcome! If you have an idea for a new feature or find a bug, please feel free to open an issue or submit a pull request on GitHub.

---

## 📜 License

This project is open-source and available for personal and educational use.

---

Built with ❤️ and C++ by Chilluminati.