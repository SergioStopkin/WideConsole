<p align="center">
    <br><br><br>
    <a href="https://github.com/SergioStopkin/WConsole">
        <img src="./doc/img/img-logo.svg"></img>
    </a>
    <br><br><br>
</p>

<p align="center">
    <a href="https://travis-ci.org/SergioStopkin/WConsole">
        <img src="https://img.shields.io/travis/SergioStopkin/WConsole.svg?style=flat-square&label=gcc/clang">
    </a>
    <a href="https://ci.appveyor.com/project/SergioStopkin/WConsole">
        <img src="https://img.shields.io/appveyor/ci/SergioStopkin/WConsole.svg?style=flat-square&logo=appveyor&label=msvc">
    </a>
    <a href="https://github.com/SergioStopkin/WConsole/blob/master/COPYING">
        <img src="https://img.shields.io/github/license/SergioStopkin/Wconsole.svg?style=flat-square"/>
    </a>
    <a href="https://github.com/SergioStopkin/WConsole/archive/master.zip">
        <img src="https://img.shields.io/github/repo-size/sergiostopkin/wconsole.svg?style=flat-square"/>
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

