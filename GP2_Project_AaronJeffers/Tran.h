#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "GameCam.h"

struct Tran
{
public:
	Tran(const glm::vec3& position = glm::vec3(), const glm::vec3& rotation = glm::vec3(), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f))
	{
		this->position = position;
		this->rotation = rotation;
		this->scale = scale;
	}

	inline glm::mat4 GetModel() const
	{
		glm::mat4 posMat = glm::translate(position);
		glm::mat4 scaleMat = glm::scale(scale);
		glm::mat4 rotX = glm::rotate(rotation.x, glm::vec3(1.0, 0.0, 0.0));
		glm::mat4 rotY = glm::rotate(rotation.y, glm::vec3(0.0, 1.0, 0.0));
		glm::mat4 rotZ = glm::rotate(rotation.z, glm::vec3(0.0, 0.0, 1.0));
		glm::mat4 rotMat = rotX * rotY * rotZ;

		return posMat * rotMat * scaleMat;
	}

	inline glm::vec3* GetPosition() { return &position; } //getters
	inline glm::vec3* GetRotation() { return &rotation; }
	inline glm::vec3* GetScale() { return &scale; }

	inline void SetPosition(const glm::vec3& position) { this->position = position; } // setters
	inline void SetRotation(const glm::vec3& rotation) { this->rotation = rotation; }
	inline void SetScale(const glm::vec3& scale) { this->scale = scale; }
protected:
private:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
};


