#ifndef ROTATINGTRIANGLE_H_INCLUDED
#define ROTATINGTRIANGLE_H_INCLUDED
#include "GameSteps.h"

class RotatingTriangle : public GameSteps
{
    public:
        explicit RotatingTriangle();

        virtual void setup();

        virtual void processEvents(const SDL_Event& event);
        virtual void processLogics();
        virtual void draw() const;

        virtual bool ended();

        virtual void teardown();
    private:
        float degreesToRotate;
        bool exit;
};

#endif // ROTATINGTRIANGLE_H_INCLUDED
