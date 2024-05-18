# Mbed CE ArmEducationX: ESE102 Project

This repository represents the projects within the [edX ArmEducationX: Embedded Systems Essentials with Arm: Get Practical with Hardware](https://www.edx.org/learn/embedded-systems/arm-education-embedded-systems-essentials-with-arm-get-practical-with-hardware) course, using the Nucleo F746ZG with the Mbed Community Edition (CE) fork.

## Why Community Edition?

My experience with the [ArmEducationX: Embedded Systems Essentials with Arm: Getting Started](https://www.edx.org/learn/embedded-systems/arm-education-embedded-systems-essentials-with-arm-getting-started) course, using the Nucleo F746ZG over the simulated model, led me to wonder—and even doubt—whether the Mbed OS framework was used in a professional/commercial environment. There were several factors, but the primary categories were the build system, IDE, and complexity compared to native vendor APIs. The core API (GPIO, Serial, Analog, etc.) was well-written and easily readable, in my opinion. However, the overall workflow left much to be desired. After noticing a pattern of outdated class material, documentation, tooling, comments on Reddit, and the lack of commits in the Mbed OS official repository, I was led to the following post by MultipleMonomials (Jamie Smith): [[Help Wanted] Mbed CE: A community fork of Mbed OS](https://forums.mbed.com/t/help-wanted-mbed-ce-a-community-fork-of-mbed-os/17998).

It became very clear that Mbed OS was not being maintained. This meant I was spending time learning an API that I would likely not use afterward. However, thanks to MultipleMonomials and the community, I shifted to using the community edition for this class, employing mbed-ce-hello-world as the template. The CE fork allowed for a significantly improved and more professional workflow, in my opinion, and it is actively maintained, opening up the possibility for future contributions.

# Setup

The following are instructions to help setup the project on your local system and are a copy from the original project with modifications as necessary.

## How to set up this project:

1. Clone it to your machine.  Don't forget to use `--recursive` to clone the submodules: `git clone --recursive https://github.com/mbed-ce/mbed-ce-hello-world.git`
2. You may want to update the mbed-os submodule to the latest version, with `cd mbed-ce-hello-world/mbed-os && git fetch origin && git reset --hard origin/master`
3. Set up the GNU ARM toolchain (and other programs) on your machine using [the toolchain setup guide](https://github.com/mbed-ce/mbed-os/wiki/Toolchain-Setup-Guide).
4. Set up the CMake project for editing.  We have three ways to do this:
    - On the [command line](https://github.com/mbed-ce/mbed-os/wiki/Project-Setup:-Command-Line)
    - Using the [CLion IDE](https://github.com/mbed-ce/mbed-os/wiki/Project-Setup:-CLion)
    - Using the [VS Code IDE](https://github.com/mbed-ce/mbed-os/wiki/Project-Setup:-VS-Code)
5. Build the `flash-HelloWorld` target to upload the code to a connected device.

## Configuring VS Code Settings

### 1. Open User Settings

You can configure VS Code to your liking through its various settings. Nearly every part of VS Code's editor, user interface, and functional behavior has options you can modify. 

I found it incredibly helpful to enable some additional `CMake` visibility settings; these configurations are mentioned below:

1. **Open User Settings**:
   - Press `Ctrl + ,` (Windows/Linux) or `⌘ + ,` (macOS) to open the Command Palette.
   - Type "Preferences: Open User Settings (JSON)" and select it from the dropdown. This will open your `settings.json` file.

### 2. Add or Modify Settings

In your `settings.json`, you can add or modify the following configurations:

```json
{
    "cmake.buildDirectory": "${workspaceFolder}/build/${variant:board}-${variant:buildType}",
    "files.associations": {
        "*.tcc": "cpp",
        "ostream": "cpp",
        "chrono": "cpp"
    },
    "cmake.configureOnOpen": true,
    "git.autofetch": true,
    "cmake.options.statusBarVisibility": "visible",
    "cmake.options.advanced": {
        "build": {
            "statusBarVisibility": "inherit",
            "inheritDefault": "visible"
        },
        "launch": {
            "statusBarVisibility": "inherit",
            "inheritDefault": "visible"
        },
        "debug": {
            "statusBarVisibility": "inherit",
            "inheritDefault": "visible"
        }
    }
}
