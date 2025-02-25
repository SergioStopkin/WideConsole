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

#pragma once

#include "wideconsole/interface/igraph.h"
#include "wideconsole/tool/intsize.h"
#include "wideconsole/type/datatype.h"
#include "wideconsole/unit/grid.h"
#include "wideconsole/unit/header.h"
#include "wideconsole/unit/object.h"
#include "wideconsole/unit/precision2d.h"
#include "wideconsole/unit/range.h"
#include "wideconsole/unit/size.h"

#include <string>
#include <utility>
#include <vector>

namespace WideConsole {

class Graph final : public IGraph, public Object {
public:
    IGrid &        grid() noexcept override { return m_grid; }
    IHeader &      header() noexcept override { return m_header; }
    IPrecision2D & precision() noexcept override { return m_precision; }
    IRange &       range() noexcept override { return m_range; }
    ISize &        size() noexcept override { return m_size; }
    ISize &        frame() noexcept override { return m_frame; }

    void setPoint(const Point point) noexcept override { m_point = wchar(point); }
    void setPointColor(const Color color) noexcept override { m_point_color = color; }

    template <DataType T>
    void printObject(const std::vector<std::pair<T, T>> & data)
    {
        // Pre-processing
        Console::preProcessing(m_size.horizontal(), m_header.size());

        const double h_step = (m_range.horizontalMax() - m_range.horizontalMin())
                            / static_cast<double>(m_size.horizontal() - 1);
        const double v_step = (m_range.verticalMax() - m_range.verticalMin()) / static_cast<double>(m_size.vertical() - 1);
        const auto   v_alignment = std::max(intSize(m_range.verticalMin()), intSize(m_range.verticalMax()))
                               + ((m_precision.verticalPrecision() > 0) ? (m_precision.verticalPrecision() + 1) : 0);
        const bool is_data_empty = (data.begin() == data.end());
        const uint h_zero        = m_size.horizontal() / 2;
        const uint v_zero        = m_size.vertical() / 2;

        std::vector<std::pair<uint, uint>> sort_data;

        if (!is_data_empty) {
            for (const auto & pair : data) {
                if ((pair.first > (m_range.horizontalMax() + h_step)) || (pair.first < (m_range.horizontalMin() - h_step))
                    || (pair.second > (m_range.verticalMax() + v_step))
                    || (pair.second < (m_range.verticalMin() - v_step))) {
                    continue;
                }

                const auto h = (pair.first - m_range.horizontalMin()) / h_step + 0.5;
                const auto v = (pair.second - m_range.verticalMin()) / v_step + 0.5;

                /// todo: optimize
                bool duplicate = false;
                for (const auto & s_pair : sort_data) {
                    if (s_pair.first == h && s_pair.second == v) {
                        duplicate = true;
                        break;
                    }
                }

                if (!duplicate) {
                    sort_data.emplace_back(h, v);
                }
            }

            // Sort data vector by second value in pair
            std::sort(sort_data.begin(), sort_data.end(), [](const auto & left, const auto & right) {
                return (left.second > right.second || (left.second == right.second && left.first < right.first));
            });
        }

        // Const data iterator
        auto data_iterator = sort_data.cbegin();

        std::wstring buff;
        buff.reserve(m_size.vertical() * m_size.horizontal() * 8); // magic eight (hateful :)

        if (Console::globalVPos() > 0) {
            Console::writePositionToBuff(&buff, Position::Up, Console::globalVPos());
        }

        if (Console::globalHPos() > 0) {
            //            h_global_pos_ = h_pos_;
        }

        // Upper arrow
        if (m_grid.isArrow()) {
            Console::writeColorToBuff(&buff, m_grid.axisColor());

            if (Console::globalHPos() > 0) {
                Console::writePositionToBuff(&buff, Position::Right, Console::globalHPos());
            }

            if (m_header.isDataHeader()) {
                buff.append(v_alignment, ' ');
            }

            for (uint hi = 0; hi < m_size.horizontal(); ++hi) {
                if (hi == h_zero) {
                    buff += wchar(m_grid.arrow() == Arrow::Big ? GridCode::BigUArrow_ : GridCode::SmallUArrow_);
                } else {
                    buff += L' ';
                }
            }

            buff += L'\n';
        }

        // Vertical loop
        for (uint vi = m_size.vertical() - 1; static_cast<int>(vi) >= 0; --vi) {
            const double vs = vi * v_step + m_range.verticalMin();

            if (Console::globalHPos() > 0) {
                Console::writePositionToBuff(&buff, Position::Right, Console::globalHPos());
            }

            // Vertical data header
            if (m_header.isDataHeader()) {
                Console::writeColorToBuff(&buff, Color::Default);

                if (vi == v_zero) {
                    m_header.writeDataToBuff(&buff, 0.0, v_alignment, m_precision.verticalPrecision());
                } else {
                    m_header.writeDataToBuff(&buff, vs, v_alignment, m_precision.verticalPrecision());
                }
            }

            // Horizontal loop
            for (uint hi = 0; hi < m_size.horizontal(); ++hi) {
                if (data_iterator != sort_data.end() && vi == data_iterator->second && hi == data_iterator->first) {
                    Console::writeColorToBuff(&buff, m_point_color);
                    buff += m_point;

                    while (data_iterator != sort_data.end() && hi == data_iterator->first
                           && vi == data_iterator->second) {
                        ++data_iterator;
                    }
                } else if (hi == h_zero) {
                    Console::writeColorToBuff(&buff, m_grid.axisColor());

                    if (vi == v_zero) {
                        buff += wchar(GridCode::Cross_);
                    } else {
                        buff += wchar(GridCode::VLine_);
                    }
                } else {
                    if (vi == v_zero) {
                        Console::writeColorToBuff(&buff, m_grid.axisColor());
                        buff += wchar(GridCode::HLine_);
                    } else {
                        if (m_grid.isGrid()) {
                            Console::writeColorToBuff(&buff, m_grid.gridColor());
                        }
                        buff += m_grid.grid();
                    }
                }
            }

            // Right arrow
            if (vi == v_zero && m_grid.isArrow()) {
                Console::writeColorToBuff(&buff, m_grid.axisColor());
                buff += wchar(m_grid.arrow() == Arrow::Big ? GridCode::BigRArrow_ : GridCode::SmallRArrow_);
            }

            buff += L'\n';
        }

        //        uint h_pos        = (m_size.horizontal() + ((m_header.isDataHeader()) ? v_alignment : 0) +
        //        ((m_grid.isArrow()) ? 1 : 0));
        uint h_pos_header = 0;

        // Horizontal data header
        if (m_header.isDataHeader()) {
            if (Console::globalHPos() > 0) {
                Console::writePositionToBuff(&buff, Position::Right, Console::globalHPos());
            }

            Console::writeColorToBuff(&buff, Color::Default);
            buff.append(v_alignment, ' ');
            h_pos_header += v_alignment;

            int count = 0;
            for (uint hi = 0; hi < m_size.horizontal(); ++hi) {
                const double hs = hi * h_step + m_range.horizontalMin();

                const uint h_alignment = std::to_string(std::abs(static_cast<int>(hs))).size() + ((hs < 0) ? 1 : 0)
                                       + ((m_precision.horizontalPrecision() > 0)
                                          ? (m_precision.horizontalPrecision() + 1)
                                          : 0)
                                       + 1; // for one space
                if (count % h_alignment == 0) {
                    m_header.writeDataToBuff(&buff, hs, h_alignment, m_precision.horizontalPrecision());
                    h_pos_header += h_alignment;
                    count = 0;
                }

                ++count;
            }
        }

        const uint h_pos_exp = m_size.horizontal() + (m_grid.isArrow() ? 1 : 0)
                             + (m_header.isDataHeader() ? v_alignment : 0);

        if (m_header.isDataHeader() && h_pos_header > h_pos_exp) {
            Console::globalHPos(Console::globalHPos() + h_pos_header);
        } else {
            Console::globalHPos(Console::globalHPos() + h_pos_exp);
        }

        Console::globalVPos(m_size.vertical() + ((m_grid.isArrow()) ? 1 : 0) + ((m_header.isDataHeader()) ? 1 : 0));

        Console::writeColorToBuff(&buff, Color::Default);
        buff += L'\n';
        Console::print(buff);
    }

    void printBuff()
    {
        // Pre-processing
        Console::preProcessing(m_size.horizontal(), m_header.size());

        const double h_step = (m_range.horizontalMax() - m_range.horizontalMin())
                            / static_cast<double>(m_size.horizontal() - 1);
        const double v_step = (m_range.verticalMax() - m_range.verticalMin()) / static_cast<double>(m_size.vertical() - 1);
        const auto   v_alignment = std::max(intSize(m_range.verticalMin()), intSize(m_range.verticalMax()))
                               + ((m_precision.verticalPrecision() > 0) ? (m_precision.verticalPrecision() + 1) : 0);
        const uint h_zero = m_size.horizontal() / 2;
        const uint v_zero = m_size.vertical() / 2;

        std::wstring buff;
        buff.reserve(m_size.vertical() * m_size.horizontal() * 8); // magic eight (hateful :)

        if (Console::globalVPos() > 0) {
            Console::writePositionToBuff(&buff, Position::Up, Console::globalVPos());
        }

        // Upper arrow
        if (m_grid.isArrow()) {
            Console::writeColorToBuff(&buff, m_grid.axisColor());

            if (Console::globalHPos() > 0) {
                Console::writePositionToBuff(&buff, Position::Right, Console::globalHPos());
            }

            if (m_header.isDataHeader()) {
                buff.append(v_alignment, ' ');
            }

            for (uint hi = 0; hi < m_size.horizontal(); ++hi) {
                if (hi == h_zero) {
                    buff += wchar(m_grid.arrow() == Arrow::Big ? GridCode::BigUArrow_ : GridCode::SmallUArrow_);
                } else {
                    buff += L' ';
                }
            }

            buff += L'\n';
        }

        // Vertical loop
        for (uint vi = m_size.vertical() - 1; static_cast<int>(vi) >= 0; --vi) {
            const double vs = vi * v_step + m_range.verticalMin();

            if (Console::globalHPos() > 0) {
                Console::writePositionToBuff(&buff, Position::Right, Console::globalHPos());
            }

            // Vertical data header
            if (m_header.isDataHeader()) {
                Console::writeColorToBuff(&buff, Color::Default);

                if (vi == v_zero) {
                    m_header.writeDataToBuff(&buff, 0.0, v_alignment, m_precision.verticalPrecision());
                } else {
                    m_header.writeDataToBuff(&buff, vs, v_alignment, m_precision.verticalPrecision());
                }
            }

            // Horizontal loop
            for (uint hi = 0; hi < m_size.horizontal(); ++hi) {
                if (hi == h_zero) {
                    Console::writeColorToBuff(&buff, m_grid.axisColor());

                    if (vi == v_zero) {
                        buff += wchar(GridCode::Cross_);
                    } else {
                        buff += wchar(GridCode::VLine_);
                    }
                } else {
                    if (vi == v_zero) {
                        Console::writeColorToBuff(&buff, m_grid.axisColor());
                        buff += wchar(GridCode::HLine_);
                    } else {
                        if (m_grid.isGrid()) {
                            Console::writeColorToBuff(&buff, m_grid.gridColor());
                        }
                        buff += m_grid.grid();
                    }
                }
            }

            // Right arrow
            if (vi == v_zero && m_grid.isArrow()) {
                Console::writeColorToBuff(&buff, m_grid.axisColor());
                buff += wchar(m_grid.arrow() == Arrow::Big ? GridCode::BigRArrow_ : GridCode::SmallRArrow_);
            }

            buff += L'\n';
        }

        //        uint h_pos        = (m_size.horizontal() + ((m_header.isDataHeader()) ? v_alignment : 0) +
        //        ((_grid.isArrow()) ? 1 : 0));
        uint h_pos_header = 0;

        // Horizontal data header
        if (m_header.isDataHeader()) {
            if (Console::globalHPos() > 0) {
                Console::writePositionToBuff(&buff, Position::Right, Console::globalHPos());
            }

            Console::writeColorToBuff(&buff, Color::Default);
            buff.append(v_alignment, ' ');
            h_pos_header += v_alignment;

            int count = 0;
            for (uint hi = 0; hi < m_size.horizontal(); ++hi) {
                const double hs = hi * h_step + m_range.horizontalMin();

                const uint h_alignment = std::to_string(std::abs(static_cast<int>(hs))).size() + ((hs < 0) ? 1 : 0)
                                       + ((m_precision.horizontalPrecision() > 0)
                                          ? (m_precision.horizontalPrecision() + 1)
                                          : 0)
                                       + 1; // for one space
                if (count % h_alignment == 0) {
                    m_header.writeDataToBuff(&buff, hs, h_alignment, m_precision.horizontalPrecision());
                    h_pos_header += h_alignment;
                    count = 0;
                }

                ++count;
            }
        }

        const uint h_pos_exp = m_size.horizontal() + (m_grid.isArrow() ? 1 : 0)
                             + (m_header.isDataHeader() ? v_alignment : 0);

        if (m_header.isDataHeader() && h_pos_header > h_pos_exp) {
            Console::globalHPos(Console::globalHPos() + h_pos_header);
        } else {
            Console::globalHPos(Console::globalHPos() + h_pos_exp);
        }

        Console::globalVPos(m_size.vertical() + ((m_grid.isArrow()) ? 1 : 0) + ((m_header.isDataHeader()) ? 1 : 0));

        Console::writeColorToBuff(&buff, Color::Default);
        buff += L'\n';
        Console::print(buff);
    }

private:
    Grid        m_grid {};
    Header      m_header {};
    Precision2D m_precision {};
    Range       m_range {};
    Size        m_size {};
    Size        m_frame {};

    wchar_t m_point { wchar(Point::Dot) };
    Color   m_point_color { Color::BrightRed };
};

} // namespace WideConsole
