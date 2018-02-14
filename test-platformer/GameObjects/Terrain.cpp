#include "GameObjects\Terrain.h"

Terrain::Terrain() {

}

Terrain::Terrain(double x1, double y1, double x2, double y2) {
	this->CollisionLine.SetPoints(x1, y1, x2, y2);
}

void Terrain::Update(Uint32 ticks) {

}

SDL_Rect* Terrain::GetCollisionRect() {
	// Return the rect around the collision line
	return this->CollisionLine.Rect();
}

Terrain::NodeVec* Terrain::GetCollisionNodes() {
	// Create new node list
	Terrain::NodeVec* nodes = new Terrain::NodeVec();
	
	// Add nodes (collision rects and self pointer)
	nodes->push_back(new Terrain::Node(this->GetCollisionRect(), this));
	
	// Return node list
	return nodes;
}
