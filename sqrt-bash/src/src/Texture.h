#pragma once

#include <GL/glew.h>
#include "stb_image.h"

class Texture {
public:
	Texture();
	Texture(char* fileloc);
	Texture(const char* fileloc);

	~Texture();

	bool Load();
	bool LoadA(); // with alpha channel
	void Use();
	void Clear();
private:
	GLuint textureID;
	int width, height, bitDepth;
	char* fileLocation;
};
