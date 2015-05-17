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
float movX;
float movY;


 //o evento
//Controle do tempo
//Uint32 lastTicks;
//Uint32 ticks;
//Estado das teclas
bool leftPressed;
bool rightPressed;
bool movUp;
bool movDown;
//bool shiftPressed;



int createFlags(bool fullscreen)
{

    //Iniciamos com a OpenGL e paleta de hardware
    int flags = SDL_OPENGL | SDL_HWPALETTE;

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

    //Sem sucesso? Lançamos uma exceção com o erro.
    if (window == NULL)
        throw std::runtime_error(SDL_GetError());

    glViewport(0,0, width, height);

    //Configuramos a função de des-inicialização
    atexit (SDL_Quit);
}

/** Espera o usuário pressionar o x da janela. */
void processEvents(){

    SDL_Event event;

    while (SDL_PollEvent(&event) != 0){
        switch (event.type){
            case SDL_QUIT:
                exit(0); //Fechamos a aplicação
                break;

            //Testamos se a tecla foi pressionada
            case SDL_KEYDOWN:
                if(event.key.keysym.sym == SDLK_LEFT)
                    leftPressed = true;
                else if (event.key.keysym.sym == SDLK_RIGHT)
                    rightPressed = true;
                else if (event.key.keysym.sym == SDLK_UP)
                    movUp = true;
                else if (event.key.keysym.sym == SDLK_DOWN)
                    movDown = true;
                /*else if (event.key.keysym.sym == SDLK_RSHIFT || event.key.keysym.sym == SDLK_LSHIFT)
                    shiftPressed = true;*/
                else if (event.key.keysym.sym == SDLK_ESCAPE)
                    exit(0);
                break;

            //Testamos se a tecla foi solta
            case SDL_KEYUP:
                if(event.key.keysym.sym == SDLK_LEFT)
                    leftPressed = false;
                else if (event.key.keysym.sym == SDLK_UP)
                    movUp = false;
                else if (event.key.keysym.sym == SDLK_DOWN)
                    movDown = false;
                else if (event.key.keysym.sym == SDLK_RIGHT)
                    rightPressed = false;
                /*else if (event.key.keysym.sym == SDLK_RSHIFT || event.key.keysym.sym == SDLK_LSHIFT)
                    shiftPressed = false;*/

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

        //Gira o triângulo
        glRotatef(degreesToRotate, 0,0,1);
        glTranslatef(movX,movY,0);

        //Desenha o triângulo
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
    //Distância para girar (em graus) =
    //velocidade (0.180f) * tempo (ticks)
    //float distance = 0.180f * ticks;
    //degreesToRotate += distance;


    //Distância para girar (em graus) =
    //velocidade (0.180f) * tempo (ticks)
    float distance = 0.180f * ticks;
    float distance2 = 0.00180f * ticks;

    //Está com a seta esquerda pressionada?
    if (leftPressed){

        //degreesToRotate += distance;
        movX -= distance2;
    }
    //Está com a seta direita pressionada?
    else if (rightPressed){
        //degreesToRotate -= distance;
        movX += distance2;
    }
    else if (movUp){
        //degreesToRotate -= distance;
        movY += distance2;
    }
    else if (movDown){
        //degreesToRotate -= distance;
        movY -= distance2;
    }
    //else if (leftPressed && shiftPressed){
       // degreesToRotate += distance;
        //movY -= distance2;
    //}
    //else if (rightPressed && shiftPressed){
       // degreesToRotate -= distance;
        //movY -= distance2;
   // }



}

int main(int argc,char* argv[])
{
    try
    {
        setup(640, 480, 8, false); //Faz a mágica acontecer
        degreesToRotate = 0;
        movY = 0;
        movX = 0;
        lastTicks = SDL_GetTicks();

        leftPressed = false;
        rightPressed = false;
        //shiftPressed = false;
        movUp = false;
        movDown = false;


        //Loop principal do jogo
        while (true)
        {
            Uint32 thisTicks = SDL_GetTicks();
            //Calcula em ticks a diferença de tempo entre
            //o quadro atual e o anterior
            ticks = thisTicks - lastTicks;

            //Atualizamos lastTicks
            lastTicks = thisTicks;

            processEvents();
            processLogics();
            draw();

            //Trocamos a superfície de desenho
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

