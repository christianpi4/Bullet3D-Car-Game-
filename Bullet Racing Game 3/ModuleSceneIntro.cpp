#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "PhysVehicle3D.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	for (int i = 0; i < CUBES; i++) {
		map_list[i] = nullptr;
	}

	for (int i = 0; i < SPHERES; i++) {
		sphere_list[i] = nullptr;
	}

	for (int j = 0; j < SPHERES2; j++) {
		sphere_list2[j] = nullptr;
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

	for (cube = node.child("hinge"); cube && ret; cube = cube.next_sibling("hinge")) {

		hingex = cube.attribute("x").as_float();
		hingey = cube.attribute("y").as_float();
		hingez = cube.attribute("z").as_float();

		hinge2x = cube.attribute("x2").as_float();
		hinge2y = cube.attribute("y2").as_float();
		hinge2z = cube.attribute("z2").as_float();

		radius = cube.attribute("r").as_float();

		LOG("%f %f %f %f %f %f %f", hingex, hingey, hingez, hinge2x, hinge2y, hinge2z, radius);

		Sphere* sphere = new Sphere(radius);
		sphere->SetPos(hingex, hingey, hingez);

		Sphere* sphere2 = new Sphere(radius);
		sphere2->SetPos(hinge2x, hinge2y, hinge2z);
		
		sphere_list[sphereAdd] = sphere;
		sphere_list2[sphereAdd2] = sphere2;

		sphereAdd++;
		sphereAdd2++;

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

	App->audio->PlayMusic("Audio/barca_anthem.ogg");

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	for (int i = 0; i < CUBES; i++) {
		if (map_list[i] != nullptr)
		{
			Cube aux_cube = *map_list[i];
			App->physics->AddBody(aux_cube, 1000000);

		}
	}

	for (int i = 0; i < SPHERES; i++) {

		for (int j = 0; j < SPHERES2; j++) {

			if (sphere_list[i] != nullptr)
			{
				if (sphere_list2[j] != nullptr)
				{

					Sphere aux_sphere = *sphere_list[i];
					Sphere aux_sphere2 = *sphere_list2[j];
					PhysBody3D* bodyA = App->physics->AddBody(aux_sphere, 1);
					PhysBody3D* bodyB = App->physics->AddBody(aux_sphere2, 1);
					App->physics->AddConstraintHinge(*bodyA, *bodyB, { 0,0,0 }, { 3,0,0 }, { 0,1,0 }, { 0,1,0 }, false);

				}

			}
		}

	}

	ramp = new Cube(14, 0.1, 10);
	ramp->color = Gold;
	ramp->SetPos(0, 1.25, 0);
	ramp->SetRotation(-15, { 1,0,0 });
	Cube aux_ramp = *ramp;
	App->physics->AddBody(aux_ramp, 0);

	ramp2 = new Cube(10, 0.1, 14);
	ramp2->color = Gold;
	ramp2->SetPos(-20, 1.23, 97.5f);
	ramp2->SetRotation(25, { 0,0,-1 });
	Cube aux_ramp2 = *ramp2;
	App->physics->AddBody(aux_ramp2, 0);

	CheckPoint({ 0,2,20 });

	App->audio->PlayMusic("Audio/avicii.ogg");

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

	for (int i = 0; i < SPHERES; i++) {

		if (sphere_list[i] != nullptr) {

			if (sphere_list2[i] != nullptr) {

				delete sphere_list[i];
				delete sphere_list2[i];

			}

		}

	}


	delete ramp;
	delete ramp2;

	
	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	/*Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();*/
	Cube floor(600, 2, 600);
	floor.SetPos(0, -1, 0);
	floor.color = Cyan;
	floor.Render();

	Cube roof(600, 2, 600);
	roof.SetPos(0, 100, 0);
	roof.color = Cyan;
	roof.Render();

	Cube wall_left(2, 100, 600);
	wall_left.SetPos(-300, 50, 0);
	wall_left.color = Cyan;
	wall_left.Render();
	
	Cube wall_right(2, 100, 600);
	wall_right.SetPos(300, 50, 0);
	wall_right.color = Cyan;
	wall_right.Render();

	Cube wall_front(600, 100, 2);
	wall_front.SetPos(0, 50, -300);
	wall_front.color = Cyan;
	wall_front.Render();

	Cube wall_back(600, 100, 2);
	wall_back.SetPos(0, 50, 300);
	wall_back.color = Cyan;
	wall_back.Render();

	
	for (int i = 0; i < CUBES; i++) {
		
		if (map_list[i] != nullptr)
		{
			map_list[i]->Render();
		}
	}

	for (int i = 0; i < SPHERES; i++) {

		for (int j = 0; j < SPHERES2; j++) {

			if (sphere_list[i] != nullptr)
			{
				if (sphere_list2[j] != nullptr)
				{

					sphere_list[i]->Render();
					sphere_list2[j]->Render();

				}

			}
			
		}
		
	}

	/*for (int i = 0; i < bullets.count(); i++)
	{
		Sphere bullet;
		bullet.radius = 0.5f;

		PhysBody3D* bullet_render;
		bullets.at(i, bullet_render);
		vec3 pos = bullet_render->GetPos();
		bullet.SetPos(pos.x, pos.y, pos.z);
		bullet.Render();
	}*/

	ramp->Render();
	ramp2->Render();

	float race_time = 0;

	if (App->T.d == false) {
		race_time = App->T.Read();
		race_time = race_time / 1000.0f;
	}
	
	char title[80];
	sprintf_s(title, "Velocity: %.1f Km/h	Time: %.2f", App->player->vehicle->GetKmh(), race_time);
	App->window->SetTitle(title);

	return UPDATE_CONTINUE;
}

/*update_status ModulePlayer::PostUpdate(float dt) {

		//FX
		vec3 pos = App->player->vehicle->GetPos();
		vec3 fvector = App->player->vehicle->ForwardVector();

		PhysBody3D* bullet = App->physics->Throw({ pos.x, pos.y, pos.z }, { fvector.x, fvector.y, fvector.z });

		bullets.add(bullet);

		if (bullets.count() > BULLETS)
		{
			App->physics->UnloadBullet(bullets.getFirst()->data);
			bullets.del(bullets.getFirst());
		}


	return UPDATE_CONTINUE;

}*/

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	PhysBody3D* b;
	if ((body1->GetBody() != App->player->vehicle->GetBody()))
	{
		b = body1;
		LOG("PASA");
		//newpos=check_p->GetPos();
		//sensor = true;
	}
	else {
		b = body1;
	}

}

void ModuleSceneIntro::CheckPoint(const vec3 pos)
{
	cube_sensor.size.x = 10;
	cube_sensor.size.y = 4;
	cube_sensor.size.z = 1;
	cube_sensor.SetPos(pos.x, pos.y, pos.z);
	check_p = App->physics->AddBody(cube_sensor, 0);
	check_p->GetTransform(&cube_sensor.transform);
	check_p->SetSensor(true);
	check_p->collision_listeners.add(this);
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


