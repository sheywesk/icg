#include "LoaderOBJ.h"
//#include <cstdio>

bool LoaderOBJ::loadOBJ(const char * path,
	std::vector<glm::vec3> & out_vertices,
	std::vector<glm::vec2> & out_uvs,
	std::vector<glm::vec3> & out_normals)
{
	// Abre o arquivo
	//FILE * file = fopen(path, "r");
	std::ifstream file(path);

	// (FILE == NULL)
	if (!file.is_open()) {
		printf("Impossible to open the file !\n");
		return false;
	}

	while (1) {

		std::string line;
		// read the first word of the line
		int res = file.get();
		//Substitui o int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

		getline(file, line);

		if (line.compare(1, 1,"v") == 0) {
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);

			/*    TESTES:
			char v1 = vertex.x;
			file.read(&v1, sizeof(float));
			char v2 = vertex.y;
			file.read(&v2, sizeof(float));
			char v3 = vertex.z;
			file.read(&v3, sizeof(float));*/

			temp_vertices.push_back(vertex);
		}
		else if (line.compare(1, 2, "vt") == 0) {
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			/*		TESTES:
			char uv1 = uv.x;
			file.read(&uv1, sizeof(float));
			char uv2 = uv.y;
			file.read(&uv2, sizeof(float));*/

			temp_uvs.push_back(uv);
		}
		else if (line.compare(1, 2, "vn") == 0) {
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			/*		TESTES:
			char normal1 = normal.x;
			file.read(&normal1, sizeof(float));
			char normal2 = normal.y;
			file.read(&normal2, sizeof(float));
			char normal3 = normal.z;
			file.read(&normal3, sizeof(float));*/

			temp_normals.push_back(normal);
		}
		else if (line.compare(1, 1, "f") == 0) {
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			
			if (matches != 9) {
				printf("File can't be read by our simple parser : ( Try exporting with other options\n");
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
	}

	// For each vertex of each triangle
	for (unsigned int i = 0; i < vertexIndices.size(); i++) {
		unsigned int vertexIndex = vertexIndices[i];
		glm::vec3 vertex = temp_vertices[vertexIndex - 1];
		out_vertices.push_back(vertex);
	}

	for (unsigned int i = 0; i < uvIndices.size(); i++) {
		unsigned int uvIndex = uvIndices[i];
		glm::vec2 uv = temp_uvs[uvIndex - 1];
		out_uvs.push_back(uv);
	}

	for (unsigned int i = 0; i < normalIndices.size(); i++) {
		unsigned int normalIndex = normalIndices[i];
		glm::vec3 normal = temp_normals[normalIndex - 1];
		out_normals.push_back(normal);
	}
}