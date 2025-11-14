# ClipSync Pro v1.0

**ClipSync Pro** is a high-performance, lightweight, and modern clipboard manager for Windows, built from the ground up with native C++ and the Qt 6 framework. It's designed for developers, writers, and power users who need a fast, reliable, and visually pleasing way to manage their copy-paste history.

---

## ✨ Features

*   **Unlimited Clipboard History**: Automatically saves every piece of text you copy.
*   **Sleek Dark UI**: A modern, professional dark theme that's easy on the eyes.
*   **Instant Search**: A case-insensitive live search bar to find any snippet in seconds.
*   **Self-Contained & Portable**: Saves history to a simple, human-readable `clipboard_history.json` file. No complex database setup.
*   **Lightweight & Fast**: Built with native C++ for minimal CPU and memory usage. It feels snappy and responsive.
*   **Easy Re-copying**: Simply double-click any item in the list to copy it back to your clipboard.
*   **Clean & Organized**: A well-structured layout with a clear title, search bar, and controls.
*   **Built with Qt 6**: Leverages the power of the industry-standard framework for cross-platform C++ development.

---

## 🚀 Getting Started

### Prerequisites

To build this project from source, you will need the following tools installed on your Windows machine:

1.  **A C++ Compiler**:
    *   **Visual Studio 2022** (Community Edition is free) with the "Desktop development with C++" workload installed.
2.  **The Qt 6 Framework**:
    *   **Qt 6.x** installed via the Qt Online Installer. Crucially, the component for **MSVC 2022 64-bit** must be selected.
3.  **CMake**:
    *   Version 3.16 or higher. This is usually included with the Visual Studio Installer or can be selected in the Qt Installer.

### Building the Project

This project uses CMake for a simple and robust build process.

1.  **Clone the repository or download the source code.**
    ```bash
    git clone https://github.com/Chilluminati2/ClipSyncPro.git
    cd clipsync-pro
    ```

2.  **Open the Correct Command Prompt.**
    Navigate to your Start Menu and open the **"x64 Native Tools Command Prompt for VS 2022"**. This terminal has the necessary environment variables for the compiler.

3.  **Configure the project using CMake.**
    Run the following command, replacing the path to your Qt installation if it's different. This command only needs to be run once, or after cleaning the build folder.

    ```cmd
    cmake -B build -G "Visual Studio 17 2022" -DQt6_DIR=C:\Qt\6.10.0\msvc2022_64\lib\cmake\Qt6
    ```

4.  **Compile the application.**
    This command will build the `ClipSyncPro.exe` file inside the `build/Debug` directory.

    ```cmd
    cmake --build build
    ```

5.  **(Optional but Recommended) Deploy Dependencies.**
    To make the application portable, navigate to the output directory and run Qt's deployment tool. This copies all necessary `.dll` files.

    ```cmd
    cd build\Debug
    windeployqt ClipSyncPro.exe
    ```

You can now run `ClipSyncPro.exe` directly!

---

## 🛠️ Project Structure

The codebase is organized with a clear separation of concerns:

*   `assets/`: Contains the application icon (`.ico`).
*   `src/core/`: The "brains" of the application. `ClipboardManager` handles 