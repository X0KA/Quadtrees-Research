#include "p2Defs.h"
#include "p2Point.h"
#include "p2Log.h"
#include "SDL/include/SDL.h"

#include "j1App.h"
#include "j1Map.h"

#include "TileQuadtree.h"



TileQuadtree::TileQuadtree(uint max_levels, uint level, SDL_Rect section, uint size): Quadtree(max_levels,level, section), size(size)
{
	for (int i = 0; i < 4; i++)
		nodes[i] = nullptr;

}

void TileQuadtree::Split()
{
	if (level == max_levels || nodes[1] != nullptr)
		return;

	nodes[0] = new TileQuadtree(max_levels,level + 1, { section.x,section.y, section.w / 2, section.h / 2 }, size/4);
	nodes[1] = new TileQuadtree(max_levels,level + 1, { section.x + section.w / 2,section.y, section.w / 2,section.h / 2 },size / 4);
	nodes[2] = new TileQuadtree(max_levels,level + 1, { section.x,section.y + section.h / 2 , section.w / 2, section.h / 2 }, size / 4);
	nodes[3] = new TileQuadtree(max_levels,level + 1, { section.x + section.w / 2,section.y + section.h / 2, section.w / 2,section.h / 2 }, size / 4);
}

void TileQuadtree::InsertTile(TileData tile)
{
	//In case there are lower subnodes, it will be stored there
	if (level < max_levels)			
	{
		
		//If there are no subnodes yet, split the current node
		if (nodes[0] == nullptr)	
			Split();

		for (int i = 0; i < 4; ++i)
		{
			if (nodes[i]->CheckTouch({ tile.position.x, tile.position.y, App->map->data.tile_width,App->map->data.tile_height }))
			{
				nodes[i]->InsertTile(tile);
				break;
			}
		}

	}

	else
	{

	}

}