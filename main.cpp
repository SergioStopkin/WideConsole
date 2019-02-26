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

            graph.Clear();
//            graph.ClearLast();
            graph.SetColor(WConsole::Color::BrightBlue);
            graph.PrintGraph(sin1);

            graph.SetColor(WConsole::Color::BrightGreen);
            graph.PrintGraph(sin2);

            graph.SetColor(WConsole::Color::BrightRed);
            graph.PrintGraph(sin3);

            // Data for charts
            std::vector<int> data;
            for (int i = 0; i < colors.size(); ++i) {
                data.emplace_back((10 * i + 5 * count) % max);
            }

            graph.NewLine();
            chart.SetPosition(graph);

            // Column chart
            chart.SetChartType(WConsole::ChartType::Column);
            chart.SetSize(5, 16);
            chart.PrintChart(data);

            // Bar chart
            chart.SetChartType(WConsole::ChartType::Bar);
            chart.SetSize(40, 2);
            chart.PrintChart(data);

            // Pie chart
            chart.SetChartType(WConsole::ChartType::Pie);
            chart.SetSize(35, 17);
            chart.PrintChart(data);

            ++count;
            l_start = std::chrono::steady_clock::now();
        }
    }

    return 0;

    // TEXT
    WConsole::Text text;
    text.SetColor(WConsole::Color::Black);         text.PrintText("Black");         text.NewLine();
    text.SetColor(WConsole::Color::Default);       text.PrintText("Default");       text.NewLine();
    text.SetColor(WConsole::Color::BrightBlack);   text.PrintText("BrightBlack");   text.NewLine();
    text.SetColor(WConsole::Color::BrightDefault); text.PrintText("BrightDefault"); text.NewLine();
    text.SetColor(WConsole::Color::White);         text.PrintText("White");         text.NewLine();
    text.SetColor(WConsole::Color::BrightWhite);   text.PrintText("BrightWhite");   text.NewLine();
    text.SetColor(WConsole::Color::Red);           text.PrintText("Red");           text.NewLine();
    text.SetColor(WConsole::Color::BrightRed);     text.PrintText("BrightRed");     text.NewLine();
    text.SetColor(WConsole::Color::Blue);          text.PrintText("Blue");          text.NewLine();
    text.SetColor(WConsole::Color::BrightBlue);    text.PrintText("BrightBlue");    text.NewLine();
    text.SetColor(WConsole::Color::Cyan);          text.PrintText("Cyan");          text.NewLine();
    text.SetColor(WConsole::Color::BrightCyan);    text.PrintText("BrightCyan");    text.NewLine();
    text.SetColor(WConsole::Color::Magenta);       text.PrintText("Magenta");       text.NewLine();
    text.SetColor(WConsole::Color::BrightMagenta); text.PrintText("BrightMagenta"); text.NewLine();
    text.SetColor(WConsole::Color::Yellow);        text.PrintText("Yellow");        text.NewLine();
    text.SetColor(WConsole::Color::BrightYellow);  text.PrintText("BrightYellow");  text.NewLine();
    text.SetColor(WConsole::Color::Green);         text.PrintText("Green");         text.NewLine();
    text.SetColor(WConsole::Color::BrightGreen);   text.PrintText("BrightGreen");   text.NewLine();
    text.SetColor(WConsole::Color::Default);

    /*std::string str = "ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz 0123456789";
    WConsole::Font font;

    font.SetForegroundColor(WConsole::Color::Yellow);
    font.SetInverseColor(true);

    font.SetFontType(WConsole::FontType::Monospace);         text.PrintText(str, font); text.NewLine();
    font.SetFontType(WConsole::FontType::SerifItal);         text.PrintText(str, font); text.NewLine();
    font.SetFontType(WConsole::FontType::SerifBold);         text.PrintText(str, font); text.NewLine();
    font.SetFontType(WConsole::FontType::SerifBoldItal);     text.PrintText(str, font); text.NewLine();
    font.SetFontType(WConsole::FontType::SansSerif);         text.PrintText(str, font); text.NewLine();
    font.SetFontType(WConsole::FontType::SansSerifItal);     text.PrintText(str, font); text.NewLine();
    font.SetFontType(WConsole::FontType::SansSerifBold);     text.PrintText(str, font); text.NewLine();
    font.SetFontType(WConsole::FontType::SansSerifBoldItal); text.PrintText(str, font); text.NewLine();
    font.SetFontType(WConsole::FontType::ScriptBold);        text.PrintText(str, font); text.NewLine();
    font.SetFontType(WConsole::FontType::FrakturBold);       text.PrintText(str, font); text.NewLine();
    font.SetFontType(WConsole::FontType::FullWidth);         text.PrintText(str, font); text.NewLine();*/

    return 0;
}
