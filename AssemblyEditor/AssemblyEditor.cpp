#include <iostream>
#include "Window.h"
int main()
{
    Window w(60,30);
    for(int i = 0; i < 20000; i++)
    {
        for(unsigned int x = 0; x < w.siize(); x++)
        {
            w[x] = rand();
        }
        w.update({ 0,0 });
    }
}
