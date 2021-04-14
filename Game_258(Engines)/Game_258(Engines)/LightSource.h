#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include <glm/glm.hpp>
#include <glew.h>


class LightSource
{
public:
	LightSource(float Ambient_,float  Diffuse_, float Specular_,glm::vec3 pos_,glm::vec3 LightColour_ );
	float GetAmbient();
	float GetDiffuse();
	float GetSpecular();
	glm::vec3 Getpos();
	glm::vec3 GetLightColour();
	void SetAmbient(float Ambient_);
	void SetDiffuse(float Diffuse_);
	void SetSpecular(float Specular_);
	void  Setpos(glm::vec3 pos_);
	void SetLightColour(glm::vec3 LightColour_);
	~LightSource();

private:
   glm::vec3 pos;
   float Ambient;
   float Diffuse;
   float Specular;
  glm::vec3 LightColour;
};

#endif