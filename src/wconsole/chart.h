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

#ifndef WCONSOLE_CHART_H_
#define WCONSOLE_CHART_H_ 1

#include <cmath>
#include <utility>
#include <vector>

#include "igrid.h"
#include "iheader.h"
#include "iprecision.h"
#include "irange.h"
#include "iwconsole.h"

namespace WConsole {

enum class ChartType : uchar {
    Column,
    Bar,
    Pie,
};

enum class Opacity : uchar {
    OP_100,
    OP_75,
    OP_50,
    OP_25,
};

class Chart final : public IWConsole, public IHeader, public IPrecisionP1, public IRange, public IGrid {
public:
    explicit Chart(const ChartType type    = ChartType::Column,
                   const Opacity   opacity = Opacity::OP_100)
                 : IWConsole  (ObjectType::Chart, 4, 6),
                   chart_type_(type) {
        SetOpacity(opacity);
        // Default colors
        SetChartColors({Color::Red, Color::Yellow, Color::Black});
    }

    void SetChartType(const ChartType type) noexcept {
        chart_type_ = type;
    }

    void SetOpacity(const Opacity opacity) noexcept {
        switch (opacity) {
            case Opacity::OP_100: brick_ = BrickCode::FF_OP100_; break;
            case Opacity::OP_75:  brick_ = BrickCode::FF_OP75_;  break;
            case Opacity::OP_50:  brick_ = BrickCode::FF_OP50_;  break;
            case Opacity::OP_25:  brick_ = BrickCode::FF_OP25_;  break;
        }
    }

    void SetChartColors(const std::vector<Color> & colors) noexcept {
        colors_ = colors;
    }

    template <typename T>
    void PrintObject(const std::vector<T> & data) {
        switch (chart_type_) {
            case ChartType::Column: PrintColumnChart(data); break;
            case ChartType::Bar:    PrintBarChart(data);    break;
            case ChartType::Pie:    PrintPieChart(data);    break;
        }
    }

private:
    enum class BrickCode : wchar_t {
        FF_OP100_ = 0x2588, // upper full,  last full,  opacity 100%
        FF_OP75_  = 0x2593, // upper full,  last full,  opacity 75%
        FF_OP50_  = 0x2592, // upper full,  last full,  opacity 50%
        FF_OP25_  = 0x2591, // upper full,  last full,  opacity 25%
        FS_       = 0x258C, // upper full,  last small
        FSI_      = 0x2590, // upper full,  last small, inverse
        SF_       = 0x2584, // upper small, last full
        SFI_      = 0x2580, // upper small, last full,  inverse
    };

    const double       Pi = (4.0 * std::atan(1.0));
    ChartType          chart_type_;
    std::vector<Color> colors_;
    BrickCode          brick_;

    void WriteBricksToBuff(std::wstring & buff, const BrickCode brick, const uint number = 1) const noexcept {
        for (uint i = 0; i < number; ++i) {
            buff += (wchar_t)brick;
        }
    }

    wchar_t GetOuterBrick(const double hs,
                          const double vs,
                          const double h_center,
                          const double v_center,
                          const double h_step,
                          const double v_step,
                          const double real_x,
                          const double real_y) const noexcept {
        BrickCode brick    = BrickCode::FF_OP100_;
        uint      quadrant = 0;

        if (real_x > h_center && real_y > v_center) {
            quadrant = 1;
//            return L'1';
        } else if (real_x <= h_center && real_y > v_center) {
            quadrant = 2;
//            return L'2';
        } else if (real_x <= h_center && real_y < v_center) {
            quadrant = 3;
//            return L'3';
        } else if (real_x > h_center && real_y < v_center) {
            quadrant = 4;
//            return L'4';
        }

        const double coef = 0.4;
        if (quadrant == 1 || quadrant == 2) {
            if ((real_y - vs) > coef) {
                brick = BrickCode::FF_OP100_;
            } else {
                brick = BrickCode::SF_;
            }
        } else if (quadrant == 3 || quadrant == 4) {
            if ((1 - (real_y - vs)) < coef) {
                brick = BrickCode::SFI_;
            } else {
                brick = BrickCode::FF_OP100_;
            }
        }

//        wprintf(L"[%u] [%f]\t(%f)\n", quadrant, vs, real_y);

        return ((wchar_t)brick);
    }

    int GetPieIndex(const double hs,
                    const double vs,
                    const double h_center,
                    const double v_center,
                    const std::vector<double> & angles) const {

        if (hs == h_center && vs == v_center) {
            return 0;
        }

        const double x = (vs - v_center) / (hs - h_center);
        double alpha = 180.0 * std::acos(x / std::sqrt(1 + x*x)) / Pi;

        if (std::isnan(alpha)) {
            alpha = 180.0 * std::acos(std::sin(std::atan(x))) / Pi;
        }

        if (hs >= h_center && vs >= v_center) {
//            return 1;
        } else if (hs < h_center && vs >= v_center) {
//            return 2;
            alpha += 180.0;
        } else if (hs < h_center && vs < v_center) {
//            return 3;
            alpha += 180.0;
        } else if (hs >= h_center && vs < v_center) {
//            return 4;
        }

        const double error   = 0.0000005;
        const double alpha_e = alpha - error;

        for (size_t i = 0; i < angles.size(); ++i) {
            if (alpha_e <= angles[i]) {
//                wprintf(L"[% 2d]%.10f <= %.10f\n", i, alpha_e, angles[i]);
                return (i);
            }
        }

        return (-1);
    }

    int GetPieIndexHeader(const double hs,
                          const double vs,
                          const double h_center,
                          const double v_center,
                          const std::vector<double> & angle) const {
        const double x = (vs - v_center) / (hs - h_center);
        double alpha = 180.0 * std::acos(x / std::sqrt(1 + x*x)) / Pi;

        if (std::isnan(alpha)) {
            alpha = 180.0 * std::acos(std::sin(std::atan(x))) / Pi;
        }

        if (hs >= h_center && vs >= v_center) {
        } else if (hs < h_center && vs >= v_center) {
            alpha += 180.0;
        } else if (hs < h_center && vs < v_center) {
            alpha += 180.0;
        } else if (hs >= h_center && vs < v_center) {
        }

        for (size_t i = 0; i < angle.size(); ++i) {
            const double angle_prev = ((i == 0) ? 0.0 : angle[i - 1]);
            const double sector     = angle[i] - angle_prev;
            const double middle     = angle_prev + sector / 2.0;
            const double error      = 0.1 * sector;

            if ((alpha - error) <= middle && (alpha + error) >= middle) {
//                wprintf(L"A- %f\tM %f\tA+ %f\n", alpha - error, middle, alpha + error);
                return ((int)i);
            }
        }


//        if (((alpha - error) <= middle && (alpha + error) >= middle) || middle >= 180.0)
//            wprintf(L"A- %f\tM %f\tA+ %f\n", alpha - error, middle, alpha + error);

        return (-1);
    }

    template <typename T>
    void PrintColumnChart(const std::vector<T> & data) {
        const T      data_max      = * std::max_element(std::begin(data), std::end(data));
//        const T      data_min      = * std::min_element(std::begin(data), std::end(data));
        const double step          = (v_max_ - v_min_) / (double)vertical_size_; //(data_max - data_min) / static_cast<T>(vertical_size_);
        const uint   over          = ((is_data_header_ && (data_max > v_max_)) ? 1 : 0);
//        const uint   clst          = vertical_size_ / static_cast<uint>(colors_.size());
//        const bool   is_data_empty = (data.begin() == data.end());
        const uint   one_h_size    = horizontal_size_ / data.size();

        std::wstring      buff;

        if (v_pos_ > 0) {
            WritePositionToBuff(buff, Position::Up, v_pos_);
        }

        std::vector<bool> print_data_once(data.size(), false);

//        size_t cs             = colors_.size();
        bool   write_over     = (over == 0);
        T      grid_value     = v_max_;
        uint   grid_alignment = (uint)(std::max(std::to_string((int)v_max_).size(), std::to_string((int)v_min_).size()));
        uint   data_alignment = 0;

        if (typeid(grid_value) == typeid(float)
            || typeid(grid_value) == typeid(double)
            || typeid(grid_value) == typeid(long double)) {
            grid_alignment += ((precision_ > 0) ? (precision_ + 1) : 0);
        }

        // Vertical loop
        for (int vi = vertical_size_ + over; vi > 0; --vi) {
            uint space_diff = 0;

            if (h_pos_ > 0) {
                WritePositionToBuff(buff, Position::Right, h_pos_);
            }

            // Grid
            if (is_grid_) {
                if (write_over) {
                    WriteColorToBuff(buff, Color::Default);
                    WriteDataToBuff(buff, grid_value, grid_alignment, precision_);
                } else {
                    buff.append(grid_alignment, ' ');
                }
            }

            /*if (vi <= ((cs - 1) * clst) && vi > 0) {
                --cs;
            }

            Color v_color = colors_[colors_.size() - cs];
            WriteColorToBuff(buff, v_color);*/

            // Data loop
            for (size_t di = 0; di < data.size(); ++di) {
                Color v_color = colors_[di % colors_.size()];
                WriteColorToBuff(buff, v_color);

                data_alignment = (uint)(std::to_string((int)data[di]).size());

                if (typeid(grid_value) == typeid(float)
                    || typeid(grid_value) == typeid(double)
                    || typeid(grid_value) == typeid(long double)) {
                    data_alignment += ((precision_ > 0) ? (precision_ + 1) : 0);
                }

                if (is_data_header_ && !print_data_once[di] && data[di] >= grid_value) {
                    /*if ((vi - 1) <= ((cs - 1) * clst)) {
                        WriteColorToBuff(buff, colors_[colors_.size() - cs + 1]);
                    }*/

                    if (space_diff > 0) {
                        WritePositionToBuff(buff, Position::Left, space_diff);
                        space_diff = 0;
                    }

                    WriteDataToBuff(buff, data[di], one_h_size, precision_);

                    space_diff = ((data_alignment > one_h_size) ? (data_alignment - one_h_size) : 0);
                    print_data_once[di] = true;
//                    WriteColorToBuff(buff, v_color);
                } else if (is_data_header_ && vi == 0 && !print_data_once[di]) {
                    if (space_diff > 0) {
                        WritePositionToBuff(buff, Position::Left, space_diff);
                        space_diff = 0;
                    }

                    WriteDataToBuff(buff, data[di], one_h_size, precision_);

                    space_diff = ((data_alignment > one_h_size) ? (data_alignment - one_h_size) : 0);
                } else if (data[di] >= grid_value) {
                    if (space_diff > 0) {
                        WritePositionToBuff(buff, Position::Left, space_diff);
                        space_diff = 0;
                    }

                    WriteBricksToBuff(buff, brick_, one_h_size - 1);
                    WriteBricksToBuff(buff, BrickCode::FS_);
                } else if (write_over) {
                    if (is_grid_) {
                        WriteColorToBuff(buff, grid_color_);
                    }

                    buff.append(one_h_size, grid_);
                    WriteColorToBuff(buff, v_color);
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

        v_pos_  = vertical_size_+ over;
        h_pos_ += (one_h_size * data.size()
                   + (is_grid_ ? grid_alignment : 0)
                   + ((data_alignment > one_h_size) ? (data_alignment - one_h_size) : 0));

        WriteColorToBuff(buff, Color::Default);
        Print(buff);
    }

    template <typename T>
    void PrintBarChart(const std::vector<T> & data) {
//        const T      data_max      = * std::max_element(std::begin(data), std::end(data));
//        const T      data_min      = * std::min_element(std::begin(data), std::end(data));
        const double step          = (h_max_ - h_min_) / (double)horizontal_size_; //(data_max - data_min) / static_cast<T>(horizontal_size_);
        const uint   over          = ((is_data_header_  ? (uint)(std::max(std::to_string((int)v_max_).size(), std::to_string((int)v_min_).size())) : 0)
                                                               + ((precision_ > 0) ? (precision_ + 1) : 0));
//        const bool is_data_empty = (data.begin() == data.end());
        const uint   one_v_size    = vertical_size_ / data.size();

        std::wstring buff;

        if (v_pos_ > 0) {
            WritePositionToBuff(buff, Position::Up, v_pos_);
        }

        // Data loop
        for (size_t di = 0; di < data.size(); ++di) {
            WriteColorToBuff(buff, colors_[di % colors_.size()]);

            uint num_bricks      = 0;
            bool print_data_once = !is_data_header_;

            if (data[di] >= h_min_ && data[di] <= h_max_) {
                num_bricks = (data[di] - h_min_) / step;
            } else if (data[di] > h_max_) {
                num_bricks = horizontal_size_;
            }

            for (uint i = 0; i < one_v_size - 1; ++i) {
                if (h_pos_ > 0) {
                    WritePositionToBuff(buff, Position::Right, h_pos_);
                }

                WriteBricksToBuff(buff, brick_, num_bricks);
                if (!print_data_once && i == (one_v_size - 1) / 2) {
                    WriteDataToBuff(buff, data[di], 1, precision_);
                    print_data_once = true;
                }
                buff += L'\n';
            }

            if (h_pos_ > 0) {
                WritePositionToBuff(buff, Position::Right, h_pos_);
            }

            WriteBricksToBuff(buff, BrickCode::SFI_, num_bricks);
            if (!print_data_once) {
                WriteDataToBuff(buff, data[di], 1, precision_);
                print_data_once = true;
            }

            buff += L'\n';
        }

        // Grid
        if (is_grid_) {
            if (h_pos_ > 0) {
                WritePositionToBuff(buff, Position::Right, h_pos_);
            }

            WriteColorToBuff(buff, Color::Default);

            DataPosition data_pos   = data_pos_;
            T            grid_value = h_min_;

            data_pos_ = DataPosition::Left;
            for (uint i = 0; i <= horizontal_size_; ) {
                uint alignment = (uint)(std::to_string((int)grid_value).size() + 1); // for one space

                if (typeid(grid_value) == typeid(float)
                    || typeid(grid_value) == typeid(double)
                    || typeid(grid_value) == typeid(long double)) {
                    alignment += ((precision_ > 0) ? (precision_ + 1) : 0);
                }

                WriteDataToBuff(buff, grid_value, alignment, precision_);

//                wprintf(L"V[%02d] A[%u] P[%d]\n", grid_value, alignment, precision_);

                i += alignment;
                grid_value += (alignment * step);
            }
            data_pos_ = data_pos;

            buff += L'\n';
        }

        v_pos_  = one_v_size * (uint)data.size() + (is_grid_ ? 1 : 0);
        h_pos_ += (horizontal_size_ + over);

        WriteColorToBuff(buff, Color::Default);
        Print(buff);
    }

    template <typename T>
    void PrintPieChart(const std::vector<T> & data) {
        bool is_data_empty = (data.begin() == data.end());
        uint alignment     = 0;

        T                   sum = (T)0;
        std::vector<T>      work_data;
        std::vector<double> angles;

        if (!is_data_empty) {
            if (is_data_header_) {
                alignment = (uint)(std::max(std::to_string((int)(* std::max_element(data.begin(), data.end()))).size(),
                                            std::to_string((int)(* std::min_element(data.begin(), data.end()))).size())
                    + ((precision_ > 0) ? (precision_ + 1) : 0)
                    + 2); // one space + more ellipse axis
            }

            for (const auto & value : data) {
                if (value > h_max_ || value < h_min_ || value > v_max_ || value < v_min_) {
                    continue;
                }

                work_data.emplace_back(value);
                sum += std::abs(value);
            }

            double percent = 0.0;
            for (size_t i = 0; i < work_data.size(); ++i) {
                percent += ((100.0 * std::abs(work_data[i])) / sum);
                angles.emplace_back(3.6 * percent);
            }

            is_data_empty = (work_data.begin() == work_data.end());
        }

        const uint h_over   = (((horizontal_size_ % 2 == 0) ? 1 : 0) + ((is_data_header_) ? (2 * alignment) : 0));
        const uint v_over   = (((vertical_size_   % 2 == 0) ? 1 : 0) + ((is_data_header_) ?               2 : 0));
        const uint h_center = horizontal_size_ / 2 + 1 + ((is_data_header_) ? alignment : 0);
        const uint v_center = vertical_size_   / 2 + 1 + ((is_data_header_) ?         1 : 0);

        // Ellipse
        const auto a = (double)(horizontal_size_ / 2); // semi-major axis
        const auto b = (double)(vertical_size_   / 2); // semi-minor axis

        std::vector<std::pair<double, double>> coord;
        std::vector<std::pair<double, double>> header_coord;
        const double                           coef_alpha = 0.01;
        // Alpha
        if (!is_data_empty) {
            for (double alpha = (Pi/2.0); alpha >= 0.0; alpha -= (coef_alpha * Pi/2.0)) {
                const double x = a * std::cos(alpha);
                const double y = b * std::sin(alpha);

                if (!std::isnan(x) && !std::isnan(y)) {
                    coord.emplace_back(( x + h_center + 0.5), ( y + v_center + 0.5));
                    coord.emplace_back(( x + h_center + 0.5), (-y + v_center + 0.5));
                    coord.emplace_back((-x + h_center + 0.5), ( y + v_center + 0.5));
                    coord.emplace_back((-x + h_center + 0.5), (-y + v_center + 0.5));
                }

                if (is_data_header_) {
//                    const double coef_sh = 5.0;
//                    const double shift   = ((alignment < coef_sh) ? alignment : coef_sh);
                    const double hx      = (a + alignment) * std::cos(alpha);
                    const double hy      = (b + 1.0)       * std::sin(alpha);

                    if (!std::isnan(hx) && !std::isnan(hy)) {
                        header_coord.emplace_back(( hx + h_center + 0.5), ( hy + v_center + 0.5));
                        header_coord.emplace_back(( hx + h_center + 0.5), (-hy + v_center + 0.5));
                        header_coord.emplace_back((-hx + h_center + 0.5), ( hy + v_center + 0.5));
                        header_coord.emplace_back((-hx + h_center + 0.5), (-hy + v_center + 0.5));
                    }
                }
            }
        }

        std::vector<std::pair<std::pair<  uint,   uint>,
                              std::pair<double, double>>> sort_coord;
        std::vector<std::pair<std::pair<  uint,   uint>,
                              std::pair<double, double>>> sort_header;

        if (!is_data_empty) {
            for (const auto & coord_pair : coord) {
                const uint x         = (uint)coord_pair.first;
                const uint y         = (uint)coord_pair.second;
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
            std::sort(sort_coord.begin(), sort_coord.end(), [](const auto & left, const auto & right) {
                return (left.first.second > right.first.second || (left.first.second == right.first.second && left.first.first < right.first.first));
            });

            if (is_data_header_) {
                for (const auto & coord_pair : header_coord) {
                    const uint   x         = (uint)coord_pair.first;
                    const uint   y         = (uint)coord_pair.second;
                    bool         duplicate = false;

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
                std::sort(sort_header.begin(), sort_header.end(), [](const auto & left, const auto & right) {
                    return (left.first.second > right.first.second || (left.first.second == right.first.second && left.first.first < right.first.first));
                });
            }
        }

        // Const iterators
        auto coord_iterator  = sort_coord.cbegin();
        auto header_iterator = sort_header.cbegin();

        std::wstring buff;
        buff.reserve(vertical_size_ * horizontal_size_ * 8); // magic eight (hateful :)

        if (v_pos_ > 0) {
            WritePositionToBuff(buff, Position::Up, v_pos_);
        }

        if (h_pos_ > 0) {
//            h_global_pos_ = h_pos_;
        }

        // Vertical loop
        std::vector<int> write_header_indexes;

        for (uint vi = vertical_size_ + v_over; vi > 0; --vi) {

            if (h_pos_ > 0) {
                WritePositionToBuff(buff, Position::Right, h_pos_);
            }

            // Horizontal loop
            double h_first = horizontal_size_ + h_over;
            double v_prev  = 0;
            int    index   = -1;

            for (uint hi = 1; hi <= horizontal_size_ + h_over; ++hi) {
                // Data header
                if (is_data_header_ && !is_data_empty && header_iterator != sort_header.end()
                    && hi == header_iterator->first.first && vi == header_iterator->first.second) {

                    if (((index = GetPieIndexHeader(hi, 2 * vi, h_center, 2.0 * v_center, angles)) != -1)
                        && (write_header_indexes.begin() == write_header_indexes.end()
                            || std::find(write_header_indexes.begin(), write_header_indexes.end(), index) == write_header_indexes.end())
                        ) {

                        WriteColorToBuff(buff, colors_[index % colors_.size()]);

                        bool end_space = true;
                        int  shift     = 0;
                        if (coord_iterator != sort_coord.end() && vi == coord_iterator->first.second) {
                            const uint diff = (uint)(coord_iterator->first.first - header_iterator->first.first);

                            if (diff < alignment) {
                                shift = alignment - diff;
                                hi = (coord_iterator->first.first - 1);
                            } else {
                                hi += (alignment - 1);
                            }
                        } else if ((coord_iterator - 1) != sort_coord.end()
                                   && (coord_iterator - 1) >= sort_coord.begin()
                                   && vi == (coord_iterator - 1)->first.second) {
                            const uint diff = (uint)(header_iterator->first.first - (coord_iterator - 1)->first.first - 1);

                            if ((horizontal_size_ + h_over - hi) < alignment) {
                                if ((horizontal_size_ + h_over - hi) == (alignment - 1)) {
                                    buff += L' ';
                                }
                                shift = alignment - (horizontal_size_ + h_over - hi) - 2;
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

                        WritePositionToBuff(buff, Position::Left, shift);
                        WriteDataToBuff(buff, data[index], (alignment - 1), precision_);
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

                    if ((index = GetPieIndex(hi, 2 * vi, h_center, 2.0 * v_center, angles)) != -1) {
                        WriteColorToBuff(buff, colors_[index % colors_.size()]);
                    }

                    buff += GetOuterBrick(hi, vi, h_center, v_center, 1, 1, coord_iterator->second.first, coord_iterator->second.second);
                    v_prev = vi;
                    ++coord_iterator;
                } else if ((coord_iterator != sort_coord.end() && vi == v_prev && hi >= h_first && hi <= coord_iterator->first.first)
                    && (index = GetPieIndex(hi, 2 * vi, h_center, 2.0 * v_center, angles)) != -1) {
                    WriteColorToBuff(buff, colors_[index % colors_.size()]);
                    buff += (wchar_t)brick_;
                } else {
                    buff += L' ';
                }
            }

            buff += L'\n';
        }

        h_pos_ += (horizontal_size_ + h_over);
        v_pos_  = (vertical_size_   + v_over + 1);

        WriteColorToBuff(buff, Color::Default);
        buff += L'\n';
        Print(buff);
    }

}; // class Chart

} // namespace WConsole

#endif // WCONSOLE_CHART_H_
