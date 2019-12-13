#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"

#define MAX_SNAKE 2

class Primitive;
struct  PhysBody3D;
struct PhysMotor3D;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	update_status PostUpdate(float dt) override;
	bool CleanUp();

	//void OnCollision(PhysBody3D* body1, PhysBody3D* body2);

	void CreateLine(float Initial_pos_x, float Initial_pos_y, float Initial_pos_z, int lenght, bool forward);
	void CreateDiagonal(float Initial_pos_x, float Initial_pos_y, float Initial_pos_z, int lenght, bool forward);

public:

	PhysBody3D* pb_chassis;
	Cube p_chassis;

	PhysBody3D* pb_wheel;
	Cylinder p_wheel;

	PhysBody3D* pb_wheel2;
	Cylinder p_wheel2;

	PhysMotor3D* left_wheel;
	PhysMotor3D* right_wheel;

	p2DynArray<Primitive*> primitives;
	void HandleDebugInput();
	void DebugSpawnPrimitive(Primitive* p);

};
