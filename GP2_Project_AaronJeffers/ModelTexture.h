#pragma once
#include <string>
#include <GL\glew.h>

class ModelTexture
{
public:
	ModelTexture();

	void TextureBind(unsigned int unit); // bind upto 32 textures
	void initialise(const std::string& fileName);  //Initialises texture on an object

	~ModelTexture();

protected:
private:

	GLuint textureHandler;
};

