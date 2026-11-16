# QtVintage

[Deutsch](README.de.md)

QtVintage provides four Qt Widgets for retro-style control panels: an LED, a seven-segment display, and two switch variants. It builds a static widget library and, optionally, a Qt Designer plugin. The CMake package exports the `qvintage::Widgets` target.

## Requirements

- CMake 3.21 or newer and a C++20 compiler
- Qt 6.2 or newer with Widgets
- Qt Designer, UiPlugin, and their development files when building the Designer plugin

## Build

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

To build only the widget library:

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DQVINTAGE_BUILD_DESIGNER_PLUGIN=OFF
cmake --build build
```

Install into a local prefix with `cmake --install build --prefix /path/to/prefix`. The Designer plugin location is controlled by `QVINTAGE_DESIGNER_PLUGIN_DIR`; check that it matches your Qt installation before installing the plugin.

## Components

| Directory | Widget |
| --- | --- |
| `LED/` | Indicator LED |
| `SEG7/` | Seven-segment display |
| `SWITCH/` | Switch |
| `SWITCH2/` | Second switch variant |

This repository has no automated test suite or release artifacts. Build both CMake configurations and inspect the widgets in Qt Designer before packaging. Copyright notices are present in source files; a repository-wide license has not yet been specified, so redistribution terms need confirmation from the rights holder.
