# wiibrew.js loader

The wiibrew.js homebrew loader app.

## Usage

This app must be loaded onto your Wii before you can run any wiibrew.js code.

### Prerequisites

 - Wii on the same local network as your computer.
    - Homebrew channel installed on the Wii (I'm using v1.1.0; there's plenty of online tutorials on how to install homebrew)
 - A computer with [Node.js](https://nodejs.org/) v5.x (or newer) installed.
 - [devkitPro](devkitpro.org) toolchain
 - [wiiload](http://wiibrew.org/wiki/Wiiload)

### Installation

Compile the loader app by running `make` in this directory. Then use wiiload to load `app.dol` onto your Wii.

*Note: You do not need to install a wiiload server plugin, the Homebrew Channel should automatically accept and execute
your .dol and .elf files for you.*

You are now ready to [start](https://github.com/wiibrewjs/wiibrewjs) writing wiibrew.js code.