#include "Collisions.h"
#include "j1Render.h"
#include "j1App.h"
#include "j1Input.h"
#include "CollisionTree.h"
#include "j1Window.h"


j1Collision::j1Collision()
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	matrix[COLLIDER_NONE][COLLIDER_NONE] = false;
	matrix[COLLIDER_NONE][COLLIDER_RECT] = false;
	matrix[COLLIDER_NONE][COLLIDER_MAX] = false;

	matrix[COLLIDER_RECT][COLLIDER_RECT] = true;
	matrix[COLLIDER_RECT][COLLIDER_NONE] =false;
	matrix[COLLIDER_RECT][COLLIDER_MAX] = false;

	matrix[COLLIDER_MAX][COLLIDER_MAX] = false;
	matrix[COLLIDER_MAX][COLLIDER_NONE] = false;
	matrix[COLLIDER_MAX][COLLIDER_RECT] = false;

	

}

// Destructor
j1Collision::~j1Collision()
{}

bool j1Collision::Start()
{
	SDL_Rect screenRect = { 0,0,0,0 };
	screenRect.w = App->win->GetWindowWidth();
	screenRect.h = App->win->GetWindowHeight();

	collisionTree = CollisionTree(5, screenRect);

	collisionTree.FullSplit();

	return true;
}

bool j1Collision::PreUpdate()
{
	// Remove all colliders scheduled for deletion
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr && colliders[i]->to_delete == true)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	// Calculate collisions
	Collider* c1;
	Collider* c2;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		// skip empty colliders
		if (colliders[i] == nullptr)
			continue;

		c1 = colliders[i];

		// avoid checking collisions already checked
		for (uint k = i + 1; k < MAX_COLLIDERS; ++k)
		{
			// skip empty colliders
			if (colliders[k] == nullptr)
				continue;

			c2 = colliders[k];

			if (c1->active == true && c2->active == true)
			{

				if (c1->CheckCollision(c2->rect) == true)
				{

					if (matrix[c1->type][c2->type] && c1->callback)
						c1->callback->OnCollision(c1, c2);

					if (matrix[c2->type][c1->type] && c2->callback)
						c2->callback->OnCollision(c2, c1);

				}
			}
		}
	}

	

	return true;

}

// Called before render is available
bool j1Collision::PostUpdate()
{

	DebugDraw();

	collisionTree.DrawQuadtree();

	return true;
}

void j1Collision::DebugDraw()
{

	if (App->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN)
		debug = !debug;

	if (debug == false)
		return;

	Uint8 alpha = 200;
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
			continue;

		if (colliders[i]->active == true)
		{
			switch (colliders[i]->type)
			{
			case COLLIDER_NONE: // white
				App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
				break;
			case COLLIDER_RECT: // red
				App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
				break;
			}
		}

	}
}

// Called before quitting
bool j1Collision::CleanUp()
{
	LOG("Freeing all colliders");

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

Collider* j1Collision::AddCollider(SDL_Rect rect, COLLIDER_TYPE type, Entity* callback)
{
	Collider* ret = nullptr;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect, type, callback);
			break;
		}
	}

	return ret;
}

bool Collider::CheckCollision(const SDL_Rect& r) const
{

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (rect.x + rect.w < r.x || r.x + r.w < rect.x || rect.y + rect.h < r.y || r.y + r.h < rect.y)
		{
			return false;
		}
	}
	return true;
}
