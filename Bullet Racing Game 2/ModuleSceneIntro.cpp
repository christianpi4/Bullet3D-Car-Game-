#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "p2Point.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
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

	const int SnakeLength = 7;
	const float StartingSize = 0.5f;
	const float SizeIncrement = 0.2f;
	const float BallDistance = 0.3f;

	float XPosSphere = 3.f;
	float XPos = 1.f;
	float Ypos = 1.f;
	float Size = StartingSize;

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

void ModuleSceneIntro::HandleDebugInput()
{
	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
		DebugSpawnPrimitive(new Sphere());
	if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
		DebugSpawnPrimitive(new Cube());
}

void ModuleSceneIntro::DebugSpawnPrimitive(Primitive * p)
{
	primitives.PushBack(p);
	p->SetPos(App->camera->Position.x, App->camera->Position.y, App->camera->Position.z);
	
	//p->body.collision_listeners.PushBack(this);
	p->body.Push(-App->camera->Z * 1000.f);
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();

	return UPDATE_CONTINUE;
}

update_status ModuleSceneIntro::PostUpdate(float dt)
{
	for (uint n = 0; n < primitives.Count(); n++)
	{
		primitives[n]->Render();
	}

	return UPDATE_CONTINUE;
}

/*void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	Color color = Color((float)(std::rand() % 255) / 255.f, (float)(std::rand() % 255) / 255.f, (float)(std::rand() % 255) / 255.f);

	body1->parentPrimitive->color = color;
	body2->parentPrimitive->color = color;
}*/

void ModuleSceneIntro::CreateLine(float Initial_pos_x, float Initial_pos_y, float Initial_pos_z, int lenght, bool forward) {


	vec3 cube_size = { 1,3,1 };
	vec3 cube_size2 = { 1,2,1 };

	for (int n = 0; n < lenght; n++) {

		if (n % 2 == 0) {

			//Cube* c = new Cube(cube_size, 10000);
			Cube* c = new Cube(1, 3, 1);
			primitives.PushBack(c);
			c->SetPos(Initial_pos_x, Initial_pos_y, Initial_pos_z);

			c->color.r = 0.7;
			c->color.g = 0;
			c->color.b = 0;
		}

		else {

			//Cube* c = new Cube(cube_size2, 10000);
			Cube* c = new Cube(1, 2, 1);
			primitives.PushBack(c);
			c->SetPos(Initial_pos_x, Initial_pos_y, Initial_pos_z);

			c->color.r = 0;
			c->color.g = 0;
			c->color.b = 1;

		}

		if (forward == true) {
			Initial_pos_x += 1.5f;
		}
		else {
			Initial_pos_z += 1.5f;
		}
	}
}

void ModuleSceneIntro::CreateDiagonal(float Initial_pos_x, float Initial_pos_y, float Initial_pos_z, int lenght, bool forward) {

	vec3 cube_size = { 1,3,1 };
	vec3 cube_size2 = { 1,2,1 };


	for (int n = 0; n < lenght; n++) {

		if (n % 2 == 0) {

			//Cube* c = new Cube(cube_size, 10000);
			Cube* c = new Cube(1, 3, 1);
			primitives.PushBack(c);
			c->SetPos(Initial_pos_x, Initial_pos_y, Initial_pos_z);

			c->color.r = 255;
			c->color.g = 0;
			c->color.b = 0;
		}

		else {

			//Cube* c = new Cube(cube_size2, 10000);
			Cube* c = new Cube(1, 2, 1);
			primitives.PushBack(c);
			c->SetPos(Initial_pos_x, Initial_pos_y, Initial_pos_z);

			c->color.r = 0;
			c->color.g = 0;
			c->color.b = 255;

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
}
