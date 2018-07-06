#include "Assets.h"
#include "Graphics.h"
#include "Scenes\Level1.h"
#include "GameObjects\Terrain.h"
#include "Physics\BSP_Tree.h"

// Forward dec the SceneManager
class SceneManager;

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
	//player->ClearInput();

	switch (Event->type) {
	case SDL_KEYDOWN:
		if (Event->key.keysym.sym == SDLK_a) {
			player->inputLeft = true;
		}

		if (Event->key.keysym.sym == SDLK_d) {
			player->inputRight = true;
		}

		if (Event->key.keysym.sym == SDLK_SPACE) {
			player->inputJump = true;
		}
		break;

	case SDL_KEYUP:
		if (Event->key.keysym.sym == SDLK_a) {
			player->inputLeft = false;
		}
		
		if (Event->key.keysym.sym == SDLK_d) {
			player->inputRight = false;
		}

		if (Event->key.keysym.sym == SDLK_SPACE) {
			player->inputJump = false;
		}
		break;

	default:
		break;
	}
}

void Level1::Update(Uint32 timeStep) {
	player->Update(timeStep);
}

void Level1::Render() {	
	for (Terrain* terrain : this->TerrainList)
		this->mGraphics->DrawLine(255, 255, 255,
			terrain->CollisionLine->Points.front()->x + 50,
			terrain->CollisionLine->Points.front()->y + 150,
			terrain->CollisionLine->Points.back()->x + 50,
			terrain->CollisionLine->Points.back()->y + 150);
	/*for (Terrain::TreeNode* terrain : this->TerrainNodes)
		this->mGraphics->DrawLine(255, 255, 255,
			terrain->first->x + 20,
			terrain->first->y + 20,
			terrain->first->x + terrain->first->w + 20,
			terrain->first->y + terrain->first->h + 20);
			*/
	this->mGraphics->DrawLine(50, 50, 255,
		this->player->BodyCollision->x + 50,
		this->player->BodyCollision->y + 150,
		this->player->BodyCollision->x + this->player->BodyCollision->w + 50,
		this->player->BodyCollision->y + this->player->BodyCollision->h + 150);
	this->mGraphics->DrawLine(50, 50, 255,
		this->player->BodyCollision->x + this->player->BodyCollision->w + 50,
		this->player->BodyCollision->y + 150,
		this->player->BodyCollision->x + 50,
		this->player->BodyCollision->y + this->player->BodyCollision->h + 150);
	
	if (player->inputLeft)
		this->mGraphics->DrawLine(255, 50, 255, 5, 5, 5, 10);
	if (player->inputJump)
		this->mGraphics->DrawLine(255, 255, 50, 10, 5, 10, 10);
	if (player->inputRight)
		this->mGraphics->DrawLine(50, 255, 255, 15, 5, 15, 10);

	if (player->GetPosition()->xspd < 0.0)
		this->mGraphics->DrawLine(50, 50, 255, 5, 15, 5, 20);
	if (player->GetPosition()->xspd == 0.0)
		this->mGraphics->DrawLine(50, 255, 50, 10, 15, 10, 20);
	if (player->GetPosition()->xspd > 0.0)
		this->mGraphics->DrawLine(255, 50, 50, 15, 15, 15, 20);

	if (player->L_Hit())
		this->mGraphics->DrawLine(0, 0, 50, 5, 25, 5, 30);
	if (player->R_Hit())
		this->mGraphics->DrawLine(50, 0, 0, 15, 25, 15, 30);
}

void Level1::Cleanup() {

}

void Level1::InitObjects() {
	// Create player
	player = new Player();
	
	player->GetPosition()->x = 100.0;
	player->GetPosition()->y = -400.0;

	// Clear terrain list
	TerrainList.clear();

	// Create terrain objects
	TerrainList.push_back(new Terrain(-20.0, 20.0, 210.0, 20.0)); // Floor
	TerrainList.push_back(new Terrain(-20.0, -60.0, -20.0, 20.0)); // Left wall
	TerrainList.push_back(new Terrain(210.0, -60.0, 210.0, 20.0)); // Right wall

	// Stuff 'em into a node list
	for (Terrain* newTerrain : TerrainList) {
		// Get the collision nodes for a terrain object
		Terrain::TreeNodeVec* newTerrainNodes = newTerrain->GetCollisionNodes();

		// Then stuff that list into the master node list
		TerrainNodes.insert(this->TerrainNodes.end(), newTerrainNodes->begin(), newTerrainNodes->end());
	}
}

void Level1::InitTrees() {
	// Create new terrain BSP tree
	this->TerrainTree = new Terrain::Tree();

	// Build BSP Tree of terrain objects
	Terrain::Tree::BuildTree(this->TerrainTree, this->TerrainNodes, this->Area);

	// Load tree references into objects
	this->player->SetTerrainTree(this->TerrainTree);
}