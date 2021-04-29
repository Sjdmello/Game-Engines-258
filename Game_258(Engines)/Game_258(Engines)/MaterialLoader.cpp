#include "MaterialLoader.h"

MaterialLoader::~MaterialLoader()
{
}

void MaterialLoader::LoadMaterial(std::string filePath_)
{
	std::ifstream in(filePath_.c_str(), std::ios::in);
	if (!in) {
		Debug::Error("Cannot open MTL file:" + filePath_, "MaterialLoader.cpp", __LINE__);
		return;
	}
	Material m = Material();
	std::string matName = "";
	std::string line;
	while (std::getline(in, line)) {
		if (line.substr(0, 7) == "newmtl ") {
			if (m.diffuseMap != 0) {
				MaterialHandler::GetInstance()->AddMaterial(m);
				m = Material();
			}
			matName = line.substr(7);
			m.diffuseMap = LoadTexture(matName);
			m.name = matName;
		}
		if (line.substr(0,7)== "Ns ") {
			if (m.shininess != 0) {
				MaterialHandler::GetInstance()->AddMaterial(m);
				m = Material();
			}
			matName = line.substr(7);
			m.shininess = LoadTexture(matName);
			m.name = matName;
		}
		if (line.substr(4, 1) == "d ") {
			if (m.transparency != 0) {
				MaterialHandler::GetInstance()->AddMaterial(m);
				m = Material();
			}
			matName = line.substr(1);
			m.transparency = LoadTexture(matName);
			m.name = matName;
		}
		if (line.substr(1, 3) == "Kd ") {
			if (m.diffuse != 0) {
				MaterialHandler::GetInstance()->AddMaterial(m);
				m = Material();
			}
			matName = line.substr(7);
			m.diffuse = LoadTexture(matName);
			m.name = matName;
	}
		if (line.substr(2, 3) == "Ks ") {
			if (m.specular != 0) {
				MaterialHandler::GetInstance()->AddMaterial(m);
				m = Material();
			}
			matName = line.substr(7);
			m.specular = LoadTexture(matName);
			m.name = matName;
		}
	if (m.diffuseMap != 0) {
		MaterialHandler::GetInstance()->AddMaterial(m);
	}
	
	in.close();
}

GLuint MaterialLoader::LoadTexture(std::string fileName_)
{
	GLuint currentTexture = Texturehandler::GetInstance()->GetTexture(fileName_);
	if (currentTexture == 0) {
		Texturehandler::GetInstance()->createTexture(fileName_, ".Resources/Textures/" + fileName_ + ".png");
		currentTexture = Texturehandler::GetInstance()->GetTexture(fileName_);
	}
	return currentTexture;
}
