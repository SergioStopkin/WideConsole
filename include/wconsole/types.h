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

using uchar = unsigned char;
using uint  = unsigned int;

enum class Color : uchar {
    Black,
    Red,
    Green,
    Yellow,
    Blue,
    Magenta,
    Cyan,
    White,
    BrightBlack,
    BrightRed,
    BrightGreen,
    BrightYellow,
    BrightBlue,
    BrightMagenta,
    BrightCyan,
    BrightWhite,
    Default,
    BrightDefault
};

struct ConsoleView {
    Color foreground { Color::Default };
    Color background { Color::Default };
    bool  is_inverse { false };
    bool  is_underline { false };
} __attribute__((packed)) __attribute__((aligned(4)));

struct ConsoleState {
    uint h_pos { 0 };
    uint v_pos { 0 };
    uint max_v_pos { 0 };
    uint col_num { 0 };
    uint row_num { 0 };
} __attribute__((packed)) __attribute__((aligned(32)));

// template<typename T>
// static uint integerPartSize(T value)
// {
//     return static_cast<uint>(std::to_string(static_cast<int>(value)).size());
// }

} // namespace WConsole
