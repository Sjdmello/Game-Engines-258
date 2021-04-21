#ifndef MESH_H
#define MESH_H

#include <glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include"Camera.h"
#include "MaterialHandler.h"

struct Vertex {
	glm::vec3 pos;
	glm::vec3 normal;
	glm::vec2 TextCoords;
	

};

struct SubMesh {
	std::vector<Vertex> vertexList;
	std::vector<unsigned int> meshIndices;
	Material material;
};

class Mesh
{
public:
	Mesh(SubMesh& subMesh_, GLuint shaderProgram_);
	~Mesh();

	void Render(Camera*camera_,std::vector<glm::mat4>& instances_);

private: 
	void GenerateBuffers();
	GLuint VAO, VBO;
	SubMesh subMesh;
	GLuint shaderProgram;
	GLuint modelLoc;
	GLuint textureID;
	GLuint viewLoc, projectionLoc,textureLoc;
	GLuint CameraLoc, LightPosLoc, LightDiffLoc, LightAmbLoc, LightSpecLoc,LightColourLoc;
};

#endif