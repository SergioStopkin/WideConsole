// Copyright © 2019 Sergio Stopkin.

/*
 * This file is part of WConsole. WConsole is free software:
 * you can redistribute it and/or modify it under the terms of the
 * GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later version.
 * 
 * WConsole is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with WConsole. See the file COPYING. If not, see <https://www.gnu.org/licenses/>.
 */

#include <chrono>

#include "wconsole/chart.h"
#include "wconsole/graph.h"
#include "wconsole/text.h"

int main() {
    // Global timer
    auto g_start    = std::chrono::steady_clock::now();
    auto g_duration = std::chrono::milliseconds(2600);

    // Local timer
    auto l_start    = std::chrono::steady_clock::now();
    auto l_duration = std::chrono::milliseconds(100);

    // GRAPH
    WConsole::Graph graph;
    graph.setSize(33, 17);
    graph.setHorizontalRange(-1.5, 1.5);
    graph.setVerticalRange(-1.5, 1.5);
    graph.setDataPosition(WConsole::DataPosition::Left);

    // Colors
    std::vector<WConsole::Color> colors { WConsole::Color::Green,
                                          WConsole::Color::BrightGreen,
                                          WConsole::Color::Yellow,
                                          WConsole::Color::BrightYellow,
                                          WConsole::Color::Red,
                                          WConsole::Color::BrightRed,
                                          WConsole::Color::Magenta,
                                          WConsole::Color::BrightMagenta };
    // CHART
    const int max = 100;

    WConsole::Chart chart;
    chart.setChartColors(colors);
    chart.setHorizontalRange(0, max);
    chart.setVerticalRange(0, max);
    // chart.showDataHeader(false);
    // chart.showGrid(false);

    int count = 1;
    while (std::chrono::steady_clock::now() < g_start + g_duration) {
        if (std::chrono::steady_clock::now() > l_start + l_duration) {
            // Sinus
            std::vector<std::pair<double, double>> sin1;
            std::vector<std::pair<double, double>> sin2;
            std::vector<std::pair<double, double>> sin3;

            for (double x = -1.5; x <= 1.5; x += 0.01) {
                const double y1 = std::sin(2.0 * x + count);
                const double y2 = std::sin(4.0 * x + count);
                const double y3 = std::sin(8.0 * x + count);

                if (!std::isnan(y1)) sin1.emplace_back(x, y1);
                if (!std::isnan(y2)) sin2.emplace_back(x, y2);
                if (!std::isnan(y3)) sin3.emplace_back(x, y3);
            }

            WConsole::Console::clear();

            graph.setPointColor(WConsole::Color::BrightBlue);
            graph.printObject(sin1);

            graph.setPointColor(WConsole::Color::BrightGreen);
            graph.printObject(sin2);

            graph.setPointColor(WConsole::Color::BrightRed);
            graph.printObject(sin3);

            // Data for charts
            std::vector<int> data;
            for (size_t i = 0; i < colors.size(); ++i) {
                data.emplace_back((10 * i + 5 * count) % max);
            }

            // Column chart
            chart.setChartType(WConsole::ChartType::Column);
            chart.setSize(40, 16);
            chart.printObject(data);

            // Bar chart
            chart.setChartType(WConsole::ChartType::Bar);
            chart.setSize(40, 16);
            chart.printObject(data);

            // Pie chart
            chart.setChartType(WConsole::ChartType::Pie);
            chart.setSize(35, 17);
            chart.printObject(data);

            ++count;
            l_start = std::chrono::steady_clock::now();
        }
    }

    // TEXT
    WConsole::Text text;
    WConsole::Console::newLine();
    text.setColor(WConsole::Color::Black);         text.printObject("Black");         WConsole::Console::newLine();
    text.setColor(WConsole::Color::Default);       text.printObject("Default");       WConsole::Console::newLine();
    text.setColor(WConsole::Color::BrightBlack);   text.printObject("BrightBlack");   WConsole::Console::newLine();
    text.setColor(WConsole::Color::BrightDefault); text.printObject("BrightDefault"); WConsole::Console::newLine();
    text.setColor(WConsole::Color::White);         text.printObject("White");         WConsole::Console::newLine();
    text.setColor(WConsole::Color::BrightWhite);   text.printObject("BrightWhite");   WConsole::Console::newLine();
    text.setColor(WConsole::Color::Red);           text.printObject("Red");           WConsole::Console::newLine();
    text.setColor(WConsole::Color::BrightRed);     text.printObject("BrightRed");     WConsole::Console::newLine();
    text.setColor(WConsole::Color::Blue);          text.printObject("Blue");          WConsole::Console::newLine();
    text.setColor(WConsole::Color::BrightBlue);    text.printObject("BrightBlue");    WConsole::Console::newLine();
    text.setColor(WConsole::Color::Cyan);          text.printObject("Cyan");          WConsole::Console::newLine();
    text.setColor(WConsole::Color::BrightCyan);    text.printObject("BrightCyan");    WConsole::Console::newLine();
    text.setColor(WConsole::Color::Magenta);       text.printObject("Magenta");       WConsole::Console::newLine();
    text.setColor(WConsole::Color::BrightMagenta); text.printObject("BrightMagenta"); WConsole::Console::newLine();
    text.setColor(WConsole::Color::Yellow);        text.printObject("Yellow");        WConsole::Console::newLine();
    text.setColor(WConsole::Color::BrightYellow);  text.printObject("BrightYellow");  WConsole::Console::newLine();
    text.setColor(WConsole::Color::Green);         text.printObject("Green");         WConsole::Console::newLine();
    text.setColor(WConsole::Color::BrightGreen);   text.printObject("BrightGreen");   WConsole::Console::newLine();
    text.setColor(WConsole::Color::Default);

    std::string str = "ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz 0123456789";
    WConsole::Font font;

    font.setForegroundColor(WConsole::Color::Yellow);
    font.setInverseColor(true);
    font.setFontType(WConsole::FontType::Monospace);         text.printObject(str, font); WConsole::Console::newLine();
    font.setFontType(WConsole::FontType::SerifItal);         text.printObject(str, font); WConsole::Console::newLine();
    font.setFontType(WConsole::FontType::SerifBold);         text.printObject(str, font); WConsole::Console::newLine();
    font.setFontType(WConsole::FontType::SerifBoldItal);     text.printObject(str, font); WConsole::Console::newLine();
    font.setFontType(WConsole::FontType::SansSerif);         text.printObject(str, font); WConsole::Console::newLine();
    font.setFontType(WConsole::FontType::SansSerifItal);     text.printObject(str, font); WConsole::Console::newLine();
    font.setFontType(WConsole::FontType::SansSerifBold);     text.printObject(str, font); WConsole::Console::newLine();
    font.setFontType(WConsole::FontType::SansSerifBoldItal); text.printObject(str, font); WConsole::Console::newLine();
    font.setFontType(WConsole::FontType::ScriptBold);        text.printObject(str, font); WConsole::Console::newLine();
    font.setFontType(WConsole::FontType::FrakturBold);       text.printObject(str, font); WConsole::Console::newLine();
    font.setFontType(WConsole::FontType::FullWidth);         text.printObject(str, font); WConsole::Console::newLine();
    text.resetFont();
    text.printObject("");

    return 0;
}
