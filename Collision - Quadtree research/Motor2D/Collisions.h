#ifndef _COLLISIONS_H__
#define _COLLISIONS_H__
#define MAX_COLLIDERS 4000

#include "j1Module.h"
#include "SDL/include/SDL.h"
#include "p2Defs.h"
#include "p2Log.h"
#include "p2Point.h"
#include "j1Module.h"
#include "j1App.h"
#include "Entity.h"
#include "CollisionTree.h"

enum COLLIDER_TYPE
{
	COLLIDER_NONE = 0,
	COLLIDER_RECT,
	COLLIDER_MAX
};

struct Collider
{
	SDL_Rect rect;
	bool active=true;
	bool to_delete = false;
	COLLIDER_TYPE type;
	Entity*		callback = nullptr;

	Collider(SDL_Rect rect, COLLIDER_TYPE type, Entity *callback = nullptr) :
		rect(rect), type(type), callback(callback) {}

	void SetPos(int x, int y)
	{
		rect.x = x;
		rect.y = y;
	}

	bool CheckCollision(const SDL_Rect& r) const;
};

class j1Collision : public j1Module
{
public:

	j1Collision();
	~j1Collision();

	bool Start() override;
	bool PreUpdate() override;
	bool PostUpdate() override;
	bool CleanUp() override;

	Collider* AddCollider(SDL_Rect rect, COLLIDER_TYPE type, Entity* entity_callback = nullptr);
	void DebugDraw();

private:

	Collider * colliders[MAX_COLLIDERS];
	bool matrix[COLLIDER_MAX][COLLIDER_MAX];
	bool debug = false;
	CollisionTree collisionTree;

};
#endif
