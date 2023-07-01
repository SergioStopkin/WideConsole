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
#include "wideconsole/unit/console.h"

namespace WideConsole {

class IObject : public Interface {
protected:
    IObject()
    {
        if (object_counter_ == 0) {
            Console::start();
        }

        ++object_counter_;
    }

    ~IObject() override
    {
        if (object_counter_ == 1) {
            Console::end();
        }

        --object_counter_;
    }

private:
    inline static int object_counter_ = 0;

    [[nodiscard]] virtual uint headerSize() const noexcept = 0;
};

} // namespace WideConsole
