#include "Camera.h"
#include <math.h>
#include <iostream>
Camera::Camera(float Initial_Degrees,vec3 Eye)
{
	float DG=Initial_Degrees;
	if(DG>=360)
	{
		while(DG>=360)
		{
			DG-=360;
		}
	}
	Degrees=DG;
	vec3 Origin=vec3(0,0,5);
	
}


Camera::~Camera(void)
{

}
void Camera::Look(char Dir)
{
   if(Dir=='a')
   {
	   Degrees += 10;
	   float X=cosf(Degrees);
	   float Z=sinf(Degrees);
	   Result=vec2(X,Z);
   }
   else if(Dir=='d')
   {
	   Degrees -= 10;
	   if(Degrees==0)
	{
		Degrees=360;
		Degrees-=10;
	}
	   float X=cosf(Degrees);
	   float Z=sinf(Degrees);
	   Result=vec2(X,Z);
   };
};
vec3 Camera::GetTarget()
{
	vec3 Target=vec3(Origin.X+Result.X,Origin.Y,Origin.Z+Result.Y);
	std::cout<<Target<<std::endl;
	return Target;
}
vec3 Camera::GetOrigin()
{
	std::cout<<Origin<<std::endl;
	return Origin;
}