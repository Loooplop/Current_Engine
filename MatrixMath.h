#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include "VectorMath.h"
class mat2
{
 public:
 mat2(float UpperLeft,float UpperRight,float LowerLeft,float LowerRight);
 mat2(float *data);
 mat2();     
~mat2();      

        mat2 mat2::operator+ (const mat2 &other);
		mat2 mat2::operator* (const mat2 &other);
		mat2 mat2::operator* (const float &other);
		mat2 mat2::operator/ (const mat2 &other);
		mat2 mat2::operator/ (const float &other);
		mat2 mat2::operator- (const mat2 &other);
		mat2 GetInverse();
		float *GetValues();
		friend std::ostream& operator<< (std::ostream &out, mat2 &Matrix);
  float M[4];
  /*
  Values= 1 2 3 4
  [ Values[0] Values[1] ] = [ 1 2 ]
  [ Values[2] Values[3] ] = [ 3 4 ]
  */  
};
class mat3
{
     public:
 mat3(float UpperLeft,float UpperCenter,float UpperRight,float MiddleLeft,float MiddleCenter,float MiddleRight,float LowerLeft,float LowerCenter,float LowerRight);
 mat3(float *data);
 mat3();     
~mat3();      

        mat3 mat3::operator+ (const mat3 &other);
		mat3 mat3::operator* (const mat3 &other);
		mat3 mat3::operator* (const float &other);
		mat3 mat3::operator/ (mat3 &other);
		mat3 mat3::operator/ (const float &other);
		mat3 mat3::operator- (const mat3 &other);
		mat3 GetInverse();
		mat3 GetTranspose();
		friend std::ostream& operator<< (std::ostream &out, mat3 &Matrix);
  float M[9];
  /*
  Values= 1 2 3 4 5 6 7 8 9
  [ Values[0] Values[1] Values[2] ] = [ 1 2 3 ]
  [ Values[3] Values[4] Values[5] ] = [ 4 5 6 ]
  [ Values[6] Values[7] Values[8] ] = [ 7 8 9 ]
  */  
};
class mat4
{
     public:
 mat4(float UpperUpperLeftLeft,float UpperUpperLeft,float UpperUpperRight,float UpperUpperRightRight,
      float UpperLeftLeft,float UpperLeft,float UpperRight,float UpperRightRight,
      float LowerLeftLeft,float LowerLeft,float LowerRight,float LowerRightRight,
      float LowerLowerLeftLeft,float LowerLowerLeft,float LowerLowerRight,float LowerLowerRightRight);
 mat4(float *data);
 mat4();     
~mat4();      

        mat4 mat4::operator+ (const mat4 &other);
		mat4 mat4::operator* (const mat4 &other);
		mat4 mat4::operator* (const float &other);
		mat4 mat4::operator/ (mat4 &other);
		mat4 mat4::operator/ (const float &other);
		mat4 mat4::operator- (const mat4 &other);
		mat4 GetInverse();
		mat4 GetTranspose();
		friend std::ostream& operator<< (std::ostream &out, mat4 &Matrix);
		vec4 mat4::operator* (const vec4 &other);
  float M[16];
  /*
  Values= 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16
  [ Values[0] Values[1] Values[2] Values[3] ] = [ 1 2 3 4 ]
  [ Values[3] Values[4] Values[5] Values[2] ] = [ 5 6 7 8 ]
  [ Values[6] Values[7] Values[8] Values[2] ] = [ 9 10 11 12 ]
  [ Values[6] Values[7] Values[8] Values[2] ] = [ 13 14 15 16 ]
  */  
};
#endif