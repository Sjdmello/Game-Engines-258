#include "Mesh.h"

Mesh::Mesh(SubMesh& subMesh_, GLuint shaderProgram_)
	:VAO(0),VBO(0), shaderProgram(0),textureID(0), viewLoc(0),projectionLoc(0),textureLoc(0){
	subMesh = subMesh_;
	shaderProgram = shaderProgram_;
	GenerateBuffers();
}


Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	if (subMesh.vertexList.size() > 0) {
		subMesh.vertexList.clear();
	}
}

void Mesh::Render(Camera* camera_, std::vector<glm::mat4>& instances_)
{
	glUniform1i(textureLoc, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, subMesh.material.diffuseMap);

	glUniform3f(CameraLoc, camera_->GetPosition().x,
		camera_->GetPosition().y, camera_->GetPosition().z);
	//glUniform3f(LightPosLoc, camera_->GetLightSources()[0]->GetPosition.x,
		//camera_->GetLightSources()[0]->GetPosition().y, camera_->GetLightSources()[0]->GetPosition().z);
	glUniform3f(LightAmbLoc, camera_->GetPosition().x,
		camera_->GetPosition().y, camera_->GetPosition().z);

	
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetView()));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetPerspective()));

	glBindVertexArray(VAO);
	glEnable(GL_DEPTH_TEST);

	for (int i = 0; i < instances_.size(); i++) {
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(instances_[i]));
		glDrawArrays(GL_TRIANGLES, 0, subMesh.vertexList.size());
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}



void Mesh::GenerateBuffers()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, subMesh.vertexList.size() * sizeof(Vertex), &subMesh.vertexList[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));


	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, TextCoords));


	

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	modelLoc = glGetUniformLocation(shaderProgram, "model");
	viewLoc = glGetUniformLocation(shaderProgram, "view");
	projectionLoc = glGetUniformLocation(shaderProgram, "projection");
	textureLoc = glGetUniformLocation(shaderProgram, "inputTexture");
	CameraLoc = glGetUniformLocation(shaderProgram, "projection");
	LightPosLoc = glGetUniformLocation(shaderProgram, "inputTexture");
	LightDiffLoc = glGetUniformLocation(shaderProgram, "projection");
	LightAmbLoc = glGetUniformLocation(shaderProgram, "inputTexture");
	LightSpecLoc = glGetUniformLocation(shaderProgram, "projection");
	textureLoc = glGetUniformLocation(shaderProgram, "inputTexture");

}
