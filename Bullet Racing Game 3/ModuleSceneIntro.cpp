#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	for (int i = 0; i < CUBES; i++) {
		map[i] = nullptr;
	}
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	CreateLine(10, 1, 0, 3, true);
	CreateLine(10, 1, 10, 3, false);
	CreateDiagonal(10, 1, 30, 3, true);
	CreateDiagonal(10, 1, 50, 3, false);
	
	

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();
	
	for (int i = 0; i < CUBES; i++) {
		if (map[i] != nullptr)
		{
			map[i]->Render();
		}
	}

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}

void ModuleSceneIntro::CreateLine(float Initial_pos_x, float Initial_pos_y, float Initial_pos_z, int lenght, bool forward) {


	vec3 cube_size = { 1,3,1 };
	vec3 cube_size2 = { 1,2,1 };
	int cubeAdd = 0;
	for (int n = 0; n < lenght; n++) {

		if (n % 2 == 0) {

			//Cube* c = new Cube(cube_size, 10000);
			Cube* c = new Cube(1, 3, 1);
			c->SetPos(Initial_pos_x, Initial_pos_y, Initial_pos_z);
		
			c->color.r = 0.7;
			c->color.g = 0;
			c->color.b = 0;
			map[cubeAdd] = c;
			cubeAdd++;

		}

		else {

			//Cube* c = new Cube(cube_size2, 10000);
			Cube* c = new Cube(1, 2, 1);
			c->SetPos(Initial_pos_x, Initial_pos_y, Initial_pos_z);

			c->color.r = 0;
			c->color.g = 0;
			c->color.b = 1;
			map[cubeAdd] = c;
			cubeAdd++;

		}

		if (forward == true) {
			Initial_pos_x += 1.5f;
		}
		else {
			Initial_pos_z += 1.5f;
		}
	}

	for (int i = 0; i < CUBES; i++) {
		if (map[i] != nullptr)
		{
			Cube newcube = *map[i];
			App->physics->AddBody(newcube, 10000);
			map[i]->Render();
		}
	}
}

void ModuleSceneIntro::CreateDiagonal(float Initial_pos_x, float Initial_pos_y, float Initial_pos_z, int lenght, bool forward) {

	vec3 cube_size = { 1,3,1 };
	vec3 cube_size2 = { 1,2,1 };
	int cubeAdd = 0;

	for (int n = 0; n < lenght; n++) {

		if (n % 2 == 0) {

			//Cube* c = new Cube(cube_size, 10000);
			Cube* c = new Cube(1, 3, 1);
			c->SetPos(Initial_pos_x, Initial_pos_y, Initial_pos_z);

			c->color.r = 255;
			c->color.g = 0;
			c->color.b = 0;
			map[cubeAdd] = c;
			cubeAdd++;

		}

		else {

			//Cube* c = new Cube(cube_size2, 10000);
			Cube* c = new Cube(1, 2, 1);
			c->SetPos(Initial_pos_x, Initial_pos_y, Initial_pos_z);

			c->color.r = 0;
			c->color.g = 0;
			c->color.b = 255;
			map[cubeAdd] = c;
			cubeAdd++;

		}

		if (forward == true) {
			Initial_pos_x += 1.5f;
			Initial_pos_z += 1.5f;
		}
		else {
			Initial_pos_x += 1.5f;
			Initial_pos_z -= 1.5f;
		}

	}

	for (int i = 0; i < CUBES; i++) {
		if (map[i] != nullptr)
		{
			Cube newcube = *map[i];
			App->physics->AddBody(newcube, 200000);
			map[i]->Render();
		}
	}


}

