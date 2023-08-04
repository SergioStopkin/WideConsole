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

namespace WideConsole {

enum class BrickCode : wchar_t {
    FF_OP100_ = 0x2588, // upper full,  last full,  opacity 100%
    FF_OP75_  = 0x2593, // upper full,  last full,  opacity 75%
    FF_OP50_  = 0x2592, // upper full,  last full,  opacity 50%
    FF_OP25_  = 0x2591, // upper full,  last full,  opacity 25%
    FS_       = 0x258C, // upper full,  last small
    FSI_      = 0x2590, // upper full,  last small, inverse
    SF_       = 0x2584, // upper small, last full
    SFI_      = 0x2580, // upper small, last full,  inverse
};

inline wchar_t wchar(const BrickCode brick) { return static_cast<wchar_t>(brick); }

} // namespace WideConsole
