#include "RotatingTriangle.h"
#include "SDL.h"
#include "GL/GL.h"
#include "GameWindow.h"

RotatingTriangle::RotatingTriangle() : exit(false), degreesToRotate(0) {}

void RotatingTriangle::setup()
{}

void RotatingTriangle::processEvents(const SDL_Event& event)
{
    switch (event.type)
    {
        case SDL_QUIT:
            exit = true;
            break;
    }
}

void RotatingTriangle::processLogics()
{
    //Distância para girar (em graus) =
    //velocidade (0.180f) * tempo (ticks)
    float distance = 0.180f * GAMEWINDOW.getTicks();

    //Lemos o estado das teclas
    Uint8* keys = SDL_GetKeyState(NULL);

    //Está com a seta esquerda pressionada?
    if (keys[SDLK_LEFT])
        degreesToRotate += distance;
    //Está com a seta direita pressionada?
    else if (keys[SDLK_RIGHT])
        degreesToRotate -= distance;
}

void RotatingTriangle::draw() const
{
    glPushMatrix();
        //Limpa a tela
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT);

        //Gira o triângulo
        glRotatef(degreesToRotate, 0,0,1);

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

bool RotatingTriangle::ended()
{
    return exit;
}

void RotatingTriangle::teardown() {}
