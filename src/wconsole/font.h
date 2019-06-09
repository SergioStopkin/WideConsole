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

#ifndef WCONSOLE_FONT_H_
#define WCONSOLE_FONT_H_ 1

#include "types.h"

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

class Font final {
public:
    explicit Font(const FontType & font_type = FontType::Monospace)
        : font_type_   (font_type),
          foreground_  (Color::Default),
          background_  (Color::Default),
          is_inverse_  (false),
          is_underline_(false) {}

    void SetFontType(const FontType & font_type) noexcept {
        font_type_ = font_type;
    }

    void SetForegroundColor(const Color & color) noexcept {
        foreground_ = color;
    }

    void SetBackgroundColor(const Color & color) noexcept {
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

} // namespace WConsole

#endif // WCONSOLE_FONT_H_
