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

#include "wconsole/interface/iprecision2d.h"

namespace WConsole {

class Precision2D final : public IPrecision2D {
public:
    void              setVerticalPrecision(const int v_precision) noexcept override { v_precision_ = v_precision; }
    void              setHorizontalPrecision(const int h_precision) noexcept override { h_precision_ = h_precision; }
    [[nodiscard]] int verticalPrecision() const noexcept { return v_precision_; }
    [[nodiscard]] int horizontalPrecision() const noexcept { return h_precision_; }

private:
    int h_precision_ { 1 };
    int v_precision_ { 1 };
};

} // namespace WConsole
