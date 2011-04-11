#include "Black.h"

using namespace std;

PickManager* PickManager::Instance = NULL;

PickManager::PickManager()
{
}

PickManager::~PickManager()
{
}

PickManager*
PickManager::get()
{
    if(!Instance)
        Instance = new PickManager();

    return Instance;
}

void list_hits(GLint hits, GLuint *names)
 {
 	int i;

 	/*
 		For each hit in the buffer are allocated 4 bytes:
 		1. Number of hits selected (always one,
 									beacuse when we draw each object
 									we use glLoadName, so we replace the
 									prevous name in the stack)
 		2. Min Z
 		3. Max Z
 		4. Name of the hit (glLoadName)
 	*/

 	printf("%d hits:\n", hits);

 	for (i = 0; i < hits; i++)
 		printf(	"Number: %d\n"
 				"Min Z: %d\n"
 				"Max Z: %d\n"
 				"Name on stack: %d\n",
 				(GLubyte)names[i * 4],
 				(GLubyte)names[i * 4 + 1],
 				(GLubyte)names[i * 4 + 2],
 				(GLubyte)names[i * 4 + 3]
 				);

 	printf("\n");
 }

void
PickManager::getPicks(int x, int y, vector<string>& objs)
{
    GLuint buff[64] = {0};
 	GLint hits, view[4];
 	int id;

 	glSelectBuffer(64, buff);
 	glGetIntegerv(GL_VIEWPORT, view);
 	glRenderMode(GL_SELECT);
 	glInitNames();
 	glPushName(0);

 	glMatrixMode(GL_PROJECTION);
 	glPushMatrix();
 		glLoadIdentity();

 		gluPickMatrix(x, y, 1.0, 1.0, view);
 		gluPerspective(BlackEngine::get()->getFieldOfVision(), 1.0, 0.0001, 1000.0);

 		glMatrixMode(GL_MODELVIEW);

 	    BlackEngine::get()->render(0);

 		glMatrixMode(GL_PROJECTION);
 	glPopMatrix();

 	hits = glRenderMode(GL_RENDER);

    list_hits(hits, buff);

 	glMatrixMode(GL_MODELVIEW);
}
