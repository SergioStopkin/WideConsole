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

#include "wconsole/interface/igrid.h"
#include "wconsole/interface/iheader.h"
#include "wconsole/interface/interface.h"
#include "wconsole/interface/iprecision1d.h"
#include "wconsole/interface/irange.h"
#include "wconsole/type/charttype.h"
#include "wconsole/type/opacity.h"

#include <vector>

namespace WConsole {

class IChart : public Interface {
public:
    virtual IGrid &        grid() noexcept                                            = 0;
    virtual IHeader &      header() noexcept                                          = 0;
    virtual IPrecision1D & precision() noexcept                                       = 0;
    virtual IRange &       range() noexcept                                           = 0;
    virtual void           setChartType(ChartType type) noexcept                      = 0;
    virtual void           setOpacity(Opacity opacity) noexcept                       = 0;
    virtual void           setChartColors(const std::vector<Color> & colors) noexcept = 0;
};

} // namespace WConsole
