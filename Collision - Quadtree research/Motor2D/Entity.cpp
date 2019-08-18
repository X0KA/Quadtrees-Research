#include "Entity.h"
#include "j1Render.h"
#include "j1App.h"
#include "j1Window.h"

#include "Collisions.h"

Entity::Entity()
{
	section = { 0,0,20,20 };
	
	direction = Movement_Direction(rand() % 4 + 1);
	
	velocity = rand() % 4 + 3;
}

bool Entity::Start()
{
	
	collider = App->collisions->AddCollider(section, COLLIDER_RECT,this);

	return true;
}

bool Entity::Update()
{
	Move();
	Draw();
	collider->SetPos(section.x, section.y);
	hitting = false;
	return true;
}

bool Entity::CleanUp()
{
	return true;
}

void Entity::Draw()
{
	if (!hitting)
		App->render->DrawQuad(section,255,0,0,150);

	else
		App->render->DrawQuad(section, 0, 255, 0, 150);
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

void Entity::OnCollision(Collider* c1, Collider* c2)
{
	hitting = true;
}