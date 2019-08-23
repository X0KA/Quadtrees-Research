#include "j1App.h"
#include "j1Render.h"
#include "CollisionTree.h"
#include "Collisions.h"

CollisionTree::CollisionTree()
{
	//Set the children to nullptr
	for (int i = 0; i < 4; ++i)
		nodes[i] = nullptr;
	
	full = false;
	empty = true;
}

CollisionTree::CollisionTree(uint max_levels, SDL_Rect section,uint level) :Quadtree(max_levels, section, level)
{
	//Set the children to nullptr
	for (int i = 0; i < 4; ++i)
		nodes[i] = nullptr;

	full = false;
	empty = true;
}

void CollisionTree::CleanUp()
{
	//Call cleanUp for all the nodes
	for (int i = 0; i < 4; ++i)
		nodes[i]->CleanUp();

	//clear the vector with the colliders
	colliders.clear();
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
		nodes[i++] = new CollisionTree(max_levels, { section.x + section.w / 2,section.y + section.h / 2 , section.w / 2,  section.h / 2 },  level + 1);
	}
}

void CollisionTree::FullSplit()
{
	if (!divided)
	{
		if (level < max_levels)
		{
			int i = 0;
			nodes[i++] = new CollisionTree(max_levels, { section.x, section.y, section.w / 2, section.h / 2 },  level + 1);
			nodes[i++] = new CollisionTree(max_levels, { section.x + section.w / 2, section.y,section.w / 2,  section.h / 2 }, level + 1);
			nodes[i++] = new CollisionTree(max_levels, { section.x, section.y + section.h / 2,section.w / 2,  section.h / 2 }, level + 1);
			nodes[i++] = new CollisionTree(max_levels, { section.x + section.w / 2,section.y + section.h / 2 , section.w / 2,  section.h / 2 },  level + 1);
			
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
		App->render->DrawQuad(section, 255, 0, 0, 100, false);

		if (divided)
			for (int i = 0; i < 4; ++i)
				nodes[i]->DrawQuadtree();
	
	
}

void CollisionTree::InsertCollider(Collider* collider)
{
	if (CheckTouch(collider->rect))
	{
		if (level < max_levels)
			for (int i = 0; i < 4; ++i)
				nodes[i]->InsertCollider(collider);

		else if (level == max_levels)
			colliders.push_back(collider);
	}
}

void CollisionTree::CleanTree()
{
	colliders.clear();

	if (divided)
		for (int i = 0; i < 4; ++i)
			nodes[i]->CleanTree();

	full = false;
	empty = true;
}

void CollisionTree::DetectCollisions()
{
	//If the current nodes is not the leave, call the fucntion to the subnodes
	if (level < max_levels)
		for (int i = 0; i < 4; ++i)
			nodes[i]->DetectCollisions();

	//if it is, detect the collisions
	else
	{
		Collider* c1;
		Collider* c2;

		for (int i = 0; i < colliders.size(); ++i)
		{
			c1 = colliders[i];
			for (int n = i + 1; n < colliders.size(); ++n)
			{
				c2 = colliders[n];

				if (c1->CheckCollision(c2->rect))
				{
					if (App->collisions->matrix[c1->type][c2->type] && c1->callback)
						c1->callback->OnCollision(c1, c2);

					if (App->collisions->matrix[c2->type][c1->type] && c2->callback)
						c2->callback->OnCollision(c2, c1);
				}
			}
		}
	}

}