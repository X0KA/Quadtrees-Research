#include "p2Defs.h"
#include "p2Log.h"
#include "SDL/include/SDL.h"

#include "Quadtree.h"
#include "j1Render.h"
#include "j1App.h"

Quadtree::Quadtree(uint level, SDL_Rect coords):level(level),coords(coords)
{
	for (int i = 0; i < 4; i++)
		nodes[i] = nullptr;

}

int Quadtree::GetIndex(SDL_Rect section)
{
	int ret = -1;


	return ret;
}

void Quadtree::Split()
{
	if (level == max_levels)
		return;

	nodes[0] = new Quadtree(level + 1, { coords.x,coords.y, coords.w / 2, coords.h / 2 });
	nodes[1] = new Quadtree(level + 1, { coords.x + coords.w / 2,coords.y, coords.w / 2, coords.h / 2 });
	nodes[2] = new Quadtree(level + 1, { coords.x,coords.y + coords.h / 2 , coords.w / 2, coords.h / 2 });
	nodes[3] = new Quadtree(level + 1, { coords.x+coords.w / 2,coords.y + coords.h/2, coords.w / 2, coords.h / 2 });
}

void Quadtree::Draw()
{
	App->render->DrawLine(coords.x, coords.y, coords.x, coords.y+ coords.h, 0,0,255);
	App->render->DrawLine(coords.x, coords.y, coords.x+ coords.w, coords.y,0,0,255);
	App->render->DrawLine(coords.x, coords.y + coords.h, coords.x + coords.w, coords.y + coords.h, 0, 0, 255);
	App->render->DrawLine(coords.x + coords.w, coords.y, coords.x + coords.w, coords.y + coords.h, 0, 0, 255);

	for (int i = 0; i < 4; ++i)
	{
		if (nodes[i] != nullptr)
			nodes[i]->Draw();
	}

}