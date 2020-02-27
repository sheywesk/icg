#pragma once
#include <GL/freeglut.h>

class Camera
{
public:
	Camera();
	GLfloat position[3];
	GLfloat target[3];
	~Camera() = default;
};

