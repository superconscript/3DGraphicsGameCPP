#include "Camera.h"
Camera::Camera() {

}

void Camera::moveCamera(direction inputDirection) {
	switch (inputDirection) {
		// Z Control
	case direction::IN:
		this->cameraPos += cameraFront * cameraSpeed;
		break;
	case direction::BACK:
		this->cameraPos -= cameraFront * cameraSpeed;
		break;
		// Y control
	case direction::UP:
		this->cameraPos += cameraUp * cameraSpeed;
		break;
	case direction::DOWN:
		this->cameraPos -= cameraUp * cameraSpeed;
		break;
		// X control
	case direction::RIGHT:
		this->cameraPos += cameraRight * cameraSpeed;
		break;
	case direction::LEFT:
		this->cameraPos -= cameraRight * cameraSpeed;
		break;

	}
}