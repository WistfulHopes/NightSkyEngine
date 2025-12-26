Installing Night Sky Engine
===================

## Download
To get Night Sky Engine, use a Git client (such as the [official client](https://git-scm.com/) or [Github Desktop](https://desktop.github.com/)) and clone the Night Sky Engine repository at https://github.com/WistfulHopes/NightSkyEngine.git. If using the command line, type in the following:

```git git clone https://github.com/WistfulHopes/NightSkyEngine.git```

## Compile the engine
To compile the Night Sky Engine, you will need Unreal Engine 5.7 and Visual Studio. The version of Visual Studio must be 2022. For detailed instructions on installing Visual Studio for use with Unreal Engine, [click here](https://docs.unrealengine.com/5.7/en-US/setting-up-visual-studio-development-environment-for-cplusplus-projects-in-unreal-engine/).

After Visual Studio is set up, you will need to generate Visual Studio project files for Night Sky Engine. To do so, right-click on NightSkyEngine.uproject, and click on "Generate Visual Studio project files".

There will be a new file in the folder, `NightSkyEngine.sln`. Open it, and once Visual Studio has loaded, press Ctrl+Shift+B to compile the engine.

| Previous          |                              Next |
|:------------------|----------------------------------:|
| [Quick Start](quick-start.md) | [Getting Your Bearings](bearings.md) |