#include "Black.h"

using namespace std;

GraphicsContext::GraphicsContext(unsigned int width, unsigned int height, bool fullscreen)
    : width(width), height(height), fullscreen(fullscreen)
{
    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
    {
        WARN( "Unable to init SDL: %s\n", SDL_GetError() );
        exit(1);
    }

    int r = IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG);
    LOG("result of IMG_Init: %d\n", r);

    r = TTF_Init();
    LOG("result of TTF_Init: %d\n", r);

    r = Mix_Init(MIX_INIT_OGG);
    LOG("result of MIX_Init: %d\n", r);

    Mix_AllocateChannels(16);
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
        LOG("Mix_OpenAudio error: %s\n", Mix_GetError());
        exit(2);
    }

    // set up screen
    setVideoMode();
}

void
GraphicsContext::setVideoMode()
{
    // opengl
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
    int flags = SDL_OPENGL;
    if(fullscreen)
        flags |= SDL_FULLSCREEN;
    screen = SDL_SetVideoMode(width, height, 16, flags);

    /*
    int flags = SDL_SWSURFACE|SDL_DOUBLEBUF;
    if(fullscreen)
        flags |= SDL_FULLSCREEN;
    screen = SDL_SetVideoMode(width, height, 16, flags);
    */


    if ( !screen )
    {
        LOG("Unable to set video mode: %s\n", SDL_GetError());
        exit(1);
    }


    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);
}

GraphicsContext::~GraphicsContext()
{
    Mix_CloseAudio();

    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void accumSetup()
{
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
    glClearAccum(0, 0, 0, 1);
    glClear(GL_ACCUM_BUFFER_BIT);
}

void accumBlur(float amount)
{
    glAccum(GL_MULT, amount);
    glAccum(GL_ACCUM, 1-amount);
    glAccum(GL_RETURN, 1.0);
}

void
GraphicsContext::setOrthoView(const Rect& rect)
{
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho(rect.left, rect.right, rect.top, rect.bottom, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
}

void
GraphicsContext::setPerspectiveView(double fovy, double aspect, double zNear, double zFar)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    gluPerspective(fovy, aspect, zNear, zFar);
    glMatrixMode(GL_MODELVIEW);
}

void
GraphicsContext::setViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height)
{
    glViewport(x, y, width, height);
}
