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

#include "console.h"
#include "font.h"
#include "iobject.h"

#include <cstring>

namespace WConsole {

class Text final : public IObject {
public:
    explicit Text(const FontType & font_type = FontType::Monospace)
        : font_(font_type)
    {
    }

    void setColor(const Color & color) noexcept { font_.setForegroundColor(color); }

    void setFont(const Font & font) noexcept { font_ = font; }

    void resetFont() noexcept { font_ = Font(); }

    void printObject(const char * s) noexcept
    {
        std::wstring buff;

        if (Console::globalVPos() > 0) {
            //            ChangePosition(Position::Up, Console::globalVPos());
            Console::writePositionToBuff(buff, Position::Up, Console::globalVPos());
        }

        if (Console::globalHPos() > 0) {
            //            h_global_pos_ = Console::globalHPos();
            //            ChangePosition(Position::Right, Console::globalHPos   ());
            Console::writePositionToBuff(buff, Position::Right, Console::globalHPos());
        }

        //        changeColor(color_);
        //        print(s);
        Console::writeViewToBuff(buff, font_.consoleView());
        Console::print(buff);
        Console::print(s);
        Console::globalHPos(0);
        //        h_global_pos_ += std::strlen(s);
    }

    void printObject(const std::string & str) noexcept { printObject(str, font_); }

    void printObject(const std::string & str, const Font & font) noexcept
    {
        std::wstring buff;

        if (Console::globalVPos() > 0) {
            Console::writePositionToBuff(buff, Position::Up, Console::globalVPos());
        }

        if (Console::globalHPos() > 0) {
            //            h_global_pos_ = Console::globalHPos();
            Console::writePositionToBuff(buff, Position::Right, Console::globalHPos());
        }

        //        std::wstring shift_pos = L"\e[0;0H";
        //        buff += shift_pos;

        Console::writeViewToBuff(buff, font.consoleView());

        if (font.fontType() == FontType::Default) {
            Console::print(buff);
            Console::print(str);
        } else {
            for (auto & wc : str) {
                if (font.fontType() == FontType::FullWidth && wc >= 0x21 && wc <= 0x7E) {
                    buff += (wc + 0xFF01 - 0x21);
                } else if (wc >= 'A' && wc <= 'Z') {
                    switch (font.fontType()) {
                    // clang-format off
                    case FontType::Serif:             buff += wc;                   break;
                    case FontType::SerifItal:         buff += (wc + 0x1D434 - 'A'); break;
                    case FontType::SerifBold:         buff += (wc + 0x1D400 - 'A'); break;
                    case FontType::SerifBoldItal:     buff += (wc + 0x1D468 - 'A'); break;
                    case FontType::SansSerif:         buff += (wc + 0x1D5A0 - 'A'); break;
                    case FontType::SansSerifItal:     buff += (wc + 0x1D608 - 'A'); break;
                    case FontType::SansSerifBold:     buff += (wc + 0x1D5D4 - 'A'); break;
                    case FontType::SansSerifBoldItal: buff += (wc + 0x1D63C - 'A'); break;
                    case FontType::Monospace:         buff += (wc + 0x1D670 - 'A'); break;
                    case FontType::ScriptBold:        buff += (wc + 0x1D4D0 - 'A'); break;
                    case FontType::FrakturBold:       buff += (wc + 0x1D56C - 'A'); break;
                    default: break;
                    } // clang-format on
                } else if (wc >= 'a' && wc <= 'z') {
                    switch (font.fontType()) {
                    // clang-format off
                    case FontType::Serif:             buff += wc;                   break;
                    case FontType::SerifItal:         buff += ((wc == 'h') ? 0x1D489 : (wc + 0x1D44E - 'a')); break;
                    case FontType::SerifBold:         buff += (wc + 0x1D41A - 'a'); break;
                    case FontType::SerifBoldItal:     buff += (wc + 0x1D482 - 'a'); break;
                    case FontType::SansSerif:         buff += (wc + 0x1D5BA - 'a'); break;
                    case FontType::SansSerifItal:     buff += (wc + 0x1D622 - 'a'); break;
                    case FontType::SansSerifBold:     buff += (wc + 0x1D5EE - 'a'); break;
                    case FontType::SansSerifBoldItal: buff += (wc + 0x1D656 - 'a'); break;
                    case FontType::Monospace:         buff += (wc + 0x1D68A - 'a'); break;
                    case FontType::ScriptBold:        buff += (wc + 0x1D4EA - 'a'); break;
                    case FontType::FrakturBold:       buff += (wc + 0x1D586 - 'a'); break;
                    default: break;
                    } // clang-format on
                } else if (wc >= '0' && wc <= '9') {
                    switch (font.fontType()) {
                    // clang-format off
                    case FontType::Serif:             buff += wc;                   break;
                    case FontType::SerifItal:         buff += wc;                   break;
                    case FontType::SerifBoldItal:     buff += wc;                   break;
                    case FontType::SansSerifItal:     buff += wc;                   break;
                    case FontType::SansSerifBoldItal: buff += wc;                   break;
                    case FontType::ScriptBold:        buff += wc;                   break;
                    case FontType::FrakturBold:       buff += wc;                   break;
                    case FontType::SerifBold:         buff += (wc + 0x1D7CE - '0'); break;
                    case FontType::SansSerif:         buff += (wc + 0x1D7E2 - '0'); break;
                    case FontType::SansSerifBold:     buff += (wc + 0x1D7EC - '0'); break;
                    case FontType::Monospace:         buff += (wc + 0x1D7F6 - '0'); break;
                    default: break;
                    } // clang-format on
                } else {
                    buff += wc;
                }
            }
            Console::print(buff);
        }

        //        Console::globalVPos() = 0;
        //        Console::globalHPos() = 0;
        //        h_global_pos_ += str.length();
    }

private:
    Font font_;

    [[nodiscard]] uint headerSize() const noexcept override { return 0; }
};

} // namespace WConsole
