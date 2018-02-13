#include "Assets.h"
#include "Graphics.h"
#include "Scenes\Level1.h"

Level1::Level1() {
	// Set current scene name
	this->SetSceneName(SceneName::Scene_Level1);
}

void Level1::SceneStart() {
	
}

void Level1::HandleEvent(SDL_Event * Event) {

}

void Level1::Update(Uint32 timeStep) {

}

void Level1::Render() {

}

void Level1::Cleanup() {

}

void Level1::InitTree() {
	this->GO_SensorTree = new BSP_Tree<Sensor<GameObject>>();

	BSP_Tree<Sensor<GameObject>>::BuildTree(this->GO_SensorTree, this->TerrainSensors, Graphics::CreateRect(this->LevelWidth, this->LevelHeight, 0, 0), 16);
}