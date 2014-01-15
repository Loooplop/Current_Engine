#pragma once
#include "MathLibrary.h"
class Camera
{
public:
	Camera(float Initial_Degrees,vec3 Eye);
	~Camera(void);
	void Look(char Dir);
	vec3 GetTarget();
	vec3 GetOrigin();
	vec3 Origin;
	float Degrees;
	vec2 Result;
};

