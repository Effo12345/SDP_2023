#include "include/main.hpp"
#include "FEHLCD.h"

int main()
{
    LCD.WriteLine("Hello World!");
    while (1) {
        LCD.Update();
        // Never end
        //Testing
    }
    return 0;
}