<p align="center">
    <br><br><br>
    <a href="https://github.com/SergioStopkin/WConsole">
        <img src="./doc/img/img-logo.svg"></img>
    </a>
    <br><br><br>
</p>

<p align="center">
    <a href="https://github.com/sergiostopkin/wconsole/actions/workflows/actions-develop.yml">
        <img src="https://img.shields.io/github/actions/workflow/status/sergiostopkin/wconsole/actions-develop.yml?style=flat-square&label=develop">
    </a>
    <a href="https://github.com/sergiostopkin/wconsole/blob/release/COPYING">
        <img src="https://img.shields.io/github/license/sergiostopkin/wconsole?style=flat-square"/>
    </a>
    <a href="https://github.com/SergioStopkin/WConsole/archive/release.zip">
        <img src="https://img.shields.io/github/repo-size/sergiostopkin/wconsole?style=flat-square"/>
    </a>
</p>

<h1 align="center">WConsole</h1>

<p align="center">
    WConsole is a simple program for building graphs, charts and text output to the console.
</p>

![](./doc/img/img-readme.png?raw=true)

## Standard

C++ 14

## Platforms

<img height=48 src="./doc/img/tux-logo.svg"> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; <img height=43 src="./doc/img/apple-logo.svg"> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; <img height=40 src="./doc/img/windows-logo.png">

Linux &nbsp;&nbsp;&nbsp;&nbsp; macOS &nbsp;&nbsp;&nbsp;&nbsp; Windows

## Getting started

For using charts, graphs and texts, include header files respectively:

```cpp
#include "wconsole/chart.h"
#include "wconsole/graph.h"
#include "wconsole/text.h"
```
The project uses `WConsole` namespace.

Create objects:

```cpp
WConsole::Chart chart;
WConsole::Graph graph;
WConsole::Text  text;
```

## Usage details

See the example in the file [main.cpp](./src/main.cpp).

See the [INTERFACE.md](./doc/INTERFACE.md) file for more details.

## Authors

**Sergio Stopkin** - <sergiistopkin@gmail.com> -  [GitHub](https://github.com/SergioStopkin)

## License

<img src="./doc/img/gplv3-logo.svg" height=80></img>

GNU General Public License version 3 or any later version. See the [COPYING](./COPYING) file for details.

