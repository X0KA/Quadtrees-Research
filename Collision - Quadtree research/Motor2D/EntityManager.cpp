#include "EntityManager.h"
#include "j1App.h"

#include "Entity.h"

EntityManager::EntityManager()
{

}

bool EntityManager::Start()
{
	

	return true;
}

bool EntityManager::Update(float dt)
{
	std::list<Entity*>::iterator it = entities.begin();
	while (it != entities.end())
	{
		(*it)->Update();

		it = next(it);
	}

	return true;
}

bool EntityManager::CleanUp()
{
	std::list<Entity*>::iterator it = entities.begin();
	while (it != entities.end())
	{
		(*it)->CleanUp();

		it = next(it);
	}
	return true;

	entities.clear();
}

Entity* EntityManager::AddEntity(int x, int y)
{
	Entity* item = nullptr;
	item = new Entity();
	
	item->section.x = x;
	item->section.y = y;
	
	entities.push_back(item);

	item->Start();

	return item;
}