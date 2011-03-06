#include "Black.h"

BlackEngine* BlackEngine::Instance = NULL;

BlackEngine::BlackEngine()
    : IsRunning(true), MaxFrameSkip(5), TicksPerSecond(30),
      MillisecondsPerTick(1000.0 / TicksPerSecond),
      GraphicsCon(NULL)
{
    ObjectMan = new ObjectManager();
}

BlackEngine::~BlackEngine()
{
    delete ObjectMan;

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

ObjectManager*
BlackEngine::getObjectManager()
{
    return ObjectMan;
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
    //event_queue_init();

    //game_manager_start(manager);

    unsigned long next_game_tick = getMilliseconds();

        //unsigned long fps_counter = 0;
        //unsigned long game_tick = 0;
        //unsigned long fps_start_time = black_sdl_get_tick();

    glMatrixMode( GL_MODELVIEW );

    while(IsRunning)
    {
        handleEvents();

        int loops = 0;
        unsigned long tick = getMilliseconds();
        while(tick > next_game_tick && loops < MaxFrameSkip)
        {
            getObjectManager()->update(next_game_tick);

            next_game_tick += MillisecondsPerTick;
            loops++;

            tick = getMilliseconds();
        }

        glClear(GL_COLOR_BUFFER_BIT);

        float interpolation = (tick + MillisecondsPerTick - next_game_tick)/MillisecondsPerTick;
        render(interpolation);

         //       ++fps_counter;
         /*
                if(black_sdl_get_tick() - fps_start_time > 1000)
                {
            manager->fps = fps_counter;
                        fps_counter = 0;
                        fps_start_time = black_sdl_get_tick();
                }
        */

        SDL_GL_SwapBuffers();
    }

    //event_queue_destroy();
}

void
BlackEngine::handleEvents()
{
    SDL_Event event;

    while(SDL_PollEvent(&event))
    {
        // broadcast message
        Message message("sdl-event", &event);

        getObjectManager()->sendASync(message);
    }
}

void
BlackEngine::render(float interpolation)
{
    getObjectManager()->render(interpolation);
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
