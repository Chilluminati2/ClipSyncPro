# ClipSync Pro

**ClipSync Pro** is a lightweight and modern clipboard manager built from the ground up with native C++ and the Qt 6 framework. It's designed for developers, writers, and power users who need a fast, reliable, and visually pleasing way to manage their copy-paste history.

---

## 📥 Installation (For Users)

The easiest way to get ClipSync Pro is to download the latest release from the official website. The package includes the application executable and all required libraries.

**[>> Go to the Official Website to Download <<](https://clipsyncpro.netlify.app/)**

---

## ✨ Features

*   **Unlimited Clipboard History**: Automatically saves text and images you copy.
*   **System Tray Integration**: Runs quietly in the background. Hiding the window no longer quits the application.
*   **Global Hotkey**: Instantly access your history from anywhere with `Ctrl+Shift+V`.
*   **Fully Custom UI**: A sleek, modern dark interface with a custom-drawn title bar and controls. No ugly default window frames!
*   **Content-Aware Previews**:
    *   🖼️ See thumbnails for copied **images**.
    *   🎨 See a color swatch for copied **color codes** (`#RRGGBB`, `rgb(...)`).
    *   🔗 Get a clean display for **links**.
*   **Instant Search**: A case-insensitive live search bar to find any snippet in seconds.
*   **Lightweight & Fast**: Built with native C++ for minimal CPU and memory usage.

---

## 🚀 Building from Source (For Developers)

If you wish to build the project yourself, follow these steps.

### Prerequisites

1.  **A C++ Compiler**: **Visual Studio 2022** (or the standalone **Visual Studio Build Tools 2022**) with the "Desktop development with C++" workload.
2.  **The Qt 6 Framework**: **Qt 6.x** installed via the Qt Online Installer. The component for **MSVC 2022 64-bit** must be selected.
3.  **CMake**: Version 3.16 or higher, added to your system's PATH.

### Build Steps

1.  **Clone the repository.**
    ```bash
    git clone https://github.com/Chilluminati2/ClipSyncPro.git
    cd ClipSyncPro
    ```

2.  **Open the Developer Command Prompt.**
    This is the most important step. Open the Start Menu and launch the **"x64 Native Tools Command Prompt for VS 2022"**.

3.  **Navigate to the project directory** within that command prompt.
    ```cmd
    cd C:\Path\To\Your\ClipSyncPro
    ```

4.  **Configure and Build.**
    These commands will configure the project and compile the optimized Release version into the `build/Release` directory.

    ```cmd
    rem First, clean any previous build
    rd /s /q build

    rem Configure the project for Release
    cmake -B build -G "Visual Studio 17 2022" -DCMAKE_BUILD_TYPE=Release

    rem Compile the application
    cmake --build build --config Release
    ```

5.  **Deploy Dependencies.**
    After building, your `.exe` needs the Qt `.dll` files to run.
    ```cmd
    rem Navigate to the output directory
    cd build\Release

    rem Run Qt's deployment tool
    windeployqt ClipSyncPro.exe

    rem Manually copy required asset folders
    xcopy ..\..\assets assets\ /E /I /Y
    xcopy ..\..\src\res res\ /E /I /Y
    ```
You can now run `ClipSyncPro.exe` directly from the `build\Release` folder.

---

## 📦 Creating a Release

This repository includes a `release.bat` script to automate the build and packaging process.

**To use it:**
1.  Open the **"x64 Native Tools Command Prompt for VS 2022"**.
2.  Navigate to the `ClipSyncPro` project directory.
3.  Run the script: `release.bat`
4.  Enter the new version number when prompted.

The script will build the project and create a `*-Windows.zip` and `*-Source.zip` package in the root directory, ready for you to upload.

---

## 📜 License

This project is distributed under the MIT License. See `LICENSE` for more information.

---

<p align="center">
Created with ❤️ and C++ by Kareem.
</p>