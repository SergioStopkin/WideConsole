#include "wideconsole/graph.h"

#include <cmath>
#include <gtest/gtest.h>

using namespace WideConsole;

TEST(TestBuff, TestBuffer)
{
    Graph graph;
    graph.size().setSize(33, 17);
    graph.range().setHorizontalRange(-1.5, 1.5);
    graph.range().setVerticalRange(-1.5, 1.5);
    graph.header().setDataPosition(DataPosition::Left);

    // Sinus
    std::vector<std::pair<double, double>> sin2;
    std::vector<std::pair<double, double>> sin3;

    double x = -1.5;
    for (size_t i = 0; i < 300; ++i) {
        const double y2 = std::sin(4.0 * x);
        const double y3 = std::sin(8.0 * x);

        if (!std::isnan(y2)) {
            sin2.emplace_back(x, y2);
        }
        if (!std::isnan(y3)) {
            sin3.emplace_back(x, y3);
        }

        x += 0.01;
    }

    // WideConsole::Console::clear();

    graph.setPointColor(WideConsole::Color::BrightGreen);
    // graph.printObject(sin2);
    graph.setPointColor(WideConsole::Color::BrightRed);
    // graph.printObject(sin3);
    // graph.printBuff();
}
