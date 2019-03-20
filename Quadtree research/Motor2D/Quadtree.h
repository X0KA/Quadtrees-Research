#ifndef __QUADTREE__H_
#define __QUADTREE__H_

class Quadtree {

private:

	uint max_levels;		//Max number of levels a quadtree will have
	uint level;				//Position in the tree
	SDL_Rect coords;		//Position and size
	Quadtree* nodes[4];		//Subnodes of the current node

public:

	//Constructor
	Quadtree(uint level, SDL_Rect coords);
	
	//Clear
	//virtual void Clear();
	//Split the node into 4 subnodes
	void Split();

	int GetIndex(SDL_Rect section);

	void Draw();
	
};

#endif // !__QUADTREE__H_

