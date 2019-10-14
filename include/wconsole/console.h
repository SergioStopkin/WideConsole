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

#ifndef WCONSOLE_CONSOLE_H_
#define WCONSOLE_CONSOLE_H_ 1

#if (defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || defined(__WINDOWS__))
#define WINDOWS 1
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

#include <algorithm>
#include <string>

#include "types.h"

namespace WConsole {

enum class Position : uchar {
    Up,
    Down,
    Right,
    Left
};

class Console final {
public:
    static void NewLine() noexcept {
        ChangePosition(Position::Down, global_state_.max_v_pos - global_state_.v_pos);
        Print("\n");
        global_state_.h_pos     = 0;
        global_state_.v_pos     = 0;
        global_state_.max_v_pos = 0;
    }

    /*void NewLineInBlock() noexcept {
        Print("\n");
        global_v_pos_ += (v_pos_ + 1);
        v_pos_ = 0;
        h_pos_ = global_h_pos_;
    }*/

    static void Clear() noexcept {
#ifdef WINDOWS
        COORD pos {0, 0};
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
#else
        Print("\ec");
#endif
        global_state_.h_pos = 0;
        global_state_.v_pos = 0;
    }

    /*void ClearLast() noexcept {
        Print("\n");
        ChangePosition(Position::Up, v_pos_ + 1);
        v_pos_ = 0;
        h_pos_ = global_h_pos_;
    }

    void ClearFirst() noexcept {
        Print("\n");
        ChangePosition(Position::Up, global_v_pos_ + v_pos_ + 1);
        h_pos_        = 0;
        v_pos_        = 0;
        global_h_pos_ = 0;
        global_v_pos_ = 0;
    }*/

    Console() = delete;

    static void ChangeColor(const Color color, const bool is_foreground = true) noexcept {
        if ((is_foreground && color != global_view_.foreground) || (!is_foreground && color != global_view_.background)) {
#ifdef WINDOWS
            switch (color) {
//                case Color::Normal:  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);                                                          break;
//                case Color::Red:     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);                                             break;
//                case Color::Green:   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);                                           break;
//                case Color::Blue:    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE);                                            break;
//                case Color::Magenta: SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED   | FOREGROUND_BLUE);                         break;
//                case Color::Yellow:  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED   | FOREGROUND_GREEN | FOREGROUND_INTENSITY); break;
//                case Color::Cyan:    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE  | FOREGROUND_INTENSITY); break;
//                case Color::White:   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED   | FOREGROUND_GREEN | FOREGROUND_BLUE);      break;

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
            if (is_foreground) {
                global_view_.foreground = color;
            } else {
                global_view_.background = color;
            }
        }
    }

    static void WriteColorToBuff(std::wstring & buff, const Color color, const bool is_foreground = true) noexcept {
        if ((is_foreground && color != global_view_.foreground) || (!is_foreground && color != global_view_.background)) {
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
            if (is_foreground) {
                global_view_.foreground = color;
            } else {
                global_view_.background = color;
            }
        }
    }

    static void ChangePosition(const Position position, const uint number) noexcept {
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
            case Position::Up    : Print("\e[" + std::to_string(number) + "A"); break;
            case Position::Down  : Print("\e[" + std::to_string(number) + "B"); break;
            case Position::Right : Print("\e[" + std::to_string(number) + "C"); break;
            case Position::Left  : Print("\e[" + std::to_string(number) + "D"); break;
        }
#endif
    }

    static void WritePositionToBuff(std::wstring & buff, const Position position, const int number) noexcept {
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

    static void WriteViewToBuff(std::wstring & buff, const ConsoleView & view) noexcept {
        buff += L"\e[";

        if (view.foreground == Color::Default || view.background == Color::Default || view.background == Color::BrightDefault) {
            buff += L"0;";
        }

        switch (view.foreground) {
            case Color::Black:         buff += L"21;30"; break;
            case Color::Red:           buff += L"21;31"; break;
            case Color::Green:         buff += L"21;32"; break;
            case Color::Yellow:        buff += L"21;33"; break;
            case Color::Blue:          buff += L"21;34"; break;
            case Color::Magenta:       buff += L"21;35"; break;
            case Color::Cyan:          buff += L"21;36"; break;
            case Color::White:         buff += L"21;37"; break;
            case Color::BrightBlack:   buff += L"1;30"; break;
            case Color::BrightRed:     buff += L"1;31"; break;
            case Color::BrightGreen:   buff += L"1;32"; break;
            case Color::BrightYellow:  buff += L"1;33"; break;
            case Color::BrightBlue:    buff += L"1;34"; break;
            case Color::BrightMagenta: buff += L"1;35"; break;
            case Color::BrightCyan:    buff += L"1;36"; break;
            case Color::BrightWhite:   buff += L"1;37"; break;
            case Color::BrightDefault: buff += L";1";   break;
            default: break;
        }

        switch (view.background) {
            case Color::Black:         buff += L";40"; break;
            case Color::Red:           buff += L";41"; break;
            case Color::Green:         buff += L";42"; break;
            case Color::Yellow:        buff += L";43"; break;
            case Color::Blue:          buff += L";44"; break;
            case Color::Magenta:       buff += L";45"; break;
            case Color::Cyan:          buff += L";46"; break;
            case Color::White:         buff += L";47"; break;
            case Color::BrightBlack:   buff += L";40"; break;
            case Color::BrightRed:     buff += L";41"; break;
            case Color::BrightGreen:   buff += L";42"; break;
            case Color::BrightYellow:  buff += L";43"; break;
            case Color::BrightBlue:    buff += L";44"; break;
            case Color::BrightMagenta: buff += L";45"; break;
            case Color::BrightCyan:    buff += L";46"; break;
            case Color::BrightWhite:   buff += L";47"; break;
            default: break;
        }

        if (view.is_underline) {
            buff += L";4";
        } else {
            buff += L";24";
        }

        if (view.is_inverse) {
            buff += L";7";
        } else {
            buff += L";27";
        }

        buff += L"m";
    }

    static void Print(const char * s) noexcept {
#ifdef WINDOWS
        std::wprintf(L"%s", s);
#else
        std::wcout << s << std::flush;
#endif
    }

    static void Print(const std::string & str) noexcept {
#ifdef WINDOWS
        std::wprintf(L"%s", str.c_str());
#else
        std::wcout << str.c_str() << std::flush;
#endif
    }

    static void Print(const wchar_t * ws) noexcept {
#ifdef WINDOWS
        std::wprintf(L"%ls", ws);
#else
        std::wcout << ws << std::flush;
#endif
    }

    static void Print(const std::wstring & wstr) noexcept {
#ifdef WINDOWS
        std::wprintf(L"%ls", wstr.c_str());
#else
        std::wcout << wstr << std::flush;
#endif
    }

    static void ShowCursor(const bool show) noexcept {
#ifdef WINDOWS
        CONSOLE_CURSOR_INFO info;
        info.bVisible = (BOOL)show;
        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
#else
        Print(std::string("\e[?25") + ((show) ? "h" : "l"));
#endif
    }

    static void PreProcessing(const uint horizontal_size, const uint header_size) noexcept {
        if (global_state_.col_num > 0 && (global_state_.h_pos + horizontal_size + header_size) > global_state_.col_num) {
            NewLine();
        }
    }

    static uint GlobalHPos() noexcept {
        return global_state_.h_pos;
    }

    static uint GlobalVPos() noexcept {
        return global_state_.v_pos;
    }

    static void GlobalHPos(const uint h_pos) noexcept {
        global_state_.h_pos = h_pos;
    }

    static void GlobalVPos(const uint v_pos) noexcept {
        global_state_.v_pos = v_pos;
        global_state_.max_v_pos = std::max(v_pos, global_state_.max_v_pos);
    }

    static void Start() noexcept {
#ifdef WINDOWS
        _setmode(_fileno(stdout), _O_WTEXT);

        CONSOLE_SCREEN_BUFFER_INFO info;
        if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info)) {
            default_color_      = 0x0A;
            default_back_color_ = 0x00;
        } else {
            default_color_      = 0x0F & info.wAttributes;
            default_back_color_ = 0xF0 & info.wAttributes;

            global_state_.col_num = info.dwSize.X;
            global_state_.row_num = info.dwSize.Y;
        }
#else
        std::ios_base::sync_with_stdio(false);
        std::wcout.imbue(std::locale(""));

        winsize wsize {};
        if (ioctl(STDIN_FILENO, TIOCGWINSZ, (char *)&wsize) != -1) {
            global_state_.col_num = wsize.ws_col;
            global_state_.row_num = wsize.ws_row;
        }
#endif
        Console::ShowCursor(false);
    }

    static void End() noexcept {
        Console::ChangeColor(Color::Default);
        Console::ShowCursor(true);
#ifdef UNIX
        std::ios_base::sync_with_stdio(true);
        std::wcout.imbue(std::locale());
#endif
    }

private:
    static ConsoleState global_state_;
    static ConsoleView  global_view_;
#ifdef WINDOWS
    static short        default_color_;
    static short        default_back_color_;
#endif
};

ConsoleState Console::global_state_;
ConsoleView  Console::global_view_;
#ifdef WINDOWS
short        Console::default_color_      = 0;
short        Console::default_back_color_ = 0;
#endif

} // namespace WConsole

#endif // WCONSOLE_CONSOLE_H_
