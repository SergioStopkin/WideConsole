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

#ifndef WCONSOLE_GRAPH_H_
#define WCONSOLE_GRAPH_H_ 1

#include <utility>
#include <string>
#include <vector>

#include "igrid.h"
#include "iheader.h"
#include "iprecision.h"
#include "irange.h"
#include "iwconsole.h"

namespace WConsole {

enum class Point : wchar_t {
    Dot           = 0x2022, //0x2981
    Triangle      = 0x25B2,
    SmallTriangle = 0x25B4,
    Rhombus       = 0x25C6,
    SmallSquare   = 0x25FE,
    Star          = 0x2605,
    Clover        = 0x2618,
    Scythe        = 0x262D,
    YinYang       = 0x262F,
    Smile         = 0x263B,
    SpadeSuit     = 0x2660,
    ClubSuit      = 0x2663,
    HeartSuit     = 0x2665,
    DiamondSuit   = 0x2666,
    Flag          = 0x2691,
    Flower        = 0x2698,
    Zeus          = 0x26A1,
    CheckMarkItal = 0x2714,
    CrossX        = 0x2716,
    CrossXItal    = 0x2718,
    Cross         = 0x271A,
    StarInCircle  = 0x272A,
    Asterisk      = 0x2731,
    BigCrossX     = 0x274C,
    Heart         = 0x2764,
    Square        = 0x2B1B,
    Pentagon      = 0x2B1F,
    Hexagon       = 0x2B22,
    Circle        = 0x2B24,
    SmallRhombus  = 0x2B25,
    Beaver        = 0xF800,
};

class Graph : public IWConsole, public IHeader, public IPrecisionP2, public IRange, public IGrid {
public:
    explicit Graph(const Point point = Point::Dot)
                 : IHeader(true, DataPosition::Left),
                   IRange (-10, 10, -10, 10),
                   point_ ((wchar_t)point) {
    }

    void SetPoint(Point point) noexcept {
        point_ = (wchar_t)point;
    }

    template <typename T>
    void PrintGraph(const std::vector<std::pair<T, T>> & data) {
        const double h_step        = (h_max_ - h_min_) / (double)(horizontal_size_ - 1);
        const double v_step        = (v_max_ - v_min_) / (double)(vertical_size_   - 1);
        const auto   v_alignment   = (uint)(std::max(std::to_string((int)v_min_).size(), std::to_string((int)v_max_).size())
                                            + ((v_precision_ > 0) ? (v_precision_ + 1) : 0));
        const bool   is_data_empty = (data.begin() == data.end());
        uint         h_zero        = 2 * horizontal_size_;
        uint         v_zero        = 2 * vertical_size_;
        double       hs_zero       = 2.0 * h_max_;
        double       vs_zero       = 2.0 * v_max_;

        std::vector<std::pair<uint, uint>> sort_data;

        if (!is_data_empty) {
            for (const auto & pair : data) {
                if (pair.first > (h_max_ + h_step) || pair.first < (h_min_ - h_step) || pair.second > (v_max_ + v_step) || pair.second < (v_min_ - v_step)) {
                    continue;
                }

                const auto h = (uint)((pair.first  - h_min_) / h_step + 0.5);
                const auto v = (uint)((pair.second - v_min_) / v_step + 0.5);

                if (pair.first >= -h_step && pair.first <= h_step && pair.first < hs_zero) {
                    hs_zero = pair.first;
                    h_zero  = h + 1;
                }

                if (pair.second >= -v_step && pair.second <= v_step && pair.second < vs_zero) {
                    vs_zero = pair.second;
                    v_zero  = v + 1;
                }

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

        typename std::vector<std::pair<uint, uint>>::const_iterator data_iterator = sort_data.begin();

        std::wstring buff;
        buff.reserve(vertical_size_ * horizontal_size_ * 8); // magic eight (hateful :)

        if (v_pos_ > 0) {
            WritePositionToBuff(buff, Position::Up, v_pos_);
        }

        if (h_pos_ > 0) {
            h_global_pos_ = h_pos_;
        }

        // Upper arrow
        if (is_arrow_) {
            WriteColorToBuff(buff, axis_color_);

            if (h_pos_ > 0) {
                WritePositionToBuff(buff, Position::Right, h_pos_);
            }

            if (is_data_header_) {
                WriteSpacesToBuff(buff, v_alignment);
            }

            for (uint hi = 0; hi < horizontal_size_; ++hi) {
                if (hi == h_zero) {
                    buff += (wchar_t)((arrow_ == Arrow::Big) ? GridCode::BigUArrow_ : GridCode::SmallUArrow_);
                } else {
                    buff += L' ';
                }
            }

            buff += L'\n';
        }

        // Vertical loop
        for (int vi = vertical_size_ - 1; vi >= 0; --vi) {
            const double vs = vi * v_step + v_min_;

            if (h_pos_ > 0) {
                WritePositionToBuff(buff, Position::Right, h_pos_);
            }

            // Vertical data header
            if (is_data_header_) {
                WriteColorToBuff(buff, Color::Default);

                if (vi == v_zero) {
                    WriteDataToBuff(buff, 0.0, v_alignment, v_precision_);
                } else {
                    WriteDataToBuff(buff, vs, v_alignment, v_precision_);
                }
            }

            // Horizontal loop
            for (uint hi = 0; hi < horizontal_size_; ++hi) {
                if (data_iterator != sort_data.end() && vi == data_iterator->second && hi == data_iterator->first) {
                    WriteColorToBuff(buff, color_);
                    buff += point_;

                    while (hi == data_iterator->first && vi == data_iterator->second && data_iterator != sort_data.end()) {
                        ++data_iterator;
                    }
                } else if (hi == h_zero) {
                    WriteColorToBuff(buff, axis_color_);

                    if (vi == v_zero) {
                        buff += (wchar_t)GridCode::Cross_;
                    } else {
                        buff += (wchar_t)GridCode::VLine_;
                    }
                } else {
                    if (vi == v_zero) {
                        WriteColorToBuff(buff, axis_color_);
                        buff += (wchar_t)GridCode::HLine_;
                    } else {
                        if (is_grid_) {
                            WriteColorToBuff(buff, grid_color_);
                        }
                        buff += grid_;
                    }
                }

            }

            // Right arrow
            if (vi == v_zero && is_arrow_) {
                WriteColorToBuff(buff, axis_color_);
                buff += (wchar_t)((arrow_ == Arrow::Big) ? GridCode::BigRArrow_ : GridCode::SmallRArrow_);
            }

            buff += L'\n';
        }

        uint h_pos        = (horizontal_size_ + ((is_data_header_) ? v_alignment : 0) + ((is_arrow_) ? 1 : 0));
        uint h_pos_header = 0;

        // Horizontal data header
        if (is_data_header_) {
            if (h_pos_ > 0) {
                WritePositionToBuff(buff, Position::Right, h_pos_);
            }

            WriteColorToBuff(buff, Color::Default);
            WriteSpacesToBuff(buff, v_alignment);
            h_pos_header += v_alignment;

            int count = 0;
            for (uint hi = 0; hi < horizontal_size_; ++hi) {
                const double hs = hi * h_step + h_min_;

                const uint h_alignment = (uint)(std::to_string(std::abs((int)hs)).size()
                                                + ((hs < 0) ? 1 : 0)
                                                + ((h_precision_ > 0) ? (h_precision_ + 1) : 0)
                                                + 1); // for one space

                if (count % h_alignment == 0 || hs == hs_zero) {
                    WriteDataToBuff(buff, hs, h_alignment, h_precision_);
                    h_pos_header += h_alignment;
                    count = 0;
                }

                ++count;
            }
        }

        const uint h_pos_exp = horizontal_size_ + (is_arrow_ ? 1 : 0) + (is_data_header_ ? v_alignment : 0);

        if (is_data_header_ && h_pos_header > h_pos_exp) {
            h_pos_ += h_pos_header;
        } else {
            h_pos_ += h_pos_exp;
        }

        v_pos_ = vertical_size_ + ((is_arrow_) ? 1 : 0) + ((is_data_header_) ? 1 : 0);

        WriteColorToBuff(buff, Color::Default);
        buff += L'\n';
        PrintBuff(buff);
    }

private:
    wchar_t point_;
};

} // namespace WConsole

#endif // WCONSOLE_GRAPH_H_
