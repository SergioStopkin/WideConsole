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

#ifndef WCONSOLE_IPRECISION_H_
#define WCONSOLE_IPRECISION_H_ 1

namespace WConsole {

class IPrecisionP1 {
public:
    void SetPrecision(const int precision) noexcept {
        precision_ = precision;
    }

protected:
    int precision_;

    explicit IPrecisionP1 (const int precision = 1)
                         : precision_(precision) {}

    virtual ~IPrecisionP1() = default;
};

class IPrecisionP2 {
public:
    void SetVerticalPrecision(const int v_precision) noexcept {
        v_precision_ = v_precision;
    }

    void SetHorizontalPrecision(const int h_precision) noexcept {
        h_precision_ = h_precision;
    }

protected:
    int h_precision_;
    int v_precision_;

    explicit IPrecisionP2 (const int h_precision = 1,
                           const int v_precision = 1)
                         : h_precision_(h_precision),
                           v_precision_(v_precision) {}

    virtual ~IPrecisionP2() = default;
};

} // namespace WConsole

#endif // WCONSOLE_IPRECISION_H_
