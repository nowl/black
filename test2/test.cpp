#include "Black.h"

#include <iostream>
#include <cmath>
#include <vector>

#include "ParticleRenderer.h"

using namespace std;

class HexRenderer : public IRenderable
{
public:
    HexRenderer(float x, float y, float z, float radius)
        : x(x), y(y), z(z), radius(radius)
    {
        r = (float)rand()/RAND_MAX;
        g = (float)rand()/RAND_MAX;
        b = (float)rand()/RAND_MAX;
    }

    virtual void Render(GraphicsContext &context, float interpolation, void *data)
    {
        //glLoadIdentity();

        //glRotatef(1.0f, 0.0f, 0.0f, 120.0f);
        //glTranslatef(x, y, -10.0f);

        glPushMatrix();
        //glLoadIdentity();

        //glRotatef(1.0f, 0.0f, 0.0f, -80.0f);

        glTranslatef(x, y, z);
        glScalef(radius, radius, 0.0f);

        glBegin( GL_TRIANGLE_FAN );
            //glTexCoord2f( 0, 0 );
            glColor3f(r, g, b);
            glVertex3f( 0.0f, 0.0f, 0.0f );
            glVertex3f( 1.0f, 0.0f, 0.0f );
            glVertex3f( 0.5f, sqrtf(3)/2, 0.0f );
            glVertex3f( -0.5f, sqrtf(3)/2, 0.0f );
            glVertex3f( -1.0f, 0.0f, 0.0f );
            glVertex3f( -0.5f, -sqrtf(3)/2, 0.0f );
            glVertex3f( 0.5f, -sqrtf(3)/2, 0.0f );
            glVertex3f( 1.0f, 0.0f, 0.0f );
        glEnd();

        glPopMatrix();
    }

private:
    float x, y, z, radius, r, g, b;
};

class FooRenderer : public IRenderable
{
public:
    virtual void Render(GraphicsContext &context, float interpolation, void *data)
    {
        //glTranslatef(1024/2, 1024/2, 0);
        //glRotatef(loop * .2, 0, 0, 1);
        //if(loop % 4000 == 0)
            //sign *= -1;
        //if(sign == 1)
            //glScalef(0.999, 0.999, 0.999);
        //else
            //glScalef(1.001, 1.001, 1.001);
        //glTranslatef(-1024/2, -1024/2, 0);

        //glRotatef(-90, 1.0, 0, 0);
        glScalef(1024, 1024, 0);
        glColor3f(1.0, 1.0, 1.0);
        glBegin( GL_QUADS );
            glTexCoord2f( 0, 0 );
            glVertex3f( 0.0f, 0.0f, 0.0f );
            glTexCoord2f( 1, 0 );
            glVertex3f( 1.0f, 0.0f, 0.0f );
            glTexCoord2f( 1, 1 );
            glVertex3f( 1.0f, 1.0f, 0.0f );
            glTexCoord2f( 0, 1 );
            glVertex3f( 0.0f, 1.0f, 0.0f );
        glEnd();
   }

};

/* assumes that x increases from left to right and y increases from
 * bottom to top
 */

class CameraController
{
public:
    CameraController(int width, int height, int screenWidth, int screenHeight)
        : dx(0), dy(0), speed(0.99), initSpeed(5),
          destW(0), destH(0), dw(0), dh(0), xrotate(0), yrotate(0),
          screenWidth(screenWidth), screenHeight(screenHeight)
    {
        glViewport( 0, 0, width, height );
    }

    void reset()
    {
        glMatrixMode( GL_MODELVIEW );
        glLoadIdentity();
    }

    void update()
    {
        reset();
        #define PI 3.1415926f
        float x = 80 * sin(yrotate*PI/180);
        float z = 80 * cos(yrotate*PI/180);

        float y = 100 * abs(cos(xrotate*PI/180));


        gluLookAt(x, y, z, 0, 0, 0, 0, 1.0, 0);

    }

    void startDragging(int x, int y)
    {
        startX = x;
        startY = y;
    }

    void draggedTo(int x, int y)
    {
        int xDiff = x - startX;
        int yDiff = y - startY;
        xrotate += yDiff;
        yrotate += xDiff;
        startX = x;
        startY = y;
    }

    void setProjCam()
    {
        glMatrixMode( GL_PROJECTION );
        glLoadIdentity();
        //glOrtho(rect.left, rect.right, rect.top, rect.bottom, -1.0f, 1.0f);
        //glFrustum(-10, 10, -10, 10, 2, 20);
        //glFrustum(-10, 10, -10, 10, 15, 100);
        gluPerspective(60, 1.0, 15, 500);
    }

    void setProjOrtho()
    {
        glMatrixMode( GL_PROJECTION );
        glLoadIdentity();
        glOrtho(0, 1024, 0, 1024, -1.0f, 1.0f);
    }

private:

    float destX, destY, dx, dy, speed, initSpeed;
    float destW, destH, dw, dh;
    int screenWidth, screenHeight;
    int startX, startY;
    int xrotate, yrotate;
};

int main(int argc, char *argv[])
{
    srand(time(NULL));

    GraphicsContext gc(1024, 1024, false);

    vector<IRenderable*> renderers;
    GameObject foo;
    foo.setRenderer(new FooRenderer());

    float rad = 1;
    for(int x=0; x<100; x++) {
        for(int y=0; y<100; y++) {
            if(x % 2 == 0)
                renderers.push_back(new HexRenderer(5 + 3.0/2*rad * x, 5 + sqrtf(3)*rad * y, 0, rad));
            else
                renderers.push_back(new HexRenderer(5 + 3.0/2*rad * x, 5 + (2*y+1) * sqrtf(3)/2*rad, 0, rad));

        }
    }

    ParticleRenderer *particles = new ParticleRenderer(0, 0, 0, 1000);

    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
    glClear( GL_COLOR_BUFFER_BIT );

    CameraController camera(1024, 1024, 1024, 1024);

    float w = 1024;
    float h = 1024;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Shader shader("particle.vert", "particle.frag");

    FileImageTexture particle_texture("part.bmp");

    // Framebuffer stuff
    FrameBuffer fbo(1024, 1024);

    accumSetup();

    // message processing loop
    SDL_Event event;
    bool done = false;
    bool dragging = false;
    //foo.sign = -1;
    bool running = true;
    int loop = 0;
    while(!done) {
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
                done = true;
            else if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_a)
                running = !running;
            else if(event.type == SDL_MOUSEBUTTONDOWN)
            {
                dragging = true;
                camera.startDragging(event.button.x, event.button.y);
            }
            else if(event.type == SDL_MOUSEBUTTONUP)
                dragging = false;
            else if(event.type == SDL_MOUSEMOTION && dragging)
                camera.draggedTo(event.motion.x, event.motion.y);
        }

        camera.setProjCam();

        camera.update();

        if(loop%4 == 0 & running)
            particles->update();

        fbo.bind();

        glClear(GL_COLOR_BUFFER_BIT);

        /*
        glPushMatrix();
        glTranslatef(-60.0f, 0.0f, 60.0f);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        vector<IRenderable*>::iterator iter = renderers.begin();
        while(iter != renderers.end())
        {
            (*iter)->Render(gc, 0, NULL);
            iter++;
        }
        glPopMatrix();
        */

        particle_texture.bind();
        particles->Render(gc, 0, NULL);
        particle_texture.unbind();

        glFlush();

        fbo.unbind();


        camera.setProjOrtho();
        camera.reset();

        glClear(GL_COLOR_BUFFER_BIT);

        shader.bind();

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, fbo.getTexture());

        shader.setUniformInt("tex0", GL_TEXTURE0);

        foo.render(gc, 0);

        glBindTexture( GL_TEXTURE_2D, 0 );

        shader.unbind();

        glFlush();

        accumBlur(0.95);

        glFlush();

        SDL_GL_SwapBuffers();


        loop++;
    }

    return 0;
}
