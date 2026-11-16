# QtVintage

[English](README.md)

QtVintage stellt vier Qt-Widgets für Bedienoberflächen im Retro-Stil bereit: eine LED, eine Siebensegmentanzeige und zwei Schaltervarianten. Das Projekt baut eine statische Widget-Bibliothek und optional ein Plugin für Qt Designer. Das CMake-Paket exportiert das Ziel `qvintage::Widgets`.

## Voraussetzungen

- CMake ab 3.21 und ein C++20-Compiler
- Qt ab 6.2 mit Widgets
- Qt Designer, UiPlugin und deren Entwicklungsdateien für das Designer-Plugin

## Bauen

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

Nur die Widget-Bibliothek bauen:

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DQVINTAGE_BUILD_DESIGNER_PLUGIN=OFF
cmake --build build
```

Mit `cmake --install build --prefix /pfad/zum/ziel` in ein lokales Verzeichnis installieren. Der Installationsort des Designer-Plugins wird über `QVINTAGE_DESIGNER_PLUGIN_DIR` gesteuert; vor der Installation sollte er zur verwendeten Qt-Installation passen.

## Komponenten

| Verzeichnis | Widget |
| --- | --- |
| `LED/` | Anzeige-LED |
| `SEG7/` | Siebensegmentanzeige |
| `SWITCH/` | Schalter |
| `SWITCH2/` | Zweite Schaltervariante |

Das Repository enthält derzeit keine automatisierten Tests oder Release-Artefakte. Vor einer Paketveröffentlichung sollten beide CMake-Konfigurationen gebaut und die Widgets in Qt Designer geprüft werden. Die Quelldateien enthalten Copyright-Hinweise; eine einheitliche Lizenz für das gesamte Repository ist noch nicht festgelegt. Die Weitergabebedingungen müssen mit dem Rechteinhaber geklärt werden.
