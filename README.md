# Sounder

## Overview

Sounder is a Qt-based application designed to provide audio processing capabilities. It leverages the Qt framework for its GUI components and FFTW for its Fast Fourier Transform computations.

## Requirements

- **CMake** version 3.5 or higher
- **Qt** version 6, with the required components: Widgets, Multimedia and PrintSupport
- **FFTW** version 3

## Installation

### Prerequisites

Ensure that CMake, Qt, and FFTW are installed on your system. You can install these dependencies using your package manager or from their official websites.

### Building Sounder

1. Clone the repository:
    ```
    git clone <repository-url>
    cd Sounder
    ```

2. Create a build directory and navigate into it:
    ```
    mkdir build
    cd build
    ```

3. Configure the project with CMake:
    ```
    cmake -DCMAKE_PREFIX_PATH=/path/to/your/qt  ..
    (e.g. cmake -DCMAKE_PREFIX_PATH=/home/foo/Qt/6.7.1/gcc_64 ..)
    ```

4. Build the project:
    ```
    make
    ```

5. Install the application:
    ```
    make install
    ```

## Usage

After installation, you can run the Sounder application from the installed location. The application provides a GUI for processing real time audio stream, including features such as visualizing frequency maps, applying custom plots, and recognizing the closest sound to the input sound. This feature can be particularly useful for tuning musical instruments.

