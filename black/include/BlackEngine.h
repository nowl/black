#ifndef __BLACK_ENGINE_H__
#define __BLACK_ENGINE_H__

#include <map>
#include <string>

class BlackEngine
{
public:
    static const unsigned int DEFAULT_FRAMESKIP;
    static const unsigned int DEFAULT_TICKS_PER_SECOND;

    static BlackEngine* get();

    void mainloop();
    unsigned int getMilliseconds();

	GameState *getGameState(const std::string name);
	GameState *getActiveGameState();
	void switchGameState(const std::string name);
    GraphicsContext* getGraphicsContext();

    void setMaxFrameSkip(unsigned long val);
    void setTicksPerSecond(unsigned long val);
    bool initGraphicsContext(unsigned int width, unsigned int height, bool fullscreen);
    void setKeyRepeat(unsigned long initial, unsigned long delay);

    void setCamera(Camera *camera);
    Camera *getCamera();

    bool IsRunning;

private:
    BlackEngine();
    ~BlackEngine();

    BlackEngine(const BlackEngine&);
    BlackEngine operator=(const BlackEngine&);

    void handleEvents();
    void render(float interpolation);

    static BlackEngine *Instance;

	std::map<const std::string, GameState*> GameStates;
	typedef std::map<const std::string, GameState*>::iterator GameStatesIter;
	GameState *ActiveGameState;

    GraphicsContext *GraphicsCon;
    Camera *Cam;

    unsigned int MaxFrameSkip, TicksPerSecond;
    float MillisecondsPerTick;
};

#endif // __BLACK_ENGINE_H__
