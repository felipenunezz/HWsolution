#include <iostream>
#include "StringH.h"

int main() {
    CString str_1("World Hello\0");
    CString str_2("Hello");

    size_t FOUNDPOS = str_1.find(str_2, 0);
    std::cout << FOUNDPOS << std::endl;
    
    return 0;
}
