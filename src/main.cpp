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

    for (int i = 1; i < 20; ++i) {
        graph.SetSize(2*i, i);
        graph.PrintBound(std::vector<std::pair<double, double>> {{0.0, 0.0}, {10, 10}, {-10, -10}});
    }

    return 0;


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

            graph.Clear();

            graph.SetPointColor(WConsole::Color::BrightBlue);
            graph.PrintBound(sin1);

            graph.SetPointColor(WConsole::Color::BrightGreen);
            graph.PrintBound(sin2);

            graph.SetPointColor(WConsole::Color::BrightRed);
            graph.PrintBound(sin3);

            // Data for charts
            std::vector<int> data;
            for (size_t i = 0; i < colors.size(); ++i) {
                data.emplace_back((10 * i + 5 * count) % max);
            }

            // Column chart
            chart.SetChartType(WConsole::ChartType::Column);
            chart.SetSize(40, 16);
            chart.PrintBound(data);

            // Bar chart
            chart.SetChartType(WConsole::ChartType::Bar);
            chart.SetSize(40, 16);
            chart.PrintBound(data);

            // Pie chart
            chart.SetChartType(WConsole::ChartType::Pie);
            chart.SetSize(35, 17);
            chart.PrintBound(data);

            ++count;
            l_start = std::chrono::steady_clock::now();
        }
    }

    // TEXT
    WConsole::Text text;
    text.NewLine();
    text.SetColor(WConsole::Color::Black);         text.PrintBound("Black");         text.NewLine();
    text.SetColor(WConsole::Color::Default);       text.PrintBound("Default");       text.NewLine();
    text.SetColor(WConsole::Color::BrightBlack);   text.PrintBound("BrightBlack");   text.NewLine();
    text.SetColor(WConsole::Color::BrightDefault); text.PrintBound("BrightDefault"); text.NewLine();
    text.SetColor(WConsole::Color::White);         text.PrintBound("White");         text.NewLine();
    text.SetColor(WConsole::Color::BrightWhite);   text.PrintBound("BrightWhite");   text.NewLine();
    text.SetColor(WConsole::Color::Red);           text.PrintBound("Red");           text.NewLine();
    text.SetColor(WConsole::Color::BrightRed);     text.PrintBound("BrightRed");     text.NewLine();
    text.SetColor(WConsole::Color::Blue);          text.PrintBound("Blue");          text.NewLine();
    text.SetColor(WConsole::Color::BrightBlue);    text.PrintBound("BrightBlue");    text.NewLine();
    text.SetColor(WConsole::Color::Cyan);          text.PrintBound("Cyan");          text.NewLine();
    text.SetColor(WConsole::Color::BrightCyan);    text.PrintBound("BrightCyan");    text.NewLine();
    text.SetColor(WConsole::Color::Magenta);       text.PrintBound("Magenta");       text.NewLine();
    text.SetColor(WConsole::Color::BrightMagenta); text.PrintBound("BrightMagenta"); text.NewLine();
    text.SetColor(WConsole::Color::Yellow);        text.PrintBound("Yellow");        text.NewLine();
    text.SetColor(WConsole::Color::BrightYellow);  text.PrintBound("BrightYellow");  text.NewLine();
    text.SetColor(WConsole::Color::Green);         text.PrintBound("Green");         text.NewLine();
    text.SetColor(WConsole::Color::BrightGreen);   text.PrintBound("BrightGreen");   text.NewLine();
    text.SetColor(WConsole::Color::Default);

    std::string str = "ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz 0123456789";
    WConsole::Font font;

    font.SetForegroundColor(WConsole::Color::Yellow);
    font.SetInverseColor(true);
    font.SetFontType(WConsole::FontType::Monospace);         text.PrintBound(str, font); text.NewLine();
    font.SetFontType(WConsole::FontType::SerifItal);         text.PrintBound(str, font); text.NewLine();
    font.SetFontType(WConsole::FontType::SerifBold);         text.PrintBound(str, font); text.NewLine();
    font.SetFontType(WConsole::FontType::SerifBoldItal);     text.PrintBound(str, font); text.NewLine();
    font.SetFontType(WConsole::FontType::SansSerif);         text.PrintBound(str, font); text.NewLine();
    font.SetFontType(WConsole::FontType::SansSerifItal);     text.PrintBound(str, font); text.NewLine();
    font.SetFontType(WConsole::FontType::SansSerifBold);     text.PrintBound(str, font); text.NewLine();
    font.SetFontType(WConsole::FontType::SansSerifBoldItal); text.PrintBound(str, font); text.NewLine();
    font.SetFontType(WConsole::FontType::ScriptBold);        text.PrintBound(str, font); text.NewLine();
    font.SetFontType(WConsole::FontType::FrakturBold);       text.PrintBound(str, font); text.NewLine();
    font.SetFontType(WConsole::FontType::FullWidth);         text.PrintBound(str, font); text.NewLine();
    text.ResetFont();
    text.PrintBound("");

    return 0;
}
