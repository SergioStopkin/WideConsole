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

#include "wconsole/interface/interface.h"
#include "wconsole/type/base.h"

namespace WConsole {

class IConsoleState : public Interface {
public:
    virtual void setHPos(uint hPos) noexcept       = 0;
    virtual void setVPos(uint vPos) noexcept       = 0;
    virtual void setMaxVPos(uint maxVPos) noexcept = 0;
    virtual void setColNum(uint colNum) noexcept   = 0;
    virtual void setRowNum(uint rowNum) noexcept   = 0;
};

} // namespace WConsole
