#include "libs.h"

using namespace std;

#define MUSEU "Objects/Colosseum[1][1][1]-1.obj"

//posições da camera
float angle = 0.0f, angleM = 0.f;
float lx = 0.0f, lz = -1.0f;
float x = 0.0f, y = 1.f, z = 5.0f;

GLuint texture[34];

int mainWindow;
int w, h;

std::vector<LoaderOBJ*> models;

void initTexture() {
	glEnable(GL_DEPTH_TEST);
	glGenTextures(34, texture);
	
}

void changeSize(int width, int heigth) {
	w = width;
	h = heigth;
	if (h == 0) {
		h = 1;
	}

	float ratio = (float)w * 1.0 / h;

	glViewport(0, 0, w, h);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.f, ratio, 1.f, 1000.f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void initModels() {
	LoaderOBJ *museu = new LoaderOBJ(MUSEU);
	if (!museu->importModel()) {
		std::cout << "Import model error!" << std::endl;
	}
	models.push_back(museu);
}

void drawModels() {
	for (int i = 0; i < models.size(); i++) {
		glPushMatrix();
		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		glStencilMask(0xFF);
		glTranslatef(0.f, 0.f, 0.f);
		glRotatef(0.f, 0.f, 1.f, 0.f);
		glScalef(5.f, 5.f, 5.f);
		models[i]->renderTheModel();
		glPopMatrix();
	
	}
}

void deleteModels() {
	delete models[0];
}

void init() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	//glFrontFace(GL_CW);

	// register callbacks
	glutIgnoreKeyRepeat(1);
	

	initModels();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE | GLUT_STENCIL);
	glutInitWindowPosition(150, 0);
	glutInitWindowSize(800, 600);
	mainWindow = glutCreateWindow("JANELINHA");

	glutReshapeFunc(changeSize);

	

	glutMainLoop();


	return 0;

}
