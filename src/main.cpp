// Copyright © 2019 Sergio Stopkin.

/*
 * This file is part of WideConsole. WideConsole is free software:
 * you can redistribute it and/or modify it under the terms of the
 * GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later version.
 *
 * WideConsole is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with WideConsole. See the file COPYING. If not, see <https://www.gnu.org/licenses/>.
 */

#include "wideconsole/chart.h"
#include "wideconsole/graph.h"
#include "wideconsole/text.h"

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
    WideConsole::Graph graph;
    graph.size().setSize(33, 17);
    graph.range().setHorizontalRange(-1.5, 1.5);
    graph.range().setVerticalRange(-1.5, 1.5);
    graph.header().setDataPosition(WideConsole::DataPosition::Left);

    // Colors
    const std::vector<WideConsole::Color> colors { WideConsole::Color::Green,   WideConsole::Color::BrightGreen,
                                                   WideConsole::Color::Yellow,  WideConsole::Color::BrightYellow,
                                                   WideConsole::Color::Red,     WideConsole::Color::BrightRed,
                                                   WideConsole::Color::Magenta, WideConsole::Color::BrightMagenta };
    // CHART
    const int max = 100;

    WideConsole::Chart chart;
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

            WideConsole::Console::clear();

            graph.setPointColor(WideConsole::Color::BrightBlue);
            graph.printObject(sin1);

            graph.setPointColor(WideConsole::Color::BrightGreen);
            graph.printObject(sin2);

            graph.setPointColor(WideConsole::Color::BrightRed);
            graph.printObject(sin3);

            // Data for charts
            std::vector<int> data;
            for (size_t i = 0; i < colors.size(); ++i) {
                data.emplace_back((10 * i + 5 * count) % max);
            }

            // Column chart
            chart.setChartType(WideConsole::ChartType::Column);
            chart.size().setSize(40, 16);
            chart.printObject(data);

            // Bar chart
            chart.setChartType(WideConsole::ChartType::Bar);
            chart.size().setSize(40, 16);
            chart.printObject(data);

            // Pie chart
            chart.setChartType(WideConsole::ChartType::Pie);
            chart.size().setSize(35, 17);
            chart.printObject(data);

            ++count;
            l_start = std::chrono::steady_clock::now();
        }
    }

    // TEXT
    WideConsole::Text text;
    WideConsole::Console::newLine();
    // clang-format off
    text.consoleView().setColor(WideConsole::Color::Black);         text.printObject("Black");         WideConsole::Console::newLine();
    text.consoleView().setColor(WideConsole::Color::Default);       text.printObject("Default");       WideConsole::Console::newLine();
    text.consoleView().setColor(WideConsole::Color::BrightBlack);   text.printObject("BrightBlack");   WideConsole::Console::newLine();
    text.consoleView().setColor(WideConsole::Color::BrightDefault); text.printObject("BrightDefault"); WideConsole::Console::newLine();
    text.consoleView().setColor(WideConsole::Color::White);         text.printObject("White");         WideConsole::Console::newLine();
    text.consoleView().setColor(WideConsole::Color::BrightWhite);   text.printObject("BrightWhite");   WideConsole::Console::newLine();
    text.consoleView().setColor(WideConsole::Color::Red);           text.printObject("Red");           WideConsole::Console::newLine();
    text.consoleView().setColor(WideConsole::Color::BrightRed);     text.printObject("BrightRed");     WideConsole::Console::newLine();
    text.consoleView().setColor(WideConsole::Color::Blue);          text.printObject("Blue");          WideConsole::Console::newLine();
    text.consoleView().setColor(WideConsole::Color::BrightBlue);    text.printObject("BrightBlue");    WideConsole::Console::newLine();
    text.consoleView().setColor(WideConsole::Color::Cyan);          text.printObject("Cyan");          WideConsole::Console::newLine();
    text.consoleView().setColor(WideConsole::Color::BrightCyan);    text.printObject("BrightCyan");    WideConsole::Console::newLine();
    text.consoleView().setColor(WideConsole::Color::Magenta);       text.printObject("Magenta");       WideConsole::Console::newLine();
    text.consoleView().setColor(WideConsole::Color::BrightMagenta); text.printObject("BrightMagenta"); WideConsole::Console::newLine();
    text.consoleView().setColor(WideConsole::Color::Yellow);        text.printObject("Yellow");        WideConsole::Console::newLine();
    text.consoleView().setColor(WideConsole::Color::BrightYellow);  text.printObject("BrightYellow");  WideConsole::Console::newLine();
    text.consoleView().setColor(WideConsole::Color::Green);         text.printObject("Green");         WideConsole::Console::newLine();
    text.consoleView().setColor(WideConsole::Color::BrightGreen);   text.printObject("BrightGreen");   WideConsole::Console::newLine();
    // clang-format on

    const std::string str = "ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz 0123456789";

    text.consoleView().setColor(WideConsole::Color::Yellow);
    text.consoleView().setInverseColor(true);
    // clang-format off
    text.setFont(WideConsole::Font::Monospace);         text.printObject(str); WideConsole::Console::newLine();
    text.setFont(WideConsole::Font::SerifItal);         text.printObject(str); WideConsole::Console::newLine();
    text.setFont(WideConsole::Font::SerifBold);         text.printObject(str); WideConsole::Console::newLine();
    text.setFont(WideConsole::Font::SerifBoldItal);     text.printObject(str); WideConsole::Console::newLine();
    text.setFont(WideConsole::Font::SansSerif);         text.printObject(str); WideConsole::Console::newLine();
    text.setFont(WideConsole::Font::SansSerifItal);     text.printObject(str); WideConsole::Console::newLine();
    text.setFont(WideConsole::Font::SansSerifBold);     text.printObject(str); WideConsole::Console::newLine();
    text.setFont(WideConsole::Font::SansSerifBoldItal); text.printObject(str); WideConsole::Console::newLine();
    text.setFont(WideConsole::Font::ScriptBold);        text.printObject(str); WideConsole::Console::newLine();
    text.setFont(WideConsole::Font::FrakturBold);       text.printObject(str); WideConsole::Console::newLine();
    text.setFont(WideConsole::Font::FullWidth);         text.printObject(str); WideConsole::Console::newLine();
    // clang-format on
    text.reset();
    text.printObject("");

    return 0;
}
