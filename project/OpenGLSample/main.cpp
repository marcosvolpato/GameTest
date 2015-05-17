#include "SDL.h"
#include "GL/gl.h"

#include <stdexcept>
#include <iostream>


SDL_Surface* window;

//Controle do tempo
Uint32 lastTicks;
Uint32 ticks;

//Total graus para rodar
float degreesToRotate;


 //o evento
//Controle do tempo
//Uint32 lastTicks;
//Uint32 ticks;
//Estado das teclas
bool leftPressed;
bool rightPressed;



int createFlags(bool fullscreen)
{

    //Iniciamos com a OpenGL e paleta de hardware
    int flags = SDL_OPENGL | SDL_HWPALETTE;

    if (fullscreen)
        flags |= SDL_FULLSCREEN;

    const SDL_VideoInfo* info = SDL_GetVideoInfo();

    //Criarmos uma superf�cie de hardware,
    //se este estiver dispon�vel
    if (info->hw_available)
        flags |= SDL_HWSURFACE;
    else
        flags |= SDL_SWSURFACE;

    //Acelera��o por hardware?
    if(info -> blit_hw)
        flags |= SDL_HWACCEL;

    return flags;
}

int setupOpenGL(int bpp, bool fullscreen)
{
    //Atributos do opengl
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, bpp);
    SDL_GL_SetAttribute( SDL_GL_ACCUM_RED_SIZE, 0);
    SDL_GL_SetAttribute( SDL_GL_ACCUM_GREEN_SIZE, 0);
    SDL_GL_SetAttribute( SDL_GL_ACCUM_BLUE_SIZE, 0);
    SDL_GL_SetAttribute( SDL_GL_ACCUM_ALPHA_SIZE, 0);

    return createFlags(fullscreen);
}

void setup(int width, int height, int bpp, bool fullscreen)
{
    //Inicializamos o subsistema de video.
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        throw std::runtime_error(SDL_GetError());

    //Tentamos criar a janela
    window = SDL_SetVideoMode(width, height, bpp,
    setupOpenGL(bpp, fullscreen));

    //Sem sucesso? Lan�amos uma exce��o com o erro.
    if (window == NULL)
        throw std::runtime_error(SDL_GetError());

    glViewport(0,0, width, height);

    //Configuramos a fun��o de des-inicializa��o
    atexit (SDL_Quit);
}

/** Espera o usu�rio pressionar o x da janela. */
void processEvents(){

    SDL_Event event;

    while (SDL_PollEvent(&event) != 0){
        switch (event.type){
            case SDL_QUIT:
                exit(0); //Fechamos a aplica��o
                break;

            //Testamos se a tecla foi pressionada
            case SDL_KEYDOWN:
                if(event.key.keysym.sym == SDLK_LEFT)
                    leftPressed = true;
                else if (event.key.keysym.sym == SDLK_RIGHT)
                    rightPressed = true;
                break;

            //Testamos se a tecla foi solta
            case SDL_KEYUP:
                if(event.key.keysym.sym == SDLK_LEFT)
                    leftPressed = false;
                else if (event.key.keysym.sym == SDLK_RIGHT)
                    rightPressed = false;
                break;
        }
    }

}

void draw()
{
    glPushMatrix();
        //Limpa a tela
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Gira o tri�ngulo
        glRotatef(degreesToRotate, 0,0,1);

        //Desenha o tri�ngulo
        glBegin(GL_TRIANGLES);
            glColor3f(1,0,0);
            glVertex2f(0.0f,0.5f);
            glColor3f(0,1,0);
            glVertex2f(-0.5f, -0.5f);
            glColor3f(0,0,1);
            glVertex2f(0.5f, -0.5f);
        glEnd();
    glPopMatrix();
}

void processLogics()
{
    //Dist�ncia para girar (em graus) =
    //velocidade (0.180f) * tempo (ticks)
    //float distance = 0.180f * ticks;
    //degreesToRotate += distance;


    //Dist�ncia para girar (em graus) =
    //velocidade (0.180f) * tempo (ticks)
    float distance = 0.180f * ticks;

    //Est� com a seta esquerda pressionada?
    if (leftPressed)
        degreesToRotate += distance;
    //Est� com a seta direita pressionada?
    else if (rightPressed)
        degreesToRotate -= distance;


}

int main(int argc,char* argv[])
{
    try
    {
        setup(640, 480, 8, false); //Faz a m�gica acontecer
        degreesToRotate = 0;
        lastTicks = SDL_GetTicks();



        //Loop principal do jogo
        while (true)
        {
            Uint32 thisTicks = SDL_GetTicks();
            //Calcula em ticks a diferen�a de tempo entre
            //o quadro atual e o anterior
            ticks = thisTicks - lastTicks;

            //Atualizamos lastTicks
            lastTicks = thisTicks;

            processEvents();
            processLogics();
            draw();

            //Trocamos a superf�cie de desenho
            //pela exibida na tela
            SDL_GL_SwapBuffers();
        }
    }
    catch (std::exception &e)
    {
        std::cout << "Error: "<< e.what();
        exit(1);
    }
}

