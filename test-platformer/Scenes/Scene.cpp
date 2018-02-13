#include "Assets.h"
#include "Graphics.h"
#include "Scenes\Scene.h"
#include "SceneManager.h"

Scene::Scene() {
	this->SetActive(false);
	this->SetManager(nullptr);
}

Scene::~Scene() {
}

void Scene::Init(SceneManager * manager) {
	this->SetManager(manager);
}

ImageData* Scene::AddImage(Assets::Image* _image, int _x, int _y) {
	// Init ImageData
	ImageData* newImage = new ImageData();

	// Set image and location
	newImage->SetImage(_image);
	newImage->SetDrawRectXY(_x, _y);

	// Add image to scene image list
	this->mImages.push_back(newImage);

	// Return image pointer
	return newImage;
}

ImageData* Scene::AddImage(ImageData* _imageData)
{
	// Add image to scene image list
	this->mImages.push_back(_imageData);

	// Return image pointer
	return _imageData;
}

ImageData* Scene::AddText(std::string _text, int _x, int _y) {
	// Init Image and ImageData
	ImageData* textImageData = new ImageData();
	
	// Generate text image
	textImageData->SetTexture(Graphics::Instance()->LoadText(
		Assets::Instance()->fonts.ExampleFont, _text, 255, 255, 255, 0));

	// Store text image in image data
	textImageData->CreateDrawRect();
	textImageData->SetDrawRectXY(_x, _y);
	textImageData->SetDrawAngle(0.0);
	textImageData->SetText(_text);
	// Store in scene image vector
	this->mImages.push_back(textImageData);

	return textImageData;
}

TextBox* Scene::AddTextBox(size_t _size, int _x, int _y)
{
	TextBox* textBox = new TextBox(_size, _x, _y);
	this->mImages.push_back(textBox);
	return textBox;
}

EventTimer* Scene::AddEventTimer(EventTimer* _eventTimer)
{
	this->mEventTimers.push_back(_eventTimer);
	return _eventTimer;
}

void Scene::PauseTimers() {
	// If a scene timer is running, pause it
	for (EventTimer* timer : this->mEventTimers)
		if (timer->isStarted())
			timer->pause();
}

void Scene::UnpauseTimers() {
	// If a scene timer is paused, unpause it
	for (EventTimer* timer : this->mEventTimers)
		if (timer->isPaused())
			timer->unpause();
}

void Scene::UpdateEventTimers() {
	for (EventTimer* timer : this->mEventTimers)
		if (timer->isStarted())
			timer->Update();
}

int Scene::KeycodeNumValue(SDL_Keycode _key) {
	return (_key >= SDLK_0 && _key <= SDLK_9) ? (int)_key - (int)SDLK_0 : -1;
}