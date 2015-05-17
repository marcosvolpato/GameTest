#include <iostream>

#include "SDL.h"

#include <stdexcept>
#include <iostream>
using namespace std;

SDL_Surface* window;

void setup(int width, int height, int bpp, bool fullscreen)
{
    //Inicializamos o subsistema de video.
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        throw std::runtime_error(SDL_GetError());

    //Definimos as flags.
    int flags = SDL_SWSURFACE;
    if (fullscreen)
        flags = flags | SDL_FULLSCREEN;

    //Tentamos criar a janela
    window = SDL_SetVideoMode(width, height, bpp, flags);

    //Sem sucesso? Lançamos uma exceção com o erro.
    if (window == NULL)
        throw std::runtime_error(SDL_GetError());

    //Configuramos a função de finalização da SDL
    atexit (SDL_Quit);
}

/** Espera o usuário pressionar o x da janela. */
void processEvents()
{
    SDL_Event event;

    while (SDL_PollEvent(&event) != 0)
    {
        switch (event.type)
        {
            case SDL_QUIT:
                exit(0); //Fechamos a apliação
                break;
        }
    }
}

int main(int argc,char* argv[])
{
    try
    {
        setup(640, 480, 8, false); //Faz a mágica acontecer

        while (true)
            processEvents();
    }
    catch (std::exception &e)
    {
        std::cout << "Error: " << e.what();
        exit(1);
    }
}

