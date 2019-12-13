#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"

class Primitive;
class  PhysBody3D;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt) override;
	update_status PostUpdate(float dt) override;

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2) override;
	void CreateLineInX(float Initial_pos_x, float Initial_pos_y, float Initial_pos_z, int lenght, bool in_x);
	//void CreateLineInZ(float Initial_pos_x, float Initial_pos_y, float Initial_pos_z, int lenght);
	void CreateDiagonal(float Initial_pos_x, float Initial_pos_y, float Initial_pos_z, int lenght, bool in_x);


	bool CleanUp();

private:
	void HandleDebugInput();
	void DebugSpawnPrimitive(Primitive* p);

	p2DynArray<Primitive*> primitives;
};
