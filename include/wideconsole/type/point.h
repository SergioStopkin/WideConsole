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

namespace WideConsole {

enum class Point : wchar_t {
    Dot           = 0x2022, // 0x2981
    Triangle      = 0x25B2,
    SmallTriangle = 0x25B4,
    Rhombus       = 0x25C6,
    SmallSquare   = 0x25FE,
    Star          = 0x2605,
    Clover        = 0x2618,
    Scythe        = 0x262D,
    YinYang       = 0x262F,
    Smile         = 0x263B,
    SpadeSuit     = 0x2660,
    ClubSuit      = 0x2663,
    HeartSuit     = 0x2665,
    DiamondSuit   = 0x2666,
    Flag          = 0x2691,
    Flower        = 0x2698,
    Zeus          = 0x26A1,
    CheckMarkItal = 0x2714,
    CrossX        = 0x2716,
    CrossXItal    = 0x2718,
    Cross         = 0x271A,
    StarInCircle  = 0x272A,
    Asterisk      = 0x2731,
    BigCrossX     = 0x274C,
    Heart         = 0x2764,
    Square        = 0x2B1B,
    Pentagon      = 0x2B1F,
    Hexagon       = 0x2B22,
    Circle        = 0x2B24,
    SmallRhombus  = 0x2B25,
    Beaver        = 0xF800,
};

inline wchar_t wchar(const Point point) { return static_cast<wchar_t>(point); }

} // namespace WideConsole
