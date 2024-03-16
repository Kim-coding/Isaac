#include "pch.h"

int main()
{
    FRAMEWORK.Init(1000, 700, "Binding of Isaac: Rebirth");
    FRAMEWORK.Do();
    FRAMEWORK.Release();
    return 0;
}