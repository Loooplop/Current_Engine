#pragma once
#define MODEL_NORMAL_VECTOR (int)0
#define MODEL_NORMAL_VECTOR_SIZE (long)0
#define MODEL_NORMAL_VECTOR_POINTER_BEGIN 'N'
#define MODEL_NORMAL_VECTOR_POINTER_END 'n'


#define MODEL_POSITION_VECTOR (int)1
#define MODEL_POSITION_VECTOR_SIZE (long)1
#define MODEL_POSITION_VECTOR_POINTER_BEGIN 'P'
#define MODEL_POSITION_VECTOR_POINTER_END 'p'


#define MODEL_TEXCOORD_VECTOR (double)2
#define MODEL_TEXCOORD_VECTOR_SIZE (long)2
#define MODEL_TEXCOORD_VECTOR_POINTER_BEGIN (short)2
#define MODEL_TEXCOORD_VECTOR_POINTER_END (short)3

#include "MathLibrary.h"
#include <vector>
#include <gl\glew.h>
#include <gl\freeglut.h>

struct MODEL
{
	vec3Vector Position;
	vec3Vector Normals;
	vec2Vector UVS;
};
class Pipeline
{
public:
	Pipeline(void);
	~Pipeline(void);
	mat4 GetPVMatrix();
	mat4 GetModelMatrix();
	mat4 GetViewMatrix();
	mat4 GetPerspectiveMatrix();
	mat3 GetNormalMatrix();
	mat4 GetOrthoMatrix();
	void Translate(float x,float y,float z);
	void Scale(float x,float y,float z);
	void Rotate(float phi,float theta,float psi);
	void SetPerspectiveMatrix(float fov,float aspect,float nears,float fars);
	void SetCamera(vec3 Origin,vec3 Target);
	void SetCamera(float Origin_x,float Origin_y,float Origin_z,float Target_x,float Target_y,float Target_z);
	void SetOrthoMatrix(float top,float bottom,float left,float right,float znear,float zfar);
	void UploadMatricestoShader(void (*function)(mat4 ModelMatrix,mat4 ViewMatrix,mat4 PerspectiveMatrix,mat4 OrthographicMatrix,mat3 NormalEyeSpaceMatrix));

	     vec3 Translation;
		 vec3 Rotation;
		 vec3 ScaleV;
		 vec3 Camera_Origin,Camera_Target;
		 vec4 Perspective;
		 vec4 OrthoCube;vec2 OrthoZ;
		 TransMatrix Handle;
		 bool Error;
		 bool hasError()
		 {
			 return Error;
		 };


    int Load_Model(const char *filename,GLenum GL_DRAW_MODE);
	vec3Vector GetModelInformation(int Model_Number,int state);
	vec2Vector GetModelInformation(int Model_Number,double state);
	vec3 *GetModelInformation(int Model_Number, char state);
	vec2 *GetModelInformation(int Model_Number, short state);
	float GetModelInformation(int Model_Number,long state);
    std::vector<MODEL> modelVector;
	std::vector<GLuint> ArrayBuffers;

	void RenderModel(int ModelNumber);
	void RenderModelWith1Texture(int ModelNumber,int TextureNumber);
	void RenderModelWith2Texture(int ModelNumber,int TextureNumber1,int TextureNumber2);
	int Load_Texture(const char *filename);
	int GetTexture(int Texture_Number);
    std::vector<int> TextureVector;
};
GLuint loadBMP_custom(const char * imagepath);
void UniformMatrix(char *name, GLuint &program,mat4 Matrix);
void UniformMatrix(char *name, GLuint &program,mat3 Matrix);
bool LoadModel(MODEL &model,const char* path);