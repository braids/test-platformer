#ifndef _BSP_TREE_H_
#define _BSP_TREE_H_

#include <vector>
#include <SDL2\SDL.h>
#include "Graphics.h"

template<typename Data> class BSP_Tree {
public:
	typedef std::vector<Data> DataVec;
	typedef std::pair<SDL_Rect*, Data> Node;
	typedef std::vector<Node*>	NodeVec;

	static const int MIN_TREE_ITEMS = 1;

	SDL_Rect* partition;
	NodeVec list;
	BSP_Tree<Data>* front;
	BSP_Tree<Data>* back;

	BSP_Tree<Data>() {
		this->partition = nullptr;
		this->list.clear();
		this->front = nullptr;
		this->back = nullptr;
	};

	void AddItems(NodeVec _list);
	void FindItems(DataVec* items, SDL_Rect* _area);

	//static void BuildTree(BSP_Tree* _tree, TreeNodeVec _list, SDL_Rect* _partition, int branchLevel);
	static void BuildTree(BSP_Tree<Data>* _tree, NodeVec _list, SDL_Rect* _partition);
};

#endif
