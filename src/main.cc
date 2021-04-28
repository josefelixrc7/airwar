#include <iostream>

#include "game.h"

int main()
{
    try
    {
        Game game;
        game.Run_();
    }
    catch (std::exception& e)
    {
        std::cout << "\nEXCEPTION: " << e.what() << std::endl;
    }
}
