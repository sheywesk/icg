#pragma once

#include <stdio.h>
#include <GL/freeglut.h>
#include <fstream>
#include <stdlib.h>
#include <map>
#include <iostream>

//assimp include files
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"
#include "assimp/DefaultLogger.hpp"
#include "assimp/LogStream.hpp"


class LoaderOBJ
{
private:
	void recursive_render(const struct aiScene *sc, const struct aiNode *nd, float scale);
	void apply_material(const aiMaterial *mtl);
	void color4_to_float4(const aiColor4D *c, float f[4]);
	void set_float4(float f[4], float a, float b, float c, float d);
	void Color4f(const aiColor4D *color);

	std::string modelpath;

	GLfloat xrot;
	GLfloat yrot;
	GLfloat zrot;

	GLfloat LightAmbient[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat LightDiffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat LightPosition[4] = { 0.0f, 0.0f, 15.0f, 1.0f };

	const aiScene* scene = NULL;
	GLuint scene_list = 0;
	aiVector3D scene_min, scene_max, scene_center;

	//imagens/texturas
	std::map<std::string, GLuint*> textureIdMap;
	GLuint *textureIds;

	Assimp::Importer importer;


public:
	LoaderOBJ(const std::string fileName);
	~LoaderOBJ();
	void renderTheModel();
	bool importModel();
};