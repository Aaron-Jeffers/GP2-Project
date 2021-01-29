#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

struct GameCam
{
public:
	GameCam()
	{
	}

	//Initialises camera with a position, fov, aspect ratio, and clipping planes
	void initialiseCamera(const glm::vec3& position, float fov, float aspect, float nearClip, float farClip)
	{
		this->position = position;
		this->forward = glm::vec3(0.0f, 0.0f, 1.0f);
		this->right = glm::vec3(1.0f, 0.0f, 0.0f);
		this->up = glm::vec3(0.0f, 1.0f, 0.0f);
		this->projection = glm::perspective(fov, aspect, nearClip, farClip);
	}

	glm::vec3 getPosition() //Gets camera position
	{
		return this->position;
	}

	inline glm::mat4 GetViewProjection() const
	{
		glm::mat4 view = glm::lookAt(position, position + forward, up);
		return projection * view;//pos of camera, position camera is pointing (vector), up (vector)
	}

	glm::vec3 position;

protected:
private:
	glm::mat4 projection;
	glm::vec3 forward;
	glm::vec3 right;
	glm::vec3 up;
};