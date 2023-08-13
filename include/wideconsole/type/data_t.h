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

#include <concepts>
#include <utility>
#include <vector>

namespace WideConsole {

template <typename T>
struct is_character : std::integral_constant<bool,
                                             std::is_same<char, typename std::remove_cv<T>::type>::value
                                             || std::is_same<signed char, typename std::remove_cv<T>::type>::value
                                             || std::is_same<unsigned char, typename std::remove_cv<T>::type>::value
                                             || std::is_same<wchar_t, typename std::remove_cv<T>::type>::value
                                             || std::is_same<char8_t, typename std::remove_cv<T>::type>::value
                                             || std::is_same<char16_t, typename std::remove_cv<T>::type>::value
                                             || std::is_same<char32_t, typename std::remove_cv<T>::type>::value> {
};

template <typename T>
concept Data_t = !is_character<T>::value && !std::is_same<bool, T>::value && std::is_arithmetic<T>::value;

#define Data1D_t std::vector<Data_t auto>
#define Data2D_t std::vector<std::pair<Data_t auto, Data_t auto>>

} // namespace WideConsole
