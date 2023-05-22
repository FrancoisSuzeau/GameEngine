#include <iostream>
#include <SDL2/SDL.h>
#include <GL/glew.h>


int main(int argc, char** argv)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Error" << std::endl;
    }
    std::cout << "Hello World!" << std::endl;

    return EXIT_SUCCESS;
}