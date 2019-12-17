#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "Primitive.h"
#include "PhysVehicle3D.h"
#include "PhysBody3D.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled), vehicle(NULL)
{
	turn = acceleration = brake = 0.0f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	VehicleInfo car;

	// Car properties ----------------------------------------
	car.chassis_size.Set(2, 0.45, 3);
	car.chassis_offset.Set(0, 1, 0);

	car.lateral_right_size.Set(0.1, 0.8, 3);
	car.lateral_right_offset.Set(0.95, 1.3, 0);

	car.lateral_left_size.Set(0.1, 0.8, 3);
	car.lateral_left_offset.Set(-0.95, 1.3, 0);

	car.front_size.Set(2, 0.4, 0.1);
	car.front_offset.Set(0, 1.3, 1.45);

	car.back_size.Set(2, 0.4, 0.1);
	car.back_offset.Set(0, 1.3, -1.45);

	car.seat_size.Set(1, 0.1, 1);
	car.seat_offset.Set(0, 1.3, -0.95);

	car.seatback_size.Set(1, 0.8, 0.15);
	car.seatback_offset.Set(0, 1.8, -1.4);

	car.handlebar_size.Set(0.2, 1.3, 0.2);
	car.handlebar_offset.Set(0, 1.5, 0.9);

	car.handles_left_size.Set(0.4, 0.1, 0.1);
	car.handles_left_offset.Set(0.3, 2, 0.9);

	car.handles_right_size.Set(0.4, 0.1, 0.1);
	car.handles_right_offset.Set(-0.3, 2, 0.9);

	car.aileron_left_size.Set(0.3, 1.3, 0.4);
	car.aileron_left_offset.Set(-0.7, 1.45, -1.6);

	car.aileron_right_size.Set(0.3, 1.3, 0.4);
	car.aileron_right_offset.Set(0.7, 1.45, -1.6);

	car.aileron_size.Set(1.7, 0.1, 0.4);
	car.aileron_offset.Set(0, 1.9, -1.9);

	car.mass = 500.0f;
	car.suspensionStiffness = 15.88f;
	car.suspensionCompression = 0.83f;
	car.suspensionDamping = 0.88f;
	car.maxSuspensionTravelCm = 1000.0f;
	car.frictionSlip = 35;
	car.maxSuspensionForce = 6000.0f;

	// Wheel properties ---------------------------------------
	float connection_height = 1.2f;
	float wheel_radius = 0.33f;
	float wheel_width = 0.38f;
	float suspensionRestLength = 1.2f;

	// Don't change anything below this line ------------------

	float half_width = car.chassis_size.x*0.5f;
	float half_length = car.chassis_size.z*0.5f;
	
	vec3 direction(0,-1,0);
	vec3 axis(-1,0,0);
	
	car.num_wheels = 3;
	car.wheels = new Wheel[3];

	// FRONT ------------------------
	car.wheels[0].connection.Set(0, connection_height, half_length);
	car.wheels[0].direction = direction;
	car.wheels[0].axis = axis;
	car.wheels[0].suspensionRestLength = suspensionRestLength;
	car.wheels[0].radius = wheel_radius;
	car.wheels[0].width = wheel_width;
	car.wheels[0].front = true;
	car.wheels[0].drive = true;
	car.wheels[0].brake = false;
	car.wheels[0].steering = true;

	// REAR-LEFT ------------------------
	car.wheels[1].connection.Set(half_width - 0.3f * wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[1].direction = direction;
	car.wheels[1].axis = axis;
	car.wheels[1].suspensionRestLength = suspensionRestLength;
	car.wheels[1].radius = wheel_radius;
	car.wheels[1].width = wheel_width;
	car.wheels[1].front = false;
	car.wheels[1].drive = false;
	car.wheels[1].brake = true;
	car.wheels[1].steering = false;

	// REAR-RIGHT ------------------------
	car.wheels[2].connection.Set(-half_width + 0.3f * wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[2].direction = direction;
	car.wheels[2].axis = axis;
	car.wheels[2].suspensionRestLength = suspensionRestLength;
	car.wheels[2].radius = wheel_radius;
	car.wheels[2].width = wheel_width;
	car.wheels[2].front = false;
	car.wheels[2].drive = false;
	car.wheels[2].brake = true;
	car.wheels[2].steering = false;
	
	vehicle = App->physics->AddVehicle(car);
	vehicle->SetPos(0, 0, -10);

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status ModulePlayer::Update(float dt)
{
	turn = acceleration = brake = 0.0f;

	if(App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
	{
		acceleration = MAX_ACCELERATION;

		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
		{
		if (turn < TURN_DEGREES)
				turn += TURN_DEGREES;
		}

		else if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
		{
		if (turn > -TURN_DEGREES)
			turn -= TURN_DEGREES;
		}
	}

	else if(App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
	{
		acceleration = -MAX_ACCELERATION;

		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
		{
			if (turn < TURN_DEGREES)
				turn += TURN_DEGREES;
		}

		else if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
		{
			if (turn > -TURN_DEGREES)
				turn -= TURN_DEGREES;
		}
		
	}

	else{
		
		if (vehicle->GetKmh() > 0.0f)
			brake = BRAKE_POWER/6;

	}

	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		Sphere s;
		s.SetPos(App->camera->Position.x, App->camera->Position.y, App->camera->Position.z);
		float force = 30.0f;

		vec3 forwardVector = vehicle->ForwardVector();
		vec3 NewCameraPosition = { CarPos.x + forwardVector.x, CarPos.y + forwardVector.y, CarPos.z + forwardVector.z };
		vec3 CamPos = App->camera->Position + (NewCameraPosition - App->camera->Position);

		App->physics->AddBody(s,10.0f)->Push(-(CamPos.x * force), -(CamPos.y * force), -(CamPos.z * force));
		s.Render();
		
	}


	CarPos = vehicle->GetPos();
	vehicle->ApplyEngineForce(acceleration);
	vehicle->Turn(turn);
	vehicle->Brake(brake);

	CameraFollow();

	vehicle->Render();

	char title[80];
	sprintf_s(title, "%.1f Km/h", vehicle->GetKmh());
	App->window->SetTitle(title);

	return UPDATE_CONTINUE;

}


void  ModulePlayer::CameraFollow()
{

	CamD = { -9.0f, 5.0f, -9.0f };
	vec3 forwardVector = vehicle->ForwardVector();
	vec3 NewCameraPosition = { CarPos.x + (forwardVector.x * CamD.x), CarPos.y + (forwardVector.y + CamD.y), CarPos.z + (forwardVector.z * CamD.z) };
	vec3 CamPos = App->camera->Position + (NewCameraPosition - App->camera->Position);

	App->camera->Look(CamPos, CarPos);
}



