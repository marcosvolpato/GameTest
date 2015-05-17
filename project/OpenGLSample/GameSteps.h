#ifndef GAMESTEPS_H_INCLUDED
#define GAMESTEPS_H_INCLUDED

union SDL_Event;

class GameSteps
{
    public:
        virtual void setup() = 0;

        virtual void processEvents(const SDL_Event& event) = 0;
        virtual void processLogics() = 0;
        virtual void draw() const = 0;

        virtual bool ended() = 0;

        virtual void teardown() = 0;
        virtual ~GameSteps() {};
};

#endif // GAMESTEPS_H_INCLUDED

