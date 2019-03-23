#include "p2Defs.h"
#include "p2Point.h"
#include "p2Log.h"
#include "SDL/include/SDL.h"
#include <assert.h>

#include "j1App.h"
#include "j1Map.h"
#include "j1Render.h"

#include "TileQuadtree.h"



TileQuadtree::TileQuadtree(uint max_levels, SDL_Rect section, uint size, uint level): Quadtree(max_levels, section, level), size(size)
{
	//Set the subnodes as nullptr
	for (int i = 0; i < 4; i++)
		nodes[i] = nullptr;

	/*We will only store the tiles in the bottom nodes, 
	so, if this node will have subnodes, it won't need room for tiles*/
	if (level != max_levels)
		tiles = nullptr;

	else
	{
		tiles = new TileData[size];

		for (int i = 0; i < size; ++i)
			tiles[i] = TileData(0, { 0,0 });

	}

	tiles_contained = 0;

	assert(level <= max_levels,"MAX LEVELS > LEVELS");
}

void TileQuadtree::Split()
{
	if (level < max_levels && divided == false)
	{
		nodes[0] = new TileQuadtree(max_levels, { section.x,section.y, section.w / 2, section.h / 2 }, size / 4, level + 1);
		nodes[1] = new TileQuadtree(max_levels, { section.x + section.w / 2,section.y, section.w / 2,section.h / 2 }, size / 4, level + 1);
		nodes[2] = new TileQuadtree(max_levels, { section.x,section.y + section.h / 2 , section.w / 2, section.h / 2 }, size / 4, level + 1);
		nodes[3] = new TileQuadtree(max_levels, { section.x + section.w / 2,section.y + section.h / 2, section.w / 2,section.h / 2 }, size / 4, level + 1);
		divided = true;
	}

}

void TileQuadtree::InsertTile(TileData tile)
{
	SDL_Rect tile_rect;
	tile_rect.x = tile.position.x;
	tile_rect.y = tile.position.y;
	tile_rect.w = 64/*App->map->data.tile_width*/;
	tile_rect.h = 64/*App->map->data.tile_height*/;

	//If the node is in the lowest level, store the tile here
	if (level == max_levels)
	{
		tiles[tiles_contained++] = tile;
		LOG("tiles_contained: %d", tiles_contained);
	}

	//In case there are lower subnodes, it will be stored there
	else if (level < max_levels)			
	{
		if (this->CheckTouch({tile_rect}))
		{
			//If there are no subnodes yet, split the current node
			if (divided == false)
				Split();

			for (int i = 0; i < 4; ++i)
			{
				if (nodes[i]->CheckTouch({ tile_rect }))
				{
					nodes[i]->InsertTile(tile);
					//break;
				}
			}
		}
	}
}

void TileQuadtree::DrawQuadtree() const
{
	for (int i = 0; i < 4; ++i)
	{
		if (nodes[i] != nullptr)
			nodes[i]->DrawQuadtree();
	}

	App->render->DrawLine(section.x, section.y, section.x, section.y + section.h, 0, 0, 255);
	App->render->DrawLine(section.x, section.y, section.x + section.w, section.y, 0, 0, 255);
	App->render->DrawLine(section.x, section.y + section.h, section.x + section.w, section.y + section.h, 0, 0, 255);
	App->render->DrawLine(section.x + section.w, section.y, section.x + section.w, section.y + section.h, 0, 0, 255);

}