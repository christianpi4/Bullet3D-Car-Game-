#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"
#include "PugiXml\src\pugixml.hpp"
#include "PhysBody3D.h"
#include "PhysVehicle3D.h"

#define MAX_SNAKE 2
#define CUBES 500
#define SPHERES 100
#define SPHERES2 100
#define RAMPS 10


class PhysBody3D;
struct PhysMotor3D;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();
	
	bool Awake();
	bool Start();
	update_status Update(float dt);
	//update_status PostUpdate(float dt);
	pugi::xml_node LoadCircuit(pugi::xml_document&) const;
	void OnCollision(PhysBody3D* body1, PhysBody3D* body2) override;
	bool CleanUp();
	void CheckPoint(const vec3 position);
	void CreateHinges(vec3 pos, vec3 pos2, float radius);
	
public:
	
	PhysBody3D* pb_chassis;
	Cube p_chassis;

	PhysBody3D* pb_wheel;
	Cylinder p_wheel;

	PhysBody3D* pb_wheel2;
	Cylinder p_wheel2;

	PhysMotor3D* left_wheel;
	PhysMotor3D* right_wheel;

	Cube* map_list[CUBES];
	Cube* ramp;
	Cube* ramp2;
	PhysBody3D* bodyA = nullptr;
	PhysBody3D* bodyB = nullptr;

	//checkpoints
	Cube cube_sensor;
	PhysBody3D* check_p;
	vec3 newpos;

	bool sensor=false;
	
	Sphere* sphere_list[SPHERES];
	Sphere* sphere_list2[SPHERES2];

	pugi::xml_document map_file;
	pugi::xml_node node;

	float x = 0, y = 0, z = 0;
	int sizex = 0, sizey = 0, sizez = 0, rot = 0;
	float hingex = 0.0f, hingey = 0.0f, hingez = 0.0f, hinge2x = 0.0f, hinge2y = 0.0f, hinge2z = 0.0f, radius = 0.0f;
	int cont = 0;
	int cubesAdd = 0;
	int sphereAdd = 0, sphereAdd2 = 0;
	int rampsAdd = 0;


};

