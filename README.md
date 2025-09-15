# StarletSamples
A repository for demonstrating the Starlet Engine.
Includes sample scenes, meshes, textures, and shaders.

## Sample Scenes

- `EmptyScene` : A single camera and skybox
- `GridScene` : Shows the functionality of **squareGrid** and **cubeGrid**
- `PrimitiveScene` : Shows the functionality of **triangle**, **square**, **cube**
- `TestScene` : A mixed set of models with different colours, modes, textures, lighting, for general debugging.

## Building the Project
This project uses **CMake**. Follow these steps to build:

### 1. Clone the Repository
```bash
git clone https://github.com/Masonlet/StarletSamples.git
cd StarletSamples
```

### 2. Create a Build Directory and Generate Build Files
```bash
mkdir build
cd build 
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
```
`-DCMAKE_EXPORT_COMPILE_COMMANDS=ON` flag generates a `compile_commands.json` file  
Can be safely omitted on Windows if you're using Visual Studio

### 3. Build the Project
- **Linux**:
  ```bash
  make
  ```

- **Windows**:
  ```bash
  cmake --build .
  ```
  Or open the generated `.sln` file in Visual Studio and build the solution.
