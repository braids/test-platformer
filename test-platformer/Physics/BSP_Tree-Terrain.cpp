#include "GameObjects/Terrain.h"
#include "Physics/BSP_Tree.cpp"

template void BSP_Tree<Terrain*>::FindItems(
	DataVec* items, 
	SDL_Rect* _area);

template void BSP_Tree<Terrain*>::BuildTree(
	BSP_Tree<Terrain*>* _tree, 
	NodeVec _list,
	SDL_Rect* _partition);

