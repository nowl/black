#ifndef __GRAPHICS_CONTEXT_H__
#define __GRAPHICS_CONTEXT_H__

class Rect;

class GraphicsContext
{
public:
    GraphicsContext(unsigned int width, unsigned int height, bool fullscreen);
    ~GraphicsContext();

    void setViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height);
    void setOrthoView(const Rect& rect);

private:
    unsigned int width, height;
    bool fullscreen;
    SDL_Surface *screen;

    void setVideoMode();
};

void accumSetup();
void accumBlur(float amount);

#endif // __GRAPHICS_CONTEXT_H__
