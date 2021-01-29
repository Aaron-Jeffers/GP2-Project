#pragma once
#include <string>
#include <GL\glew.h>
#include "Tran.h"
#include "GameCam.h"

class Shader
{
public:
	Shader(); //Constructor

	void BindTexture(); //Set gpu to use our shaders
	void Update(const Tran& transform, const GameCam& camera); //Updates transform and camera
	void initialise(const std::string& filename); //Initialises shader 

	std::string LoadTextureShader(const std::string& fileName);  //Loads the shader
	void CheckError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage); //Checks for errors 
	GLuint CreateTextureShader(const std::string& text, unsigned int type);

	~Shader(); //Destructor

protected:
private:
	static const unsigned int NUM_SHADERS = 2; // number of shaders

	enum
	{
		TRANSFORM_UNIFORMS,
		NUM_UNIFORMS
	};

	GLuint program; // Track the shader program
	GLuint shaders[NUM_SHADERS]; //array of shaders
	GLuint uniforms[NUM_UNIFORMS]; //no of uniform variables
};
