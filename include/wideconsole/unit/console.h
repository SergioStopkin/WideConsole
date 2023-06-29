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

#if (defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || defined(__WINDOWS__))
#define WINDOWS  1
#define NOMINMAX 1
#else
#define UNIX 1
#endif

#ifdef WINDOWS
#include <cwchar>
#include <fcntl.h>
#include <io.h>
#include <windows.h>
#else
#include <iostream>
#include <locale>
#include <sys/ioctl.h>
#include <unistd.h>
#endif

#include "wideconsole/type/color.h"
#include "wideconsole/type/position.h"
#include "wideconsole/unit/consolestate.h"
#include "wideconsole/unit/consoleview.h"

#include <algorithm>
#include <string>

namespace WideConsole {

class Console final {
public:
    Console() = delete;

    static void newLine() noexcept
    {
        changePosition(Position::Down, _globalState.maxVPos() - _globalState.vPos());
        print("\n");
        _globalState.setHPos(0);
        _globalState.setVPos(0);
        _globalState.setMaxVPos(0);
    }

    /*void NewLineInBlock() noexcept {
        print("\n");
        global_v_pos_ += (v_pos_ + 1);
        v_pos_ = 0;
        h_pos_ = global_h_pos_;
    }*/

    static void clear() noexcept
    {
#ifdef WINDOWS
        COORD pos { 0, 0 };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
#else
        print("\ec");
#endif
        _globalState.setHPos(0);
        _globalState.setVPos(0);
    }

    /*void ClearLast() noexcept {
        print("\n");
        changePosition(Position::Up, v_pos_ + 1);
        v_pos_ = 0;
        h_pos_ = global_h_pos_;
    }

    void ClearFirst() noexcept {
        print("\n");
        changePosition(Position::Up, global_v_pos_ + v_pos_ + 1);
        h_pos_        = 0;
        v_pos_        = 0;
        global_h_pos_ = 0;
        global_v_pos_ = 0;
    }*/

    static void changeColor(const Color color, const bool is_foreground = true) noexcept
    {
        if ((is_foreground && color != _globalView.foreground()) || (!is_foreground && color != _globalView.background())) {
#ifdef WINDOWS
            switch (color) { // clang-format off
            // case Color::Normal:  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);                                                          break;
            // case Color::Red:     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);                                             break;
            // case Color::Green:   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);                                           break;
            // case Color::Blue:    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE);                                            break;
            // case Color::Magenta: SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED   | FOREGROUND_BLUE);                         break;
            // case Color::Yellow:  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED   | FOREGROUND_GREEN | FOREGROUND_INTENSITY); break;
            // case Color::Cyan:    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE  | FOREGROUND_INTENSITY); break;
            // case Color::White:   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED   | FOREGROUND_GREEN | FOREGROUND_BLUE);      break;

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
            } // clang-format on
#else
            switch (color) {
            // clang-format off
            case Color::Black:         print("\e[0;30m"); break;
            case Color::Red:           print("\e[0;31m"); break;
            case Color::Green:         print("\e[0;32m"); break;
            case Color::Yellow:        print("\e[0;33m"); break;
            case Color::Blue:          print("\e[0;34m"); break;
            case Color::Magenta:       print("\e[0;35m"); break;
            case Color::Cyan:          print("\e[0;36m"); break;
            case Color::White:         print("\e[0;37m"); break;
            case Color::BrightBlack:   print("\e[1;30m"); break;
            case Color::BrightRed:     print("\e[1;31m"); break;
            case Color::BrightGreen:   print("\e[1;32m"); break;
            case Color::BrightYellow:  print("\e[1;33m"); break;
            case Color::BrightBlue:    print("\e[1;34m"); break;
            case Color::BrightMagenta: print("\e[1;35m"); break;
            case Color::BrightCyan:    print("\e[1;36m"); break;
            case Color::BrightWhite:   print("\e[1;37m"); break;
            case Color::Default:       print("\e[0m");    break;
            case Color::BrightDefault: print("\e[;1m");   break;
            } // clang-format on
#endif
            if (is_foreground) {
                _globalView.setColor(color);
            } else {
                _globalView.setBackgroundColor(color);
            }
        }
    }

    static void writeColorToBuff(std::wstring * buff, const Color color, const bool is_foreground = true) noexcept
    {
        if ((is_foreground && color != _globalView.foreground()) || (!is_foreground && color != _globalView.background())) {
#ifdef WINDOWS
            print(*buff);
            changeColor(color);
            *buff = L"";
#else
            switch (color) {
            // clang-format off
            case Color::Black:         *buff += L"\e[0m\e[30m";   break;
            case Color::Red:           *buff += L"\e[0;31m";      break;
            case Color::Green:         *buff += L"\e[0m\e[32m";   break;
            case Color::Yellow:        *buff += L"\e[0m\e[33m";   break;
            case Color::Blue:          *buff += L"\e[0m\e[34m";   break;
            case Color::Magenta:       *buff += L"\e[0m\e[35m";   break;
            case Color::Cyan:          *buff += L"\e[0m\e[36m";   break;
            case Color::White:         *buff += L"\e[0m\e[37m";   break;
            case Color::BrightBlack:   *buff += L"\e[0;1m\e[30m"; break;
            case Color::BrightRed:     *buff += L"\e[0;1m\e[31m"; break;
            case Color::BrightGreen:   *buff += L"\e[0;1m\e[32m"; break;
            case Color::BrightYellow:  *buff += L"\e[0;1m\e[33m"; break;
            case Color::BrightBlue:    *buff += L"\e[0;1m\e[34m"; break;
            case Color::BrightMagenta: *buff += L"\e[0;1m\e[35m"; break;
            case Color::BrightCyan:    *buff += L"\e[0;1m\e[36m"; break;
            case Color::BrightWhite:   *buff += L"\e[0;1m\e[37m"; break;
            case Color::Default:       *buff += L"\e[;0m";        break;
            case Color::BrightDefault: *buff += L"\e[;1m";        break;
            } // clang-format on
#endif
            if (is_foreground) {
                _globalView.setColor(color);
            } else {
                _globalView.setBackgroundColor(color);
            }
        }
    }

    static void changePosition(const Position position, const uint number) noexcept
    {
#ifdef WINDOWS
        COORD                      pos;
        CONSOLE_SCREEN_BUFFER_INFO info;

        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);

        pos.X = info.dwCursorPosition.X;
        pos.Y = info.dwCursorPosition.Y;

        switch (position) {
        // clang-format off
        case Position::Up    : pos.Y -= number; break;
        case Position::Down  : pos.Y += number; break;
        case Position::Right : pos.X += number; break;
        case Position::Left  : pos.X -= number; break;
        } // clang-format on

        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
#else
        //        printf( "%s%d;%dH", CSI, fila + 1, columna + 1 );
        switch (position) {
        // clang-format off
        case Position::Up    : print("\e[" + std::to_string(number) + "A"); break;
        case Position::Down  : print("\e[" + std::to_string(number) + "B"); break;
        case Position::Right : print("\e[" + std::to_string(number) + "C"); break;
        case Position::Left  : print("\e[" + std::to_string(number) + "D"); break;
        } // clang-format on
#endif
    }

    static void writePositionToBuff(std::wstring * buff, const Position position, const int number) noexcept
    {
        if (number > 0) {
#ifdef WINDOWS
            print(*buff);
            changePosition(position, number);
            *buff = L"";
#else
            switch (position) {
            // clang-format off
            case Position::Up    : *buff += L"\e[" + std::to_wstring(number) + L'A'; break;
            case Position::Down  : *buff += L"\e[" + std::to_wstring(number) + L'B'; break;
            case Position::Right : *buff += L"\e[" + std::to_wstring(number) + L'C'; break;
            case Position::Left  : *buff += L"\e[" + std::to_wstring(number) + L'D'; break;
            } // clang-format on
#endif
        }
    }

    static void print(const char * s) noexcept
    {
#ifdef WINDOWS
        std::wprintf(L"%s", s);
#else
        std::wcout << s << std::flush;
#endif
    }

    static void print(const std::string & str) noexcept
    {
#ifdef WINDOWS
        std::wprintf(L"%s", str.c_str());
#else
        std::wcout << str.c_str() << std::flush;
#endif
    }

    static void print(const wchar_t * ws) noexcept
    {
#ifdef WINDOWS
        std::wprintf(L"%ls", ws);
#else
        std::wcout << ws << std::flush;
#endif
    }

    static void print(const std::wstring & wstr) noexcept
    {
#ifdef WINDOWS
        std::wprintf(L"%ls", wstr.c_str());
#else
        std::wcout << wstr << std::flush;
#endif
    }

    static void showCursor(const bool show) noexcept
    {
#ifdef WINDOWS
        CONSOLE_CURSOR_INFO info;
        info.bVisible = (BOOL)show;
        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
#else
        std::string str { "\e[?25" };
        if (show) {
            str.append("h");
        } else {
            str.append("l");
        }
        print(str);
#endif
    }

    static void preProcessing(const uint horizontal_size, const uint header_size) noexcept
    {
        if (_globalState.colNum() > 0 && (_globalState.hPos() + horizontal_size + header_size) > _globalState.colNum()) {
            newLine();
        }
    }

    static uint globalHPos() noexcept { return _globalState.hPos(); }

    static uint globalVPos() noexcept { return _globalState.vPos(); }

    static void globalHPos(const uint h_pos) noexcept { _globalState.setHPos(h_pos); }

    static void globalVPos(const uint v_pos) noexcept
    {
        _globalState.setVPos(v_pos);
        _globalState.setMaxVPos(std::max(v_pos, _globalState.maxVPos()));
    }

    static void start() noexcept
    {
#ifdef WINDOWS
        _setmode(_fileno(stdout), _O_WTEXT);

        CONSOLE_SCREEN_BUFFER_INFO info;
        if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info)) {
            default_color_      = 0x0A;
            default_back_color_ = 0x00;
        } else {
            default_color_      = 0x0F & info.wAttributes;
            default_back_color_ = 0xF0 & info.wAttributes;

            _globalState.setColNum(info.dwSize.X);
            _globalState.setRowNum(info.dwSize.Y);
        }
#else
        std::ios_base::sync_with_stdio(false);
        std::wcout.imbue(std::locale(""));

        winsize wsize {};
        // char * pWSize = &wsize;
        // if (ioctl(STDIN_FILENO, TIOCGWINSZ, reinterpret_cast<char *>(&wsize)) != -1) {
        if (ioctl(STDIN_FILENO, TIOCGWINSZ, &wsize) != -1) { // NOLINT(cppcoreguidelines-pro-type-vararg, hicpp-vararg)
            _globalState.setColNum(wsize.ws_col);
            _globalState.setRowNum(wsize.ws_row);
        }
#endif
        Console::showCursor(false);
    }

    static void end() noexcept
    {
        Console::changeColor(Color::Default);
        Console::showCursor(true);
#ifdef UNIX
        std::ios_base::sync_with_stdio(true);
        std::wcout.imbue(std::locale());
#endif
    }

private:
    inline static ConsoleState _globalState;
    inline static ConsoleView  _globalView;
#ifdef WINDOWS
    inline static short default_color_      = 0;
    inline static short default_back_color_ = 0;
#endif
};

} // namespace WideConsole
