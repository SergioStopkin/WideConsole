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

#include "wideconsole/interface/interface.h"
#include "wideconsole/type/font.h"
#include "wideconsole/unit/consoleview.h"

#include <string>

namespace WideConsole {

class IText : public Interface {
public:
    virtual void setFont(Font font) noexcept                       = 0;
    virtual void setConsoleView(const ConsoleView & view) noexcept = 0;
    virtual void reset() noexcept                                  = 0;
    virtual void printObject(const char * s) noexcept              = 0;
    virtual void printObject(const std::string & str) noexcept     = 0;

    [[nodiscard]] virtual IConsoleView & consoleView() noexcept = 0;
};

} // namespace WideConsole
