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
    graph.SetSize(33, 17);
    graph.SetHorizontalRange(-1.5, 1.5);
    graph.SetVerticalRange(-1.5, 1.5);
    graph.SetDataPosition(WConsole::DataPosition::Left);

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
    chart.SetChartColors(colors);
    chart.SetHorizontalRange(0, max);
    chart.SetVerticalRange(0, max);
    chart.ShowDataHeader(false);
    chart.ShowGrid(false);

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

            WConsole::Console::Clear();

            graph.SetPointColor(WConsole::Color::BrightBlue);
            graph.PrintObject(sin1);

            graph.SetPointColor(WConsole::Color::BrightGreen);
            graph.PrintObject(sin2);

            graph.SetPointColor(WConsole::Color::BrightRed);
            graph.PrintObject(sin3);

            // Data for charts
            std::vector<int> data;
            for (size_t i = 0; i < colors.size(); ++i) {
                data.emplace_back((10 * i + 5 * count) % max);
            }

            // Column chart
            chart.SetChartType(WConsole::ChartType::Column);
            chart.SetSize(40, 16);
            chart.PrintObject(data);

            // Bar chart
            chart.SetChartType(WConsole::ChartType::Bar);
            chart.SetSize(40, 16);
            chart.PrintObject(data);

            // Pie chart
            chart.SetChartType(WConsole::ChartType::Pie);
            chart.SetSize(35, 17);
            chart.PrintObject(data);

            ++count;
            l_start = std::chrono::steady_clock::now();
        }
    }

    // TEXT
    WConsole::Text text;
    WConsole::Console::NewLine();
    text.SetColor(WConsole::Color::Black);         text.PrintObject("Black");         WConsole::Console::NewLine();
    text.SetColor(WConsole::Color::Default);       text.PrintObject("Default");       WConsole::Console::NewLine();
    text.SetColor(WConsole::Color::BrightBlack);   text.PrintObject("BrightBlack");   WConsole::Console::NewLine();
    text.SetColor(WConsole::Color::BrightDefault); text.PrintObject("BrightDefault"); WConsole::Console::NewLine();
    text.SetColor(WConsole::Color::White);         text.PrintObject("White");         WConsole::Console::NewLine();
    text.SetColor(WConsole::Color::BrightWhite);   text.PrintObject("BrightWhite");   WConsole::Console::NewLine();
    text.SetColor(WConsole::Color::Red);           text.PrintObject("Red");           WConsole::Console::NewLine();
    text.SetColor(WConsole::Color::BrightRed);     text.PrintObject("BrightRed");     WConsole::Console::NewLine();
    text.SetColor(WConsole::Color::Blue);          text.PrintObject("Blue");          WConsole::Console::NewLine();
    text.SetColor(WConsole::Color::BrightBlue);    text.PrintObject("BrightBlue");    WConsole::Console::NewLine();
    text.SetColor(WConsole::Color::Cyan);          text.PrintObject("Cyan");          WConsole::Console::NewLine();
    text.SetColor(WConsole::Color::BrightCyan);    text.PrintObject("BrightCyan");    WConsole::Console::NewLine();
    text.SetColor(WConsole::Color::Magenta);       text.PrintObject("Magenta");       WConsole::Console::NewLine();
    text.SetColor(WConsole::Color::BrightMagenta); text.PrintObject("BrightMagenta"); WConsole::Console::NewLine();
    text.SetColor(WConsole::Color::Yellow);        text.PrintObject("Yellow");        WConsole::Console::NewLine();
    text.SetColor(WConsole::Color::BrightYellow);  text.PrintObject("BrightYellow");  WConsole::Console::NewLine();
    text.SetColor(WConsole::Color::Green);         text.PrintObject("Green");         WConsole::Console::NewLine();
    text.SetColor(WConsole::Color::BrightGreen);   text.PrintObject("BrightGreen");   WConsole::Console::NewLine();
    text.SetColor(WConsole::Color::Default);

    std::string str = "ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz 0123456789";
    WConsole::Font font;

    font.SetForegroundColor(WConsole::Color::Yellow);
    font.SetInverseColor(true);
    font.SetFontType(WConsole::FontType::Monospace);         text.PrintObject(str, font); WConsole::Console::NewLine();
    font.SetFontType(WConsole::FontType::SerifItal);         text.PrintObject(str, font); WConsole::Console::NewLine();
    font.SetFontType(WConsole::FontType::SerifBold);         text.PrintObject(str, font); WConsole::Console::NewLine();
    font.SetFontType(WConsole::FontType::SerifBoldItal);     text.PrintObject(str, font); WConsole::Console::NewLine();
    font.SetFontType(WConsole::FontType::SansSerif);         text.PrintObject(str, font); WConsole::Console::NewLine();
    font.SetFontType(WConsole::FontType::SansSerifItal);     text.PrintObject(str, font); WConsole::Console::NewLine();
    font.SetFontType(WConsole::FontType::SansSerifBold);     text.PrintObject(str, font); WConsole::Console::NewLine();
    font.SetFontType(WConsole::FontType::SansSerifBoldItal); text.PrintObject(str, font); WConsole::Console::NewLine();
    font.SetFontType(WConsole::FontType::ScriptBold);        text.PrintObject(str, font); WConsole::Console::NewLine();
    font.SetFontType(WConsole::FontType::FrakturBold);       text.PrintObject(str, font); WConsole::Console::NewLine();
    font.SetFontType(WConsole::FontType::FullWidth);         text.PrintObject(str, font); WConsole::Console::NewLine();
    text.ResetFont();
    text.PrintObject("");
    return 0;
}
