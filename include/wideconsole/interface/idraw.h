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
#include "wideconsole/interface/iheader.h"
#include "wideconsole/interface/interface.h"
#include "wideconsole/interface/irange.h"
#include "wideconsole/interface/isize.h"

namespace WideConsole {

class IDraw : public Interface {
public:
    virtual IGrid &   grid() noexcept   = 0;
    virtual IHeader & header() noexcept = 0;
    virtual IRange &  range() noexcept  = 0;
    virtual ISize &   size() noexcept   = 0;
};

} // namespace WideConsole
