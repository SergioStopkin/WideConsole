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

#include "wconsole/interface/irange.h"

#include <algorithm>

namespace WConsole {

class Range final : public IRange {
public:
    void setVerticalRange(const double v_min, const double v_max) noexcept override
    {
        v_min_ = std::min(v_min, v_max);
        v_max_ = std::max(v_min, v_max);
    }
    void setHorizontalRange(const double h_min, const double h_max) noexcept override
    {
        h_min_ = std::min(h_min, h_max);
        h_max_ = std::max(h_min, h_max);
    }

    [[nodiscard]] double verticalMin() const noexcept { return v_min_; }
    [[nodiscard]] double verticalMax() const noexcept { return v_max_; }
    [[nodiscard]] double horizontalMin() const noexcept { return h_min_; }
    [[nodiscard]] double horizontalMax() const noexcept { return h_max_; }

private:
    double v_min_ { 0 };
    double v_max_ { 100 };
    double h_min_ { 0 };
    double h_max_ { 100 };
};

} // namespace WConsole
