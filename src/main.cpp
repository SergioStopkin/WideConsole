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

#include "wconsole/chart.h"
#include "wconsole/graph.h"
#include "wconsole/text.h"

#include <chrono>

int main()
{
    // Global timer
    auto g_start    = std::chrono::steady_clock::now();
    auto g_duration = std::chrono::milliseconds(2600);

    // Local timer
    auto l_start    = std::chrono::steady_clock::now();
    auto l_duration = std::chrono::milliseconds(100);

    // GRAPH
    WConsole::Graph graph;
    graph.setSize(33, 17);
    graph.range().setHorizontalRange(-1.5, 1.5);
    graph.range().setVerticalRange(-1.5, 1.5);
    graph.header().setDataPosition(WConsole::DataPosition::Left);

    // Colors
    std::vector<WConsole::Color> colors { WConsole::Color::Green,        WConsole::Color::BrightGreen,  WConsole::Color::Yellow,
                                          WConsole::Color::BrightYellow, WConsole::Color::Red,          WConsole::Color::BrightRed,
                                          WConsole::Color::Magenta,      WConsole::Color::BrightMagenta };
    // CHART
    const int max = 100;

    WConsole::Chart chart;
    chart.setChartColors(colors);
    chart.range().setHorizontalRange(0, max);
    chart.range().setVerticalRange(0, max);
    // chart.header().showDataHeader(false);
    // chart.grid().showGrid(false);

    int count = 1;
    while (std::chrono::steady_clock::now() < g_start + g_duration) {
        if (std::chrono::steady_clock::now() > l_start + l_duration) {
            // Sinus
            std::vector<std::pair<double, double>> sin1;
            std::vector<std::pair<double, double>> sin2;
            std::vector<std::pair<double, double>> sin3;

            double x = -1.5;
            for (size_t i = 0; i < 300; ++i) {
                const double y1 = std::sin(2.0 * x + count);
                const double y2 = std::sin(4.0 * x + count);
                const double y3 = std::sin(8.0 * x + count);

                if (!std::isnan(y1)) {
                    sin1.emplace_back(x, y1);
                }
                if (!std::isnan(y2)) {
                    sin2.emplace_back(x, y2);
                }
                if (!std::isnan(y3)) {
                    sin3.emplace_back(x, y3);
                }

                x += 0.01;
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
    // clang-format off
    text.consoleView().setColor(WConsole::Color::Black);         text.printObject("Black");         WConsole::Console::newLine();
    text.consoleView().setColor(WConsole::Color::Default);       text.printObject("Default");       WConsole::Console::newLine();
    text.consoleView().setColor(WConsole::Color::BrightBlack);   text.printObject("BrightBlack");   WConsole::Console::newLine();
    text.consoleView().setColor(WConsole::Color::BrightDefault); text.printObject("BrightDefault"); WConsole::Console::newLine();
    text.consoleView().setColor(WConsole::Color::White);         text.printObject("White");         WConsole::Console::newLine();
    text.consoleView().setColor(WConsole::Color::BrightWhite);   text.printObject("BrightWhite");   WConsole::Console::newLine();
    text.consoleView().setColor(WConsole::Color::Red);           text.printObject("Red");           WConsole::Console::newLine();
    text.consoleView().setColor(WConsole::Color::BrightRed);     text.printObject("BrightRed");     WConsole::Console::newLine();
    text.consoleView().setColor(WConsole::Color::Blue);          text.printObject("Blue");          WConsole::Console::newLine();
    text.consoleView().setColor(WConsole::Color::BrightBlue);    text.printObject("BrightBlue");    WConsole::Console::newLine();
    text.consoleView().setColor(WConsole::Color::Cyan);          text.printObject("Cyan");          WConsole::Console::newLine();
    text.consoleView().setColor(WConsole::Color::BrightCyan);    text.printObject("BrightCyan");    WConsole::Console::newLine();
    text.consoleView().setColor(WConsole::Color::Magenta);       text.printObject("Magenta");       WConsole::Console::newLine();
    text.consoleView().setColor(WConsole::Color::BrightMagenta); text.printObject("BrightMagenta"); WConsole::Console::newLine();
    text.consoleView().setColor(WConsole::Color::Yellow);        text.printObject("Yellow");        WConsole::Console::newLine();
    text.consoleView().setColor(WConsole::Color::BrightYellow);  text.printObject("BrightYellow");  WConsole::Console::newLine();
    text.consoleView().setColor(WConsole::Color::Green);         text.printObject("Green");         WConsole::Console::newLine();
    text.consoleView().setColor(WConsole::Color::BrightGreen);   text.printObject("BrightGreen");   WConsole::Console::newLine();
    // clang-format on

    const std::string str = "ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz 0123456789";

    text.consoleView().setColor(WConsole::Color::Yellow);
    text.consoleView().setInverseColor(true);
    // clang-format off
    text.setFont(WConsole::Font::Monospace);         text.printObject(str); WConsole::Console::newLine();
    text.setFont(WConsole::Font::SerifItal);         text.printObject(str); WConsole::Console::newLine();
    text.setFont(WConsole::Font::SerifBold);         text.printObject(str); WConsole::Console::newLine();
    text.setFont(WConsole::Font::SerifBoldItal);     text.printObject(str); WConsole::Console::newLine();
    text.setFont(WConsole::Font::SansSerif);         text.printObject(str); WConsole::Console::newLine();
    text.setFont(WConsole::Font::SansSerifItal);     text.printObject(str); WConsole::Console::newLine();
    text.setFont(WConsole::Font::SansSerifBold);     text.printObject(str); WConsole::Console::newLine();
    text.setFont(WConsole::Font::SansSerifBoldItal); text.printObject(str); WConsole::Console::newLine();
    text.setFont(WConsole::Font::ScriptBold);        text.printObject(str); WConsole::Console::newLine();
    text.setFont(WConsole::Font::FrakturBold);       text.printObject(str); WConsole::Console::newLine();
    text.setFont(WConsole::Font::FullWidth);         text.printObject(str); WConsole::Console::newLine();
    // clang-format on
    text.reset();
    text.printObject("");

    return 0;
}
