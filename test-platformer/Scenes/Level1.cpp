#include "Assets.h"
#include "Graphics.h"
#include "Scenes\Level1.h"

Level1::Level1() {
	// Set current scene name
	this->SetSceneName(SceneName::Scene_Level1);
}

void Level1::SceneStart() {
	// Set scene area
	this->LevelWidth = 2000;
	this->LevelHeight = 800;
	this->Area = Graphics::CreateRect(this->LevelWidth, this->LevelHeight, 0, 0);

	this->InitObjects();
	this->InitTrees();
}

void Level1::HandleEvent(SDL_Event * Event) {

}

void Level1::Update(Uint32 timeStep) {

}

void Level1::Render() {

}

void Level1::Cleanup() {

}

void Level1::InitObjects() {
	// Create player
	player = new Player();
	player->GetPosition()->x = 10.0;
	player->GetPosition()->y = 10.0;

	// Create terrain objects
	TerrainList.push_back(new Terrain(-20.0, -20.0, 60.0, -20.0)); // Floor
	TerrainList.push_back(new Terrain(-20.0, 60.0, -20.0, -20.0)); // Left wall

	// Stuff 'em into a node list
	for (Terrain* newTerrain : TerrainList) {
		// Get the collision nodes for a terrain object
		Terrain::NodeVec* newTerrainNodes = newTerrain->GetCollisionNodes();

		// Then stuff that list into the master node list
		TerrainNodes.insert(this->TerrainNodes.end(), newTerrainNodes->begin(), newTerrainNodes->end());
	}
}

void Level1::InitTrees() {
	// Create new terrain BSP tree
	this->TerrainTree = new BSP_Tree<Terrain>();

	// Build BSP Tree of terrain objects
	BSP_Tree<Terrain>::BuildTree(this->TerrainTree, this->TerrainNodes, this->Area);
}