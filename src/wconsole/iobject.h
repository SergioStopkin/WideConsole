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

#ifndef WCONSOLE_IOBJECT_H_
#define WCONSOLE_IOBJECT_H_ 1

#include <utility>
#include <vector>

#include "console.h"
#include "types.h"

namespace WConsole {

class Chart;
class Graph;
class Text;

class IObject {
public:
    void SetSize(const uint horizontal_size, const uint vertical_size) noexcept {
        horizontal_size_ = horizontal_size;
        vertical_size_   = vertical_size;
    }

    template <typename T>
    void PrintBound(const std::vector<T> & data) {
        PrintHost(object_ref_.chart, data);
    }

    template <typename T>
    void PrintBound(const std::vector<std::pair<T, T>> & data) {
        PrintHost(object_ref_.graph, data);
    }

    template <typename T>
    void PrintBound(const T & data) {
        PrintHost(object_ref_.text, data);
    }

    template <typename T, typename F>
    void PrintBound(const T & data, const F & font) {
        PrintHost(object_ref_.text, data, font);
    }


protected:
    enum class ObjectType : uchar {
        Chart,
        Graph,
        Text
    };

    uint h_pos_ = 0;
    uint v_pos_ = 0;

    ObjectType object_type_;
    uint       horizontal_size_;
    uint       vertical_size_;

    explicit IObject(const ObjectType object_type,
                     const uint       horizontal_size = 22,
                     const uint       vertical_size   = 11)
        : object_type_    (object_type),
          horizontal_size_(horizontal_size),
          vertical_size_  (vertical_size) {
        // Set reference to the object
        switch (object_type_) {
            case ObjectType::Chart : object_ref_.chart = (Chart *)this; break;
            case ObjectType::Graph : object_ref_.graph = (Graph *)this; break;
            case ObjectType::Text  : object_ref_.text  = (Text  *)this; break;
        }

        if (object_counter_ == 0) {
            Console::Start();
            Console::ShowCursor(false);
        }

        ++object_counter_;
    }

    virtual ~IObject() {
        if (object_counter_ == 1) {
            Console::ChangeColor(Color::Default);
            Console::ShowCursor(true);
#ifdef UNIX
            Console::End();
#endif
        }

        --object_counter_;
    }

private:
    union ObjectRef {
        Chart * chart;
        Graph * graph;
        Text  * text;
    };

    static int object_counter_;

    ObjectRef object_ref_;

    template <class O, typename ... ARGS>
    void PrintHost(const O    &     object,
                   const ARGS & ... data) {
        // Pre-processing
//        if (global_col_num_ > 0 && (global_h_pos_ + horizontal_size_) > global_col_num_) {
//            NewLine();
//        }
//        h_pos_ = global_h_pos_;
//        v_pos_ = global_v_pos_;

        // Call PrintObject() in derived objects
        object->PrintObject(data ...);

        // Post-processing
//        global_h_pos_ = h_pos_;
//        global_v_pos_ = v_pos_;
    }
};

int IObject::object_counter_ = 0;

}; // namespace WConsole

#endif // WCONSOLE_IOBJECT_H_
