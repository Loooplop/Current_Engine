#ifndef VERTICE_H
#define VERTICE_H
#include <iostream>
/*
 * No description
 */
class vec2
{
	public:
		// class constructor
		vec2(float f1,float f2);
		vec2();
		~vec2();
		vec2 vec2::operator+ (const vec2 &other);
		vec2 vec2::operator* (const vec2 &other);
		vec2 vec2::operator/ (const vec2 &other);
		vec2 vec2::operator- (const vec2 &other);
		float GetMagnitude();
		float GetX();
		float GetY();
		friend std::ostream& operator<< (std::ostream &out, vec2 &Vector);
		//private:
        float X,Y;
		
};
class vec3
{
	public:
		// class constructor
		vec3(float f1,float f2,float f3);
		vec3();
		~vec3();
		vec3 vec3::operator+ (const vec3 &other);
		vec3 vec3::operator* (const vec3 &other);
		vec3 vec3::operator/ (const vec3 &other);
		vec3 vec3::operator- (const vec3 &other);
		float GetMagnitude();
		float GetX();
		float GetY();
		float GetZ();
		friend std::ostream& operator<< (std::ostream &out, vec3 &Vector);
		float *GetArray();
		//private:
        float X,Y,Z;
		
};
class vec4
{
	public:
		// class constructor
		vec4(float f1,float f2,float d3,float f4);
		vec4();
		~vec4();
		vec4 vec4::operator+ (const vec4 &other);
		vec4 vec4::operator* (const vec4 &other);
		vec4 vec4::operator/ (const vec4 &other);
		vec4 vec4::operator- (const vec4 &other);
		float GetMagnitude();
		float GetX();
		float GetY();
		float GetZ();
		float GetW();
		friend std::ostream& operator<< (std::ostream &out, vec4 &Vector);
		//private:
        float X,Y,Z,W;
		
};
float Abs(float x);
vec3 normalize(vec3 v);
float DotProduct(vec4 v1,vec4 v2);
float DotProduct(vec3 v1,vec3 v2);
#endif // vec4_H