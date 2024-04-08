#include <iostream>
#include "archive.h"
#include "utilities.h"

enum Actions { EXIT, INSERT, FIND, REMOVE, CLEAN };

int main() {
    TArchive<int> archive;
    TArchive<int> values;
    size_t n, pos;
    
    size_t* fpos = nullptr;
    
    int fvalues;
    int rvalue = 0;
    int user;


    std::exception err;
    bool exit = false;
    bool success;
    
    InputSystem::InsertMode mode;
    InputSystem::FindMode fmode;
    InputSystem::RemoveMode rmode;

    while (!exit) {
        system("cls");
        OutputSystem::show(archive);
        std::cout << "Menu:\n 1. insert,\n 2. find,\n 3. delete,\n 4. clean,\n 0. exit.\nYour choose: ";
        std::cin >> user;

        if (user == Actions::EXIT) { exit = true; }
        if (user == Actions::INSERT) 
        {
            InputSystem::insert<int>(values , n, pos, mode);
            success = false;
            if (mode == InputSystem::InsertMode::Back)
            {
                try
                {
                    archive.push_back(values._data() [0]);
                    success = true;
                }
                catch (std::exception err) { std::cerr << err.what() << std::endl; }
            }
            else if (mode == InputSystem::InsertMode::Front)
            {
                try
                {
                    archive.push_front(values._data() [0]);
                    success = true;
                }
                catch (std::exception err) { std::cerr << err.what() << std::endl; }
            }
            else if (mode == InputSystem::InsertMode::ByPos) {
                try
                {
                    archive.insert(values, pos);
                    success = true;
                }
                catch (std::exception err) { std::cerr << err.what() << std::endl; }
            }
            else if (mode == InputSystem::InsertMode::exit) { success = true; }
            if (success) { OutputSystem::insert(); }
            system("pause"); 
        }
        if (user == Actions::FIND) 
        {
            if (fpos != nullptr) { delete[] fpos; fpos = nullptr; }
            fvalues = InputSystem::Find(archive, fmode);
            success = false;

            if (fmode == InputSystem::FindMode::all) {
                try
                {
                    fpos = archive.find_all(fvalues);
                    success = true;
                }
                catch (std::exception err) { std::cerr << err.what() << std::endl; }
            }
            if (fmode == InputSystem::FindMode::first) {
                try
                {
                    fpos = archive.find_first(fvalues);
                    success = true;
                }
                catch (std::exception err) { std::cerr << err.what() << std::endl; }
            }
            if (fmode == InputSystem::FindMode::last) {
                try
                {
                    fpos = archive.find_last(fvalues);
                    success = true;
                }
                catch (std::exception err) { std::cerr << err.what() << std::endl; }
            }
            if (fmode != InputSystem::FindMode::fexit)
            {
                std::cout << "Amount found: ";
                std::cout << fpos[0];
                std::cout << ".\n" << std::endl;

                std::cout << "Found position:";
                std::cout << "{ ";
                for (size_t i = 1; i <= fpos[0]; i++)
                {
                    if (i != fpos[0]) std::cout << fpos[i] << ", ";
                    else std::cout << fpos[i] << " ";
                }
                std::cout << "}\n" << std::endl;
            }
            else { success = true; }
            if (success) { OutputSystem::insert(); }

            system("pause");
        }
        if (user == Actions::REMOVE) 
        {
            InputSystem::Remove(n, pos, rvalue, rmode);
            success = false;

            if (rmode == InputSystem::RemoveMode::rback) 
            {                   
                try
                {
                    archive.pop_back();   
                    success = true;
                }
                catch (std::exception err) { std::cerr << err.what() << std::endl; }
            }
            if (rmode == InputSystem::RemoveMode::rfront) 
            {                   
                try
                {
                    archive.pop_front();
                    success = true;
                }
                catch (std::exception err) { std::cerr << err.what() << std::endl; }
            }
            if (rmode == InputSystem::RemoveMode::erase) 
            {              
                try
                {
                    archive.erase(pos, n);
                    success = true;
                }
                catch (std::exception err) { std::cerr << err.what() << std::endl; }
            }
            if (rmode == InputSystem::RemoveMode::rall) 
            {                     
                try
                {
                    archive.remove_all(rvalue);
                    success = true;
                }
                catch (std::exception err) { std::cerr << err.what() << std::endl; }
            }
            if (rmode == InputSystem::RemoveMode::rfirst) 
            {               
                try
                {
                    archive.remove_first(rvalue);
                    success = true;
                }
                catch (std::exception err) { std::cerr << err.what() << std::endl; }
            }
            if (rmode == InputSystem::RemoveMode::rlast) 
            {                
                try
                {
                    archive.remove_last(rvalue);
                    success = true;
                }
                catch (std::exception err) { std::cerr << err.what() << std::endl; }
            }
            if (rmode == InputSystem::RemoveMode::rByPos) 
            {                
                try
                {
                    archive.remove_by_index(pos);
                    success = true;
                }
                catch (std::exception err) { std::cerr << err.what() << std::endl; }
            }

            else if (rmode == InputSystem::RemoveMode::rexit) { success = true; }
            if (success) { OutputSystem::insert(); }

            system("pause");
        }
        if (user == Actions::CLEAN) 
        { 
            archive.clear();
            system("pause");
        }
    }

    return 0;
}