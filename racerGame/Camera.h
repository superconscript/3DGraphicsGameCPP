#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "GameObject.h"
enum class direction { UP, DOWN, LEFT, RIGHT, IN, BACK };
class Camera {
public:
	Camera(float* deltaTime);
	Camera(float* deltaTime, float speed, glm::vec3 cameraPosition);
	~Camera();

void	moveCamera(direction inputDirection);
void rotateCamera(direction inputDireciton);
glm::mat4 getView();
private:
	float* deltaTime;
	float cameraSpeed = 5.0f; // Default per second
	float cameraRotationSpeed = 80.0f; // horizontal rotation speed in degrees per second;
	float cameraRotationSpeedVertical = 40.0f; // Vertical rotation speed per second
//Euler Angles
	float yaw = -90.0f;
	float pitch = 0.0f;
	float roll = 0.0f;
	
	/*
	
//	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraFront = glm::normalize(directionEuler);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
//	glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);
	glm::mat4 view = glm::lookAt(cameraPos, // position
		cameraPos + cameraFront, //target
		cameraUp); // up
		*/

	glm::vec3 cameraPos = glm::vec3(0.0f, 1.0f, 3.0f);
	//	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;
	glm::vec3 cameraTarget;
	glm::vec3 cameraDirection;
	glm::vec3 up;
	glm::vec3 cameraRight;
	//	glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);
	glm::mat4 view; // up
};

class FollowCamera : Camera {
	FollowCamera(float* deltaTime, gameObject* objectToFollow); //Camera(float* deltaTime);
	FollowCamera(float* deltaTime, float speed, glm::vec3 cameraPosition, gameObject* objectToFollow);	//Camera(float* deltaTime, float speed, glm::vec3 cameraPosition);
	~FollowCamera();
//	Camera(float* deltaTime, float speed, glm::vec3 cameraPosition);

void	setTargetObject(gameObject* objectToFollow);
gameObject* getTargetObject();

private:
	gameObject* trackingObject;
};