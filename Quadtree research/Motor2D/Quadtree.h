#ifndef __QUADTREE__H_
#define __QUADTREE__H_

class Quadtree {

public:

	//Constructor
	Quadtree(uint max_levels,uint level, SDL_Rect section);

	//Split the node into 4 subnodes
	virtual void Split();

	void DrawQuadtree() const;

	bool CheckTouch(const SDL_Rect& rect);

protected:
	
	uint max_levels;		//Max number of levels a quadtree will have
	uint level;				//Position in the tree
	SDL_Rect section;		//Position and size

	//MAYBE MUST BE REMOVED
	//Quadtree* nodes[4];		//Subnodes of the current node
	
};

#endif // !__QUADTREE__H_

