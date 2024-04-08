#pragma once
#include <iostream>
#include <Windows.h>
#include "archive.h"

namespace InputSystem {
    enum InsertMode { Back, Front, ByPos, exit};
    enum FindMode {all, first, last, fexit};
    enum RemoveMode { rback, rfront, erase, rall, rfirst, rlast, rByPos, rexit};

    template <typename T>
    TArchive<T>& insert(TArchive<T>& Mvalue, size_t& n, size_t& pos, InputSystem::InsertMode& mode) noexcept {
        int v;
        int user;

        std::cout << "Choose insert mode:\n";
        std::cout << "0 - to the back,\n";
        std::cout << "1 - to the front,\n";
        std::cout << "2 - at given position,\n";
        std::cout << "3 - back.\n";
        std::cout << "Your choice: ";
        std::cin >> user;

        if (user == 0) { mode = Back; }
        if (user == 1) { mode = Front; }
        if (user == 2) { mode = ByPos; }
        if (user == 3) { mode = exit; }
        
        if (mode == ByPos) 
        {
            std::cout << "Input values for insert (enter to finish): ";    
            do {
                std::cin >> v;
                Mvalue.push_back(v);

            } while (std::cin.get() != '\n');
        }
        else if (mode != exit)
        {
            std::cout << "Input values for insert: ";
            std::cin >> v;
            Mvalue.push_back(v);
        }
        if (mode == ByPos) 
        {
            std::cout << "Input position for insert: ";
            std::cin >> pos;
        }

        return Mvalue;
    }

    template <typename T>
    int Find(const TArchive<T>& archive, InputSystem::FindMode& mode) 
    {
        size_t* fpos = nullptr;
        int n = 0;
        int user;

        std::cout << "Choose insert mode:\n";
        std::cout << "0 - find all,\n";
        std::cout << "1 - find first,\n";
        std::cout << "2 - find last,\n";
        std::cout << "3 - back.\n";
        std::cout << "Your choose: ";
        std::cin >> user;

        if (user == 0) { mode = all; }
        if (user == 1) { mode = first; }
        if (user == 2) { mode = last; }
        if (user == 3) { mode = fexit; }

        if (mode == all || mode == first || mode == last) 
        {
            std::cout << "Value due to serch: ";
            std::cin >> n;
        }
        return n;
    }

    template <typename T>
    void Remove(size_t& n, size_t& pos, T& value, InputSystem::RemoveMode& mode)
    {
        n = 0;
        int user;
        std::cout << "Choose Erasing mode:\n";
        std::cout << "0 - pop back,\n";
        std::cout << "1 - pop front,\n";
        std::cout << "2 - erase,\n";
        std::cout << "3 - remove all,\n";
        std::cout << "4 - remove first.\n";
        std::cout << "5 - remove last.\n";
        std::cout << "6 - remove by index.\n";
        std::cout << "7 - back.\n";
        std::cout << "Your choice: ";
        std::cin >> user;

        if (user == 0) { mode = rback; }
        if (user == 1) { mode = rfront; }
        if (user == 2) { mode = erase; }
        if (user == 3) { mode = rall;  }
        if (user == 4) { mode = rfirst; }
        if (user == 5) { mode = rlast; }
        if (user == 6) { mode = rByPos; }
        if (user == 7) { mode = rexit; }

        if (mode != rexit) 
        {
            //if (mode == rback) {}
            //if (mode == rfront) {}
            if (mode == erase) 
            {
                std::cout << "Which position to delete:";
                std::cin >> pos;
                std::cout << "\n How many:";
                std::cin >> n;
            }
            if (mode == rall || mode == rfirst || mode == rlast) 
            {
                std::cout << "Which value to delete:";
                std::cin >> value;
            }

            if (mode == rByPos) 
            {
                std::cout << "Which position to delete:";
                std::cin >> pos;
            }
        }
    }
}

namespace OutputSystem {
    static void setCursor(int column, int line) 
    {
        COORD coord;
        coord.X = column;
        coord.Y = line;
        SetConsoleCursorPosition(
            GetStdHandle(STD_OUTPUT_HANDLE),
            coord
        );
    }

    static void getCursor(int& column, int& line) noexcept 
    {
        CONSOLE_SCREEN_BUFFER_INFO csbi;

        if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) 
        {
            column = csbi.dwCursorPosition.X;
            line = csbi.dwCursorPosition.Y;
        }
        else 
        {
            column = 0;
            line = 0;
        }
    }

    static void insert() noexcept { std::cout << "Done." << std::endl; }
    static void find() noexcept { std::cout << "Done." << std::endl; }

    template <typename T>
    void show(const TArchive<T>& archive) noexcept {
        std::cout << "Archive: { ";
        archive.print();
        if (!archive.empty()) {
            int column, line;
            getCursor(column, line);
            column -= 2;
            setCursor(column, line);
        }
        std::cout << " }\n";
    }
}