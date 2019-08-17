#ifndef __j1ENTITYMANAGER_H__
#define __j1ENTITYMANAGER_H__

#define MAX_ENEMIES 100 
#define MAX_TOWERS 8

#include "j1Module.h"
#include <list>

class Entity;

class EntityManager :public j1Module
{
public:

	EntityManager();
	~EntityManager() {}

	bool Start();
	bool Update(float dt);
	bool CleanUp();

public:

	Entity* AddEntity(int x, int y);

public:

	std::list<Entity*> entities;

};


#endif //  __j1ENTITYMANAGER_H__

