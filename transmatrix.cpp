#include "transmatrix.h" // class's header file
#include <math.h>
const float M_PI = 3.1415926535897932384626433832795f;
// class constructor
TransMatrix::TransMatrix()
{
	// insert your code here
}

// class destructor
TransMatrix::~TransMatrix()
{
	// insert your code here
}
mat4 TransMatrix::IdentidyMx()
{
  return mat4(1,0,0,0,
              0,1,0,0,
              0,0,1,0,
              0,0,0,1);     
};
mat4 TransMatrix::TranslationMxf(float x,float y,float z)
{
     return mat4(1,0,0,x,
                 0,1,0,y,
                 0,0,1,z,
                 0,0,0,1);
};
mat4 TransMatrix::TranslationMxv(vec3 Vector)
{
     return mat4(1,0,0,Vector.X,
                 0,1,0,Vector.Y,
                 0,0,1,Vector.Z,
                 0,0,0,1); 
};
mat4 TransMatrix::ScaleMxf(float x,float y,float z)
{
     return mat4(x,0,0,0,
                 0,y,0,0,
                 0,0,z,0,
                 0,0,0,1);
};
mat4 TransMatrix::ScaleMxv(vec3 Vector)
{
     return mat4(Vector.X,0,0,0,
                 0,Vector.Y,0,0,
                 0,0,Vector.Z,0,
                 0,0,0,1); 
};
mat4 TransMatrix::RotateXMxf(float phi)
{
     phi=phi*(M_PI/180);
     return mat4(1,0,0,0,
                 0,cos(phi),sin(phi),0,
                 0,-sin(phi),cos(phi),0,
                 0,0,0,1); 
}
mat4 TransMatrix::RotateYMxf(float theta)
{
     theta=theta*(M_PI/180);
     return mat4(cos(theta),0,sin(theta),0,
              0,1,0,0,
              -sin(theta),0,cos(theta),0,
              0,0,0,1);
}
mat4 TransMatrix::RotateZMxf(float psi)
{
     psi=psi*(M_PI/180);
     return mat4(cos(psi),sin(psi),0,0,
              -sin(psi),cos(psi),0,0,
              0,0,1,0,
              0,0,0,1);
}
mat4 TransMatrix::RotateXYZMxf(float phi,float theta,float psi)
{
   return RotateZMxf(psi)*RotateYMxf(theta)*RotateXMxf(phi);
};
inline vec3 normalize(vec3 v)
{
    float lenght=sqrt(v.GetX()*v.GetX()+v.GetY()*v.GetY()+v.GetZ()*v.GetZ());   
    float x=v.GetX()/lenght;
    float y=v.GetY()/lenght;
    float z=v.GetZ()/lenght;
    return vec3(x,y,z);
};
inline vec3 CrossProduct(vec3 v1,vec3 v2)
{
     float X=(v1.GetY()*v2.GetZ())-(v1.GetZ()*v2.GetY());
     float Y=(v1.GetZ()*v2.GetX())-(v1.GetX()*v2.GetZ());
     float Z=(v1.GetX()*v2.GetY())-(v1.GetY()*v2.GetX());
     return vec3(X,Y,Z);   
};
mat4 TransMatrix::ViewMx(vec3 Origin,vec3 Target,vec3 Up)
{
     vec3 vz=normalize(Origin-Target);
     vec3 vx=normalize(CrossProduct(Up,vz));
     vec3 vy=CrossProduct(vz,vx);
     mat4 inverseViewMatrix=mat4(vx.X,vx.Y,vx.Z,0,
                                 vy.X,vy.Y,vy.Z,0,
                                 vz.X,vz.Y,vz.Z,0,
								 Origin.X,Origin.Y,Origin.Z,1).GetTranspose();
	 return inverseViewMatrix.GetInverse();
};
float Pi=M_PI/180;
mat4 TransMatrix::PerspectiveMx(float fov, float aspect,float znear, float zfar)
{
float coty = 1.0f / tan(fov * (M_PI / 180.0f));
   mat4 Pers(coty / aspect,0,0,0,
              0,coty,0,0,
              0,0,(znear + zfar) / (znear - zfar),-1,
              0,0,2.0f * znear * zfar / (znear - zfar),0);
   return Pers.GetTranspose();
}
mat4 TransMatrix::OrthographicMx(float top,float bottom,float left,float right,float near,float far)
{
	return mat4(2/(right-left),0,0,-(right+left)/(right-left),
		        0,2/(top-bottom),0,-(top+bottom)/(top-bottom),
				0,0,-1/(far-near),-near/(far-near),
				0,0,0,1).GetTranspose();
};