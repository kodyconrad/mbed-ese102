# Mbed CE ArmEducationX: ESE102 Project

This repository represents the projects within the [edX ArmEducationX: Embedded Systems Essentials with Arm: Get Practical with Hardware](https://www.edx.org/learn/embedded-systems/arm-education-embedded-systems-essentials-with-arm-get-practical-with-hardware) course, using the [Nucleo F746ZG](https://www.st.com/en/microcontrollers-microprocessors/stm32f746zg.html) with the Mbed Community Edition (CE) fork.

## Why Community Edition?

My experience with the [ArmEducationX: Embedded Systems Essentials with Arm: Getting Started](https://www.edx.org/learn/embedded-systems/arm-education-embedded-systems-essentials-with-arm-getting-started) course, using the Nucleo F746ZG over the Docker simulated model, led me to investigate if the Mbed OS framework was used in a professional/commercial capacity. The main pain points were around the build system, IDE, and complexity compared to native vendor APIs. The core API (GPIO, Serial, Analog, etc.) is well-written and easily readable, in my opinion. However, the overall workflow left much to be desired. After noticing a pattern of outdated class material, documentation, tooling, comments on Reddit, and the lack of commits in the Mbed OS official repository, I was led to the following post by MultipleMonomials (Jamie Smith): [[Help Wanted] Mbed CE: A community fork of Mbed OS](https://forums.mbed.com/t/help-wanted-mbed-ce-a-community-fork-of-mbed-os/17998).

It became clear that the official Mbed OS was not being maintained as well as the new community edition (CE), so I shifted over to use the ladder for this class and any others I may take moving forward that use `Mbed OS`.

## Setup

The following are instructions to help setup the project on your local system and are a copy from the original project with modifications as necessary.

> The following were copied and updated from the [mbed-ce-hello-world](https://github.com/mbed-ce/mbed-ce-hello-world)

1. Clone it to your machine.  Don't forget to use `--recursive` to clone the submodules: `git clone --recursive https://github.com/mbed-ce/mbed-ce-hello-world.git`
2. You may want to update the mbed-os submodule to the latest version, with `cd mbed-ce-hello-world/mbed-os && git fetch origin && git reset --hard origin/master`
3. Set up the GNU ARM toolchain (and other programs) on your machine using [the toolchain setup guide](https://github.com/mbed-ce/mbed-os/wiki/Toolchain-Setup-Guide).
4. Set up the CMake project for editing.  We have three ways to do this:
    - On the [command line](https://github.com/mbed-ce/mbed-os/wiki/Project-Setup:-Command-Line)
    - Using the [CLion IDE](https://github.com/mbed-ce/mbed-os/wiki/Project-Setup:-CLion)
    - Using the [VS Code IDE](https://github.com/mbed-ce/mbed-os/wiki/Project-Setup:-VS-Code)
5. Build the `flash-ESE102M#` target to upload the code to a connected device, where `#` is the module number to be built.

    **VS Code Notes**

    1. Use `Ctrl + Shift + P` to then type or select the `CMake: Select Build Target` option i.e. `flash-ESE102M1`.
    2. Use `Ctrl + Shift + P` to then type or select the `CMake: Select Variant` to select from Develop, Debug, etc.

### Connections & References

I will use the [X-NUCLEO-IKS4A1](https://www.st.com/en/ecosystems/x-nucleo-iks4a1.html) instead of the separate temperature sensor presented in the class.

> In addition, due to the use of the X-Nucleo for sensors and for simplicity and compatibility, we will use the Arduino compatible pins for all IO/Control unless specified otherwise. **This offers the best chance that people will be able to re-use the code or adapt it fairly easily.**

**References**:

- [Nucleo F746ZG Board Pinout](https://os.mbed.com/platforms/ST-Nucleo-F746ZG/#board-pinout)

**Pins**:

- **SPI**, SPI1_SCK (D13), MISO (D12), MOSI (D11)
- **Backlight Control**, PWM2/4 (A0)
- **Light Sensor**, ADC1/10 (A1)

### VS Code

#### 1. Open User Settings

You can configure VS Code to your liking through its various settings. Nearly every part of VS Code's editor, user interface, and functional behavior has options you can modify. 

I found it incredibly helpful to enable some additional `CMake` visibility settings; these configurations are mentioned below:

1. **Open User Settings**:
   - Press `Ctrl + ,` (Windows/Linux) or `⌘ + ,` (macOS) to open the Command Palette.
   - Type "Preferences: Open User Settings (JSON)" and select it from the dropdown. This will open your `settings.json` file.

#### 2. Add or Modify Settings

In your `.vscode/settings.json`, you can add, remove, modify to your hearts content.Below are settings that I found to be helpful for these Mbed OS CE CMake projects.

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
