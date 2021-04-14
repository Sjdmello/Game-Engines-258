#include "LightSource.h"

LightSource::LightSource(float Ambient_,float Diffuse_,float Specular_, glm::vec3 pos_, glm::vec3 LightColour_)
{
	pos = pos_;
	 Ambient = Ambient_;
	 Diffuse = Diffuse_;
	 Specular = Specular_;
	LightColour = LightColour_;
	
}

float LightSource::GetAmbient()
{
	return Ambient;
}

float LightSource::GetDiffuse()
{
	return Diffuse;
}



void LightSource::Setpos(glm::vec3 pos_)
{
	pos = pos_;
}

void LightSource::SetLightColour(glm::vec3 LightColour_)
{
	LightColour = LightColour_;
}

LightSource::~LightSource()
{
}

float LightSource::GetSpecular()
{
	return Specular;
}

glm::vec3 LightSource::Getpos()
{
	return  pos;
}

glm::vec3 LightSource::GetLightColour()
{
	return LightColour;
}

void LightSource::SetAmbient(float Ambient_)
{
	Ambient = Ambient_;
}

void LightSource::SetDiffuse(float Diffuse_)
{
	Diffuse = Diffuse_;
}

void LightSource::SetSpecular(float Specular_)
{
	Specular = Specular_;
}
