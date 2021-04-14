#ifndef TEXTUREHANDLER_H
#define TEXTUREHANDLER_H

#include <memory>
#include <string>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include "Debug.h"
#include <glew.h>

struct Texture {
	GLuint textureID = 0;
	float width = 0.0f;
	float height = 0.0f;
	std::string textureName = "";
};
class Texturehandler
{
public:
	Texturehandler(const Texturehandler&) = delete;
	Texturehandler(Texturehandler&&) = delete;
	Texturehandler& operator=(const Texturehandler&) = delete;
	Texturehandler& operator=(Texturehandler&&) = delete;
	static Texturehandler* GetInstance();
	void OnDestroy();

	void createTexture(const std::string& textureName_, const std::string& textureFilePath_);
	const GLuint GetTexture(const std::string& textureName_);
	const Texture* GetTextureData(const std::string textureName_);

private:
	Texturehandler();
	~Texturehandler();

	static std::unique_ptr<Texturehandler> textureInstance;
	friend std::default_delete<Texturehandler>;
	static std::vector<Texture*>textures;
		
};

#endif