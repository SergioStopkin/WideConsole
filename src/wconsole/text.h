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

#include "iwconsole.h"

namespace WConsole {

enum class FontType {
    Serif,
    SerifItal,
    SerifBold,
    SerifBoldItal,
    SansSerif,
    SansSerifItal,
    SansSerifBold,
    SansSerifBoldItal,
    Monospace,
    ScriptBold,
    FrakturBold,
    FullWidth,
};

class Font {
public:
    explicit Font()
                : font_type_   (FontType::Monospace),
                  foreground_  (Color::Default),
                  background_  (Color::Default),
                  is_inverse_  (false),
                  is_underline_(false) {}

    void SetFontType(const FontType font_type) noexcept {
        font_type_ = font_type;
    }

    void SetForegroundColor(const Color color) noexcept {
        foreground_ = color;
    }

    void SetBackgroundColor(const Color color) noexcept {
        background_ = color;
    }

    void SetInverseColor(const bool is_inverse) noexcept {
        is_inverse_ = is_inverse;
    }

    void SetUnderline(const bool is_underline) noexcept {
        is_underline_ = is_underline;
    }

    FontType GetFontType() const noexcept {
        return font_type_;
    }

    void WriteParametersToBuff(std::wstring & buff) const noexcept {
        buff += L"\e[";

        if (foreground_ == Color::Default || background_ == Color::Default || background_ == Color::BrightDefault) {
            buff += L"0;";
        }

        switch (foreground_) {
            case Color::Black:         buff += L"21;30"; break;
            case Color::Red:           buff += L"21;31"; break;
            case Color::Green:         buff += L"21;32"; break;
            case Color::Yellow:        buff += L"21;33"; break;
            case Color::Blue:          buff += L"21;34"; break;
            case Color::Magenta:       buff += L"21;35"; break;
            case Color::Cyan:          buff += L"21;36"; break;
            case Color::White:         buff += L"21;37"; break;
            case Color::BrightBlack:   buff += L"1;30"; break;
            case Color::BrightRed:     buff += L"1;31"; break;
            case Color::BrightGreen:   buff += L"1;32"; break;
            case Color::BrightYellow:  buff += L"1;33"; break;
            case Color::BrightBlue:    buff += L"1;34"; break;
            case Color::BrightMagenta: buff += L"1;35"; break;
            case Color::BrightCyan:    buff += L"1;36"; break;
            case Color::BrightWhite:   buff += L"1;37"; break;
            case Color::BrightDefault: buff += L";1";   break;
            default: break;
        }

        switch (background_) {
            case Color::Black:         buff += L";40"; break;
            case Color::Red:           buff += L";41"; break;
            case Color::Green:         buff += L";42"; break;
            case Color::Yellow:        buff += L";43"; break;
            case Color::Blue:          buff += L";44"; break;
            case Color::Magenta:       buff += L";45"; break;
            case Color::Cyan:          buff += L";46"; break;
            case Color::White:         buff += L";47"; break;
            case Color::BrightBlack:   buff += L";40"; break;
            case Color::BrightRed:     buff += L";41"; break;
            case Color::BrightGreen:   buff += L";42"; break;
            case Color::BrightYellow:  buff += L";43"; break;
            case Color::BrightBlue:    buff += L";44"; break;
            case Color::BrightMagenta: buff += L";45"; break;
            case Color::BrightCyan:    buff += L";46"; break;
            case Color::BrightWhite:   buff += L";47"; break;
            default: break;
        }

        if (is_underline_) {
            buff += L";4";
        } else {
            buff += L";24";
        }

        if (is_inverse_) {
            buff += L";7";
        } else {
            buff += L";27";
        }

        buff += L"m";
    }

private:
    FontType font_type_;
    Color    foreground_;
    Color    background_;
    bool     is_inverse_;
    bool     is_underline_;
};

class Text final : public IWConsole {
public:
    Font font;

    explicit Text() {
    }

    void PrintText(const char * str) noexcept {
        if (v_pos_ > 0) {
            ChangePosition(Position::Up, v_pos_);
        }

        if (h_pos_ > 0) {
            h_global_pos_ = h_pos_;
            ChangePosition(Position::Right, h_pos_);
        }

        ChangeColor(color_);
        Print(str);
        h_pos_ = 0;
        h_global_pos_ += std::strlen(str);
    }

    void PrintText(const std::string & str) noexcept {
        PrintText(str, font);
    }

    void PrintText(const std::string & str, const Font font) noexcept {
        std::wstring buff;

        if (v_pos_ > 0) {
            WritePositionToBuff(buff, Position::Up, v_pos_);
        }

        if (h_pos_ > 0) {
            h_global_pos_ = h_pos_;
            WritePositionToBuff(buff, Position::Right, h_pos_);
        }

//        std::wstring shift_pos = L"\e[0;0H";
//        buff += shift_pos;

        font.WriteParametersToBuff(buff);

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

        Print(buff);

        v_pos_ = 0;
        h_pos_ = 0;
//        h_global_pos_ += str.length();
    }
};

} // namespace WConsole

#endif // WCONSOLE_TEXT_H_
