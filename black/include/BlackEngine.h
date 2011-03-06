#ifndef __BLACK_ENGINE_H__
#define __BLACK_ENGINE_H__

class BlackEngine
{
public:
    static BlackEngine* get();

    void mainloop();
    unsigned int getMilliseconds();

    ObjectManager* getObjectManager();
    GraphicsContext* getGraphicsContext();

    void setMaxFrameSkip(unsigned long val);
    void setTicksPerSecond(unsigned long val);
    bool initGraphicsContext(unsigned int width, unsigned int height, bool fullscreen);

    bool IsRunning;

private:
    BlackEngine();
    ~BlackEngine();

    BlackEngine(const BlackEngine&);
    BlackEngine operator=(const BlackEngine&);

    void handleEvents();
    void render(float interpolation);

    static BlackEngine *Instance;

    ObjectManager *ObjectMan;
    GraphicsContext *GraphicsCon;

    unsigned int MaxFrameSkip, TicksPerSecond;
    float MillisecondsPerTick;
};

#endif // __BLACK_ENGINE_H__
