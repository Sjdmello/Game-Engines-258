#ifndef MATERIALLOADER_H
#define MATERIALLOADER_H

#include "MaterialHandler.h"
#include "Texturehandler.h"
#include <sstream>

class MaterialLoader
{
public:
	MaterialLoader(const MaterialLoader&) = delete;
	MaterialLoader(MaterialLoader&&) = delete;
	MaterialLoader& operator=(const MaterialLoader&) = delete;
	MaterialLoader& operator=(MaterialLoader&&) = delete;

	MaterialLoader() = delete;
	~MaterialLoader();

	static void LoadMaterial(std::string filePath_);
private:
	static GLuint LoadTexture(std::string fileName_);
};

#endif