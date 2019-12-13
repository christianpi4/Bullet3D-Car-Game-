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

	
	/*Sphere* auxiliar_sphere = nullptr;

	for (int n = 0; n < SnakeLength; n++)
	{
		Sphere* s = new Sphere(Size, 1000);
		primitives.PushBack(s);
		s->SetPos(XPos, 3.f, 10.f);

		//TODO 2: Link all the spheres with your P2P constraints
		if (primitives.Count() > 1) {
			
			App->physics->AddConstraintHinge(**primitives.At(n - 1), **primitives.At(n), btVector3{ (-s->GetRadius()),0,0 }, btVector3{ (auxiliar_sphere->GetRadius()),0,0 }, btVector3{ 0,0,1 }, btVector3{ 0,0,1 });
			App->physics->AddConstraintP2P(**primitives.At(n-1), **primitives.At(n), btVector3{ (-s->GetRadius()),0,0 }, btVector3{ (auxiliar_sphere->GetRadius()),0,0 });
			
		}

		auxiliar_sphere = s;
		XPos += Size + Size + SizeIncrement + BallDistance;
		Size += SizeIncrement;
		
	}*/

	//Line, DiagonalF, DiagonalB
	//True = Forward			
	//False = Backward			

	
		/*CreateLine(11,1,11,7, true);
		CreateDiagonalF(21.5,1,11,4, true);
		CreateLine(27.5, 1, 17.5, 7, false);
		CreateDiagonalF(27.5, 1, 28, 4, false);*/

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
	if (App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
		DebugSpawnPrimitive(new Cylinder());
	if (App->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN)
		for (uint n = 0; n < primitives.Count(); n++)
			primitives[n]->SetPos((float)(std::rand() % 40 - 20), 10.f, (float)(std::rand() % 40 - 20));
	if (App->input->GetKey(SDL_SCANCODE_5) == KEY_DOWN)
		for (uint n = 0; n < primitives.Count(); n++)
			primitives[n]->body.Push(vec3((float)(std::rand() % 500) - 250, 500, (float)(std::rand() % 500) - 250));

	if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_DOWN)
	{
		//TODO: NEW CODE
		//A snippet of new code that may be useful for you. Nothing to do here really


		//Get a vector indicating the direction from the camera viewpoint to the "mouse"
		const vec2 mousePos(((float)App->input->GetMouseX() / (float)App->window->Width()) * 2.f - 1.f,
			-((float)App->input->GetMouseY() / (float)App->window->Height()) * 2.f + 1.f);
		const vec4 rayEye = inverse(App->renderer3D->ProjectionMatrix) * vec4(mousePos.x, mousePos.y, -1.f, 1.f);
		const vec4 rayWorld(inverse(App->camera->GetViewMatrix()) * vec4(rayEye.x, rayEye.y, -1.f, 0.f));

		vec3 Dir(rayWorld.x, rayWorld.y, rayWorld.z);
		//Cast a ray from the camera, in the "mouse" direction
		PhysBody3D* body = App->physics->RayCast(App->camera->Position, Dir);
		if (body)
		{
			//Change the color of the clicked primitive
			body->parentPrimitive->color = Color((float)(std::rand() % 255) / 255.f, (float)(std::rand() % 255) / 255.f, (float)(std::rand() % 255) / 255.f);
		}
	}
}

void ModuleSceneIntro::DebugSpawnPrimitive(Primitive * p)
{
	primitives.PushBack(p);
	p->SetPos(App->camera->Position.x, App->camera->Position.y, App->camera->Position.z);
	p->body.collision_listeners.PushBack(this);
	p->body.Push(-App->camera->Z * 1000.f);
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	Plane p(vec3(0, 1, 0));
	p.axis = true;
	p.Render();

	if (App->debug == true)
		HandleDebugInput();

	for (uint n = 0; n < primitives.Count(); n++)
		primitives[n]->Update();

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

void ModuleSceneIntro::OnCollision(PhysBody3D * body1, PhysBody3D * body2)
{
	Color color = Color((float)(std::rand() % 255) / 255.f, (float)(std::rand() % 255) / 255.f, (float)(std::rand() % 255) / 255.f);

	body1->parentPrimitive->color = color;
	body2->parentPrimitive->color = color;

}

void ModuleSceneIntro::CreateLine(float Initial_pos_x, float Initial_pos_y, float Initial_pos_z, int lenght, bool forward) {
	
	
	vec3 cube_size = { 1,3,1 };
	vec3 cube_size2 = { 1,2,1 };

	for (int n = 0; n < lenght; n++) {

		if (n % 2 == 0) {
			
			Cube* c = new Cube(cube_size, 10000);
			primitives.PushBack(c);
			c->SetPos(Initial_pos_x, Initial_pos_y, Initial_pos_z);

			c->color.r = 0.7;
			c->color.g = 0;
			c->color.b = 0;
		}

		else {

			Cube* c = new Cube(cube_size2, 10000);
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

			Cube* c = new Cube(cube_size, 10000);
			primitives.PushBack(c);
			c->SetPos(Initial_pos_x, Initial_pos_y, Initial_pos_z);

			c->color.r = 255;
			c->color.g = 0;
			c->color.b = 0;
		}

		else {

			Cube* c = new Cube(cube_size2, 10000);
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

