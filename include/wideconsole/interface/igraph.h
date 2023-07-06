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

#include "wideconsole/interface/idraw.h"
#include "wideconsole/interface/iprecision2d.h"
#include "wideconsole/type/point.h"

namespace WideConsole {

class IGraph : public IDraw {
public:
    virtual IPrecision2D & precision() noexcept                = 0;
    virtual void           setPoint(Point point) noexcept      = 0;
    virtual void           setPointColor(Color color) noexcept = 0;
};

} // namespace WideConsole
