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

#include "wideconsole/interface/igrid.h"
#include "wideconsole/type/gridcode.h"

namespace WideConsole {

class Grid final : public IGrid {
public:
    void setAxisColor(const Color color) noexcept override { axis_color_ = color; }
    void setGridColor(const Color color) noexcept override { grid_color_ = color; }
    void setArrow(const Arrow arrow) noexcept override { arrow_ = arrow; }
    void showArrow(const bool show) noexcept override { is_arrow_ = show; }
    void showGrid(const bool show) noexcept override
    {
        is_grid_ = show;
        grid_    = (show ? wchar(GridCode::SmallDot_) : ' ');
    }

    [[nodiscard]] Color   axisColor() const noexcept { return axis_color_; }
    [[nodiscard]] Color   gridColor() const noexcept { return grid_color_; }
    [[nodiscard]] Arrow   arrow() const noexcept { return arrow_; }
    [[nodiscard]] wchar_t grid() const noexcept { return grid_; }
    [[nodiscard]] bool    isArrow() const noexcept { return is_arrow_; }
    [[nodiscard]] bool    isGrid() const noexcept { return is_grid_; }

private:
    Color   axis_color_ { Color::Default };
    Color   grid_color_ { Color::White };
    Arrow   arrow_ { Arrow::Small };
    wchar_t grid_ { wchar(GridCode::SmallDot_) };
    bool    is_arrow_ { true };
    bool    is_grid_ { true };
};

} // namespace WideConsole
