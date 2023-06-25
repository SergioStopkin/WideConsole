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

#include "wconsole/interface/iconsolestate.h"

namespace WConsole {

class ConsoleState final : public IConsoleState {
public:
    void setHPos(const uint hPos) noexcept override { _hPos = hPos; }
    void setVPos(const uint vPos) noexcept override { _vPos = vPos; }
    void setMaxVPos(const uint maxVPos) noexcept override { _maxVPos = maxVPos; }
    void setColNum(const uint colNum) noexcept override { _colNum = colNum; }
    void setRowNum(const uint rowNum) noexcept override { _rowNum = rowNum; }

    [[nodiscard]] uint hPos() const noexcept { return _hPos; }
    [[nodiscard]] uint vPos() const noexcept { return _vPos; }
    [[nodiscard]] uint maxVPos() const noexcept { return _maxVPos; }
    [[nodiscard]] uint colNum() const noexcept { return _colNum; }
    [[nodiscard]] uint rowNum() const noexcept { return _rowNum; }

private:
    uint _hPos { 0 };
    uint _vPos { 0 };
    uint _maxVPos { 0 };
    uint _colNum { 0 };
    uint _rowNum { 0 };
};

} // namespace WConsole
