#include "Camera.h"
Camera::Camera(float* deltaTime) {
	this->deltaTime = deltaTime;
	glm::vec3 directionEuler;
	directionEuler.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	directionEuler.y = sin(glm::radians(pitch));
	directionEuler.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	cameraFront = glm::normalize(directionEuler);
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	cameraDirection = glm::normalize(cameraPos - cameraTarget);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	cameraRight = glm::normalize(glm::cross(up, cameraDirection));
	//	glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);
	view = glm::lookAt(cameraPos, // position
		cameraPos + cameraFront, //target
		cameraUp); // up
}

Camera::Camera(float* deltaTime, float speed, glm::vec3 cameraPosition) {
	this->deltaTime = deltaTime;
	glm::vec3 directionEuler;
	directionEuler.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	directionEuler.y = sin(glm::radians(pitch));
	directionEuler.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	this->cameraSpeed = speed;
	this->cameraPos = cameraPosition;

	cameraFront = glm::normalize(directionEuler);
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	cameraDirection = glm::normalize(cameraPos - cameraTarget);
	 up = glm::vec3(0.0f, 1.0f, 0.0f);
	cameraRight = glm::normalize(glm::cross(up, cameraDirection));
	//	glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);
	view = glm::lookAt(cameraPos, // position
		cameraPos + cameraFront, //target
		cameraUp); // up
}

void Camera::moveCamera(direction inputDirection) {
	switch (inputDirection) {
		// Z Control
	case direction::IN:
		this->cameraPos += cameraFront * cameraSpeed * (*deltaTime);
		break;
	case direction::BACK:
		this->cameraPos -= cameraFront * cameraSpeed * (*deltaTime);
		break;
		// Y control
	case direction::UP:
		this->cameraPos += cameraUp * cameraSpeed * (*deltaTime);
		break;
	case direction::DOWN:
		this->cameraPos -= cameraUp * cameraSpeed * (*deltaTime);
		break;
		// X control
	case direction::RIGHT:
		this->cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * (*deltaTime);
		break;
	case direction::LEFT:
		this->cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * (*deltaTime);
		break;

	}
	//up = glm::vec3(0.0f, 1.0f, 0.0f);
	view = glm::lookAt(cameraPos, // position
		cameraPos + cameraFront, //target
		cameraUp); // up
}

void Camera::rotateCamera(direction inputDirection) {
	switch (inputDirection){
		case direction::UP:
			this->pitch += this->cameraRotationSpeed * (*deltaTime);
			break;
		case direction::DOWN:
			this->pitch -= this->cameraRotationSpeed * (*deltaTime);
			break;
			// X control
		case direction::RIGHT:
			this->yaw += this->cameraRotationSpeed * (*deltaTime);
			break;
		case direction::LEFT:
			this->yaw -= this->cameraRotationSpeed * (*deltaTime);
			break;

		
}
	if (pitch > 89.9f) {
		pitch = 89.9f;
	}

	if (pitch < -89.9f) {
	pitch = -89.9f;
}

glm::vec3 directionEuler;
directionEuler.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
directionEuler.y = sin(glm::radians(pitch));
directionEuler.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
cameraFront = glm::normalize(directionEuler);
view = glm::lookAt(cameraPos, // position
	cameraPos + cameraFront, //target
	cameraUp); // up
}
glm::mat4 Camera::getView() {
	return this->view;
}





FollowCamera::FollowCamera(float* deltaTime, gameObject* objectToFollow) :
Camera(deltaTime){
	this->trackingObject = objectToFollow;
}


FollowCamera::FollowCamera(float* deltaTime, float speed, glm::vec3 cameraPosition, gameObject* objectToFollow) :
Camera(deltaTime, speed, cameraPosition){
	this->trackingObject = objectToFollow;
}