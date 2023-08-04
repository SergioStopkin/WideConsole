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

#include "wideconsole/interface/ichart.h"
#include "wideconsole/type/brickcode.h"
#include "wideconsole/unit/grid.h"
#include "wideconsole/unit/header.h"
#include "wideconsole/unit/object.h"
#include "wideconsole/unit/precision1d.h"
#include "wideconsole/unit/range.h"
#include "wideconsole/unit/size.h"

#include <cmath>
#include <utility>
#include <vector>

namespace WideConsole {

class Chart final : public IChart, public Object {
public:
    IGrid &        grid() noexcept override { return _grid; }
    IHeader &      header() noexcept override { return _header; }
    IPrecision1D & precision() noexcept override { return _precision; }
    IRange &       range() noexcept override { return _range; }
    ISize &        size() noexcept override { return _size; }

    void setChartType(const ChartType type) noexcept override { chart_type_ = type; }
    void setChartColors(const std::vector<Color> & colors) noexcept override { colors_ = colors; }
    void setOpacity(const Opacity opacity) noexcept override
    {
        switch (opacity) {
        // clang-format off
        case Opacity::OP_100: brick_ = BrickCode::FF_OP100_; break;
        case Opacity::OP_75:  brick_ = BrickCode::FF_OP75_;  break;
        case Opacity::OP_50:  brick_ = BrickCode::FF_OP50_;  break;
        case Opacity::OP_25:  brick_ = BrickCode::FF_OP25_;  break;
        } // clang-format on
    }

    template <typename T>
    void printObject(const std::vector<T> & data)
    {
        // Pre-processing
        Console::preProcessing(_size.horizontal(), (chart_type_ == ChartType::Pie ? (2 * _header.size()) : _header.size()));

        switch (chart_type_) {
        // clang-format off
        case ChartType::Column: printColumnChart(data); break;
        case ChartType::Bar:    printBarChart(data);    break;
        case ChartType::Pie:    printPieChart(data);    break;
        } // clang-format on
    }

private:
    using sort_t = std::vector<std::pair<std::pair<uint, uint>, std::pair<double, double>>>;

    Grid        _grid {};
    Header      _header {};
    Precision1D _precision {};
    Range       _range {};
    Size        _size {};

    const double       PiRad = (4.0 * std::atan(1.0));
    const double       PiDeg = 180.0;
    ChartType          chart_type_ { ChartType::Column };
    std::vector<Color> colors_ { Color::Red, Color::Yellow, Color::Black };
    BrickCode          brick_ { BrickCode::FF_OP100_ };

    static void writeBricksToBuff(std::wstring * buff, const BrickCode brick, const uint number = 1)
    {
        // for (uint i = 0; i < number; ++i) {
        //     *buff += wchar(brick);
        // }
        buff->append(number, wchar(brick));
    }

    static wchar_t outerBrick([[maybe_unused]] const double hs,
                              const double                  vs,
                              const double                  h_center,
                              const double                  v_center,
                              [[maybe_unused]] const double h_step,
                              [[maybe_unused]] const double v_step,
                              const double                  real_x,
                              const double                  real_y) noexcept
    {
        BrickCode brick    = BrickCode::FF_OP100_;
        uint      quadrant = 0;

        if (real_x > h_center && real_y > v_center) {
            quadrant = 1;
        } else if (real_x <= h_center && real_y > v_center) {
            quadrant = 2;
        } else if (real_x <= h_center && real_y < v_center) {
            quadrant = 3;
        } else if (real_x > h_center && real_y < v_center) {
            quadrant = 4;
        }

        const double coef = 0.4;
        if (quadrant == 1 || quadrant == 2) {
            if ((real_y - vs) <= coef) {
                brick = BrickCode::SF_;
            }
        } else if (quadrant == 3 || quadrant == 4) {
            if ((1 - (real_y - vs)) < coef) {
                brick = BrickCode::SFI_;
            }
        }

        return wchar(brick);
    }

    [[nodiscard]] int
    pieIndex(const double hs, const double vs, const double h_center, const double v_center, const std::vector<double> & angles) const
    {
        if (hs == h_center && vs == v_center) {
            return 0;
        }

        const double x     = (vs - v_center) / (hs - h_center);
        double       alpha = PiDeg * std::acos(x / std::sqrt(1 + x * x)) / PiRad;

        if (std::isnan(alpha)) {
            alpha = PiDeg * std::acos(std::sin(std::atan(x))) / PiRad;
        }

        // if (hs >= h_center && vs >= v_center) {
        //                return 1;
        // } else if (hs < h_center && vs >= v_center) {
        //                return 2;
        //     alpha += PiDeg;
        // } else if (hs < h_center && vs < v_center) {
        //                return 3;
        //     alpha += PiDeg;
        // } else if (hs >= h_center && vs < v_center) {
        //                return 4;
        // }
        // if (hs < h_center && (vs >= v_center || vs < v_center)) {
        if (hs < h_center) {
            alpha += PiDeg;
        }

        const double error   = 0.0000005;
        const double alpha_e = alpha - error;

        for (size_t i = 0; i < angles.size(); ++i) {
            if (alpha_e <= angles[i]) {
                //                wprintf(L"[% 2d]%.10f <= %.10f\n", i, alpha_e, angles[i]);
                return i;
            }
        }

        return -1;
    }

    [[nodiscard]] int
    pieIndexHeader(const double hs, const double vs, const double h_center, const double v_center, const std::vector<double> & angle) const
    {
        const double x     = (vs - v_center) / (hs - h_center);
        double       alpha = PiDeg * std::acos(x / std::sqrt(1 + x * x)) / PiRad;

        if (std::isnan(alpha)) {
            alpha = PiDeg * std::acos(std::sin(std::atan(x))) / PiRad;
        }

        // if (hs >= h_center && vs >= v_center) {
        // } else if (hs < h_center && vs >= v_center) {
        //     alpha += PiDeg;
        // } else if (hs < h_center && vs < v_center) {
        //     alpha += PiDeg;
        // } else if (hs >= h_center && vs < v_center) {
        // }
        if (hs < h_center) {
            alpha += PiDeg;
        }

        for (size_t i = 0; i < angle.size(); ++i) {
            const double angle_prev = ((i == 0) ? 0.0 : angle[i - 1]);
            const double sector     = angle[i] - angle_prev;
            const double middle     = angle_prev + sector / 2.0;
            const double error      = 0.1 * sector;

            if ((alpha - error) <= middle && (alpha + error) >= middle) {
                //                wprintf(L"A- %f\tM %f\tA+ %f\n", alpha - error, middle, alpha + error);
                return static_cast<int>(i);
            }
        }

        //        if (((alpha - error) <= middle && (alpha + error) >= middle) || middle >= PiDeg)
        //            wprintf(L"A- %f\tM %f\tA+ %f\n", alpha - error, middle, alpha + error);

        return -1;
    }

    template <typename T>
    void printColumnChart(const std::vector<T> & data)
    {
        const T data_max = *std::max_element(std::begin(data), std::end(data));
        //        const T      data_min      = * std::min_element(std::begin(data), std::end(data));
        const double step = (_range.verticalMax() - _range.verticalMin())
                          / static_cast<double>(_size.vertical()); //(data_max - data_min) / static_cast<T>(_size.vertical());
        const uint over = ((_header.isDataHeader() && (data_max > _range.verticalMax())) ? 1 : 0);
        //        const uint   clst          = _size.vertical() / static_cast<uint>(colors_.size());
        //        const bool   is_data_empty = (data.begin() == data.end());
        const uint one_h_size = _size.horizontal() / data.size();

        std::wstring buff;

        if (Console::globalVPos() > 0) {
            Console::writePositionToBuff(&buff, Position::Up, Console::globalVPos());
        }

        std::vector<bool> print_data_once(data.size(), false);

        //        size_t cs             = colors_.size();
        bool write_over     = (over == 0);
        T    grid_value     = _range.verticalMax();
        uint grid_alignment = static_cast<uint>(
            std::max(std::to_string(static_cast<int>(_range.verticalMax())).size(), std::to_string(static_cast<int>(_range.verticalMin())).size()));
        uint data_alignment = 0;

        if (typeid(grid_value) == typeid(float) || typeid(grid_value) == typeid(double) || typeid(grid_value) == typeid(long double)) {
            grid_alignment += ((_precision.precision() > 0) ? (_precision.precision() + 1) : 0);
        }

        // Vertical loop
        for (int vi = _size.vertical() + over; vi > 0; --vi) {
            uint space_diff = 0;

            if (Console::globalHPos() > 0) {
                Console::writePositionToBuff(&buff, Position::Right, Console::globalHPos());
            }

            // Grid
            if (_grid.isGrid()) {
                if (write_over) {
                    Console::writeColorToBuff(&buff, Color::Default);
                    _header.writeDataToBuff(&buff, grid_value, grid_alignment, _precision.precision());
                } else {
                    buff.append(grid_alignment, ' ');
                }
            }

            /*if (vi <= ((cs - 1) * clst) && vi > 0) {
                --cs;
            }

            Color v_color = colors_[colors_.size() - cs];
            Console::writeColorToBuff(&buff, v_color);*/

            // Data loop
            for (size_t di = 0; di < data.size(); ++di) {
                Color v_color = colors_[di % colors_.size()];
                Console::writeColorToBuff(&buff, v_color);

                data_alignment = static_cast<uint>(std::to_string(static_cast<int>(data[di])).size());

                if (typeid(grid_value) == typeid(float) || typeid(grid_value) == typeid(double) || typeid(grid_value) == typeid(long double)) {
                    data_alignment += ((_precision.precision() > 0) ? (_precision.precision() + 1) : 0);
                }

                if (_header.isDataHeader() && !print_data_once[di] && data[di] >= grid_value) {
                    /*if ((vi - 1) <= ((cs - 1) * clst)) {
                        Console::writeColorToBuff(&buff, colors_[colors_.size() - cs + 1]);
                    }*/

                    if (space_diff > 0) {
                        Console::writePositionToBuff(&buff, Position::Left, space_diff);
                        space_diff = 0;
                    }

                    _header.writeDataToBuff(&buff, data[di], one_h_size, _precision.precision());

                    space_diff          = ((data_alignment > one_h_size) ? (data_alignment - one_h_size) : 0);
                    print_data_once[di] = true;
                    //                    Console::writeColorToBuff(&buff, v_color);
                } else if (_header.isDataHeader() && vi == 0 && !print_data_once[di]) {
                    if (space_diff > 0) {
                        Console::writePositionToBuff(&buff, Position::Left, space_diff);
                        space_diff = 0;
                    }

                    _header.writeDataToBuff(&buff, data[di], one_h_size, _precision.precision());

                    space_diff = ((data_alignment > one_h_size) ? (data_alignment - one_h_size) : 0);
                } else if (data[di] >= grid_value) {
                    if (space_diff > 0) {
                        Console::writePositionToBuff(&buff, Position::Left, space_diff);
                        space_diff = 0;
                    }

                    writeBricksToBuff(&buff, brick_, one_h_size - 1);
                    writeBricksToBuff(&buff, BrickCode::FS_);
                } else if (write_over) {
                    if (_grid.isGrid()) {
                        Console::writeColorToBuff(&buff, _grid.gridColor());
                    }

                    buff.append(one_h_size, _grid.grid());
                    Console::writeColorToBuff(&buff, v_color);
                } else {
                    if (space_diff > one_h_size) {
                        space_diff -= one_h_size;
                    } else {
                        buff.append(one_h_size - space_diff, ' ');
                        space_diff = 0;
                    }
                }
            }

            buff += L"\n";
            if (write_over) {
                grid_value -= step;
            }
            write_over = true;
        }

        Console::globalVPos(_size.vertical() + over);
        Console::globalHPos(Console::globalHPos()
                            + (one_h_size * data.size() + (_grid.isGrid() ? grid_alignment : 0)
                               + ((data_alignment > one_h_size) ? (data_alignment - one_h_size) : 0)));

        Console::writeColorToBuff(&buff, Color::Default);
        Console::print(buff);
    }

    template <typename T>
    void printBarChart(const std::vector<T> & data)
    {
        //        const T      data_max      = * std::max_element(std::begin(data), std::end(data));
        //        const T      data_min      = * std::min_element(std::begin(data), std::end(data));
        const double step = (_range.horizontalMax() - _range.horizontalMin())
                          / static_cast<double>(_size.horizontal()); //(data_max - data_min) / static_cast<T>(_size.horizontal());
        const uint over = ((_header.isDataHeader() ? static_cast<uint>(std::max(std::to_string(static_cast<int>(_range.verticalMax())).size(),
                                                                                std::to_string(static_cast<int>(_range.verticalMin())).size()))
                                                   : 0)
                           + ((_precision.precision() > 0) ? (_precision.precision() + 1) : 0));
        //        const bool is_data_empty = (data.begin() == data.end());
        const uint one_v_size = _size.vertical() / data.size();

        std::wstring buff;

        if (Console::globalVPos() > 0) {
            Console::writePositionToBuff(&buff, Position::Up, Console::globalVPos());
        }

        // Data loop
        for (size_t di = 0; di < data.size(); ++di) {
            Console::writeColorToBuff(&buff, colors_[di % colors_.size()]);

            uint num_bricks      = 0;
            bool print_data_once = !_header.isDataHeader();

            if (data[di] >= _range.horizontalMin() && data[di] <= _range.horizontalMax()) {
                num_bricks = (data[di] - _range.horizontalMin()) / step;
            } else if (data[di] > _range.horizontalMax()) {
                num_bricks = _size.horizontal();
            }

            for (uint i = 0; i < one_v_size - 1; ++i) {
                if (Console::globalHPos() > 0) {
                    Console::writePositionToBuff(&buff, Position::Right, Console::globalHPos());
                }

                writeBricksToBuff(&buff, brick_, num_bricks);
                if (!print_data_once && i == (one_v_size - 1) / 2) {
                    _header.writeDataToBuff(&buff, data[di], 1, _precision.precision());
                    print_data_once = true;
                }
                buff += L'\n';
            }

            if (Console::globalHPos() > 0) {
                Console::writePositionToBuff(&buff, Position::Right, Console::globalHPos());
            }

            writeBricksToBuff(&buff, BrickCode::SFI_, num_bricks);
            if (!print_data_once) {
                _header.writeDataToBuff(&buff, data[di], 1, _precision.precision());
                print_data_once = true;
            }

            buff += L'\n';
        }

        // Grid
        if (_grid.isGrid()) {
            if (Console::globalHPos() > 0) {
                Console::writePositionToBuff(&buff, Position::Right, Console::globalHPos());
            }

            Console::writeColorToBuff(&buff, Color::Default);

            DataPosition data_pos   = _header.dataPosition();
            T            grid_value = _range.horizontalMin();

            _header.setDataPosition(DataPosition::Left);
            for (uint i = 0; i <= _size.horizontal();) {
                uint alignment = static_cast<uint>(std::to_string(static_cast<int>(grid_value)).size() + 1); // for one space

                if (typeid(grid_value) == typeid(float) || typeid(grid_value) == typeid(double) || typeid(grid_value) == typeid(long double)) {
                    alignment += ((_precision.precision() > 0) ? (_precision.precision() + 1) : 0);
                }

                _header.writeDataToBuff(&buff, grid_value, alignment, _precision.precision());

                //                wprintf(L"V[%02d] A[%u] P[%d]\n", grid_value, alignment, _precision.precision());

                i += alignment;
                grid_value += (alignment * step);
            }
            _header.setDataPosition(data_pos);

            buff += L'\n';
        }

        Console::globalVPos(one_v_size * static_cast<uint>(data.size()) + (_grid.isGrid() ? 1 : 0));
        Console::globalHPos(Console::globalHPos() + _size.horizontal() + over);

        Console::writeColorToBuff(&buff, Color::Default);
        Console::print(buff);
    }

    template <typename T>
    void printPieChart(const std::vector<T> & data)
    {
        bool is_data_empty = (data.begin() == data.end());
        uint alignment     = 0;

        T                   sum = static_cast<T>(0);
        std::vector<T>      work_data;
        std::vector<double> angles;

        if (!is_data_empty) {
            if (_header.isDataHeader()) {
                alignment = static_cast<uint>(std::max(std::to_string(static_cast<int>(*std::max_element(data.begin(), data.end()))).size(),
                                                       std::to_string(static_cast<int>(*std::min_element(data.begin(), data.end()))).size())
                                              + ((_precision.precision() > 0) ? (_precision.precision() + 1) : 0)
                                              + 2); // one space + more ellipse axis
            }

            for (const auto & value : data) {
                if (value > _range.horizontalMax() || value < _range.horizontalMin() || value > _range.verticalMax()
                    || value < _range.verticalMin()) {
                    continue;
                }

                work_data.emplace_back(value);
                sum += std::abs(value);
            }

            double percent = 0.0;
            for (const auto it : work_data) {
                percent += ((100.0 * std::abs(it)) / sum);
                angles.emplace_back(3.6 * percent);
            }

            is_data_empty = (work_data.begin() == work_data.end());
        }

        const uint h_over   = (((_size.horizontal() % 2 == 0) ? 1 : 0) + ((_header.isDataHeader()) ? (2 * alignment) : 0));
        const uint v_over   = (((_size.vertical() % 2 == 0) ? 1 : 0) + ((_header.isDataHeader()) ? 2 : 0));
        const uint h_center = _size.horizontal() / 2 + 1 + ((_header.isDataHeader()) ? alignment : 0);
        const uint v_center = _size.vertical() / 2 + 1 + ((_header.isDataHeader()) ? 1 : 0);

        // Ellipse
        // const auto a = static_cast<double>(_size.horizontal() / 2); // semi-major axis
        // const auto b = static_cast<double>(_size.vertical() / 2);   // semi-minor axis
        const size_t a = _size.horizontal() / 2; // semi-major axis
        const size_t b = _size.vertical() / 2;   // semi-minor axis

        std::vector<std::pair<double, double>> coord;
        std::vector<std::pair<double, double>> header_coord;
        // const double                           coef_alpha = 0.01; // >= 0.5 && < 0.005 => segfault
        const size_t multiplier = 100;

        // Alpha
        double alpha = PiRad / 2.0;
        if (!is_data_empty) {
            // for (double alpha = (PiRad / 2.0); alpha >= 0.0; alpha -= (coef_alpha * PiRad / 2.0)) {
            for (size_t i = 0; i <= multiplier; ++i) {
                const double x = a * std::cos(alpha);
                const double y = b * std::sin(alpha);

                if (!std::isnan(x) && !std::isnan(y)) {
                    coord.emplace_back((x + h_center + 0.5), (y + v_center + 0.5));
                    coord.emplace_back((x + h_center + 0.5), (-y + v_center + 0.5));
                    coord.emplace_back((-x + h_center + 0.5), (y + v_center + 0.5));
                    coord.emplace_back((-x + h_center + 0.5), (-y + v_center + 0.5));
                }

                if (_header.isDataHeader()) {
                    //                    const double coef_sh = 5.0;
                    //                    const double shift   = ((alignment < coef_sh) ? alignment : coef_sh);
                    const double hx = (a + alignment) * std::cos(alpha);
                    const double hy = (b + 1.0) * std::sin(alpha);

                    if (!std::isnan(hx) && !std::isnan(hy)) {
                        header_coord.emplace_back((hx + h_center + 0.5), (hy + v_center + 0.5));
                        header_coord.emplace_back((hx + h_center + 0.5), (-hy + v_center + 0.5));
                        header_coord.emplace_back((-hx + h_center + 0.5), (hy + v_center + 0.5));
                        header_coord.emplace_back((-hx + h_center + 0.5), (-hy + v_center + 0.5));
                    }
                }

                alpha -= PiRad / (2.0 * multiplier);
            }
        }

        sort_t sort_coord;
        sort_t sort_header;

        if (!is_data_empty) {
            for (const auto & coord_pair : coord) {
                const uint x         = static_cast<uint>(coord_pair.first);
                const uint y         = static_cast<uint>(coord_pair.second);
                bool       duplicate = false;

                /// todo: optimize
                for (const auto & s_pair : sort_coord) {
                    if (s_pair.first.first == x && s_pair.first.second == y) {
                        duplicate = true;
                        break;
                    }
                }

                if (!duplicate) {
                    sort_coord.emplace_back(std::make_pair(x, y), coord_pair);
                }
            }

            // Sort coordinates by second value in pair
            sort(&sort_coord);

            if (_header.isDataHeader()) {
                for (const auto & coord_pair : header_coord) {
                    const uint x         = static_cast<uint>(coord_pair.first);
                    const uint y         = static_cast<uint>(coord_pair.second);
                    bool       duplicate = false;

                    /// todo: optimize
                    for (const auto & s_pair : sort_header) {
                        if (s_pair.first.first == x && s_pair.first.second == y) {
                            duplicate = true;
                            break;
                        }
                    }

                    if (!duplicate) {
                        sort_header.emplace_back(std::make_pair(x, y), coord_pair);
                    }
                }

                // Sort header coordinates by second value in pair
                sort(&sort_header);
            }
        }

        // Const iterators
        auto coord_iterator  = sort_coord.cbegin();
        auto header_iterator = sort_header.cbegin();

        std::wstring buff;
        buff.reserve(_size.vertical() * _size.horizontal() * 8); // magic eight (hateful :)

        if (Console::globalVPos() > 0) {
            Console::writePositionToBuff(&buff, Position::Up, Console::globalVPos());
        }

        if (Console::globalHPos() > 0) {
            //            h_global_pos_ = Console::globalHPos();
        }

        // Vertical loop
        std::vector<int> write_header_indexes;

        for (uint vi = _size.vertical() + v_over; vi > 0; --vi) {
            if (Console::globalHPos() > 0) {
                Console::writePositionToBuff(&buff, Position::Right, Console::globalHPos());
            }

            // Horizontal loop
            double h_first = _size.horizontal() + h_over;
            double v_prev  = 0;
            int    index   = -1;

            for (uint hi = 1; hi <= _size.horizontal() + h_over; ++hi) {
                // Data header
                if (_header.isDataHeader() && !is_data_empty && header_iterator != sort_header.end() && hi == header_iterator->first.first
                    && vi == header_iterator->first.second) {
                    if (((index = pieIndexHeader(hi, 2 * vi, h_center, 2.0 * v_center, angles)) != -1)
                        && (write_header_indexes.begin() == write_header_indexes.end()
                            || std::find(write_header_indexes.begin(), write_header_indexes.end(), index) == write_header_indexes.end())) {
                        Console::writeColorToBuff(&buff, colors_[index % colors_.size()]);

                        bool end_space = true;
                        int  shift     = 0;
                        if (coord_iterator != sort_coord.end() && vi == coord_iterator->first.second) {
                            const uint diff = static_cast<uint>(coord_iterator->first.first - header_iterator->first.first);

                            if (diff < alignment) {
                                shift = alignment - diff;
                                hi    = (coord_iterator->first.first - 1);
                            } else {
                                hi += (alignment - 1);
                            }
                        } else if ((coord_iterator - 1) != sort_coord.end() && (coord_iterator - 1) >= sort_coord.begin()
                                   && vi == (coord_iterator - 1)->first.second) {
                            const uint diff = static_cast<uint>(header_iterator->first.first - (coord_iterator - 1)->first.first - 1);

                            if ((_size.horizontal() + h_over - hi) < alignment) {
                                if ((_size.horizontal() + h_over - hi) == (alignment - 1)) {
                                    buff += L' ';
                                }
                                shift     = alignment - (_size.horizontal() + h_over - hi) - 2;
                                end_space = false;
                            } else if (diff == 0) {
                                buff += L' ';
                                ++hi;
                            } else {
                                shift = diff / 2;
                            }

                            hi += (alignment - shift - 1);
                        } else {
                            shift = (alignment - 1) / 2;
                            hi += (alignment - shift - 1);
                        }

                        Console::writePositionToBuff(&buff, Position::Left, shift);
                        _header.writeDataToBuff(&buff, data[index], (alignment - 1), _precision.precision());
                        if (end_space) {
                            buff += L' ';
                        }
                        write_header_indexes.emplace_back(index);
                    } else {
                        buff += L' ';
                    }

                    while (header_iterator->first.second == vi && header_iterator->first.first <= hi) {
                        ++header_iterator;
                    }
                } else if (coord_iterator != sort_coord.end() && hi == coord_iterator->first.first && vi == coord_iterator->first.second) {
                    if (vi != v_prev) {
                        h_first = hi;
                    }

                    if ((index = pieIndex(hi, 2 * vi, h_center, 2.0 * v_center, angles)) != -1) {
                        Console::writeColorToBuff(&buff, colors_[index % colors_.size()]);
                    }

                    buff += outerBrick(hi, vi, h_center, v_center, 1, 1, coord_iterator->second.first, coord_iterator->second.second);
                    v_prev = vi;
                    ++coord_iterator;
                } else if (coord_iterator != sort_coord.end() && hi == coord_iterator->first.first && vi == coord_iterator->first.second) {
                } else if ((coord_iterator != sort_coord.end() && vi == v_prev && hi >= h_first && hi <= coord_iterator->first.first)
                           && (index = pieIndex(hi, 2 * vi, h_center, 2.0 * v_center, angles)) != -1) {
                    Console::writeColorToBuff(&buff, colors_[index % colors_.size()]);
                    buff += outerBrick(hi, vi, h_center, v_center, 1, 1, coord_iterator->second.first, coord_iterator->second.second);
                } else {
                    buff += L' ';
                }
            }

            buff += L'\n';
        }

        Console::globalHPos(Console::globalHPos() + _size.horizontal() + h_over);
        Console::globalVPos(_size.vertical() + v_over + 1);

        Console::writeColorToBuff(&buff, Color::Default);
        buff += L'\n';
        Console::print(buff);
    }

    static void sort(sort_t * data) noexcept
    {
        std::sort(data->begin(), data->end(), [](const auto & left, const auto & right) {
            return (left.first.second > right.first.second || (left.first.second == right.first.second && left.first.first < right.first.first));
        });
    }
};

} // namespace WideConsole
