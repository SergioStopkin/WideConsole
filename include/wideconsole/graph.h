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
    IGrid &        grid() noexcept override { return _grid; }
    IHeader &      header() noexcept override { return _header; }
    IPrecision2D & precision() noexcept override { return _precision; }
    IRange &       range() noexcept override { return _range; }
    ISize &        size() noexcept override { return _size; }

    void setPoint(const Point point) noexcept override { point_ = wchar(point); }
    void setPointColor(const Color color) noexcept override { point_color_ = color; }

    template <typename T>
    void printObject(const std::vector<std::pair<T, T>> & data)
    {
        // Pre-processing
        Console::preProcessing(_size.horizontal(), _header.size());

        const double h_step      = (_range.horizontalMax() - _range.horizontalMin()) / static_cast<double>(_size.horizontal() - 1);
        const double v_step      = (_range.verticalMax() - _range.verticalMin()) / static_cast<double>(_size.vertical() - 1);
        const auto   v_alignment = static_cast<uint>(
            std::max(std::to_string(static_cast<int>(_range.verticalMin())).size(), std::to_string(static_cast<int>(_range.verticalMax())).size())
            + ((_precision.verticalPrecision() > 0) ? (_precision.verticalPrecision() + 1) : 0));
        const bool is_data_empty = (data.begin() == data.end());
        const uint h_zero        = _size.horizontal() / 2;
        const uint v_zero        = _size.vertical() / 2;

        std::vector<std::pair<uint, uint>> sort_data;

        if (!is_data_empty) {
            for (const auto & pair : data) {
                if (pair.first > (_range.horizontalMax() + h_step) || pair.first < (_range.horizontalMin() - h_step)
                    || pair.second > (_range.verticalMax() + v_step) || pair.second < (_range.verticalMin() - v_step)) {
                    continue;
                }

                const auto h = static_cast<uint>((pair.first - _range.horizontalMin()) / h_step + 0.5);
                const auto v = static_cast<uint>((pair.second - _range.verticalMin()) / v_step + 0.5);

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
        buff.reserve(_size.vertical() * _size.horizontal() * 8); // magic eight (hateful :)

        if (Console::globalVPos() > 0) {
            Console::writePositionToBuff(&buff, Position::Up, Console::globalVPos());
        }

        if (Console::globalHPos() > 0) {
            //            h_global_pos_ = h_pos_;
        }

        // Upper arrow
        if (_grid.isArrow()) {
            Console::writeColorToBuff(&buff, _grid.axisColor());

            if (Console::globalHPos() > 0) {
                Console::writePositionToBuff(&buff, Position::Right, Console::globalHPos());
            }

            if (_header.isDataHeader()) {
                buff.append(v_alignment, ' ');
            }

            for (uint hi = 0; hi < _size.horizontal(); ++hi) {
                if (hi == h_zero) {
                    buff += wchar(_grid.arrow() == Arrow::Big ? GridCode::BigUArrow_ : GridCode::SmallUArrow_);
                } else {
                    buff += L' ';
                }
            }

            buff += L'\n';
        }

        // Vertical loop
        for (uint vi = _size.vertical() - 1; static_cast<int>(vi) >= 0; --vi) {
            const double vs = vi * v_step + _range.verticalMin();

            if (Console::globalHPos() > 0) {
                Console::writePositionToBuff(&buff, Position::Right, Console::globalHPos());
            }

            // Vertical data header
            if (_header.isDataHeader()) {
                Console::writeColorToBuff(&buff, Color::Default);

                if (vi == v_zero) {
                    _header.writeDataToBuff(&buff, 0.0, v_alignment, _precision.verticalPrecision());
                } else {
                    _header.writeDataToBuff(&buff, vs, v_alignment, _precision.verticalPrecision());
                }
            }

            // Horizontal loop
            for (uint hi = 0; hi < _size.horizontal(); ++hi) {
                if (data_iterator != sort_data.end() && vi == data_iterator->second && hi == data_iterator->first) {
                    Console::writeColorToBuff(&buff, point_color_);
                    buff += point_;

                    while (data_iterator != sort_data.end() && hi == data_iterator->first && vi == data_iterator->second) {
                        ++data_iterator;
                    }
                } else if (hi == h_zero) {
                    Console::writeColorToBuff(&buff, _grid.axisColor());

                    if (vi == v_zero) {
                        buff += wchar(GridCode::Cross_);
                    } else {
                        buff += wchar(GridCode::VLine_);
                    }
                } else {
                    if (vi == v_zero) {
                        Console::writeColorToBuff(&buff, _grid.axisColor());
                        buff += wchar(GridCode::HLine_);
                    } else {
                        if (_grid.isGrid()) {
                            Console::writeColorToBuff(&buff, _grid.gridColor());
                        }
                        buff += _grid.grid();
                    }
                }
            }

            // Right arrow
            if (vi == v_zero && _grid.isArrow()) {
                Console::writeColorToBuff(&buff, _grid.axisColor());
                buff += wchar(_grid.arrow() == Arrow::Big ? GridCode::BigRArrow_ : GridCode::SmallRArrow_);
            }

            buff += L'\n';
        }

        //        uint h_pos        = (_size.horizontal() + ((_header.isDataHeader()) ? v_alignment : 0) + ((_grid.isArrow()) ? 1 : 0));
        uint h_pos_header = 0;

        // Horizontal data header
        if (_header.isDataHeader()) {
            if (Console::globalHPos() > 0) {
                Console::writePositionToBuff(&buff, Position::Right, Console::globalHPos());
            }

            Console::writeColorToBuff(&buff, Color::Default);
            buff.append(v_alignment, ' ');
            h_pos_header += v_alignment;

            int count = 0;
            for (uint hi = 0; hi < _size.horizontal(); ++hi) {
                const double hs = hi * h_step + _range.horizontalMin();

                const uint h_alignment = static_cast<uint>(std::to_string(std::abs(static_cast<int>(hs))).size() + ((hs < 0) ? 1 : 0)
                                                           + ((_precision.horizontalPrecision() > 0) ? (_precision.horizontalPrecision() + 1) : 0)
                                                           + 1); // for one space
                if (count % h_alignment == 0) {
                    _header.writeDataToBuff(&buff, hs, h_alignment, _precision.horizontalPrecision());
                    h_pos_header += h_alignment;
                    count = 0;
                }

                ++count;
            }
        }

        const uint h_pos_exp = _size.horizontal() + (_grid.isArrow() ? 1 : 0) + (_header.isDataHeader() ? v_alignment : 0);

        if (_header.isDataHeader() && h_pos_header > h_pos_exp) {
            Console::globalHPos(Console::globalHPos() + h_pos_header);
        } else {
            Console::globalHPos(Console::globalHPos() + h_pos_exp);
        }

        Console::globalVPos(_size.vertical() + ((_grid.isArrow()) ? 1 : 0) + ((_header.isDataHeader()) ? 1 : 0));

        Console::writeColorToBuff(&buff, Color::Default);
        buff += L'\n';
        Console::print(buff);
    }

private:
    Grid        _grid {};
    Header      _header {};
    Precision2D _precision {};
    Range       _range {};
    Size        _size {};

    wchar_t point_ { wchar(Point::Dot) };
    Color   point_color_ { Color::BrightRed };
};

} // namespace WideConsole
