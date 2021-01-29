#pragma once
#include <glm\glm.hpp>
#include <GL\glew.h>
#include <string>
#include "object_loader.h"

struct Vertex
{
public:
	Vertex(const glm::vec3& position, const glm::vec2& textureCoordinates)
	{
		this->position = position;  //Sets position of an object
		this->textureCoordinates = textureCoordinates;  //Sets the texture coordinates for an objerct 
		this->normal = normal; //Sets the normals on an object 
	}

	glm::vec3* GetPosition() { return &position; }  //gets objects position
	glm::vec2* GetTextureCoordinates() { return &textureCoordinates; }  //Gets object's texture coordinates 
	glm::vec3* GetNormal() { return &normal; }  //Gets objects' normals 

private:
	glm::vec3 position;   
	glm::vec2 textureCoordinates;
	glm::vec3 normal;
};

/// <summary>
/// Structure to 'draw' a sphere aropund an object for collision detection
/// </summary>
struct Sphere
{
public:
	Sphere()
	{
	}
	Sphere(glm::vec3& pos, float radius)
	{
		this->position = pos;
	}

	glm::vec3 GetPosition()  //Gets sphere's position
	{
		return position;
	}
	float GetRadius() //Gets sphere's radius 
	{
		return radius;
	}

	void SetPosition(glm::vec3 position) //Sets sphere's position
	{
		this->position = position;
	}
	void SetRadius(float radius)  //Sets sphere's radius
	{
		this->radius = radius;
	}
private:
	glm::vec3 position;
	float radius;
};

class Mesh
{
public:
	Mesh();
	~Mesh();

	void drawMesh();  //draws the mesh
	void initialise(Vertex* vertices, unsigned int noVertices, unsigned int* indices, unsigned int noIndices); //initialises mesh
	void loadModel(const std::string& fileName);  //Loads the model
	void initialiseModel(const IndexedModel& model); //Initialises model 
	void updateSphereVars(glm::vec3 pos, float radius);  //Updates collision sphere data for an object

	glm::vec3 getSpherePosition()
	{
		return sphere.GetPosition();
	}
	float getSphereRadius()
	{
		return sphere.GetRadius();
	}

private:
	enum
	{
		POSITION_VERTEXBUFFER,
		TEXTURECOORDINATES_VERTEXBUFFER,
		NORMAL_VERTEXBUFFER,
		INDEX_VERTEXBUFFER,
		NO_BUFFERS
	};

	Sphere sphere;
	GLuint vertexArrayObject;
	GLuint vertexArrayBuffers[NO_BUFFERS]; // create array of buffers
	unsigned int drawCount; //how much of the vertexArrayObject to draw
};
