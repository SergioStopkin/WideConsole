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

#ifndef WCONSOLE_IPRINT_H_
#define WCONSOLE_IPRINT_H_ 1

#include <string>

#include "types.h"

namespace WConsole {

class IPrint {
protected:
    IPrint() = default;

    virtual ~IPrint() = default;

    void Print(const char * str) const noexcept {
        wprintf(L"%s", str);
    }

    void Print(const std::string & str) const noexcept {
        wprintf(L"%s", str.c_str());
    }

    void WriteNToBuff(std::wstring & buff, const wchar_t wc, const uint number) const noexcept {
        for (uint i = 0; i < number; ++i) {
            buff += wc;
        }
    }

    void WriteSpacesToBuff(std::wstring & buff, const uint number) const noexcept {
        for (uint i = 0; i < number; ++i) {
            buff += L' ';
        }
    }
};

}; // namespace WConsole

#endif // WCONSOLE_IPRINT_H_
