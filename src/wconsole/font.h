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

enum class FontType : uchar {
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
    explicit Font(const FontType    & font_type = FontType::Monospace,
                  const ConsoleView & view      = ConsoleView())
                : font_type_(font_type),
                  view_     (view) {
    }

    void SetFontType(const FontType & font_type) noexcept {
        font_type_ = font_type;
    }

    void SetForegroundColor(const Color & color) noexcept {
        view_.foreground = color;
    }

    void SetBackgroundColor(const Color & color) noexcept {
        view_.background = color;
    }

    void SetInverseColor(const bool is_inverse) noexcept {
        view_.is_inverse = is_inverse;
    }

    void SetUnderline(const bool is_underline) noexcept {
        view_.is_underline = is_underline;
    }

    FontType GetFontType() const noexcept {
        return font_type_;
    }

    ConsoleView GetConsoleState() const noexcept {
        return view_;
    }

private:
    FontType    font_type_;
    ConsoleView view_;
};

} // namespace WConsole

#endif // WCONSOLE_FONT_H_
