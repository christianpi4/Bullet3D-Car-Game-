#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

struct PhysVehicle3D;

#define MAX_ACCELERATION 2000.0f
#define TURN_DEGREES 15.0f * DEGTORAD
#define BRAKE_POWER 250.0f

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();
	void  CameraFollow();

public:

	vec3 position;
	vec3 CamD;
	vec3 CarPos;

	bool camera = true;

	PhysVehicle3D* vehicle;
	float turn;
	float acceleration;
	float brake;
};