#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Scene.h"
#include "EntityManager.h"

#include "Quadtree.h"

j1Scene::j1Scene() : j1Module()
{
	name.assign("scene");
}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{

	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN) {
		int x, y;
		App->input->GetMousePosition(x,y);
		App->entityManager->AddEntity(x, y);
		LOG("%d colliders creaed", ++collidersCreated);
	}

	if (App->input->GetKey(SDL_SCANCODE_2) == KEY_REPEAT) {
		int x, y;
		App->input->GetMousePosition(x, y);
		App->entityManager->AddEntity(x, y);
		LOG("%d colliders creaed", ++collidersCreated);
	}

	if (App->input->GetKey(SDL_SCANCODE_3) == KEY_REPEAT) {
		for (int i =0; i < 10; ++i)
		{
			int x, y;
			App->input->GetMousePosition(x, y);
			App->entityManager->AddEntity(x, y);
			LOG("%d colliders creaed", ++collidersCreated);
		}
	}

	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	bool ret = true;

	if(App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}