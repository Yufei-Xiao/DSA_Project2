# DSA_Project2

A C++ and Qt-based application for managing and sorting course data.

## 🛠 How to Build and Run

### 📋 Prerequisites
* **Qt 6.10.2**: The project is configured to use the **MinGW 64-bit** kit.
* **CMake (Version 3.20 or higher)**: Required for build configuration.
* **C++17 Compiler**: Ensure your compiler (GCC/MinGW or MSVC) supports the C++17 standard.
* **IDE**: [CLion](https://github.com/Yufei-Xiao/DSA_Project2) or **Qt Creator** is highly recommended.

### ⚙️ Setup & Configuration
1.  **Clone the Repository**:
    ```bash
    git clone [https://github.com/Yufei-Xiao/DSA_Project2.git](https://github.com/Yufei-Xiao/DSA_Project2.git)
    cd DSA_Project2
    ```

2.  **Verify the Qt Path**:
    Open `CMakeLists.txt` and ensure the `CMAKE_PREFIX_PATH` matches your local Qt installation. The current configuration is:
    ```cmake
    set(CMAKE_PREFIX_PATH "C:/Qt/6.10.2/mingw_64")
    ```
    *Note: If your Qt is installed in a different folder, update this path before proceeding.*

### 🚀 Building the Project
1.  **Open in IDE(Clion)**: Open the project folder in your chosen IDE. It should detect the `CMakeLists.txt` automatically.
2.  **Configure CMake**: Select a build profile that uses the MinGW 64-bit toolchain to match the Qt version.
3.  **Build**: Run the **Build** command (e.g., `Ctrl+F9` in CLion).

> **💡 Automatic Data Handling:** > The build script includes a `POST_BUILD` command that automatically copies the `/Data` folder from the source directory into your build output folder. You do **not** need to move the CSV files manually.

### 🏃 Running the Application
1.  **Via IDE**: Click the **Run** button.
2.  **Manual Execution**:
    * Navigate to your build output folder (e.g., `cmake-build-debug`).
    * Run `DSA_Project2.exe`.
    * Ensure the `Data/` folder is present in the same directory as the executable (this is handled automatically during the build).

---

## 📂 Project Structure
* `main.cpp`: Sorting Algorithms and UI logic.
* `Course.h`: A course struct
* `Data/`: Contains the CSV files used for course information.
