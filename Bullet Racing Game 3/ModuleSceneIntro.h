#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"
#include "PugiXml\src\pugixml.hpp"

#define MAX_SNAKE 2
#define CUBES 500
#define RAMPS 10


struct PhysBody3D;
struct PhysMotor3D;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();
	
	bool Awake();
	bool Start();
	update_status Update(float dt);
	pugi::xml_node LoadCircuit(pugi::xml_document&) const;
	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);
	bool CleanUp();

	
	
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

	pugi::xml_document map_file;
	pugi::xml_node node;

	float x = 0, y = 0, z = 0;
	int sizex = 0, sizey = 0, sizez = 0, rot = 0;
	int cont = 0;
	int cubesAdd = 0;
	int rampsAdd = 0;

	int barça_anthem;

};
