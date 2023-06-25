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

#include "wconsole/interface/igrid.h"
#include "wconsole/type/gridcode.h"

namespace WConsole {

class Grid final : public IGrid {
public:
    void setAxisColor(const Color color) noexcept override { axis_color_ = color; }

    void setGridColor(const Color color) noexcept override { grid_color_ = color; }

    void setArrow(const Arrow arrow) noexcept override { arrow_ = arrow; }

    void showArrow(const bool show) noexcept override { is_arrow_ = show; }

    void showGrid(const bool show) noexcept override
    {
        is_grid_ = show;
        grid_    = (show ? static_cast<wchar_t>(GridCode::SmallDot_) : ' ');
    }

    [[nodiscard]] Color   axisColor() const noexcept { return axis_color_; }
    [[nodiscard]] Color   gridColor() const noexcept { return grid_color_; }
    [[nodiscard]] Arrow   arrow() const noexcept { return arrow_; }
    [[nodiscard]] wchar_t grid() const noexcept { return grid_; }
    [[nodiscard]] bool    isArrow() const noexcept { return is_arrow_; }
    [[nodiscard]] bool    isGrid() const noexcept { return is_grid_; }

    // explicit Grid(const Color axis_color = Color::Default, // NOLINT(cppcoreguidelines-pro-type-member-init, hicpp-member-init)
    //                const Color grid_color = Color::White,
    //                const Arrow arrow      = Arrow::Small,
    //                const bool  show_arrow = true,
    //                const bool  show_grid  = true)
    //     : axis_color_(axis_color)
    //     , grid_color_(grid_color)
    //     , arrow_(arrow)
    //     , is_arrow_(show_arrow)
    // {
    //     showGrid(show_grid);
    // }

    // ~Grid() override = default;

private:
    Color   axis_color_ { Color::Default };
    Color   grid_color_ { Color::White };
    Arrow   arrow_ { Arrow::Small };
    wchar_t grid_ { static_cast<wchar_t>(GridCode::SmallDot_) };
    bool    is_arrow_ { true };
    bool    is_grid_ { true };
};

} // namespace WConsole
