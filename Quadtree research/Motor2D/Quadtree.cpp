#include "p2Defs.h"
#include "p2Log.h"
#include "SDL/include/SDL.h"

#include "Quadtree.h"
#include "j1Render.h"
#include "j1App.h"

Quadtree::Quadtree(uint max_levels, SDL_Rect section, uint level) :max_levels(max_levels), level(level), section(section)
{
	divided = false;
}

//void Quadtree::Split()
//{
//	if (level == max_levels || nodes[1]!=nullptr)
//		return;
//
//	nodes[0] = new Quadtree(max_levels, level + 1, { section.x,section.y, section.w /  2, section.h / 2 });
//	nodes[1] = new Quadtree(max_levels,level + 1, { section.x + section.w / 2,section.y, section.w / 2, section.h / 2 });
//	nodes[2] = new Quadtree(max_levels,level + 1, { section.x,section.y + section.h / 2 , section.w / 2, section.h / 2 });
//	nodes[3] = new Quadtree(max_levels,level + 1, { section.x+ section.w / 2,section.y + section.h/2, section.w / 2, section.h / 2 });
//}

void Quadtree::DrawQuadtree() const
{
	App->render->DrawLine(section.x, section.y, section.x, section.y+ section.h, 0,0,255);
	App->render->DrawLine(section.x, section.y, section.x+ section.w, section.y,0,0,255);
	App->render->DrawLine(section.x, section.y + section.h, section.x + section.w, section.y + section.h, 0, 0, 255);
	App->render->DrawLine(section.x + section.w, section.y, section.x + section.w, section.y + section.h, 0, 0, 255);

	/*for (int i = 0; i < 4; ++i)
	{
		if (nodes[i] != nullptr)
			nodes[i]->DrawQuadtree();
	}*/

}

bool Quadtree::CheckTouch(const SDL_Rect& rect)
{
	if (rect.x + rect.w < section.x || section.x + section.w < rect.x || rect.y + rect.h < section.y || section.y + section.h < rect.y)
	{
		return false;
	}
	return true;
}