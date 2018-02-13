#include "Physics\BSP_Tree.h"

template <typename Data>
BSP_Tree<Data>::BSP_Tree() {
	this->partition = nullptr;
	this->list.clear();
	this->front = nullptr;
	this->back = nullptr;
}

template <typename Data>
void BSP_Tree<Data>::AddItems(NodeVec _list) {
	this->list.insert(this->list.end(), _list.begin(), _list.end());
}

template <typename Data>
void BSP_Tree<Data>::FindItems(DataVec* items, SDL_Rect* _area) {
	// If no subtrees, add current item list
	if (!this->front && !this->back) {
		// Add all node data to the data list
		items.insert(items.end(), this->list.begin(), this->list.end());
		
		// Bail outta here, we're done
		return;
	}

	// If front subtree exists and collides, check subtree
	if (this->front) {
		if (SDL_HasIntersection(this->front->partition, _area))
			front->FindItems(items, _area);
	}

	// If front subtree exists and collides, check subtree
	if (this->back) {
		if (SDL_HasIntersection(this->back->partition, _area)) {
			back->FindItems(items, _area);
		}
	}
	
	return;
}

template<typename Data>
void BSP_Tree<Data>::BuildTree(BSP_Tree* _tree, NodeVec _list, SDL_Rect* _area) {
	// Set partition
	_tree->partition = _area;

	// Initialize front/back rects
	SDL_Rect* frontRect;
	SDL_Rect* backRect;

	// Set front/back rects
	if (_tree->partition->w > _tree->partition->h) {
		int halfWidth = _tree->partition->w / 2;
		frontRect = Graphics::CreateRect(halfWidth, _tree->partition->h, _tree->partition->x, _tree->partition->y);
		backRect = Graphics::CreateRect(halfWidth, _tree->partition->h, _tree->partition->x + halfWidth, _tree->partition->y);
	}
	else {
		int halfHeight = _tree->partition->h / 2;
		frontRect = Graphics::CreateRect(_tree->partition->w, halfHeight, _tree->partition->x, _tree->partition->y);
		backRect = Graphics::CreateRect(_tree->partition->w, halfHeight, _tree->partition->x, _tree->partition->y + halfHeight);
	}

	// Initialize front/back lists
	NodeVec frontList;
	NodeVec backList;

	// Sort items into partition lists
	for (Node* item : _list) {
		if (SDL_HasIntersection(item.first, frontRect))
			frontList.push_back(item);
		if (SDL_HasIntersection(item.first, backRect))
			backList.push_back(item);
	}

	// If both lists match or one item left, don't create subtrees. This means we have a small enough space that subdivisions won't help.
	if (frontList == backList || _tree->list->size() <= BSP_Tree::MIN_TREE_ITEMS) {
		_tree->AddItems(_list);
		delete frontRect;
		delete backRect;
		return;
	}

	// If a list has items, create new sub-branch.
	if (!frontList.empty()) {
		_tree->front = new BSP_Tree();
		BSP_Tree::BuildTree(_tree->front, frontList, frontRect);
	}
	if (!backList.empty()) {
		_tree->back = new BSP_Tree();
		BSP_Tree::BuildTree(_tree->back, backList, backRect);
	}
}


// Below func uses branchlevel to determine how deep the tree goes. I don't want to delete it 
// just yet, the code can be appropriated later for neat BSP tree funcs.
/*
template <typename T>
void BSP_Tree<T>::BuildTree(BSP_Tree* _tree, NodeVec _list, SDL_Rect* _partition, int branchLevel) {
	// Set partition
	_tree->partition = _partition;

	// Add list to current tree
	_tree->AddItems(_list);

	// If no sub-branches, return.
	if (branchLevel == 0)
		return;

	SDL_Rect* frontRect;
	SDL_Rect* backRect;
	NodeVec frontList;
	NodeVec backList;


	// Set front/back rects
	if (_tree->partition->w > _tree->partition->h) {
		Uint32 halfWidth = _tree->partition->w / 2;
		frontRect = Graphics::CreateRect(halfWidth, _tree->partition->h, _tree->partition->x, _tree->partition->y);
		backRect = Graphics::CreateRect(halfWidth, _tree->partition->h, _tree->partition->x + halfWidth, _tree->partition->y);
	}
	else {
		Uint32 halfHeight = _tree->partition->h / 2;
		frontRect = Graphics::CreateRect(_tree->partition->w, halfHeight, _tree->partition->x, _tree->partition->y);
		backRect = Graphics::CreateRect(_tree->partition->w, halfHeight, _tree->partition->x, _tree->partition->y + halfHeight);
	}


	// Sort items into partition lists
	for (T* item : _list) {
		if (SDL_HasIntersection(item->Rect(), frontRect))
			frontList.push_back(item);
		if (SDL_HasIntersection(item->Rect(), backRect))
			backList.push_back(item);
	}

	// If a list has items, create new sub-branch.
	if (!frontList.empty()) {
		_tree->front = new BSP_Tree();
		BSP_Tree::BuildTree(_tree->front, frontList, frontRect, branchLevel - 1);
	}
	if (!backList.empty()) {
		_tree->back = new BSP_Tree();
		BSP_Tree::BuildTree(_tree->back, backList, backRect, branchLevel - 1);
	}
}
*/