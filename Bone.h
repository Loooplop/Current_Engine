#pragma once
#include "MatrixMath.h"
#include "VectorMath.h"
#include <math.h>
class Bone
{
public:
	Bone(bool MasterBone,Bone *parentBone,vec3 Offset,int NumofChildBone);
	Bone(void);
	~Bone(void);
	void TranslateChild(vec3 TranslationOffsets);
	void RotateChild(float angle,int AxisofRotation);
	void RotateFather(float angle,int AxisofRotation);
	void CalculateOrientationMatrix();
	void CalculatePositionMatrix();
private:
	bool _IsMasterBone;
	Bone *_ParentBone;
	Bone *_ChildBones;
	vec3 _Offset;
	mat4 _OrientationMatrix, _PositionMatrix;
	double _AngleXY,_AngleXZ,_AngleYZ;
	double _DistanceBetweenBone;
	vec3 _FinalTranslation,_FinalRotation;
};

