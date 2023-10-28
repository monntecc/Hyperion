# **Hyperion Game Engine**

Hyperion is a cross-platform game engine developed in C++. It provides a comprehensive set of features for game development, including:

* Rendering: Hyperion supports a variety of rendering APIs, including OpenGL, DirectX, and Vulkan. It also includes a number of advanced rendering features, such as deferred rendering, shadow mapping, and post-processing. (Planning)
* Physics: Hyperion includes a physics engine that supports rigid body dynamics, collision detection, and constraints. (Planning)
* Audio: Hyperion includes an audio engine that supports 3D positional audio, effects, and music. (Planning)
* Input: Hyperion includes an input system that supports keyboard, mouse, and gamepad input. (Planning)
* Networking: Hyperion includes a networking system that supports multiplayer games. (Planning)

**Getting Started**

To get started with Hyperion, you will need to install the following dependencies:

* C++ compiler
* Premake 5
* OpenGL, DirectX, or Vulkan SDK (depending on which rendering API you want to use) (For now we're only support's OpenGL)

Once you have installed the dependencies, you can clone the Hyperion repository and build the engine:

```
git clone https://github.com/nylestroke/Hyperion.git
cd Hyperion
Scripts/premake/premake-gen.bat
```
Open solution in Visual Studio 2022 or higher, build, and open start project 'Sandbox'

This will generate a binary file called `Hyperion` in the `build` directory. You can then run the engine by executing the binary file.

**Usage**

To create a new game with Hyperion, you can use the following command: (Planning)

```
Hyperion new_project <project_name>
```

This will create a new directory for your project and generate a basic project template.

Once you have created a new project, you can start developing your game by adding code to the `src` directory. The `src` directory contains the source code for all of the engine's features.

To run your game, you can use the following command:

```
cd <project_name>
./Hyperion
```

This will start the engine and load your game project.

**Documentation**

The Hyperion documentation is available at [insert documentation link here]. (Planning)

**Contributing**

If you are interested in contributing to Hyperion, please see the contribution guidelines: [insert contribution guidelines link here]. (Planning)

**License**

Hyperion is licensed under the Apache 2.0 License: [https://github.com/nylestroke/Hyperion/blob/master/LICENSE].