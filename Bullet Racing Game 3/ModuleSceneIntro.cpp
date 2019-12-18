#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "ModuleAudio.h"


ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	for (int i = 0; i < CUBES; i++) {
		map_list[i] = nullptr;
	}
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

bool ModuleSceneIntro::Awake() {

	bool ret = true;

	node = LoadCircuit(map_file);
	
	pugi::xml_node cube;

	for (cube = node.child("cube_size"); cube && ret; cube = cube.next_sibling("cube_size")) {

		sizex = cube.attribute("x").as_int();
		sizey = cube.attribute("y").as_int();
		sizez = cube.attribute("z").as_int();
		LOG("%i %i %i", sizex, sizey, sizez);
	}

	for (cube = node.child("box"); cube && ret; cube = cube.next_sibling("box")) {
		Cube* box = new Cube(sizex, sizey+1, sizez);

		x = cube.attribute("x").as_float();
		y = cube.attribute("y").as_float();
		z = cube.attribute("z").as_float();
		rot = cube.attribute("rotation").as_int();

		LOG("%f %f %f %i", x, y, z, rot);
		
		if (cont % 2 == 0) {

			box->color.r = 0.7;
			box->color.g = 0;
			box->color.b = 0;

		}
		
		else {

			box->color.r = 0;
			box->color.g = 0;
			box->color.b = 0.7;

		}

		box->SetPos(x, y + box->size.y*0.5, z);
		box->SetRotation(rot, { 0,1,0 });
	
		map_list[cubesAdd] = box;

		cubesAdd++;
		cont++;
	}

	

	/*Sphere* auxiliar_sphere = nullptr;

	for (int n = 0; n < SnakeLength; n++)
	{
		

		if (primitives.Count() > 1) {

			App->physics->AddConstraintHinge(**primitives.At(n - 1), **primitives.At(n), btVector3{ (-s->GetRadius()),0,0 }, btVector3{ (auxiliar_sphere->GetRadius()),0,0 }, btVector3{ 0,0,1 }, btVector3{ 0,0,1 });
			App->physics->AddConstraintP2P(**primitives.At(n-1), **primitives.At(n), btVector3{ (-s->GetRadius()),0,0 }, btVector3{ (auxiliar_sphere->GetRadius()),0,0 });

		}

		auxiliar_sphere = s;
		XPos += Size + Size + SizeIncrement + BallDistance;
		Size += SizeIncrement;

	}*/
	
	return ret;
}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;



	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	for (int i = 0; i < CUBES; i++) {
		if (map_list[i] != nullptr)
		{
			Cube aux_cube = *map_list[i];
			App->physics->AddBody(aux_cube, 1000000);

		}
	}

	ramp = new Cube(14, 0.1, 10);
	ramp->color = Gold;
	ramp->SetPos(0, 1.25, 0);
	ramp->SetRotation(-15, { 1,0,0 });
	Cube aux_ramp = *ramp;
	App->physics->AddBody(aux_ramp, 0);

	ramp2 = new Cube(5, 0.1, 2.5);
	ramp2->color = Gold;
	ramp2->SetPos(10, 0, 0);
	ramp2->SetRotation(45, { 0,0,1 });
	Cube aux_ramp2 = *ramp2;
	App->physics->AddBody(aux_ramp2, 0);

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");
	for (int i = 0; i < CUBES; i++) {
		
		if (map_list[i] != nullptr) {
			
			delete map_list[i];

		}

	}

	delete ramp;
	delete ramp2;

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();
	/*Cube plane(600, 2, 600);
	plane.SetPos(0, -1, 0);
	plane.color = Cyan;
	plane.Render();

	Cube plane2(600, 2, 600);
	plane2.SetPos(0, 100, 0);
	plane2.color = Cyan;
	plane2.Render();*/

	Cube plane3(2, 100, 600);
	plane3.SetPos(-300, 50, 0);
	plane3.color = Cyan;
	plane3.Render();
	
	Cube plane4(2, 100, 600);
	plane4.SetPos(300, 50, 0);
	plane4.color = Cyan;
	plane4.Render();

	Cube plane5(600, 100, 2);
	plane5.SetPos(0, 50, -300);
	plane5.color = Cyan;
	plane5.Render();

	Cube plane6(600, 100, 2);
	plane6.SetPos(0, 50, 300);
	plane6.color = Cyan;
	plane6.Render();

	
	for (int i = 0; i < CUBES; i++) {
		
		if (map_list[i] != nullptr)
		{
			
			map_list[i]->Render();

		}
	}

	ramp->Render();
	ramp2->Render();

	App->audio->PlayMusic("Audio/barça_anthem.ogg");


	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{

}

pugi::xml_node ModuleSceneIntro::LoadCircuit(pugi::xml_document& map_file) const
{
	
	pugi::xml_node ret;

	pugi::xml_parse_result result = map_file.load_file("Map_Cube_Coords.xml");

	if (result == NULL) { 
		
		LOG("Could not load map xml file map.xml. pugi error: %s", result.description()); 

	}

	else {

		ret = map_file.child("map");

	}

	return ret;

}

