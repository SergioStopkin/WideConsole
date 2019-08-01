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

#ifndef WCONSOLE_TEXT_H_
#define WCONSOLE_TEXT_H_ 1

#include <cstring>

#include "console.h"
#include "font.h"
#include "iobject.h"

namespace WConsole {

class Text final : public IObject {
public:
    explicit Text(const FontType & font_type = FontType::Monospace)
                : font_  (font_type) {
    }

    void SetColor(const Color & color) noexcept {
        font_.SetForegroundColor(color);
    }

    void SetFont(const Font & font) noexcept {
        font_ = font;
    }

    void ResetFont() noexcept {
        font_ = Font();
    }

    void PrintObject(const char * s) noexcept {
        std::wstring buff;

        if (Console::GlobalVPos() > 0) {
//            ChangePosition(Position::Up, Console::GlobalVPos());
            Console::WritePositionToBuff(buff, Position::Up, Console::GlobalVPos());
        }

        if (Console::GlobalHPos() > 0) {
//            h_global_pos_ = Console::GlobalHPos();
//            ChangePosition(Position::Right, Console::GlobalHPos());
            Console::WritePositionToBuff(buff, Position::Right, Console::GlobalHPos());
        }

//        ChangeColor(color_);
//        Print(s);
        Console::WriteStateToBuff(buff, font_.GetConsoleView());
        Console::Print(buff);
        Console::Print(s);
        Console::GlobalHPos(0);
//        h_global_pos_ += std::strlen(s);
    }

    void PrintObject(const std::string & str) noexcept {
        PrintObject(str, font_);
    }

    void PrintObject(const std::string & str, const Font & font) noexcept {
        std::wstring buff;

        if (Console::GlobalVPos() > 0) {
            Console::WritePositionToBuff(buff, Position::Up, Console::GlobalVPos());
        }

        if (Console::GlobalHPos() > 0) {
//            h_global_pos_ = Console::GlobalHPos();
            Console::WritePositionToBuff(buff, Position::Right, Console::GlobalHPos());
        }

//        std::wstring shift_pos = L"\e[0;0H";
//        buff += shift_pos;

        Console::WriteStateToBuff(buff, font.GetConsoleView());

        for (auto & wc : str) {
            if (font.GetFontType() == FontType::FullWidth && wc >= 0x21 && wc <= 0x7E) {
                buff += (wc + 0xFF01 - 0x21);
            } else if (wc >= 'A' && wc <= 'Z') {
                switch (font.GetFontType()) {
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
                }
            } else if (wc >= 'a' && wc <= 'z') {
                switch (font.GetFontType()) {
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
                }
            } else if (wc >= '0' && wc <= '9') {
                switch (font.GetFontType()) {
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
                }
            } else {
                buff += wc;
            }
        }

        Console::Print(buff);

//        Console::GlobalVPos() = 0;
//        Console::GlobalHPos() = 0;
//        h_global_pos_ += str.length();
    }

private:
    Font font_;

    uint HeaderSize() const noexcept override {
        return 0;
    }
};

} // namespace WConsole

#endif // WCONSOLE_TEXT_H_
