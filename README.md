# Sounder

Sounder to aplikacja napisana w C++ używająca biblioteki Qt oraz FFTW do przetwarzania i wizualizacji danych dźwiękowych. Może posłużyć do strojenia instrumentów.

## Minimalne Wymagania

### System operacyjny
- Windows, macOS, Linux

### Kompilator
- Kompatybilny z C++17

### Narzędzia budowania
- CMake w wersji 3.5 lub nowszej

### Biblioteki
- Qt6 z komponentami:
  - Widgets
  - Multimedia
  - PrintSupport
- FFTW3 (Fastest Fourier Transform in the West)

## Instalacja

### Krok 1: Zainstaluj wymagane pakiety

#### Windows
1. [Pobierz i zainstaluj Qt](https://www.qt.io/download-qt-installer)
2. Zainstaluj FFTW3, np. przez [vcpkg](https://github.com/microsoft/vcpkg):
    ```sh
    vcpkg install fftw3
    ```

#### macOS
1. Zainstaluj Qt przez [Homebrew](https://brew.sh/):
    ```sh
    brew install qt
    ```
2. Zainstaluj FFTW3:
    ```sh
    brew install fftw
    ```

#### Linux (Ubuntu)
1. Zainstaluj Qt:
    ```sh
    sudo apt-get install qt5-default qttools5-dev-tools
    ```
2. Zainstaluj FFTW3:
    ```sh
    sudo apt-get install libfftw3-dev
    ```

### Krok 2: Skonfiguruj i zbuduj projekt

1. Sklonuj repozytorium:
    ```sh
    git clone <URL_do_repozytorium>
    cd Sounder
    ```
2. Utwórz katalog build i przejdź do niego:
    ```sh
    mkdir build
    cd build
    ```
3. Skonfiguruj projekt przy użyciu CMake:
    ```sh
    cmake ..
    ```
4. Zbuduj projekt:
    ```sh
    cmake --build .
    ```

## Uruchamianie aplikacji

Po zakończeniu budowania, uruchom aplikację z katalogu build:
```sh
./Sounder
