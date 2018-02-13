#include "Camera.h"
#include "GameObjects\GameObject.h"

Camera::Camera() {
	this->viewport = Graphics::CreateRect(0, 0, Graphics::GAMEAREA_WIDTH, Graphics::GAMEAREA_HEIGHT);
}

void Camera::Init(SDL_Rect* _viewport) {
	this->viewport = _viewport;
	this->target = nullptr;
}

Uint32 Camera::CameraOffsetX() {
	return (this->target == nullptr) ? this->viewport->x : this->target->GetImageData()->GetDrawRect()->x;
}

Uint32 Camera::CameraOffsetY() {
	return (this->target == nullptr) ? this->viewport->y : this->target->GetImageData()->GetDrawRect()->y;
}

void Camera::SetTargetGameObject(GameObject* _target) {
	this->target = _target;
}

void Camera::CenterOnTarget() {
	// Center on x
	this->viewport->x = ((int)target->GetImageData()->GetDrawRect()->x + target->GetImageData()->GetDrawRect()->w / 2) - this->viewport->w / 2;
	// Center on y
	this->viewport->y = ((int)target->GetImageData()->GetDrawRect()->y + target->GetImageData()->GetDrawRect()->h / 2) - this->viewport->h / 2;
}
