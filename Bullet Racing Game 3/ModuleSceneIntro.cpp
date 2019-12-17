#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"


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
		
		Cube* box = new Cube(sizex, sizey, sizez);

		x = cube.attribute("x").as_float();
		y = cube.attribute("y").as_float();
		z = cube.attribute("z").as_float();
		rot = cube.attribute("rotation").as_int();

		LOG("%i %i %i", x, y, z);
		
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
	
	/*for (int i = 0; i < RAMPS; i++)
	{*/
		Cube* ramp = new Cube(20, 1, 10);
		ramp->color.r = 0;
		ramp->color.g = 0;
		ramp->color.b = 0;
		ramp->SetPos(100 + ramp->size.x*0.5, ramp->size.y*0.5, 100 + ramp->size.z*0.5);
		ramp->SetRotation(45, { 1,0,0 });

		
	//}
	
		ramp_list[rampsAdd] = ramp;
		rampsAdd++;

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
			App->physics->AddBody(aux_cube, 10000);
		}
	}

	
		if (ramp_list[0] != nullptr)
		{
			Cube aux_ramp = *ramp_list[0];
			App->physics->AddBody(aux_ramp, 10000);
		}
	


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
	/*for (int i = 0; i < RAMPS; i++) {

		if (ramp_list[i] != nullptr) {

			delete ramp_list[i];

		}

	}*/
	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();
	
	for (int i = 0; i < CUBES; i++) {
		
		if (map_list[i] != nullptr)
		{
			
			map_list[i]->Render();

		}
	}

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

