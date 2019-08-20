#ifndef _ENTITY_H__
#define _ENTITY_H__

#include "SDL/include/SDL.h"
#include "p2Point.h"

struct Collider;

enum class Movement_Direction {
	NONE=0,
	UPWARDS,
	DOWNWARDS,
	LEFT,
	RIGHT
};

class Entity
{
public:

	Entity();

	bool Start();
	bool Update();
	bool CleanUp();

public:

	void Draw() const ;
	void Move();
	void OnCollision(Collider* c1, Collider* c2);

public:
	
	SDL_Rect section;
	Movement_Direction direction;
	int velocity;
	Collider* collider;
	bool hitting=false;
};

#endif
