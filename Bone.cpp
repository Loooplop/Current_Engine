#include "Bone.h"


Bone::Bone(bool MasterBone,Bone *parentBone,vec3 Offset,int NumofChildBone)
{
	if(MasterBone==true)
	{
	_IsMasterBone=true;
	_ParentBone=this;
	_Offset=Offset;
	_ChildBones=new Bone[NumofChildBone];
	}
	else 
	{
		_IsMasterBone=false;
		_ParentBone=parentBone;
		_Offset=Offset;
		_ChildBones= new Bone[NumofChildBone];
		_DistanceBetweenBone=Offset.GetMagnitude();
	};
};
void Bone::TranslateChild(vec3 TranslationOffsets)
{
	
};
void Bone::RotateChild(float angle,int AxisofRotation)
{
	
};
void Bone::RotateFather(float angle,int AxisofRotation)
{
	
};
void Bone::CalculateOrientationMatrix()
{
	
};
void Bone::CalculatePositionMatrix()
{
	
};
Bone::Bone(void)
{

};
Bone::~Bone(void)
{

}
