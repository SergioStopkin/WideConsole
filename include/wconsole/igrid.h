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

#pragma once

#include "types.h"

namespace WConsole {

class IGrid {
public:
    enum class Arrow : uchar { Big, Small };

    void SetAxisColor(const Color color) noexcept { axis_color_ = color; }

    void SetGridColor(const Color color) noexcept { grid_color_ = color; }

    void SetArrow(const Arrow arrow) noexcept { arrow_ = arrow; }

    void ShowArrow(const bool show) noexcept { is_arrow_ = show; }

    void ShowGrid(const bool show) noexcept
    {
        is_grid_ = show;
        grid_    = ((show) ? (wchar_t)GridCode::SmallDot_ : ' ');
    }

protected:
    enum class GridCode : wchar_t {
        SmallUArrow_ = 0x25B4,
        SmallRArrow_ = 0x25B8,
        SmallDArrow_ = 0x25BE,
        SmallLArrow_ = 0x25C2,
        BigUArrow_   = 0x25B2,
        BigRArrow_   = 0x25B6,
        BigDArrow_   = 0x25BC,
        BigLArrow_   = 0x25C0,
        VLine_       = 0x2502,
        HLine_       = 0x2500,
        Cross_       = 0x253C,
        LUCorner_    = 0x250C,
        RUCorner_    = 0x2510,
        LDCorner_    = 0x2514,
        RDCorner_    = 0x2518,
        LT_          = 0x251C,
        RT_          = 0x2524,
        UT_          = 0x252C,
        DT_          = 0x2534,
        SmallDot_    = 0x00b7, // 0x0387
    };

    Color   axis_color_;
    Color   grid_color_;
    Arrow   arrow_;
    wchar_t grid_;
    bool    is_arrow_;
    bool    is_grid_;

    explicit IGrid(const Color axis_color = Color::Default,
                   const Color grid_color = Color::White,
                   const Arrow arrow      = Arrow::Small,
                   const bool  show_arrow = true,
                   const bool  show_grid  = true)
        : axis_color_(axis_color)
        , grid_color_(grid_color)
        , arrow_(arrow)
        , is_arrow_(show_arrow)
    {
        ShowGrid(show_grid);
    }

    virtual ~IGrid() = default;
};

} // namespace WConsole
