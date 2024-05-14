# Mbed CE - ESE102 Project

This repository represents the projects within [ESE102 ArmEducationX: Embedded Systems Essentials with Arm: Get Practical with Hardware](https://www.edx.org/learn/embedded-systems/arm-education-embedded-systems-essentials-with-arm-get-practical-with-hardware) course using the Nucleo F746ZG with the Mbed Community Edition (CE) fork.

## Why Community Edition?

My journey taking the first official Embedded Systems Essentials with Arm – Professional Certificate on edX led me to wonder exactly how much the Mbed OS framework was being used in the commercial products space. The development environments felt very hobbyist, developer content/projects always seemed very old, and the build system was attrocious. Was this a fruitless endeavor? Could my time be better spent using the standard STM32 development tools and resources? The answer, is a maybe, but I already spent the money on the class, so it was now a question of "How do I make the most out of ESE102?"

These questions eventually led me to the following post by MultipleMonomials (Jamie Smith) [[Help Wanted] Mbed CE: A community fork of Mbed OS](https://forums.mbed.com/t/help-wanted-mbed-ce-a-community-fork-of-mbed-os/17998). Thus, I created this project from [mbed-ce-hello-world](https://github.com/mbed-ce/mbed-ce-hello-world) to finish off the second course, and it would at least be leveraging a fork that is actively supported and maintained by the community.

## Initial Connections

Reference the [Mbed Nucleo F746ZG Pinout for CN8](https://os.mbed.com/media/uploads/jeromecoutant/nucleo_f746zg_zio_left_2022_10_19_V6L6hlp.png)

We will use the **SPI3** channel to control the **SN74HC595**.

### Connection Table

| SN74HC595 Pin Name | Nucleo F746ZG Pin Name | Function |
| ------------------ | ---------------------- | -------- |
| SER               | PC_12 (SPI3_MOSI)     | SPI 3 master out slave in; where the data is output.     |
| RCLK              | PD_2                  | Chip select GPIO output; controls when the register is clocked in.      |
| SRCLK             | PC_10 (SPI3_SCK)     | SPI 3 Clock signal.     |
| SRCLR             | 3V3                   | Shift register clear pin high; if low, it will clear the shift register.     |
| OE                | GND                   | Output Enable low to enable output pins.      |

# Setup

The following are instructions to help setup the project on your local system.

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

You can configure VS Code to your liking through its various settings. Nearly every part of VS Code's editor, user interface, and functional behavior has options you can modify. To get started, follow these steps:

1. **Open User Settings**:
   - Press `Ctrl + ,` (Windows/Linux) or `⌘ + ,` (macOS) to open the Command Palette.
   - Type "Preferences: Open User Settings (JSON)" and select it from the dropdown. This will open your `settings.json` file.

### 2. Add or Modify Settings

In your `settings.json`, you can add or modify the following configurations:

> These are settings that i found to be helpful in using a CMake based project.

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
