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

#include "wideconsole/interface/isize.h"
#include "wideconsole/unit/console.h"

#include <utility>
#include <vector>

namespace WideConsole {

class Size final : public ISize {
public:
    void setSize(const uint horizontal, const uint vertical) noexcept override
    {
        _horizontal = horizontal;
        _vertical   = vertical;
    }

    [[nodiscard]] uint horizontal() const noexcept { return _horizontal; }
    [[nodiscard]] uint vertical() const noexcept { return _vertical; }

private:
    uint _horizontal { 22 };
    uint _vertical { 11 };
};

} // namespace WideConsole
