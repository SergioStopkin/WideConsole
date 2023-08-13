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

#include "wideconsole/interface/iconsoleview.h"

#include <string>

namespace WideConsole {

class ConsoleView final : public IConsoleView {
public:
    void setColor(const Color color) noexcept override { _foreground = color; }
    void setBackgroundColor(const Color color) noexcept override { _background = color; }
    void setInverseColor(const bool isInverse) noexcept override { _isInverse = isInverse; }
    void setUnderline(const bool isUnderline) noexcept override { _isUnderline = isUnderline; }

    [[nodiscard]] Color foreground() const noexcept { return _foreground; }
    [[nodiscard]] Color background() const noexcept { return _background; }
    [[nodiscard]] bool  isInverse() const noexcept { return _isInverse; }
    [[nodiscard]] bool  isUnderline() const noexcept { return _isUnderline; }

    void writeViewToBuff(std::wstring * buff) noexcept
    {
        *buff += L"\e[";

        if (_foreground == Color::Default || _background == Color::Default || _background == Color::BrightDefault) {
            *buff += L"0;";
        }

        switch (_foreground) { // clang-format off
        case Color::Black:         *buff += L"21;30"; break;
        case Color::Red:           *buff += L"21;31"; break;
        case Color::Green:         *buff += L"21;32"; break;
        case Color::Yellow:        *buff += L"21;33"; break;
        case Color::Blue:          *buff += L"21;34"; break;
        case Color::Magenta:       *buff += L"21;35"; break;
        case Color::Cyan:          *buff += L"21;36"; break;
        case Color::White:         *buff += L"21;37"; break;
        case Color::BrightBlack:   *buff += L"1;30"; break;
        case Color::BrightRed:     *buff += L"1;31"; break;
        case Color::BrightGreen:   *buff += L"1;32"; break;
        case Color::BrightYellow:  *buff += L"1;33"; break;
        case Color::BrightBlue:    *buff += L"1;34"; break;
        case Color::BrightMagenta: *buff += L"1;35"; break;
        case Color::BrightCyan:    *buff += L"1;36"; break;
        case Color::BrightWhite:   *buff += L"1;37"; break;
        case Color::BrightDefault: *buff += L";1";   break;
        default: break;
        } // clang-format on

        switch (_background) { // clang-format off
        case Color::Black:         *buff += L";40"; break;
        case Color::Red:           *buff += L";41"; break;
        case Color::Green:         *buff += L";42"; break;
        case Color::Yellow:        *buff += L";43"; break;
        case Color::Blue:          *buff += L";44"; break;
        case Color::Magenta:       *buff += L";45"; break;
        case Color::Cyan:          *buff += L";46"; break;
        case Color::White:         *buff += L";47"; break;
        case Color::BrightBlack:   *buff += L";40"; break;
        case Color::BrightRed:     *buff += L";41"; break;
        case Color::BrightGreen:   *buff += L";42"; break;
        case Color::BrightYellow:  *buff += L";43"; break;
        case Color::BrightBlue:    *buff += L";44"; break;
        case Color::BrightMagenta: *buff += L";45"; break;
        case Color::BrightCyan:    *buff += L";46"; break;
        case Color::BrightWhite:   *buff += L";47"; break;
        default: break;
        } // clang-format on

        if (_isUnderline) {
            *buff += L";4";
        } else {
            *buff += L";24";
        }

        if (_isInverse) {
            *buff += L";7";
        } else {
            *buff += L";27";
        }

        *buff += L"m";
    }

private:
    Color _foreground { Color::Default };
    Color _background { Color::Default };
    bool  _isInverse { false };
    bool  _isUnderline { false };
};

} // namespace WideConsole
