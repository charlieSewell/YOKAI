[![Build Status](https://github.com/charlieSewell/ICT398-Game-Engine/workflows/Windows/badge.svg)](https://github.com/charlieSewell/ICT398-Game-Engine/actions/workflows/Windows.yml)
[![Build Status](https://github.com/charlieSewell/ICT398-Game-Engine/workflows/macOS/badge.svg)](https://github.com/charlieSewell/ICT398-Game-Engine/actions/workflows/macOS.yml)
[![Build Status](https://github.com/charlieSewell/ICT398-Game-Engine/workflows/Linux/badge.svg)](https://github.com/charlieSewell/ICT398-Game-Engine/actions/workflows/Linux.yml)
# Yokai-Game-Engine
<p align=center>
  <b> Yokai Game Engine </b>
</p>

<p align="center">
  <a href="#building">Building</a> •
  <a href="#contributing">Contributing</a> •
  <a href="#license">License</a>
</p>


## Building
### Tools
* macOS: [xcode][xcode command line tool][brew][brew-dl]
* Windows: [vcpkg][vcpkg-dl], [Visual Studio 2019][VS2019-dl]

### Dependencies
* Linux: `apt install build-essential clang ninja-build clang-9 \
  libstdc++-9-dev ninja-build libgl1-mesa-dev libx11-dev \
  libxrandr-dev libudev-dev libfreetype6-dev \
  libopenal-dev libflac++-dev libvorbis-dev \
  libxinerama-dev libxcursor-dev libxi-dev`
* macOS: `brew install cmake ninja llvm`
* Windows: `None` 

### GIT LFS
Ensure you have GIT LFS installed.
```
git lfs install
```

### Cloning
```
git clone https://github.com/charlieSewell/ICT398-Game-Engine.git
cd ICT398-Game-Engine
git checkout master
git submodule update --init --recursive --depth 1
```

### Building

#### Linux & macOS:
```
CXX=clang++ cmake -S . -B build -G Ninja -D CMAKE_BUILD_TYPE=Release
```
Change directory to whatever you specified X as.
```
cmake --build . && ./ICT398-Game-Engine
```
#### Windows:
    * Open Visual Studio as Administrator (required to make symbolic links)
    * Press Continue without Code
    * In Visual Studio, select Open → CMake, Navigate to the project folder and select `CMakeLists.txt`
    * From the "Select Startup Item" menu, select `ICT398-Game-Engine.exe`

## License
This project is licensed under the MIT license. Please see the [LICENSE](LICENSE) file
for details
