//------------------------------------------------------
//Includes
#include "Shaders.h"
#include "Pipeline.h"
#include "Bone.h"
#include <math.h>
using namespace std;
//-------------------------------------------------------
//Variables
TransMatrix Handler; //Handler object that codes uses for Creating the Model, View, and Projection matrices
GLuint Vert,Frag,ProgId;//Variables that hold handles to Vertex Shader, Fragment Shader, and Program
GLuint VertS,FragS,ProgIdS;//Variables that hold handles to Vertex Shader, Fragment Shader, and Program
Pipeline Renderer;
float X=0;
float Y=0;
float Z=7;
//--------------------------------------------------------
//Function Header-ResizeFunction.
//INPUTS Integer Width = Width of Current Window
//       Integer Height = Height of Current Window
// OUTPUT NONE-/Void Function
void ResizeFunction(int Width, int Height)
{
	glViewport(0, 0, Width,Height);// Reset ViewPort
	Renderer.SetPerspectiveMatrix(45,(float)Width/(float)Height,1.0f,100.0f);
};
float v=180;
float FPS_Variable=0;
void CalculateFrameRate()
    {

        static float framesPerSecond    = 0.0f;       // This will store our fps
        static float lastTime   = 0.0f;       // This will hold the time from the last frame
        float currentTime = GetTickCount() * 0.001f;    
        ++framesPerSecond;
        if( currentTime - lastTime > 1.0f )
        {
            lastTime = currentTime;
            FPS_Variable=framesPerSecond;
            char title[80];
            sprintf(title, "VBO Example - %.2f", FPS_Variable);
            glutSetWindowTitle(title);
            framesPerSecond = 0;
        }
    }
void MatrixUpload(mat4 Model,mat4 View,mat4 Perspective,mat4 Ortho,mat3 Normal)
{
	UniformMatrix("Perspective",ProgId,Perspective);
	UniformMatrix("View",ProgId,View);
	UniformMatrix("Model",ProgId,Model);
	UniformMatrix("NormalMatrix",ProgId,Normal);
	UniformMatrix("Rotation",ProgId,Handler.TranslationMxf(-.5,-.5,-.5));
}
void ShadowShaderMatrixFunc(mat4 Model,mat4 View,mat4 Perspective,mat4 Ortho,mat3 Normal)
{
	UniformMatrix("Ortho",ProgIdS,Ortho);
	UniformMatrix("View",ProgIdS,View);
	UniformMatrix("Model",ProgIdS,Model);
}
float converter=3.141592653589793f/180.0f;
float xpos,ypos,zpos;
void RenderFunction(void)
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glUseProgram(ProgId);
	
	Renderer.Translate(0,0,0);
	Renderer.UploadMatricestoShader(MatrixUpload);
    Renderer.RenderModelWith1Texture(0,0);

	CalculateFrameRate();
    glutSwapBuffers();
};
float Speed = 1.0f;
void KeyBoard(unsigned char Key,int x,int y)
{
	switch(Key)
	{
	case 'a':
		X-=Speed;
		break;
    case 'd':
		X+=Speed;
		break;
	case 'w':
		Z-=Speed;
		break;
    case 's':
		Z+=Speed;
		break;
	case 'q':
		Y+=Speed;
		break;
    case 'z':
		Y-=Speed;
		break;

   }
   Renderer.SetCamera(X,Y,Z,X,Y,Z-5);
   glUniform3fv(glGetUniformLocation(ProgId,"EyePos"),1,vec3(X,Y,Z).GetArray());
}
void GLEWInit()
{
	glewInit();

	setShaders("Vertex.vs","Fragment.fs",Vert,Frag,ProgId);

	Renderer.Load_Model("Box.obj",GL_STATIC_DRAW);
	Bone Master(true,NULL,vec3(0,0,0),0);
	Renderer.Load_Model("SHADOW.obj",GL_STATIC_DRAW);
	Renderer.Load_Texture("CheckBoardTexture.bmp");
	Renderer.Load_Texture("fnejr.bmp");
	Renderer.SetOrthoMatrix(10,-10,-10,10,1,100);
	Renderer.SetPerspectiveMatrix(45,640/480,1,1000);
	Renderer.SetCamera(X,Y,Z,X,Y,Z-5);

	glUniform1i(glGetUniformLocation(ProgId,"Sampler"),0);
	glUniform3fv(glGetUniformLocation(ProgId,"LightPos"),1,vec3(10,7,12).GetArray());
	glUniform3fv(glGetUniformLocation(ProgId,"LightCol"),1,vec3(1,1,1).GetArray());
	glUniform3fv(glGetUniformLocation(ProgId,"EyePos"),1,vec3(0,3,7).GetArray());
}
int main(int argc, char* argv[])
{
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 50);
	glutInitWindowSize(640,480);
    glutCreateWindow("Hi");

	glEnable(GL_DEPTH_TEST);
	GLEWInit();
	
	glutReshapeFunc(ResizeFunction);
	glutDisplayFunc(RenderFunction);
	glutKeyboardFunc(KeyBoard);
	glutIdleFunc(RenderFunction);
	glutMainLoop();
	exit(0);
};