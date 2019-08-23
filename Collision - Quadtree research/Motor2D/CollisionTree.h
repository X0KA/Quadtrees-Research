#ifndef _COLLISIONTREE_H__
#define _COLLISIONTREE_H__

#include "Quadtree.h"
#include <vector>

struct Collider;

class CollisionTree : public Quadtree {

public:

	//Defuault constructor
	CollisionTree();

	//Constructor
	CollisionTree(uint max_levels, SDL_Rect section,uint level = 1);
	
	void CleanUp();

public:

	//Split the node into 4 subnodes
	void Split();

	void FullSplit();

	void DrawQuadtree() const;

	bool CheckTouch(const SDL_Rect& rect);	

	void InsertCollider(Collider* collider);

	void CleanTree();

	void DetectCollisions();

private:

	//Vector containing all the colliders
	std::vector<Collider*> colliders;

	//Children of this node
	CollisionTree* nodes[4];

private:

	bool full;
	bool empty;

};

#endif