Installing Night Sky Engine
===================

There are two methods to installing Night Sky Engine: downloading the official release, or building from development source. For those who don't need to touch C++ code, or just want a quick and easy setup, I recommend grabbing the official release. However, if you want to mess around with the engine, or just want the latest changes, you will need to build from source.

!!! warning

    The official release only has support for Windows on x64. While other platforms do work, they are not bunudled with the official release. You will need to build from source for Mac, Linux, or Windows on ARM.

# Download Official Release
Starting from version 1.0.1, there are multiple versions of the official release that can be installed: the full project, the low-end project, and the plugin.

- The full project comes with a ton of example assets to get started with. It is designed for high-end machines, such as more powerful PCs or console.
- The low-end project comes with the same assets, but is much lighter on the graphics end. It is designed for low-end machines, such as mobile.
- The plugin is all of the code required to use Night Sky Engine, but without any of the assets.

## Full Project
To download the latest full project release, simply download `NightSkyEngine.rar` from [this link.](https://github.com/WistfulHopes/NightSkyEngine/releases/latest). Then, extract `NightSkyEngine.rar` using your tool of choice.

Then, you will need to install Unreal Engine 5.7. Details can be found [here](https://www.unrealengine.com/en-US/download). After installing Unreal Engine, you may run it, then open `NightSkyEngine/NightSkyEngine.uproject` from within the editor.

## Low-End Project
To download the latest low-end project release, simply download `NSELowEnd.rar` from [this link.](https://github.com/WistfulHopes/NightSkyEngine/releases/latest). Then, extract `NSELowEnd.rar` using your tool of choice.

Then, you will need to install Unreal Engine 5.7. Details can be found [here](https://www.unrealengine.com/en-US/download). After installing Unreal Engine, you may run it, then open `NightSkyEngine/NightSkyEngine.uproject` from within the editor.

## Plugin
To download the latest plugin release, simply download `NSEPlugin.rar` from [this link.](https://github.com/WistfulHopes/NightSkyEngine/releases/latest). Then, extract `NSEPlugin.rar` using your tool of choice.

Then, you will need to install Unreal Engine 5.7. Details can be found [here](https://www.unrealengine.com/en-US/download). After installing Unreal Engine, you may run it, then create a new project. Finally, put the contents of `NSEPlugin.rar` in `<Project Folder>\Plugins`, so that the `NightSkyEngine` folder sits within the `Plugins` folder.

# Build From Source
Building from source takes more steps than just downloading the release. You'll need to know how to use Git and Visual Studio (or your IDE of choice).

## Clone the Engine
To get Night Sky Engine, use a Git client (such as the [official client](https://git-scm.com/) or [Github Desktop](https://desktop.github.com/)) and clone the Night Sky Engine repository at https://github.com/WistfulHopes/NightSkyEngine.git. If using the command line, type in the following:

```git clone https://github.com/WistfulHopes/NightSkyEngine.git```

## Compile the engine
To compile the Night Sky Engine, you will need Unreal Engine 5.7 and Visual Studio. The version of Visual Studio must be 2022. For detailed instructions on installing Visual Studio for use with Unreal Engine, [click here](https://docs.unrealengine.com/5.7/en-US/setting-up-visual-studio-development-environment-for-cplusplus-projects-in-unreal-engine/).

After Visual Studio is set up, you will need to generate Visual Studio project files for Night Sky Engine. To do so, right-click on NightSkyEngine.uproject, and click on "Generate Visual Studio project files".

There will be a new file in the folder, `NightSkyEngine.sln`. Open it, and once Visual Studio has loaded, press Ctrl+Shift+B to compile the engine.

| Previous          |                              Next |
|:------------------|----------------------------------:|
| [Quick Start](quick-start.md) | [Getting Your Bearings](bearings.md) |