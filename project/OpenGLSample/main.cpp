#include "SDL.h"
#include "GL/gl.h"
#include <stdexcept>
#include <iostream>

SDL_Surface* window;

Uint32 createFlags(bool fullscreen)
{
    //Iniciamos com a OpenGL e paleta de hardware
    Uint32 flags = SDL_OPENGL | SDL_HWPALETTE;

    if (fullscreen)
        flags |= SDL_FULLSCREEN;

    const SDL_VideoInfo* info = SDL_GetVideoInfo();

    //Criarmos uma superfície de hardware,
    //se este estiver disponível
    if (info->hw_available)
        flags |= SDL_HWSURFACE;
    else
        flags |= SDL_SWSURFACE;

    //Aceleração por hardware?
    if(info -> blit_hw)
        flags |= SDL_HWACCEL;

    return flags;
}

int setupOpenGL(int bpp, bool fullscreen)
{
    //Atributos do opengl
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, bpp > 24 ? 24 : bpp);
    SDL_GL_SetAttribute( SDL_GL_ACCUM_RED_SIZE, 0);
    SDL_GL_SetAttribute( SDL_GL_ACCUM_GREEN_SIZE, 0);
    SDL_GL_SetAttribute( SDL_GL_ACCUM_BLUE_SIZE, 0);
    SDL_GL_SetAttribute( SDL_GL_ACCUM_ALPHA_SIZE, 0);

    return createFlags(fullscreen);
}

void setup(int width, int height, int bpp, bool fullscreen)
{
    //Inicializamos o subsistema de video.
    if (SDL_Init(SDL_INIT_VIDEO) == -1)
        throw std::runtime_error(SDL_GetError());

    //Tentamos criar a janela
    window = SDL_SetVideoMode(width, height, bpp,
    setupOpenGL(bpp, fullscreen));

    //Sem sucesso? Lançamos uma exceção com o erro.
    if (window == NULL)
        throw std::runtime_error(SDL_GetError());
     //Dizemos para o OpenGL usar toda a tela
     glViewport(0,0, width, height);
    //Configuramos a função de des-inicialização
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

        //Desenhamos um triângulo
        while (true)
        {
            processEvents();
            glClearColor(0.0, 0.0, 0.0, 0.0);
            glClear(GL_COLOR_BUFFER_BIT);

            glBegin(GL_TRIANGLES);
                glColor3f(1,0,0); glVertex2f(0.0f,0.5f);
                glColor3f(0,1,0); glVertex2f(-0.5f, -0.5f);
                glColor3f(0,0,1); glVertex2f(0.5f, -0.5f);
            glEnd();
            SDL_GL_SwapBuffers();
        }
    }
    catch (std::exception &e)
    {
        std::cout << "Error: " << e.what();
        exit(1);
    }
}//</iostream></stdexcept>

