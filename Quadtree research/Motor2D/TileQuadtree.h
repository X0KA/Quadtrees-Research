#ifndef _TILEQUADTREE_H__
#define _TILEQUADTREE_H__

#include "Quadtree.h"


struct TileData
{
	TileData(uint id, iPoint position) :id(id),position(position) {};
	uint id;
	iPoint position;
};

class TileQuadtree : public Quadtree
{
public:

	TileQuadtree(uint max_levels,uint level, SDL_Rect position, uint size);

	void Split();

	void DrawMap();

	void InsertTile(TileData tile);

	

protected: 

	TileQuadtree* nodes[4];	//Subnodes of the current node
	TileData* tiles;		//Array which contains all the tiles
	uint	size;			//Amount of tiles this node has
	

};

#endif // !_TILEQUADTREE_H__
