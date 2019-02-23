<h1 align="center">
WConsole
</h1>

<p align="center">
<img height=22 src="https://travis-ci.org/SergioStopkin/WConsole.svg?branch=master">
</p>

<p align="center">
WConsole is a simple program for building graphs, charts and text output to the console.
</p>

## Standard

C++ 14

## Platforms

<img height=48 src="https://upload.wikimedia.org/wikipedia/commons/3/3c/TuxFlat.svg"> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; <img height=43 src="https://upload.wikimedia.org/wikipedia/commons/d/df/Apple-Apple.svg"> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; <img height=40 src="https://upload.wikimedia.org/wikipedia/commons/thumb/5/5f/Windows_logo_-_2012.svg/1024px-Windows_logo_-_2012.svg.png">

Linux &nbsp;&nbsp;&nbsp;&nbsp; macOS &nbsp;&nbsp;&nbsp;&nbsp; Windows

## Getting Started

For using charts, graphs and texts include header files, respectively:

```
#include "wconsole/chart.h"
#include "wconsole/graph.h"
#include "wconsole/text.h"
```
The project uses `WConsole` namespace.

Create objects:

```
WConsole::Chart chart;
WConsole::Graph graph;
WConsole::Text  text;
```

See the [INTERFACE.md](INTERFACE.md) file for more details.

## Compilers

* [GCC](https://gcc.gnu.org/) - Linux, macOS
* [MinGW](http://www.mingw.org/) - Windows

Don't forget

```
-std=c++14
```

## Authors

**Sergio Stopkin** - <sergiistopkin@gmail.com> -  [GitHub](https://github.com/SergioStopkin)

## License

<img src="https://upload.wikimedia.org/wikipedia/commons/9/93/GPLv3_Logo.svg" height=100></img>

GNU General Public License version 3 or any later version. See the [COPYING](COPYING) file for details.

