<p align="center">
    <br><br><br>
    <a href="https://github.com/SergioStopkin/WideConsole">
        <img src="./doc/img/img-logo.svg"></img>
    </a>
    <br><br><br>
</p>

<p align="center">
    <a href="https://github.com/sergiostopkin/wideconsole/actions/workflows/actions-develop.yml">
        <img src="https://img.shields.io/github/actions/workflow/status/sergiostopkin/wideconsole/actions-develop.yml?style=flat-square&label=develop">
    </a>
    <a href="https://github.com/sergiostopkin/wideconsole/blob/release/COPYING">
        <img src="https://img.shields.io/github/license/sergiostopkin/wideconsole?style=flat-square"/>
    </a>
    <a href="https://github.com/SergioStopkin/WideConsole/archive/develop.zip">
        <img src="https://img.shields.io/github/repo-size/sergiostopkin/wideconsole?style=flat-square&label=download"/>
    </a>
</p>

<h1 align="center">WideConsole</h1>

<p align="center">
    WideConsole is a simple program for building graphs, charts and text output to the console.
</p>

![](./doc/img/img-readme.png?raw=true)

## Standard

C++ 14

## Platforms

<img height=42 src="./doc/img/logo-tux.svg"> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; <img height=42 src="./doc/img/logo-apple.svg"> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; <img height=34 src="./doc/img/logo-windows.svg">

Linux &nbsp;&nbsp;&nbsp;&nbsp; macOS &nbsp;&nbsp;&nbsp;&nbsp; Windows

## Getting started

For using charts, graphs and texts, include header files respectively:

```cpp
#include "wideconsole/chart.h"
#include "wideconsole/graph.h"
#include "wideconsole/text.h"
```
The project uses `WideConsole` namespace.

Create objects:

```cpp
WideConsole::Chart chart;
WideConsole::Graph graph;
WideConsole::Text  text;
```

## Usage details

See the example in the file [main.cpp](./src/main.cpp).

See the [INTERFACE.md](./doc/INTERFACE.md) file for more details.

## Authors

**Sergio Stopkin** - <sergiistopkin@gmail.com> -  [GitHub](https://github.com/SergioStopkin)

## License

<img src="./doc/img/logo-gplv3.svg" height=80></img>

GNU General Public License version 3 or any later version. See the [COPYING](./COPYING) file for details.

