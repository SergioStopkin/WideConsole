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

#include <algorithm>

namespace WConsole {

class IRange {
public:
    void SetVerticalRange(const double v_min, const double v_max) noexcept
    {
        v_min_ = std::min(v_min, v_max);
        v_max_ = std::max(v_min, v_max);
    }

    void SetHorizontalRange(const double h_min, const double h_max) noexcept
    {
        h_min_ = std::min(h_min, h_max);
        h_max_ = std::max(h_min, h_max);
    }

protected:
    explicit IRange(const double v_min = 0, const double v_max = 100, const double h_min = 0, const double h_max = 100)
        : v_min_(v_min)
        , v_max_(v_max)
        , h_min_(h_min)
        , h_max_(h_max)
    {
    }

    virtual ~IRange() = default;

    double v_min_;
    double v_max_;
    double h_min_;
    double h_max_;
};

} // namespace WConsole
