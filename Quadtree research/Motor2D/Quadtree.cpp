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

void Quadtree::DrawQuadtree() const
{
	App->render->DrawLine(section.x, section.y, section.x, section.y+ section.h, 0,0,255);
	App->render->DrawLine(section.x, section.y, section.x+ section.w, section.y,0,0,255);
	App->render->DrawLine(section.x, section.y + section.h, section.x + section.w, section.y + section.h, 0, 0, 255);
	App->render->DrawLine(section.x + section.w, section.y, section.x + section.w, section.y + section.h, 0, 0, 255);

}

bool Quadtree::CheckTouch(const SDL_Rect& rect)
{
	if ((rect.x < section.x-rect.w/2) ||
		(rect.x + rect.w) > (section.x + section.w+ rect.w / 2) ||
		(rect.y < section.y - rect.h / 2) ||
		(rect.y + rect.h) > (section.y + section.h+ rect.h / 2))
		return false;

	return true;
}