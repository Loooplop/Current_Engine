#include "VectorMath.h" // class's header file
#include <math.h>
#include <iostream>
//------------------------------------------------
vec2::vec2(float f1,float f2)
{
	X=f1;
    Y=f2;
}
vec2::vec2()
{
                  
}
// class destructor
vec2::~vec2()
{
	// insert your code here
}
vec2 vec2::operator+ (const vec2 &other)
{
    return vec2(X+other.X,Y+other.Y);
}
vec2 vec2::operator- (const vec2 &other)
{
    return vec2(X-other.X,Y-other.Y);
}
vec2 vec2::operator* (const vec2 &other)
{
    return vec2(X*other.X,Y*other.Y);
}
vec2 vec2::operator/ (const vec2 &other)
{
    return vec2(X/other.X,Y/other.Y);
}
float vec2::GetX()
{
      return X;
};
float vec2::GetY()
{
      return Y;
};
float vec2::GetMagnitude()
{
	return sqrt(X*X+Y*Y);
};
std::ostream& operator<< (std::ostream &out, vec2 &Vector)
{
 out<<"|"<<Vector.X<<","<<Vector.Y<<"|"<<std::endl;
 return out;       

};
//-----------------------------------------------------------------------------------------------------------------------
vec3::vec3(float f1,float f2,float f3)
{
	X=f1;
    Y=f2;
    Z=f3;
}
vec3::vec3()
{
                  
}
// class destructor
vec3::~vec3()
{
	// insert your code here
}
vec3 vec3::operator+ (const vec3 &other)
{
    return vec3(X+other.X,Y+other.Y, Z+other.Z);
}
vec3 vec3::operator- (const vec3 &other)
{
    return vec3(X-other.X,Y-other.Y, Z-other.Z);
}
vec3 vec3::operator* (const vec3 &other)
{
    return vec3(X*other.X,Y*other.Y, Z*other.Z);
}
vec3 vec3::operator/ (const vec3 &other)
{
    return vec3(X/other.X,Y/other.Y, Z/other.Z);
}
float vec3::GetX()
{
      return X;
};
float vec3::GetY()
{
      return Y;
};
float vec3::GetZ()
{
      return Z;
};
float vec3::GetMagnitude()
{
	return sqrt(X*X+Y*Y+Z*Z);
};
std::ostream& operator<< (std::ostream &out, vec3 &Vector)
{
 out<<"|"<<Vector.X<<","<<Vector.Y<<","<<Vector.Z<<"|"<<std::endl;
 return out;       

};
float  *vec3::GetArray()
{
	float S[]= {X,Y,Z};
	return S;
};
//---------------------------------------------------------------------------
vec4::vec4(float f1,float f2,float f3,float f4)
{
	X=f1;
    Y=f2;
    Z=f3;
    W=f4;
}
vec4::vec4()
{
                  
}
// class destructor
vec4::~vec4()
{
	// insert your code here
}
vec4 vec4::operator+ (const vec4 &other)
{
    return vec4(X+other.X,Y+other.Y, Z+other.Z,W+other.W);
}
vec4 vec4::operator- (const vec4 &other)
{
    return vec4(X-other.X,Y-other.Y, Z-other.Z,W-other.W);
}
vec4 vec4::operator* (const vec4 &other)
{
    return vec4(X*other.X,Y*other.Y, Z*other.Z,W*other.W);
}
vec4 vec4::operator/ (const vec4 &other)
{
    return vec4(X/other.X,Y/other.Y, Z/other.Z,W/other.W);
}
float vec4::GetX()
{
      return X;
};
float vec4::GetY()
{
      return Y;
};
float vec4::GetZ()
{
      return Z;
};
float vec4::GetW()
{
      return W;
};
float vec4::GetMagnitude()
{
	return sqrt(X*X+Y*Y+Z*Z+W*W);
};
std::ostream& operator<< (std::ostream &out, vec4 &Vector)
{
 out<<"|"<<Vector.X<<","<<Vector.Y<<","<<Vector.Z<<","<<Vector.W<<"|"<<std::endl;
 return out;       

};
inline vec3 CrossProduct(vec3 v1,vec3 v2)
{
     float X=(v1.GetY()*v2.GetZ())-(v1.GetZ()*v2.GetY());
     float Y=(v1.GetZ()*v2.GetX())-(v1.GetX()*v2.GetZ());
     float Z=(v1.GetX()*v2.GetY())-(v1.GetY()*v2.GetX());
     return vec3(X,Y,Z);   
};
