#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

//TODO: refactor file to .h and .cpp
enum Camera_Movement
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 25.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera
{
public:
	bool attached = false;

	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;

	float Yaw;
	float Pitch;
	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;
	//TODO: refactor
	glm::mat4 vm;

	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
	{
		Position = position;
		WorldUp = up;
		Yaw = yaw;
		Pitch = pitch;
		updateCameraVectors();
	}

	glm::mat4 GetViewMatrix() const
	{
		if (attached)
		{
			return vm;
		}
		return glm::lookAt(Position, Position + Front, Up);
	}

	void setAttachedCameraView(glm::vec3 attachPosition, glm::vec3 targetPosition, float distanceFactor)
	{
		glm::vec3 offset = glm::vec3(0.0f, 0.1f, -0.5f);
		glm::vec3 cameraPosition = attachPosition + offset;
		glm::vec3 cameraTarget = attachPosition - targetPosition;
		glm::vec3 orbitalCoordinates = cameraPosition * distanceFactor;
		vm = glm::lookAt(orbitalCoordinates, cameraTarget, glm::vec3(0.0f, 1.0f, 0.0f));
		Position = orbitalCoordinates;
	}

	void ProcessKeyboard(Camera_Movement direction, float deltaTime)
	{
		if (attached)
		{
			return;
		}
		float velocity = MovementSpeed * deltaTime;
		if (direction == FORWARD)
			Position += Front * velocity;
		if (direction == BACKWARD)
			Position -= Front * velocity;
		if (direction == LEFT)
			Position -= Right * velocity;
		if (direction == RIGHT)
			Position += Right * velocity;
	}

	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
	{
		xoffset *= MouseSensitivity;
		yoffset *= MouseSensitivity;

		Yaw += xoffset;
		Pitch += yoffset;

		// make sure that when pitch is out of bounds, screen doesn't get flipped
		if (constrainPitch)
		{
			if (Pitch > 89.0f)
				Pitch = 89.0f;
			if (Pitch < -89.0f)
				Pitch = -89.0f;
		}

		updateCameraVectors();
	}

	void ProcessMouseScroll(float yoffset)
	{
		Zoom -= (float)yoffset;
		if (Zoom < 1.0f)
			Zoom = 1.0f;
		if (Zoom > 45.0f)
			Zoom = 45.0f;
	}

private:
	void updateCameraVectors()
	{
		glm::vec3 front;
		front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		front.y = sin(glm::radians(Pitch));
		front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		Front = glm::normalize(front);
		Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
		Up = glm::normalize(glm::cross(Right, Front));
	}
};
#endif
