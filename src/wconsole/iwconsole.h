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

#ifndef WCONSOLE_IWCONSOLE_H_
#define WCONSOLE_IWCONSOLE_H_ 1

#if (defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || defined(__WINDOWS__))
#define WINDOWS 1
#define NOMINMAX 1
#else
#define UNIX 1
#endif

#ifdef WINDOWS
#include <fcntl.h>
#include <io.h>
#include <windows.h>
#else
#include <clocale>
#endif

#include "types.h"

namespace WConsole {

class IWConsole {
public:
    void SetColor(const Color color) noexcept {
        color_ = color;
    }

    void SetSize(const uint horizontal_size, const uint vertical_size) noexcept {
        horizontal_size_ = horizontal_size;
        vertical_size_   = vertical_size;
    }

    void SetPosition(const IWConsole & object) noexcept {
        h_pos_ = object.h_pos_;
        v_pos_ = object.v_pos_;
    }

    void NewLine() noexcept {
        Print("\n");
        v_global_pos_ += (v_pos_ + 1);
        v_pos_ = 0;
        h_pos_ = 0;
    }

    void NewLineInBlock() noexcept {
        Print("\n");
        v_global_pos_ += (v_pos_ + 1);
        v_pos_ = 0;
        h_pos_ = h_global_pos_;
    }

    void Clear() noexcept {
#ifdef WINDOWS
        COORD pos {0, 0};
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
#else
        Print("\ec");
#endif
        v_pos_        = 0;
        h_pos_        = 0;
        v_global_pos_ = 0;
        h_global_pos_ = 0;
    }

    void ClearLast() noexcept {
        Print("\n");
        ChangePosition(Position::Up, v_pos_ + 1);
        v_pos_ = 0;
        h_pos_ = h_global_pos_;
    }

    void ClearFirst() noexcept {
        Print("\n");
        ChangePosition(Position::Up, v_global_pos_ + v_pos_ + 1);
        h_pos_        = 0;
        v_pos_        = 0;
        h_global_pos_ = 0;
        v_global_pos_ = 0;
    }

protected:
    enum class Position {
        Up,
        Down,
        Right,
        Left
    };

    uint  horizontal_size_;
    uint  vertical_size_;
    Color color_;
    Color color_prev_;
    Color back_color_;
    Color back_color_prev_;
#ifdef WINDOWS
    short default_color_;
    short default_back_color_;
#endif
    uint  h_global_pos_;
    uint  v_global_pos_;
    uint  h_pos_;
    uint  v_pos_;

    explicit IWConsole(const uint  horizontal_size = 20,
                       const uint  vertical_size   = 10,
                       const Color color           = Color::Default)
                     : horizontal_size_(horizontal_size),
                       vertical_size_  (vertical_size),
                       color_          (color),
                       color_prev_     (Color::Default),
                       v_global_pos_   (0),
                       h_global_pos_   (0),
                       v_pos_          (0),
                       h_pos_          (0) {
#ifdef WINDOWS
        _setmode(_fileno(stdout), _O_WTEXT);

        CONSOLE_SCREEN_BUFFER_INFO info;
        if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info)) {
            default_color_      = 0x0A;
            default_back_color_ = 0x00;
        }
        default_color_      = 0x0F & info.wAttributes;
        default_back_color_ = 0xF0 & info.wAttributes;
#else
        setlocale(LC_CTYPE, "");
#endif
        ShowCursor(false);
    }

    virtual ~IWConsole() {
        ChangeColor(Color::Default);
        ShowCursor(true);
    }

    void ChangeColor(const Color color) noexcept {
#ifdef WINDOWS
        switch (color) {
//            case Color::Normal:  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);                                                          break;
//            case Color::Red:     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);                                             break;
//            case Color::Green:   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);                                           break;
//            case Color::Blue:    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE);                                            break;
//            case Color::Magenta: SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED   | FOREGROUND_BLUE);                         break;
//            case Color::Yellow:  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED   | FOREGROUND_GREEN | FOREGROUND_INTENSITY); break;
//            case Color::Cyan:    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE  | FOREGROUND_INTENSITY); break;
//            case Color::White:   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED   | FOREGROUND_GREEN | FOREGROUND_BLUE);      break;

            case Color::Black:         SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x00); break;
            case Color::Blue:          SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x01); break;
            case Color::Green:         SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x02); break;
            case Color::Cyan:          SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x03); break;
            case Color::Red:           SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x04); break;
            case Color::Magenta:       SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x05); break;
            case Color::Yellow:        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x06); break;
            case Color::White:         SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07); break;

            case Color::BrightBlack:   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x08); break;
            case Color::BrightBlue:    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x09); break;
            case Color::BrightGreen:   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0A); break;
            case Color::BrightCyan:    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0B); break;
            case Color::BrightRed:     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0C); break;
            case Color::BrightMagenta: SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0D); break;
            case Color::BrightYellow:  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0E); break;
            case Color::BrightWhite:   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F); break;

            case Color::Default:       SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), default_color_); break;
            case Color::BrightDefault: SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), default_color_); break;
        }
#else
        switch (color) {
            case Color::Black:         Print("\e[0;30m"); break;
            case Color::Red:           Print("\e[0;31m"); break;
            case Color::Green:         Print("\e[0;32m"); break;
            case Color::Yellow:        Print("\e[0;33m"); break;
            case Color::Blue:          Print("\e[0;34m"); break;
            case Color::Magenta:       Print("\e[0;35m"); break;
            case Color::Cyan:          Print("\e[0;36m"); break;
            case Color::White:         Print("\e[0;37m"); break;
            case Color::BrightBlack:   Print("\e[1;30m"); break;
            case Color::BrightRed:     Print("\e[1;31m"); break;
            case Color::BrightGreen:   Print("\e[1;32m"); break;
            case Color::BrightYellow:  Print("\e[1;33m"); break;
            case Color::BrightBlue:    Print("\e[1;34m"); break;
            case Color::BrightMagenta: Print("\e[1;35m"); break;
            case Color::BrightCyan:    Print("\e[1;36m"); break;
            case Color::BrightWhite:   Print("\e[1;37m"); break;
            case Color::Default:       Print("\e[0m");    break;
            case Color::BrightDefault: Print("\e[;1m");   break;
        }
#endif
    }

    void WriteColorToBuff(std::wstring & buff, const Color color) noexcept {
        if (color != color_prev_) {
#ifdef WINDOWS
            Print(buff);
            ChangeColor(color);
            buff = L"";
#else
            switch (color) {
                case Color::Black:         buff += L"\e[0m\e[30m";   break;
                case Color::Red:           buff += L"\e[0;31m";      break;
                case Color::Green:         buff += L"\e[0m\e[32m";   break;
                case Color::Yellow:        buff += L"\e[0m\e[33m";   break;
                case Color::Blue:          buff += L"\e[0m\e[34m";   break;
                case Color::Magenta:       buff += L"\e[0m\e[35m";   break;
                case Color::Cyan:          buff += L"\e[0m\e[36m";   break;
                case Color::White:         buff += L"\e[0m\e[37m";   break;
                case Color::BrightBlack:   buff += L"\e[0;1m\e[30m"; break;
                case Color::BrightRed:     buff += L"\e[0;1m\e[31m"; break;
                case Color::BrightGreen:   buff += L"\e[0;1m\e[32m"; break;
                case Color::BrightYellow:  buff += L"\e[0;1m\e[33m"; break;
                case Color::BrightBlue:    buff += L"\e[0;1m\e[34m"; break;
                case Color::BrightMagenta: buff += L"\e[0;1m\e[35m"; break;
                case Color::BrightCyan:    buff += L"\e[0;1m\e[36m"; break;
                case Color::BrightWhite:   buff += L"\e[0;1m\e[37m"; break;
                case Color::Default:       buff += L"\e[;0m";        break;
                case Color::BrightDefault: buff += L"\e[;1m";        break;
            }
#endif
            color_prev_ = color;
        }
    }

    void ChangePosition(const Position position, const uint number) const noexcept {
#ifdef WINDOWS
        COORD pos;
        CONSOLE_SCREEN_BUFFER_INFO info;

        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);

        pos.X = info.dwCursorPosition.X;
        pos.Y = info.dwCursorPosition.Y;

        switch (position) {
            case Position::Up    : pos.Y -= number; break;
            case Position::Down  : pos.Y += number; break;
            case Position::Right : pos.X += number; break;
            case Position::Left  : pos.X -= number; break;
        }

        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
#else
//        printf( "%s%d;%dH", CSI, fila + 1, columna + 1 );
        switch (position) {
            case Position::Up    : Print("\033[" + std::to_string(number) + "A"); break;
            case Position::Down  : Print("\033[" + std::to_string(number) + "B"); break;
            case Position::Right : Print("\033[" + std::to_string(number) + "C"); break;
            case Position::Left  : Print("\033[" + std::to_string(number) + "D"); break;
        }
#endif
    }

    void WritePositionToBuff(std::wstring & buff, const Position position, const int number) const noexcept {
        if (number > 0) {
#ifdef WINDOWS
            Print(buff);
            ChangePosition(position, number);
            buff = L"";
#else
            switch (position) {
                case Position::Up    : buff += L"\e[" + std::to_wstring(number) + L'A'; break;
                case Position::Down  : buff += L"\e[" + std::to_wstring(number) + L'B'; break;
                case Position::Right : buff += L"\e[" + std::to_wstring(number) + L'C'; break;
                case Position::Left  : buff += L"\e[" + std::to_wstring(number) + L'D'; break;
            }
#endif
        }
    }

    void Print(const char * s) const noexcept {
#if (defined(__STDC_LIB_EXT1__))
        wprintf_s(L"%s", s);
#else
        wprintf(L"%s", s);
#endif
    }

    void Print(const std::string & str) const noexcept {
#if (defined(__STDC_LIB_EXT1__))
        wprintf_s(L"%s", str.c_str());
#else
        wprintf(L"%s", str.c_str());
#endif
    }

    void Print(const wchar_t * ws) const noexcept {
#if (defined(__STDC_LIB_EXT1__))
        wprintf_s(L"%ls", ws);
#else
        wprintf(L"%ls", ws);
#endif
    }

    void Print(const std::wstring & wstr) const noexcept {
#if (defined(__STDC_LIB_EXT1__))
        wprintf_s(L"%ls", wstr.c_str());
#else
        wprintf(L"%ls", wstr.c_str());
#endif
    }

private:
    void ShowCursor(const bool show) const noexcept {
#ifdef WINDOWS
        CONSOLE_CURSOR_INFO info;
        info.bVisible = (BOOL)show;
        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
#else
        Print(std::string("\33[?25") + ((show) ? "h" : "l"));
#endif
    }
};

} // namespace WConsole

#endif // WCONSOLE_IWCONSOLE_H_
