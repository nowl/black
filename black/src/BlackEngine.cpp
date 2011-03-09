#include "Black.h"

using namespace std;

const unsigned int BlackEngine::DEFAULT_FRAMESKIP = 5;
const unsigned int BlackEngine::DEFAULT_TICKS_PER_SECOND = 30;

BlackEngine* BlackEngine::Instance = NULL;

BlackEngine::BlackEngine()
    : IsRunning(true), MaxFrameSkip(DEFAULT_FRAMESKIP),
      TicksPerSecond(DEFAULT_TICKS_PER_SECOND),
      MillisecondsPerTick(1000.0 / TicksPerSecond),
      GraphicsCon(NULL), ActiveGameState(NULL),
      Cam(NULL)
{
}

BlackEngine::~BlackEngine()
{
    GameStatesIter iter;
    iter = GameStates.begin();
    for(; iter != GameStates.end(); iter++)
        delete iter->second;

    if(GraphicsCon)
        delete GraphicsCon;
}

BlackEngine*
BlackEngine::get()
{
    if(!Instance)
        Instance = new BlackEngine();

    return Instance;
}

void
BlackEngine::switchGameState(const string name)
{
    ActiveGameState = getGameState(name);
}

GameState *
BlackEngine::getActiveGameState()
{
    return ActiveGameState;
}

GameState*
BlackEngine::getGameState(const string name)
{
    GameStatesIter iter = GameStates.find(name);
    if(iter == GameStates.end())
    {
        // doesn't exist, create this gamestate and return it
        GameState *gs = new GameState(name); 
        GameStates[name] = gs;
        return gs;
    }

    return GameStates[name];
}

GraphicsContext*
BlackEngine::getGraphicsContext()
{
    return GraphicsCon;
}

unsigned int
BlackEngine::getMilliseconds()
{
    return SDL_GetTicks();
}

void
BlackEngine::setMaxFrameSkip(unsigned long val)
{
    MaxFrameSkip = val;
}

void
BlackEngine::setTicksPerSecond(unsigned long val)
{
    TicksPerSecond = val;
    MillisecondsPerTick = 1000.0 / TicksPerSecond;
}

void
BlackEngine::mainloop()
{
    // TODO: check for ActiveGameState and possibly throw an exception
    
    unsigned long next_game_tick = getMilliseconds();

    glMatrixMode( GL_MODELVIEW );

    while(IsRunning)
    {
        handleEvents();
        
        int loops = 0;
        unsigned long tick = getMilliseconds();
        while(tick > next_game_tick && loops < MaxFrameSkip)
        {
            ActiveGameState->update(next_game_tick);

            next_game_tick += MillisecondsPerTick;
            loops++;

            tick = getMilliseconds();
        }

        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        
        float interpolation = (tick + MillisecondsPerTick - next_game_tick)/MillisecondsPerTick;
        render(interpolation);

        SDL_GL_SwapBuffers();
    }
}

void
BlackEngine::handleEvents()
{
    SDL_Event event;

    while(SDL_PollEvent(&event))
    {
        // broadcast message
        Message message("sdl-event", &event);

        ActiveGameState->sendASync(message);
    }
}

void
BlackEngine::render(float interpolation)
{
    ActiveGameState->render(interpolation);
}

bool
BlackEngine::initGraphicsContext(unsigned int width, unsigned int height, bool fullscreen)
{
    if(!GraphicsCon)
    {
        GraphicsCon = new GraphicsContext(1280, 1024, false);
        return true;
    }

    return false;
}

void
BlackEngine::setKeyRepeat(unsigned long initial, unsigned long delay)
{
    SDL_EnableKeyRepeat(initial, delay);
}

void
BlackEngine::setCamera(Camera *camera)
{
    Cam = camera;
}

Camera *
BlackEngine::getCamera()
{
    return Cam;
}
