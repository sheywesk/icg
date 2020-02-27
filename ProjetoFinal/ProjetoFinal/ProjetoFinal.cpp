#include "libs.h"


using namespace std;

#define MUSEU "Objects/Colosseum[1][1][1]-1.obj"

float angle = 0.0f, angleM = 0.0f;
float lx = 0.0f, lz = -1.0f;
float x = 0.0f, y = 1.0f, z = 5.0f;

int mainWindow;
int w, h;

std::vector<LoaderOBJ*> model;

void changeSize(int width, int heigth) {
	w = width;
	h = heigth;
	if (h == 0)
		h = 1;
	float ratio = (float)w * 1.0 / h;

	glViewport(0, 0, w, h);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.f, ratio, 1.f, 1000.f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void initModel() {
	LoaderOBJ *museu = new LoaderOBJ(MUSEU);
	if (!museu->importModel()) {
		std::cout << "Import model error!" << std::endl;
	}
	model.push_back(museu);
}

void drawModel() {
	for (int i = 0; i < model.size(); i++) {
		glPushMatrix();
		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		glStencilMask(0xFF);
		glTranslatef(0.f, 0.f, 0.f);
		glRotatef(0.0f, 0.0f, 1.f, 0.f);
		glScalef(5.f, 5.f, 5.f);
		model[i]->renderTheModel();
		glPopMatrix();

	}
}

void deleteModel() {
	delete model[0];
}

void display() {
	


}

int main(int argc, char **argv)
{
	display();

	printf("abriu");

	return 0;

}
