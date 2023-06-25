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

namespace WConsole {

enum class GridCode : wchar_t {
    SmallUArrow_ = 0x25B4,
    SmallRArrow_ = 0x25B8,
    SmallDArrow_ = 0x25BE,
    SmallLArrow_ = 0x25C2,
    BigUArrow_   = 0x25B2,
    BigRArrow_   = 0x25B6,
    BigDArrow_   = 0x25BC,
    BigLArrow_   = 0x25C0,
    VLine_       = 0x2502,
    HLine_       = 0x2500,
    Cross_       = 0x253C,
    LUCorner_    = 0x250C,
    RUCorner_    = 0x2510,
    LDCorner_    = 0x2514,
    RDCorner_    = 0x2518,
    LT_          = 0x251C,
    RT_          = 0x2524,
    UT_          = 0x252C,
    DT_          = 0x2534,
    SmallDot_    = 0x00b7, // 0x0387
};

} // namespace WConsole
