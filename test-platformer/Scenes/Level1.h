#ifndef _DEFAULTSCENE_H_
#define _DEFAULTSCENE_H_

#include <vector>
#include <SDL2\SDL.h>
#include "GameObjects\Terrain.h"
#include "Physics\BSP_Tree.h"
#include "Physics\Sensor.h"
#include "Scenes\Scene.h"

class Level1 : public Scene {
public:
	int LevelWidth;
	int LevelHeight;

	Terrain::Vec Terrains;
	Sensor<GameObject>::Vec TerrainSensors;
	BSP_Tree<Sensor<GameObject>>* GO_SensorTree;

	Level1();

	void SceneStart();
	void HandleEvent(SDL_Event* Event);
	void Update(Uint32 timeStep);
	void Render();
	void Cleanup();

	void InitTree();
};

#endif
