#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"

#define MAX_ACCELERATION 1000.0f
#define MIN_ACCELERATION 0.f
#define TURN_DEGREES 15.0f * DEGTORAD
#define BRAKE_POWER 10.f

struct PhysVehicle3D;
class Primitive;
class  PhysBody3D;

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update(float dt) override;
	bool CleanUp();

	void CameraFollow();
	bool CameraFollow1 = true;
	vec3 position;
	vec3 CamD;
public:
	
	void HandleDebugInput();

	PhysVehicle3D* vehicle;
	float turn;
	float acceleration;
	float brake;
};
