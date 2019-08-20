#include "j1App.h"
#include "j1Render.h"
#include "CollisionTree.h"
#include "Collisions.h"

CollisionTree::CollisionTree()
{
	//Set the children to nullptr
	for (int i = 0; i < 4; ++i)
		nodes[i] = nullptr;
	
}

CollisionTree::CollisionTree(uint max_levels, SDL_Rect section, uint level) :Quadtree(max_levels, section, level)
{
	//Set the children to nullptr
	for (int i = 0; i < 4; ++i)
		nodes[i] = nullptr;

}

void CollisionTree::CleanUp()
{
	int i = 0;
}

void CollisionTree::Split()
{
	if (!divided)
	{
		divided = true;

		int i = 0;
		nodes[i++] = new CollisionTree(max_levels, {section.x, section.y, section.w/2, section.h/2}, level + 1);
		nodes[i++] = new CollisionTree(max_levels, { section.x + section.w / 2, section.y,section.w / 2,  section.h / 2 }, level + 1);
		nodes[i++] = new CollisionTree(max_levels, { section.x, section.y + section.h / 2,section.w / 2,  section.h / 2 }, level + 1);
		nodes[i++] = new CollisionTree(max_levels, { section.x + section.w / 2,section.y + section.h / 2 , section.w / 2,  section.h / 2 }, level + 1);
	}
}

void CollisionTree::FullSplit()
{
	if (!divided)
	{
		if (level < max_levels)
		{
			int i = 0;
			nodes[i++] = new CollisionTree(max_levels, { section.x, section.y, section.w / 2, section.h / 2 }, level + 1);
			nodes[i++] = new CollisionTree(max_levels, { section.x + section.w / 2, section.y,section.w / 2,  section.h / 2 }, level + 1);
			nodes[i++] = new CollisionTree(max_levels, { section.x, section.y + section.h / 2,section.w / 2,  section.h / 2 }, level + 1);
			nodes[i++] = new CollisionTree(max_levels, { section.x + section.w / 2,section.y + section.h / 2 , section.w / 2,  section.h / 2 }, level + 1);
			
			if (level + 1 < max_levels)
				for (int i = 0; i < 4; ++i)
					nodes[i]->FullSplit();
		}
		divided = true;
	}
}

bool CollisionTree::CheckTouch(const SDL_Rect& rect)
{
	bool ret = true;

	if (rect.x > section.x + section.w ||
		rect.x + rect.w < section.x ||
		rect.y > section.y + section.h ||
		rect.y + rect.h < section.y)
		ret = false;

	return ret;
}

void CollisionTree::DrawQuadtree()const
{
	App->render->DrawQuad(section, 255,0,0,255,false);

	if (divided)
		for (int i = 0; i < 4; ++i)
			nodes[i]->DrawQuadtree();
	
}