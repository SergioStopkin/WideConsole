<head>
    <meta charset="UTF-8">
</head>

<h1>Main interface</h1>

| | Name | File |
|-| ---- | ---- |
| class | [Chart](#chart) | [chart.h](../src/wconsole/chart.h) |
| class | [Graph](#graph) | [graph.h](../src/wconsole/graph.h) |
| class | [Text](#text) | [text.h](../src/wconsole/text.h) |
| abstarct class | [*IWConsole*](#iwconsole) | [iwconsole.h](../src/wconsole/iwconsole.h) |
| abstarct class | [*IHeader*](#iheader) | [iheader.h](../src/wconsole/iheader.h) |
| abstarct class | [*IRange*](#irange) | [irange.h](../src/wconsole/irange.h) |
| abstarct class | [*IGrid*](#igrid) | [igrid.h](../src/wconsole/igrid.h) |
| abstarct class | [*IPrecisionP1*](#iprecision-p1) | [iprecision.h](../src/wconsole/iprecision.h) |
| abstarct class | [*IPrecisionP2*](#iprecision-p2) | [iprecision.h](../src/wconsole/iprecision.h) |

<h1 id="chart">Chart</h1>

| Public methods | Description | Derived |
| -------------- | ----------- | ------- |
| [(constructor)](#chart-constructor) | Constructs the chart object |
| [SetChartType](#set-chart-type) | Sets the [ChartType](#chart-type) |
| [SetOpacity](#set-opacity) | Sets the [Opacity](#opacity) |
| [SetChartColors](#set-chart-colors) | Sets the chart [Color](#color)s |
| [PrintChart](#print-chart) | Print the chart to the console |
| [SetColor](#set-color) | Sets the chart [Color](#color) | [IWConsole](#iwconsole) |
| [SetSize](#set-size) | Sets the size ...  | [IWConsole](#iwconsole) |
| [SetPosition](#set-position) | Sets the [Position](#position) | [IWConsole](#iwconsole) |
| [NewLine](#new-line) | Print the new line and ...  | [IWConsole](#iwconsole) |
| [NewLineInBlock](#new-line-in-block) | Print the new line in block and ...  | [IWConsole](#iwconsole) |
| [Clear](#clear) | Clear console output | [IWConsole](#iwconsole) |
| [ClearLast](#clear-last) | Clear the last chart  | [IWConsole](#iwconsole) |
| [ClearFirst](#clear-first) | Go to the position of the first printing chart | [IWConsole](#iwconsole) |
| [SetDataPosition](#set-data-position) | Sets the [DataPosition](data-position) | [IHeader](#iheader) |
| [ShowDataHeader](#show-data-header) | Show the data header  | [IHeader](#iheader) |
| [SetVerticalRange](#set-vertical-range) | Sets the vertical range value (Y) | [IRange](#irange) |
| [SetHorizontalRange](#set-horizontal-range) | Sets the horizontal range value (X) | [IRange](#irange) |
| [SetAxisColor](#set-axis-color) | Sets the axis [Color](#color) | [IGrid](#igrid) |
| [SetGridColor](#set-grid-color) | Sets the grid [Color](#color) | [IGrid](#igrid) |
| [SetArrow](#set-arrow) | Sets the [Arrow](#arrow)  | [IGrid](#igrid) |
| [ShowArrow](#show-arrow) | Show the arrow | [IGrid](#igrid) |
| [ShowGrid](#show-grid) | Show the grid | [IGrid](#igrid) |
| [SetPrecision](#set-precision) | Sets the precision of ...  | [IPrecisionP1](#iprecision-p1) |

```cpp
explicit Chart(const ChartType type = ChartType::Column, const Opacity opacity = Opacity::OP_100);
```

<span id="chart-constructor" style="font-family: monospace; font-size: 23px;">
    <i>explicit</i> <b>Chart</b>(<i>const ChartType</i> <b>type</b> = <i>ChartType::Column</i>,
                                 <i>const Opacity</i> <b>opacity</b> = <i>Opacity::OP_100</i>);
</span><br>
<span style="font-family: sans-serif;">Constructs the chart object.<br>
<b><i>type</i></b> — pointer to the c-style string<br></span>
<b><i>opacity</i></b> — pointer to the c-style string<br></span>

| | |
|-|-|
| ***type*** | the chart type |
| ***opacity*** | the chart opacity |

<h1 id="graph">Graph</h1>

| Public methods | Description | Derived |
| -------------- | ----------- | ------- |
| [(constructor)](#graph-constructor) | Constructs the graph object |
| [SetPoint](#set-point) | Sets the [Point](#point) type |
| [PrintGraph](#print-graph) | Print the graph to the console |
| [SetColor](#set-color) | Sets the chart [Color](#color) | [IWConsole](#iwconsole) |
| [SetSize](#set-size) | Sets the size ...  | [IWConsole](#iwconsole) |
| [SetPosition](#set-position) | Sets the [Position](#position) | [IWConsole](#iwconsole) |
| [NewLine](#new-line) | Print the new line and ...  | [IWConsole](#iwconsole) |
| [NewLineInBlock](#new-line-in-block) | Print the new line in block and ...  | [IWConsole](#iwconsole) |
| [Clear](#clear) | Clear console output | [IWConsole](#iwconsole) |
| [ClearLast](#clear-last) | Clear the last chart  | [IWConsole](#iwconsole) |
| [ClearFirst](#clear-first) | Go to the position of the first printing chart | [IWConsole](#iwconsole) |
| [SetDataPosition](#set-data-position) | Sets the [DataPosition](data-position) | [IHeader](#iheader) |
| [ShowDataHeader](#show-data-header) | Show the data header  | [IHeader](#iheader) |
| [SetVerticalRange](#set-vertical-range) | Sets the vertical range value (Y) | [IRange](#irange) |
| [SetHorizontalRange](#set-horizontal-range) | Sets the horizontal range value (X) | [IRange](#irange) |
| [SetAxisColor](#set-axis-color) | Sets the axis [Color](#color) | [IGrid](#igrid) |
| [SetGridColor](#set-grid-color) | Sets the grid [Color](#color) | [IGrid](#igrid) |
| [SetArrow](#set-arrow) | Sets the [Arrow](#arrow)  | [IGrid](#igrid) |
| [ShowArrow](#show-arrow) | Show the arrow | [IGrid](#igrid) |
| [ShowGrid](#show-grid) | Show the grid | [IGrid](#igrid) |
| [SetVerticalPrecision](#set-vertical-precision) | Sets the vertical precision of ...  | [IPrecisionP2](#iprecision-p2) |
| [SetHorizontalPrecision](#set-horizontal-precision) | Sets the horizontal precision of ...  | [IPrecisionP2](#iprecision-p2) |

<h1 id="text">Text</h1>

| Public methods | Description | Derived |
| -------------- | ----------- | ------- |
| [(constructor)](#text-constructor) | Constructs the text object |
| [PrintText](#print-text) | Print the text to the console |
| [SetColor](#set-color) | Sets the chart [Color](#color) | [IWConsole](#iwconsole) |
| [SetSize](#set-size) | Sets the size ...  | [IWConsole](#iwconsole) |
| [SetPosition](#set-position) | Sets the [Position](#position) | [IWConsole](#iwconsole) |
| [NewLine](#new-line) | Print the new line and ...  | [IWConsole](#iwconsole) |
| [NewLineInBlock](#new-line-in-block) | Print the new line in block and ...  | [IWConsole](#iwconsole) |
| [Clear](#clear) | Clear console output | [IWConsole](#iwconsole) |
| [ClearLast](#clear-last) | Clear the last chart  | [IWConsole](#iwconsole) |
| [ClearFirst](#clear-first) | Go to the position of the first printing chart | [IWConsole](#iwconsole) |

<h1 id="iwconsole"><i>IWConsole</i></h1>

| Public methods | Description |
| -------------- | ----------- |
| [SetColor](#set-color) | Sets the chart [Color](#color) |
| [SetSize](#set-size) | Sets the size ...  |
| [SetPosition](#set-position) | Sets the [Position](#position) |
| [NewLine](#new-line) | Print the new line and ...  |
| [NewLineInBlock](#new-line-in-block) | Print the new line in block and ...  |
| [Clear](#clear) | Clear console output |
| [ClearLast](#clear-last) | Clear the last chart  |
| [ClearFirst](#clear-first) | Go to the position of the first printing chart |

<h1 id="iheader"><i>IHeader</i></h1>

| Public methods | Description |
| -------------- | ----------- |
| [SetDataPosition](#set-data-position) | Sets the [DataPosition](data-position) |
| [ShowDataHeader](#show-data-header) | Show the data header  |

<h1 id="irange"><i>IRange</i></h1>

| Public methods | Description |
| -------------- | ----------- |
| [SetVerticalRange](#set-vertical-range) | Sets the vertical range value (Y) |
| [SetHorizontalRange](#set-horizontal-range) | Sets the horizontal range value (X) |

<h1 id="igrid"><i>IGrid</i></h1>

| Public methods | Description |
| -------------- | ----------- |
| [SetAxisColor](#set-axis-color) | Sets the axis [Color](#color) |
| [SetGridColor](#set-grid-color) | Sets the grid [Color](#color) |
| [SetArrow](#set-arrow) | Sets the [Arrow](#arrow)  |
| [ShowArrow](#show-arrow) | Show the arrow |
| [ShowGrid](#show-grid) | Show the grid |

<h1 id="iprecision-p1"><i>IPrecisionP1</i></h1>

| Public methods | Description |
| -------------- | ----------- |
| [SetPrecision](#set-precision) | Sets the precision of ... |

<h1 id="iprecision-p2"><i>IPrecisionP2</i></h1>

| Public methods | Description |
| -------------- | ----------- |
| [SetVerticalPrecision](#set-vertical-precision) | Sets the vertical precision of ...  |
| [SetHorizontalPrecision](#set-horizontal-precision) | Sets the horizontal precision of ...  |




<pre>
<font color=008000>████▌████▌████▌████▌</font>
<font color=00FF00>████▌████▌████▌████▌</font>
<font color=FF0000>████▌████▌████▌████▌</font>
<font color="blue">████▌████▌████▌████▌████▌</font>
<font color="purple">████▌████▌████▌████▌████▌████▌</font>
<font color="cyan">████▌████▌████▌████▌████▌████▌</font>
</pre>