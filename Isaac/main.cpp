#include "pch.h"

int main()
{
    FRAMEWORK.Init(1000, 700, "Timber");
    FRAMEWORK.Do();
    FRAMEWORK.Release();
    return 0;
}