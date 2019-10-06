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

#ifndef WCONSOLE_TYPES_H_
#define WCONSOLE_TYPES_H_ 1

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
    Color foreground;
    Color background;
    bool  is_inverse;
    bool  is_underline;

    ConsoleView()
              : foreground  (Color::Default),
                background  (Color::Default),
                is_inverse  (false),
                is_underline(false) {
    }
};

struct ConsoleState {
    uint h_pos;
    uint v_pos;
    uint col_num;
    uint row_num;

    ConsoleState()
               : h_pos  (0),
                 v_pos  (0),
                 col_num(0),
                 row_num(0) {
    }
};

} // namespace WConsole

#endif // WCONSOLE_TYPES_H_
