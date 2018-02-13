#include "GameObjects\GameObject.h"

GameObject::GameObject() {

}

GameObject::~GameObject() {

}

void GameObject::SetDrawPos(Uint32 _x, Uint32 _y) {
	this->mImageData.GetDrawRect()->x = _x;
	this->mImageData.GetDrawRect()->y = _y;
	this->mImageData.GetDrawRect()->w = this->GetImageData()->GetImage()->rect->w;
	this->mImageData.GetDrawRect()->h = this->GetImageData()->GetImage()->rect->h;
	this->mImageData.SetDrawAngle(this->GetPosition()->ang);
}