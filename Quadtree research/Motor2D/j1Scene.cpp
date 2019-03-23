#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Map.h"
#include "j1PathFinding.h"
#include "j1Scene.h"

#include "Quadtree.h"
#include "TileQuadtree.h"

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
	if(App->map->Load("iso.tmx") == true)
	{
		int w, h;
		uchar* data = NULL;
		if(App->map->CreateWalkabilityMap(w, h, &data))
			App->pathfinding->SetMap(w, h, data);

		RELEASE_ARRAY(data);
	}

	debug_tex = App->tex->Load("maps/path2.png");

	int map_height = App->map->data.height*App->map->data.tile_height;
	int map_width = App->map->data.width*App->map->data.tile_width;

	//TEST
	
	//TEST

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

	if(App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		App->render->camera.y += 1;

	if(App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		App->render->camera.y -= 1;

	if(App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		App->render->camera.x += 1;

	if(App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		App->render->camera.x -= 1;

	

	App->map->Draw();

	//TEST

	static std::list<MapLayer*>::iterator item = App->map->data.layers.begin();

	static MapLayer* prrra = *item;

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT)
	{
		
			prrra->tile_tree->InsertTile(TileData(50, { 0, 300 }));
		
			prrra->tile_tree->InsertTile(TileData(50, { 0, 800 }));
		prrra->tile_tree->InsertTile(TileData(50, { -200, 50 }));
		prrra->tile_tree->InsertTile(TileData(50, { 400, 500 }));
	}
	//TEST
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