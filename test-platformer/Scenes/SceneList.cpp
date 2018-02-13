#include "Scenes\SceneList.h"
#include "Scenes\Level1.h"

Scene::Vec* SceneList::GetSceneList()
{
	Scene::Vec* sceneList = new Scene::Vec;

	sceneList->push_back(new Level1());

	return sceneList;
}
