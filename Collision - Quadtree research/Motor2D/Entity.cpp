#include "Entity.h"
#include "j1Render.h"
#include "j1App.h"
#include "j1Window.h"

Entity::Entity()
{
	section = { 0,0,50,50 };
	
	direction = Movement_Direction(rand() % 4 + 1);
	
	velocity = rand() % 3 + 3;
}

bool Entity::Start()
{
	return true;
}

bool Entity::Update()
{
	Move();
	Draw();
	return true;
}

bool Entity::CleanUp()
{
	return true;
}

void Entity::Draw()
{
	App->render->DrawQuad(section,255,0,0,150);
}

void Entity::Move()
{
	switch (direction)
	{
	case Movement_Direction::NONE:
		break;
	case Movement_Direction::UPWARDS:
		section.y -= velocity;
		if (section.y < 0)
			direction = Movement_Direction::DOWNWARDS;
		break;
	case Movement_Direction::DOWNWARDS:
		section.y += velocity;
		if (section.y + section.h > App->win->GetWindowHeight())
			direction = Movement_Direction::UPWARDS;
		break;
	case Movement_Direction::LEFT:
		section.x -= velocity;
		if (section.x < 0)
			direction = Movement_Direction::RIGHT;
		break;
	case Movement_Direction::RIGHT:
		section.x += velocity;
		if (section.x+ section.w > App->win->GetWindowWidth())
			direction = Movement_Direction::LEFT;
		break;
	default:
		break;
	}

}