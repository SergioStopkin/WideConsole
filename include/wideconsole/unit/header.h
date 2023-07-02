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

#include "wideconsole/interface/iheader.h"
#include "wideconsole/type/dataposition.h"

#include <iomanip>
#include <sstream>
#include <typeinfo>

namespace WideConsole {

class Header final : public IHeader {
public:
    void setDataPosition(const DataPosition pos) noexcept override { _dataPos = pos; }
    void showDataHeader(const bool show) noexcept override { _isDataHeader = show; }

    [[nodiscard]] bool         isDataHeader() const noexcept { return _isDataHeader; }
    [[nodiscard]] DataPosition dataPosition() const noexcept { return _dataPos; }
    [[nodiscard]] uint         size() const noexcept { return _headerSize; }

    template <typename T>
    void writeDataToBuff(std::wstring * buff, T value, uint alignment, int precision) noexcept
    {
        std::wstring wvalue;
        _headerSize = alignment;

        if (typeid(value) == typeid(float) || typeid(value) == typeid(double) || typeid(value) == typeid(long double)) {
            std::wstringstream wsstream;
            wsstream << std::fixed << std::setprecision(precision) << value;
            wvalue = wsstream.str();
        } else {
            wvalue = std::to_wstring(value);
        }

        const auto str_len = static_cast<uint>(wvalue.length());
        uint       diff    = 0;

        if (alignment > str_len) {
            switch (_dataPos) {
            case DataPosition::Left: diff = alignment - str_len; break;
            case DataPosition::Right:
                diff = 0; // alignment - str_len - (alignment - str_len);
                buff->append(alignment - str_len, ' ');
                break;
            case DataPosition::Center:
                diff = alignment - str_len - ((alignment - str_len) / 2);
                buff->append(((alignment - str_len) / 2), ' ');
                break;
            }
        }

        *buff += wvalue;

        if (alignment > str_len) {
            buff->append(diff, ' ');
        }
    }

private:
    bool         _isDataHeader { true };
    DataPosition _dataPos { DataPosition::Center };
    uint         _headerSize { 0 };
};

} // namespace WideConsole
