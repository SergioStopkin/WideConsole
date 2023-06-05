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
#include "types.h"

#include <utility>
#include <vector>

namespace WConsole {

class IObject {
public:
    void setSize(const uint horizontal_size, const uint vertical_size) noexcept
    {
        horizontal_size_ = horizontal_size;
        vertical_size_   = vertical_size;
    }

protected:
    uint horizontal_size_;
    uint vertical_size_;

    explicit IObject(const uint horizontal_size = 22, const uint vertical_size = 11)
        : horizontal_size_(horizontal_size)
        , vertical_size_(vertical_size)
    {
        if (object_counter_ == 0) {
            Console::start();
        }

        ++object_counter_;
    }

    virtual ~IObject()
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

} // namespace WConsole
