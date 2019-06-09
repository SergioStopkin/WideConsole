<head>
    <meta charset="UTF-8">
</head>

```diff
- This document is not finished!
```

<h1>Public interface</h1>

| | Name | File |
|-| ---- | ---- |
| class | [Chart](#chart) | [chart.h](../src/wconsole/chart.h) |
| class | [Graph](#graph) | [graph.h](../src/wconsole/graph.h) |
| class | [Text](#text) | [text.h](../src/wconsole/text.h) |
| class | [Font](#font) | [font.h](../src/wconsole/font.h) |
| abstract class | [*IWConsole*](#iwconsole) | [iwconsole.h](../src/wconsole/iwconsole.h) |
| abstract class | [*IHeader*](#iheader) | [iheader.h](../src/wconsole/iheader.h) |
| abstract class | [*IRange*](#irange) | [irange.h](../src/wconsole/irange.h) |
| abstract class | [*IGrid*](#igrid) | [igrid.h](../src/wconsole/igrid.h) |
| abstract class | [*IPrecisionP1*](#iprecision-p1) | [iprecision.h](../src/wconsole/iprecision.h) |
| abstract class | [*IPrecisionP2*](#iprecision-p2) | [iprecision.h](../src/wconsole/iprecision.h) |

#### UML Class diagram:
![uml class](http://www.plantuml.com/plantuml/proxy?cache=no&src=https://raw.github.com/SergioStopkin/WConsole/master/doc/UMLClass.md)

<h1 id="chart">Chart</h1>

| Public methods | Description | Derived |
| -------------- | ----------- | ------- |
| [(constructor)](#chart-constructor) | Constructs the chart object |
| [SetChartType](#set-chart-type) | Sets the [ChartType](#chart-type) |
| [SetOpacity](#set-opacity) | Sets the [Opacity](#opacity) |
| [SetChartColors](#set-chart-colors) | Sets the chart [Color](#color)s |
| [PrintChart](#print-chart) | Print the chart to the console |
| [SetColor](#set-color) | Sets the chart [Color](#color) | [*IWConsole*](#iwconsole) |
| [SetSize](#set-size) | Sets the size ...  | [*IWConsole*](#iwconsole) |
| [SetPosition](#set-position) | Sets the position | [*IWConsole*](#iwconsole) |
| [NewLine](#new-line) | Print the new line and ...  | [*IWConsole*](#iwconsole) |
| [NewLineInBlock](#new-line-in-block) | Print the new line in block and ...  | [*IWConsole*](#iwconsole) |
| [Clear](#clear) | Clear console output | [*IWConsole*](#iwconsole) |
| [ClearLast](#clear-last) | Clear the last chart  | [*IWConsole*](#iwconsole) |
| [ClearFirst](#clear-first) | Go to the position of the first printing chart | [*IWConsole*](#iwconsole) |
| [SetDataPosition](#set-data-position) | Sets the [DataPosition](#data-position) | [*IHeader*](#iheader) |
| [ShowDataHeader](#show-data-header) | Show the data header  | [*IHeader*](#iheader) |
| [SetVerticalRange](#set-vertical-range) | Sets the vertical range value (Y) | [*IRange*](#irange) |
| [SetHorizontalRange](#set-horizontal-range) | Sets the horizontal range value (X) | [*IRange*](#irange) |
| [SetAxisColor](#set-axis-color) | Sets the axis [Color](#color) | [*IGrid*](#igrid) |
| [SetGridColor](#set-grid-color) | Sets the grid [Color](#color) | [*IGrid*](#igrid) |
| [SetArrow](#set-arrow) | Sets the [Arrow](#arrow)  | [*IGrid*](#igrid) |
| [ShowArrow](#show-arrow) | Show the arrow | [*IGrid*](#igrid) |
| [ShowGrid](#show-grid) | Show the grid | [*IGrid*](#igrid) |
| [SetPrecision](#set-precision) | Sets the precision of ...  | [*IPrecisionP1*](#iprecision-p1) |

<p id="chart-constructor" class="func">
    <t class="keyw">explicit</t> <b>Chart</b>
    <t class="mark">(</t><t class="keyw">const</t>
    ChartType <b>type</b>
    <t class="keyw">=</t>
    ChartType<t class="mark">::</t>Column<t class="mark">,</t>
    <t class="keyw">const</t>
    Opacity <b>opacity</b>
    <t class="keyw">=</t>
    Opacity<t class="mark">::</t>OP_100<t class="mark">)</t><t class="term">;</t>
</p>

Constructs the chart object.</br>
`type` [ChartType](#chart-type)</br>
`opacity` chart [Opacity](#opacity)</br>
</br>

<p id="set-chart-type" class="func">
    <t class="keyw">void</t> <b>SetChartType</b>
    <t class="mark">(</t><t class="keyw">const</t>
    ChartType <b>type</b><t class="mark">)</t>
    <t class="keyw">noexcept</t><t class="term">;</t>
</p>

Setting the chart type.</br>
`type` [ChartType](#chart-type)</br>
</br>

<p id="set-opacity" class="func">
    <t class="keyw">void</t> <b>SetOpacity</b>
    <t class="mark">(</t><t class="keyw">const</t>
    Opacity <b>opacity</b><t class="mark">)</t>
    <t class="keyw">noexcept</t><t class="term">;</t>
</p>

Setting the opacity of the bricks.</br>
`opacity` [Opacity](#opacity)</br>
</br>

<p id="set-chart-colors" class="func">
    <t class="keyw">void</t> <b>SetChartColors</b>
    <t class="mark">(</t><t class="keyw">const</t>
    std<t class="mark">::</t>vector<t class="keyw"><</t>Color<t class="keyw">></t>
    & <b>colors</b><t class="mark">)</t>
    <t class="keyw">noexcept</t><t class="term">;</t>
</p>

Setting the chart colors. If the colors are less than the data, the colors are repeated.</br>
`colors` [Color](#color)s</br>
</br>

<p id="print-chart" class="func">
    <t class="keyw">template</t> <t class="keyw"><</t><t class="keyw">typename</t> T<t class="keyw">></t></br>
    <t class="keyw">void</t> <b>PrintChart</b>
    <t class="mark">(</t><t class="keyw">const</t>
    std<t class="mark">::</t>vector<t class="keyw"><</t>T<t class="keyw">></t>
    & <b>data</b><t class="mark">)</t><t class="term">;</t>
</p>

Print chart.</br>
`data` data vector</br>
</br>

<h1 id="graph">Graph</h1>

| Public methods | Description | Derived |
| -------------- | ----------- | ------- |
| [(constructor)](#graph-constructor) | Constructs the graph object |
| [SetPoint](#set-point) | Sets the [Point](#point) type |
| [PrintGraph](#print-graph) | Print the graph to the console |
| [SetColor](#set-color) | Sets the chart [Color](#color) | [*IWConsole*](#iwconsole) |
| [SetSize](#set-size) | Sets the size ...  | [*IWConsole*](#iwconsole) |
| [SetPosition](#set-position) | Sets the position | [*IWConsole*](#iwconsole) |
| [NewLine](#new-line) | Print the new line and ...  | [*IWConsole*](#iwconsole) |
| [NewLineInBlock](#new-line-in-block) | Print the new line in block and ...  | [*IWConsole*](#iwconsole) |
| [Clear](#clear) | Clear console output | [*IWConsole*](#iwconsole) |
| [ClearLast](#clear-last) | Clear the last chart  | [*IWConsole*](#iwconsole) |
| [ClearFirst](#clear-first) | Go to the position of the first printing chart | [*IWConsole*](#iwconsole) |
| [SetDataPosition](#set-data-position) | Sets the [DataPosition](#data-position) | [*IHeader*](#iheader) |
| [ShowDataHeader](#show-data-header) | Show the data header  | [*IHeader*](#iheader) |
| [SetVerticalRange](#set-vertical-range) | Sets the vertical range value (Y) | [*IRange*](#irange) |
| [SetHorizontalRange](#set-horizontal-range) | Sets the horizontal range value (X) | [*IRange*](#irange) |
| [SetAxisColor](#set-axis-color) | Sets the axis [Color](#color) | [*IGrid*](#igrid) |
| [SetGridColor](#set-grid-color) | Sets the grid [Color](#color) | [*IGrid*](#igrid) |
| [SetArrow](#set-arrow) | Sets the [Arrow](#arrow)  | [*IGrid*](#igrid) |
| [ShowArrow](#show-arrow) | Show the arrow | [*IGrid*](#igrid) |
| [ShowGrid](#show-grid) | Show the grid | [*IGrid*](#igrid) |
| [SetVerticalPrecision](#set-vertical-precision) | Sets the vertical precision of ...  | [*IPrecisionP2*](#iprecision-p2) |
| [SetHorizontalPrecision](#set-horizontal-precision) | Sets the horizontal precision of ...  | [*IPrecisionP2*](#iprecision-p2) |

<p id="graph-constructor" class="func">
    <t class="keyw">explicit</t> <b>Graph</b>
    <t class="mark">(</t><t class="keyw">const</t>
    Point <b>point</b>
    <t class="keyw">=</t>
    Point<t class="mark">::</t>Dot<t class="mark">)</t><t class="term">;</t>
</p>

Constructs the graph object.</br>
`point` [Point](#point)</br>
</br>

<p id="set-point" class="func">
    <t class="keyw">void</t> <b>SetPoint</b>
    <t class="mark">(</t><t class="keyw">const</t>
    Point <b>point</b><t class="mark">)</t>
    <t class="keyw">noexcept</t><t class="term">;</t>
</p>

Setting the point.</br>
`point` [Point](#point)</br>
</br>

<p id="print-graph" class="func">
    <t class="keyw">template</t> <t class="keyw"><</t><t class="keyw">typename</t> T<t class="keyw">></t></br>
    <t class="keyw">void</t> <b>PrintGraph</b>
    <t class="mark">(</t><t class="keyw">const</t>
    std<t class="mark">::</t>vector<t class="keyw"><</t>std<t class="mark">::</t>pair<t class="keyw"><</t>T,
    T<t class="keyw">></t><t class="keyw">></t>
    & <b>data</b><t class="mark">)</t><t class="term">;</t>
</p>

Print garph.</br>
`data` coordinate pairs vector</br>
</br>


<h1 id="text">Text</h1>

| Public methods | Description | Derived |
| -------------- | ----------- | ------- |
| [(constructor)](#text-constructor) | Constructs the text object |
| [PrintText](#print-text) | Print the text to the console |
| [SetColor](#set-color) | Sets the chart [Color](#color) | [*IWConsole*](#iwconsole) |
| [SetSize](#set-size) | Sets the size ...  | [*IWConsole*](#iwconsole) |
| [SetPosition](#set-position) | Sets the position | [*IWConsole*](#iwconsole) |
| [NewLine](#new-line) | Print the new line and ...  | [*IWConsole*](#iwconsole) |
| [NewLineInBlock](#new-line-in-block) | Print the new line in block and ...  | [*IWConsole*](#iwconsole) |
| [Clear](#clear) | Clear console output | [*IWConsole*](#iwconsole) |
| [ClearLast](#clear-last) | Clear the last chart  | [*IWConsole*](#iwconsole) |
| [ClearFirst](#clear-first) | Go to the position of the first printing chart | [*IWConsole*](#iwconsole) |

<p id="text-constructor" class="func">
    <t class="keyw">explicit</t> <b>Text</b>
    <t class="mark">(</t><t class="keyw">const</t>
    FontType & <b>font_type</b>
    <t class="keyw">=</t>
    FontType<t class="mark">::</t>Monospace<t class="mark">)</t><t class="term">;</t>
</p>

Constructs the text object.</br>
`font_type` [FontType](#font-type)</br>
</br>

<p id="print-text" class="func">
    <t class="keyw">void</t> <b>PrintText</b>
    <t class="mark">(</t><t class="keyw">const char *</t>
    <b>s</b><t class="mark">)</t>
    <t class="keyw">noexcept</t><t class="term">;</t>
    </br>
    <t class="keyw">void</t> <b>PrintText</b>
    <t class="mark">(</t><t class="keyw">const</t>
    std<t class="mark">::</t>string
    & <b>str</b><t class="mark">)</t>
    <t class="keyw">noexcept</t><t class="term">;</t>
    </br>
    <t class="keyw">void</t> <b>PrintText</b>
    <t class="mark">(</t><t class="keyw">const</t>
    std<t class="mark">::</t>string
    & <b>str</b>,
    <t class="keyw">const</t> Font
    & <b>font</b><t class="mark">)</t>
    <t class="keyw">noexcept</t><t class="term">;</t>
</p>

Print text.</br>
`s` pointer to C-string</br>
`str` string</br>
`font` [Font](#font) object</br>
</br>

<h1 id="font">Font</h1>

| Public methods | Description |
| -------------- | ----------- |
| [(constructor)](#font-constructor) | Constructs the font object |
| [SetFontType](#set-font-type) | Sets the [FontType](#font-type) |
| [SetForegroundColor](#set-foreground-color) | Sets the foreground [Color](#color) |
| [SetBackgroundColor](#set-background-color) | Sets the background [Color](#color) |
| [SetInverseColor](#set-inverse-color) | Sets the inverse color |
| [SetUnderline](#set-underline) | Sets the underline |
| [GetFontType](#get-font-type) | Gets the [FontType](#font-type) |
| [WriteParametersToBuff](#write-parameters-to-buff) | Write parameters to `std::wstring` buffer |

<p id="font-constructor" class="func">
    <t class="keyw">explicit</t> <b>Font</b>
    <t class="mark">(</t><t class="keyw">const</t>
    FontType & <b>font_type</b>
    <t class="keyw">=</t>
    FontType<t class="mark">::</t>Monospace<t class="mark">)</t><t class="term">;</t>
</p>

Constructs the font object.</br>
`font_type` [FontType](#font-type)</br>
</br>

<p id="set-font-type" class="func">
    <t class="keyw">void</t> <b>SetFontType</b>
    <t class="mark">(</t><t class="keyw">const</t>
    FontType & <b>font_type</b><t class="mark">)</t>
    <t class="keyw">noexcept</t><t class="term">;</t>
</p>

Setting the font type.</br>
`font_type` [FontType](#font-type)</br>
</br>

<p id="set-foreground-color" class="func">
    <t class="keyw">void</t> <b>SetForegroundColor</b>
    <t class="mark">(</t><t class="keyw">const</t>
    Color & <b>color</b><t class="mark">)</t>
    <t class="keyw">noexcept</t><t class="term">;</t>
</p>

Setting the foreground color.</br>
`color` the foreground [Color](#color)</br>
</br>

<p id="set-background-color" class="func">
    <t class="keyw">void</t> <b>SetBackgroundColor</b>
    <t class="mark">(</t><t class="keyw">const</t>
    Color & <b>color</b><t class="mark">)</t>
    <t class="keyw">noexcept</t><t class="term">;</t>
</p>

Setting the background color.</br>
`color` the background [Color](#color)</br>
</br>

<p id="set-inverse-color" class="func">
    <t class="keyw">void</t> <b>SetInverseColor</b>
    <t class="mark">(</t><t class="keyw">const bool</t>
    <b>is_inverse</b><t class="mark">)</t>
    <t class="keyw">noexcept</t><t class="term">;</t>
</p>

Setting the inverse color.</br>
`is_inverse` `true` - inverse, `false` - not inverse</br>
</br>

<p id="set-underline" class="func">
    <t class="keyw">void</t> <b>SetUnderline</b>
    <t class="mark">(</t><t class="keyw">const bool</t>
    <b>is_underline</b><t class="mark">)</t>
    <t class="keyw">noexcept</t><t class="term">;</t>
</p>

Setting the underline.</br>
`is_underline` `true` - underline, `false` - not underline</br>
</br>

<p id="get-font-type" class="func">
    FontType <b>GetFontType</b>
    <t class="mark">()</t>
    <t class="keyw">const</t> <t class="keyw">noexcept</t><t class="term">;</t>
</p>

Return the [FontType](#font-type).</br>
</br>

<p id="write-parameters-to-buff" class="func">
    <t class="keyw">void</t> <b>WriteParametersToBuff</b>
    <t class="mark">(</t>std<t class="mark">::</t>wstring
    & <b>buff</b><t class="mark">)</t>
    <t class="keyw">const</t> <t class="keyw">noexcept</t><t class="term">;</t>
</p>

Write parameters to `std::wstring` buffer.</br>
`buff` `std::wstring` buffer</br>
</br>

<h1 id="iwconsole"><i>IWConsole</i></h1>

| Public methods | Description |
| -------------- | ----------- |
| [SetColor](#set-color) | Sets the chart [Color](#color) |
| [SetSize](#set-size) | Sets the size ...  |
| [SetPosition](#set-position) | Sets the position |
| [NewLine](#new-line) | Print the new line and ...  |
| [NewLineInBlock](#new-line-in-block) | Print the new line in block and ...  |
| [Clear](#clear) | Clear console output |
| [ClearLast](#clear-last) | Clear the last chart  |
| [ClearFirst](#clear-first) | Go to the position of the first printing chart |

<h1 id="iheader"><i>IHeader</i></h1>

| Public methods | Description |
| -------------- | ----------- |
| [SetDataPosition](#set-data-position) | Sets the [DataPosition](#data-position) |
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

<h1>Data structures</h1>

<p id="arrow">

```cpp
enum class Arrow {
        Big,
        Small
    };
```

<p id="chart-type">

```cpp
enum class ChartType {
    Column,
    Bar,
    Pie,
};
```

<p id="color">

```cpp
enum class Color {
    Black,
    Red,
    Green,
    Yellow,
    Blue,
    Magenta,
    Cyan,
    White,
    BrightBlack,
    BrightRed,
    BrightGreen,
    BrightYellow,
    BrightBlue,
    BrightMagenta,
    BrightCyan,
    BrightWhite,
    Default,
    BrightDefault
};
```

<p id="data-position">

```cpp
enum class DataPosition {
    Right,
    Left,
    Center
};
```

<p id="font-type">

```cpp
enum class FontType {
    Serif,
    SerifItal,
    SerifBold,
    SerifBoldItal,
    SansSerif,
    SansSerifItal,
    SansSerifBold,
    SansSerifBoldItal,
    Monospace,
    ScriptBold,
    FrakturBold,
    FullWidth,
};
```

<p id="opacity">

```cpp
enum class Opacity {
    OP_100,
    OP_75,
    OP_50,
    OP_25,
};
```

<p id="point">

```cpp
enum class Point : wchar_t {
    Dot           = 0x2022,
    Triangle      = 0x25B2,
    SmallTriangle = 0x25B4,
    Rhombus       = 0x25C6,
    SmallSquare   = 0x25FE,
    Star          = 0x2605,
    Clover        = 0x2618,
    Scythe        = 0x262D,
    YinYang       = 0x262F,
    Smile         = 0x263B,
    SpadeSuit     = 0x2660,
    ClubSuit      = 0x2663,
    HeartSuit     = 0x2665,
    DiamondSuit   = 0x2666,
    Flag          = 0x2691,
    Flower        = 0x2698,
    Zeus          = 0x26A1,
    CheckMarkItal = 0x2714,
    CrossX        = 0x2716,
    CrossXItal    = 0x2718,
    Cross         = 0x271A,
    StarInCircle  = 0x272A,
    Asterisk      = 0x2731,
    BigCrossX     = 0x274C,
    Heart         = 0x2764,
    Square        = 0x2B1B,
    Pentagon      = 0x2B1F,
    Hexagon       = 0x2B22,
    Circle        = 0x2B24,
    SmallRhombus  = 0x2B25,
    Beaver        = 0xF800,
};
```

--------------------------------------------------------
<style>
    .func {
        font-family:    monospace;
        font-size:      16px;
        padding:        8px 13px;
        color:          white;
        background:     steelblue;
        /* background:     #3465a4; */
    } 
    .keyw {
        font-weight:    bold;
        color:          #fce94f;
    } 
    .mark {
        color:          #34e2e2;
    } 
    .term {
        color:          violet;
    } 
</style>
