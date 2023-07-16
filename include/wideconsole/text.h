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

#include "wideconsole/interface/itext.h"
#include "wideconsole/unit/object.h"

#include <cstring>

namespace WideConsole {

class Text final : public IText, public Object {
public:
    IConsoleView & consoleView() noexcept override { return _view; }
    void           setFont(const Font font) noexcept override { _font = font; }
    void           setConsoleView(const ConsoleView & view) noexcept override { _view = view; }

    void reset() noexcept override
    {
        _font = Font {};
        _view = ConsoleView {};
    }

    void printObject(const char * s) noexcept override
    {
        std::wstring buff;

        if (Console::globalVPos() > 0) {
            //            ChangePosition(Position::Up, Console::globalVPos());
            Console::writePositionToBuff(&buff, Position::Up, Console::globalVPos());
        }

        if (Console::globalHPos() > 0) {
            //            h_global_pos_ = Console::globalHPos();
            //            ChangePosition(Position::Right, Console::globalHPos   ());
            Console::writePositionToBuff(&buff, Position::Right, Console::globalHPos());
        }

        //        changeColor(color_);
        //        print(s);
        _view.writeViewToBuff(&buff);
        Console::print(buff);
        Console::print(s);
        Console::globalHPos(0);
        //        h_global_pos_ += std::strlen(s);
    }

    void printObject(const std::string & str) noexcept override // NOLINT(readability-convert-member-functions-to-static)
    {
        std::wstring buff;

        if (Console::globalVPos() > 0) {
            Console::writePositionToBuff(&buff, Position::Up, Console::globalVPos());
        }

        if (Console::globalHPos() > 0) {
            //            h_global_pos_ = Console::globalHPos();
            Console::writePositionToBuff(&buff, Position::Right, Console::globalHPos());
        }

        //        std::wstring shift_pos = L"\e[0;0H";
        //        buff += shift_pos;

        _view.writeViewToBuff(&buff);

        if (_font == Font::Default) {
            Console::print(buff);
            Console::print(str);
        } else {
            for (const auto & wc : str) {
                if (_font == Font::FullWidth && wc >= 0x21 && wc <= 0x7E) {
                    buff += (wc + 0xFF01 - 0x21);
                } else if (wc >= 'A' && wc <= 'Z') {
                    switch (_font) {
                    // clang-format off
                    case Font::Serif:             buff += wc;                   break;
                    case Font::SerifItal:         buff += (wc + 0x1D434 - 'A'); break;
                    case Font::SerifBold:         buff += (wc + 0x1D400 - 'A'); break;
                    case Font::SerifBoldItal:     buff += (wc + 0x1D468 - 'A'); break;
                    case Font::SansSerif:         buff += (wc + 0x1D5A0 - 'A'); break;
                    case Font::SansSerifItal:     buff += (wc + 0x1D608 - 'A'); break;
                    case Font::SansSerifBold:     buff += (wc + 0x1D5D4 - 'A'); break;
                    case Font::SansSerifBoldItal: buff += (wc + 0x1D63C - 'A'); break;
                    case Font::Monospace:         buff += (wc + 0x1D670 - 'A'); break;
                    case Font::ScriptBold:        buff += (wc + 0x1D4D0 - 'A'); break;
                    case Font::FrakturBold:       buff += (wc + 0x1D56C - 'A'); break;
                    default: break;
                    } // clang-format on
                } else if (wc >= 'a' && wc <= 'z') {
                    switch (_font) {
                    // clang-format off
                    case Font::Serif:             buff += wc;                   break;
                    case Font::SerifItal:         buff += ((wc == 'h') ? 0x1D489 : (wc + 0x1D44E - 'a')); break;
                    case Font::SerifBold:         buff += (wc + 0x1D41A - 'a'); break;
                    case Font::SerifBoldItal:     buff += (wc + 0x1D482 - 'a'); break;
                    case Font::SansSerif:         buff += (wc + 0x1D5BA - 'a'); break;
                    case Font::SansSerifItal:     buff += (wc + 0x1D622 - 'a'); break;
                    case Font::SansSerifBold:     buff += (wc + 0x1D5EE - 'a'); break;
                    case Font::SansSerifBoldItal: buff += (wc + 0x1D656 - 'a'); break;
                    case Font::Monospace:         buff += (wc + 0x1D68A - 'a'); break;
                    case Font::ScriptBold:        buff += (wc + 0x1D4EA - 'a'); break;
                    case Font::FrakturBold:       buff += (wc + 0x1D586 - 'a'); break;
                    default: break;
                    } // clang-format on
                } else if (wc >= '0' && wc <= '9') {
                    switch (_font) {
                    // clang-format off
                    case Font::Serif:
                    case Font::SerifItal:
                    case Font::SerifBoldItal:
                    case Font::SansSerifItal:
                    case Font::SansSerifBoldItal:
                    case Font::ScriptBold:
                    case Font::FrakturBold:       buff += wc;                   break;
                    case Font::SerifBold:         buff += (wc + 0x1D7CE - '0'); break;
                    case Font::SansSerif:         buff += (wc + 0x1D7E2 - '0'); break;
                    case Font::SansSerifBold:     buff += (wc + 0x1D7EC - '0'); break;
                    case Font::Monospace:         buff += (wc + 0x1D7F6 - '0'); break;
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
    Font        _font { Font::Monospace };
    ConsoleView _view {};
};

} // namespace WideConsole
