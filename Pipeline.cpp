#include "Pipeline.h"

Pipeline::Pipeline(void)
{
	vec3 Reset(0,0,0);
	Translation=Reset;
	Rotation=Reset;
	ScaleV=vec3(1,1,1);
	Camera_Origin=Reset;
	Camera_Target=Reset;
    Perspective=vec4(0,0,0,0);
	Error=false;
}


Pipeline::~Pipeline(void)
{

}
mat4 Pipeline::GetPVMatrix()
{
	mat4 Model = Handle.TranslationMxv(Translation)*Handle.RotateXYZMxf(Rotation.X,Rotation.Y,Rotation.Z)*Handle.ScaleMxv(ScaleV);
	mat4 View = Handle.ViewMx(Camera_Origin,Camera_Target,vec3(0,1,0));
	mat4 Pers = Handle.PerspectiveMx(Perspective.X,Perspective.Y,Perspective.Z,Perspective.W);
	return Pers*View*Model;
};
void Pipeline::UploadMatricestoShader(void (*function)(mat4 ModelMatrix,mat4 ViewMatrix,mat4 PerspectiveMatrix,mat4 OrthographicMatrix,mat3 NormalEyeSpaceMatrix))
{
	function(GetModelMatrix(),GetViewMatrix(),GetPerspectiveMatrix(),GetOrthoMatrix(),GetNormalMatrix());
}
mat4 Pipeline::GetModelMatrix()
{
	return Handle.TranslationMxv(Translation)*Handle.RotateXYZMxf(Rotation.X,Rotation.Y,Rotation.Z)*Handle.ScaleMxv(ScaleV);
}
mat4 Pipeline::GetViewMatrix()
{
	return Handle.ViewMx(Camera_Origin,Camera_Target,vec3(0,1,0));
};
mat4 Pipeline::GetPerspectiveMatrix()
{
  return Handle.PerspectiveMx(Perspective.X,Perspective.Y,Perspective.Z,Perspective.W);
};
mat4 Pipeline::GetOrthoMatrix()
{
	return Handle.OrthographicMx(OrthoCube.GetX(),OrthoCube.GetY(),OrthoCube.GetZ(),OrthoCube.GetW(),OrthoZ.GetX(),OrthoZ.GetY());
}
mat3 Pipeline::GetNormalMatrix()
{
	mat4 temp = GetViewMatrix()*GetModelMatrix();
	mat3 TopLeft =mat3(temp.M[0],temp.M[1],temp.M[2],
		               temp.M[4],temp.M[5],temp.M[6],
					   temp.M[8],temp.M[9],temp.M[10]);
	TopLeft=TopLeft.GetInverse();
	return TopLeft.GetTranspose();
};
void Pipeline::Translate(float x,float y,float z)
{
	Translation = vec3(x,y,z);
};
void Pipeline::Rotate(float phi,float theta,float psi)
{
	Rotation=vec3(phi,theta,psi);
};
void Pipeline::Scale(float x,float y,float z)
{
    ScaleV=vec3(x,y,z);		
};
void Pipeline::SetPerspectiveMatrix(float fov,float aspect,float nears,float fars)
{
	Perspective=vec4(fov,aspect,nears,fars);
};
void Pipeline::SetOrthoMatrix(float top,float bottom,float left,float right,float znear,float zfar)
{
		OrthoCube=vec4(top,bottom,left,right);
		OrthoZ=vec2(znear,zfar);
};
void Pipeline::SetCamera(vec3 Origin,vec3 Target)
{
  Camera_Origin=Origin;
  Camera_Target=Target;
};
void Pipeline::SetCamera(float Origin_x,float Origin_y,float Origin_z,float Target_x,float Target_y,float Target_z)
{
	Camera_Origin=vec3(Origin_x,Origin_y,Origin_z);
  Camera_Target=vec3(Target_x,Target_y,Target_z);
};
//---------------------------------------------------------------------------------------------------------------------------------------------


int Pipeline::Load_Model(const char *filename,GLenum GL_DRAW_MODE)
{
   MODEL temp;
   LoadModel(temp,filename);
   modelVector.push_back(temp);
   int MemoryLocation= modelVector.size()-1;
   GLuint P=0;
   GLuint N=0;
   GLuint T=0;
   glGenBuffers(1, &N);
    
    glBindBuffer(GL_ARRAY_BUFFER, N);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3)*((int)GetModelInformation(MemoryLocation,MODEL_NORMAL_VECTOR_SIZE)),GetModelInformation(MemoryLocation,MODEL_NORMAL_VECTOR_POINTER_BEGIN), GL_DRAW_MODE);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &P);
    
    glBindBuffer(GL_ARRAY_BUFFER, P);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3)*((int)GetModelInformation(MemoryLocation,MODEL_POSITION_VECTOR_SIZE)),GetModelInformation(MemoryLocation,MODEL_POSITION_VECTOR_POINTER_BEGIN), GL_DRAW_MODE);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &T);
    
    glBindBuffer(GL_ARRAY_BUFFER, T);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec2)*((int)GetModelInformation(MemoryLocation,MODEL_TEXCOORD_VECTOR_SIZE)),GetModelInformation(MemoryLocation,MODEL_TEXCOORD_VECTOR_POINTER_BEGIN), GL_DRAW_MODE);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
	ArrayBuffers.push_back(P);
	ArrayBuffers.push_back(N);
	ArrayBuffers.push_back(T);
	return MemoryLocation;
};
void Pipeline::RenderModel(int ModelNumber)
{
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER,ArrayBuffers[ModelNumber*3]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER,ArrayBuffers[1+ModelNumber*3]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDrawArrays(GL_TRIANGLES, 0, GetModelInformation(ModelNumber,MODEL_POSITION_VECTOR_SIZE));
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);


};
void Pipeline::RenderModelWith1Texture(int ModelNumber,int TextureNumber){
	if(ModelNumber>=modelVector.size())
	{
		std::cout<<"Model "<<ModelNumber<<" has Requested but not been initialized"<<std::endl;
		Error=true;
		return;
	}
	if(TextureNumber>=TextureVector.size())
	{
		std::cout<<"Texture "<<ModelNumber<<" has Requested but not been initialized"<<std::endl;
		Error=true;
		return;
	}
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, ArrayBuffers[0+ModelNumber*3]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER,ArrayBuffers[1+ModelNumber*3]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER,ArrayBuffers[2+ModelNumber*3]);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_TRUE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, GetTexture(TextureNumber));
	glDrawArrays(GL_TRIANGLES, 0, GetModelInformation(ModelNumber,MODEL_POSITION_VECTOR_SIZE));
    glBindTexture(GL_TEXTURE_2D, 0);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
};
vec3Vector Pipeline::GetModelInformation(int Model_Number,int state)
{
	vec3Vector Error;
	if(Model_Number<modelVector.size()){
	switch(state)
	{
	case 0:
		if(modelVector[Model_Number].Normals.size() != 0)
		{
		return modelVector[Model_Number].Normals;
		}
		else
		{
			std::cout<<"Model "<<Model_Number<<"'s Normal Vector is empty"<<std::endl;
			(*this).Error=true;
			return Error;
		};
		break;

	case 1:
		if(modelVector[Model_Number].Position.size() != 0)
		{
			return modelVector[Model_Number].Position;
		}
		else
		{
			std::cout<<"Model "<<Model_Number<<"'s Position Vector is empty"<<std::endl;
			(*this).Error=true;
			return Error;
		};
		break;

	default:
		std::cout<<"Not using MODEL_XXXXX_VECTOR"<<std::endl;
		(*this).Error=true;
		return Error;
	}
   }
   else
   {
	   std::cout<<"Model "<<Model_Number<<" has not been initialized"<<std::endl;
	   (*this).Error=true;
	   return Error;
   }

};
vec2Vector Pipeline::GetModelInformation(int Model_Number,double state)
{
	vec2Vector Error;
	if(Model_Number<modelVector.size()){
	switch((int)state)
	{
	case 2:
		if(modelVector[Model_Number].Normals.size() != 0)
		{
			std::cout<<"Returning Texture Coordinates Vector"<<std::endl;
			return modelVector[Model_Number].UVS;
		}
		else
		{
			std::cout<<"Model "<<Model_Number<<"'s Texture Coordinates Vector is empty"<<std::endl;
			(*this).Error=true;
			return Error;
		};
		break;

	default:
		std::cout<<"Not using MODEL_XXXXX_VECTOR or casting state variable"<<std::endl;
		(*this).Error=true;
		return Error;
	}
   }
   else
   {
	   std::cout<<"Model "<<Model_Number<<" has not been initialized"<<std::endl;
	   (*this).Error=true;
	   return Error;
   }
};
vec3 *Pipeline::GetModelInformation(int Model_Number, char state)
{
	vec3 *Error;
	if(Model_Number<modelVector.size()){
	switch(state)
	{
	case 'P':
		if(modelVector[Model_Number].Normals.size() != 0)
		{
			return &modelVector[Model_Number].Position[0];
		}
		else
		{
			std::cout<<"Model "<<Model_Number<<"'s Normal Vector is empty"<<std::endl;
			(*this).Error=true;
			return Error;
		};
		break;
	case 'p':
		if(modelVector[Model_Number].Normals.size() != 0)
		{
			return &modelVector[Model_Number].Position.back();
		}
		else
		{
			std::cout<<"Model "<<Model_Number<<"'s Normal Vector is empty"<<std::endl;
			(*this).Error=true;
			return Error;
		};
		break;

	case 'N':
		if(modelVector[Model_Number].Position.size() != 0)
		{
			return &modelVector[Model_Number].Normals[0];
		}
		else
		{
			std::cout<<"Model "<<Model_Number<<"'s Position Vector is empty"<<std::endl;
			(*this).Error=true;
			return Error;
		};
	case 'n':
		if(modelVector[Model_Number].Position.size() != 0)
		{
			return &modelVector[Model_Number].Normals.back();
		}
		else
		{
			std::cout<<"Model "<<Model_Number<<"'s Position Vector is empty"<<std::endl;
			(*this).Error=true;
			return Error;
		};

	default:
		std::cout<<"Not using MODEL_XXXXX_VECTOR_POINTER_XXXXX or casting state variable"<<std::endl;
		(*this).Error=true;
		return Error;
	}
   }
   else
   {
	   std::cout<<"Model "<<Model_Number<<" has not been initialized"<<std::endl;
	   (*this).Error=true;
	   return Error;
   }
};
vec2 *Pipeline::GetModelInformation(int Model_Number, short state)
{
	vec2 *Error;
	if(Model_Number<modelVector.size()){
	switch(state)
	{
	case (short)2:
		if(modelVector[Model_Number].Position.size() != 0)
		{
			return &modelVector[Model_Number].UVS[0];
		}
		else
		{
			std::cout<<"Model "<<Model_Number<<"'s Position Vector is empty"<<std::endl;
			(*this).Error=true;
			return Error;
		};
		break;
	case (short)3:
		if(modelVector[Model_Number].Position.size() != 0)
		{
			return &modelVector[Model_Number].UVS.back();
		}
		else
		{
			std::cout<<"Model "<<Model_Number<<"'s Position Vector is empty"<<std::endl;
			(*this).Error=true;
			return Error;
		};
		break;

	default:
		std::cout<<"Not using MODEL_XXXXX_VECTOR_POINTER or casting state variable"<<std::endl;
		(*this).Error=true;
		return Error;
	}
   }
   else
   {
	   std::cout<<"Model "<<Model_Number<<" has not been initialized"<<std::endl;
	   (*this).Error=true;
	   return Error;
   }
};
float Pipeline::GetModelInformation(int Model_Number,long state)
{
	float Error;
	if(Model_Number<modelVector.size()){
	switch(state)
	{
	case 0:
		return (float)modelVector[Model_Number].Normals.size();
		break;

	case 1:
		return (float)modelVector[Model_Number].Position.size();
		break;
	case 2:
		return (float)modelVector[Model_Number].UVS.size();
		break;

	default:
		std::cout<<"Not using MODEL_XXXXX_VECTOR_SIZE or casting state variable"<<std::endl;
		(*this).Error=true;
		return Error;
	}
   }
   else
   {
	   std::cout<<"Model "<<Model_Number<<" has not been initialized"<<std::endl;
	   (*this).Error=true;
	   return Error;
   }
}
//---------------------------------------------------------------------------------------------------------------------------------------
int Pipeline::Load_Texture(const char *filename)
{
	int temp;
	temp = loadBMP_custom(filename);
	TextureVector.push_back(temp);
	return TextureVector.size()-1;
};
int Pipeline::GetTexture(int Texture_Number)
{
   return TextureVector[Texture_Number];
};
//-----------------------------------------------------------------------------------------------------------------------------------
GLuint loadBMP_custom(const char * imagepath)
{

        printf("Reading image %s\n", imagepath);

        // Data read from the header of the BMP file
        unsigned char header[54];
        unsigned int dataPos;
        unsigned int imageSize;
        unsigned int width, height;
        // Actual RGB data
        unsigned char * data;

        // Open the file
        FILE * file = fopen(imagepath,"rb");
        if (!file)                                                          {printf("%s could not be opened. Are you in the right directory ? Don't forget to read the FAQ !\n", imagepath); return 0;}

        // Read the header, i.e. the 54 first bytes

        // If less than 54 byes are read, problem
        if ( fread(header, 1, 54, file)!=54 ){ 
                printf("Not a correct BMP file\n");
                return 0;
        }
        // A BMP files always begins with "BM"
        if ( header[0]!='B' || header[1]!='M' ){
                printf("Not a correct BMP file\n");
                return 0;
        }
        // Make sure this is a 24bpp file
        if ( *(int*)&(header[0x1E])!=0  )         {printf("Not a correct BMP file\n");    return 0;}
        if ( *(int*)&(header[0x1C])!=24 )         {printf("Not a correct BMP file\n");    return 0;}

        // Read the information about the image
        dataPos    = *(int*)&(header[0x0A]);
        imageSize  = *(int*)&(header[0x22]);
        width      = *(int*)&(header[0x12]);
        height     = *(int*)&(header[0x16]);

        // Some BMP files are misformatted, guess missing information
        if (imageSize==0)    imageSize=width*height*3; // 3 : one byte for each Red, Green and Blue component
        if (dataPos==0)      dataPos=54; // The BMP header is done that way

        // Create a buffer
        data = new unsigned char [imageSize];

        // Read the actual data from the file into the buffer
        fread(data,1,imageSize,file);

        // Everything is in memory now, the file wan be closed
        fclose (file);

        // Create one OpenGL texture
        GLuint textureID;
        glGenTextures(1, &textureID);
        
        // "Bind" the newly created texture : all future texture functions will modify this texture
        glBindTexture(GL_TEXTURE_2D, textureID);

        // Give the image to OpenGL
        glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // OpenGL has now copied the data. Free our own version
        delete [] data;

        // Poor filtering, or ...
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 

        // ... nice trilinear filtering.
		glBindTexture(GL_TEXTURE_2D, 0);
        // Return the ID of the texture we just created
        return textureID;
}
void UniformMatrix(char *name, GLuint &program,mat4 Matrix)
{
	int Loc=glGetUniformLocation(program,name);
	
	glUniformMatrix4fv(Loc,1,1,Matrix.M);
};
void UniformMatrix(char *name, GLuint &program,mat3 Matrix)
{
	int Loc=glGetUniformLocation(program,name);
	
	glUniformMatrix3fv(Loc,1,GL_TRUE,Matrix.M);
};
bool LoadModel(MODEL &model,const char* path){
        printf("Loading OBJ file %s...\n", path);

        std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
        std::vector<vec3> temp_vertices; 
        std::vector<vec2> temp_uvs;
        std::vector<vec3> temp_normals;
        FILE * file = fopen(path, "r");
        if( file == NULL ){
                printf("Impossible to open the file ! Are you in the right path ? See Tutorial 1 for details\n");
                return false;
        }
        while( 1 ){
                char lineHeader[100];
                // read the first word of the line
                int res = fscanf(file, "%s", lineHeader);
                if (res == EOF)
                        break; // EOF = End Of File. Quit the loop.

                // else : parse lineHeader
                
                if ( strcmp( lineHeader, "v" ) == 0 ){
                        vec3 vertex;
                        fscanf(file, "%f %f %f\n", &vertex.X, &vertex.Y, &vertex.Z );
                        temp_vertices.push_back(vertex);
                }else if ( strcmp( lineHeader, "vt" ) == 0 ){
                        vec2 uv;
                        fscanf(file, "%f %f\n", &uv.X, &uv.Y );
                        temp_uvs.push_back(uv);
                }else if ( strcmp( lineHeader, "vn" ) == 0 ){
                        vec3 normal;
                        fscanf(file, "%f %f %f\n", &normal.X, &normal.Y, &normal.Z );
                        temp_normals.push_back(normal);
                }else if ( strcmp( lineHeader, "f" ) == 0 ){
                        std::string vertex1, vertex2, vertex3;
                        unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
                        int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
                        if (matches != 9){
                                printf("File can't be read by our simple parser :-( Try exporting with other options\n");
                                return false;
                        }
                        vertexIndices.push_back(vertexIndex[0]);
                        vertexIndices.push_back(vertexIndex[1]);
                        vertexIndices.push_back(vertexIndex[2]);
                        uvIndices    .push_back(uvIndex[0]);
                        uvIndices    .push_back(uvIndex[1]);
                        uvIndices    .push_back(uvIndex[2]);
                        normalIndices.push_back(normalIndex[0]);
                        normalIndices.push_back(normalIndex[1]);
                        normalIndices.push_back(normalIndex[2]);
                }else{
                        // Probably a comment, eat up the rest of the line
                        char stupidBuffer[100];
                        fgets(stupidBuffer, 100, file);
                }

        }

        // For each vertex of each triangle
        for( unsigned int i=0; i<vertexIndices.size(); i++ ){

                // Get the indices of its attributes
                unsigned int vertexIndex = vertexIndices[i];
                unsigned int uvIndex = uvIndices[i];
                unsigned int normalIndex = normalIndices[i];
                
                // Get the attributes thanks to the index
                vec3 vertex = temp_vertices[ vertexIndex-1 ];
                vec2 uv = temp_uvs[ uvIndex-1 ];
                vec3 normal = temp_normals[ normalIndex-1 ];
                
                // Put the attributes in buffers
				model.Position.push_back(vertex);
				model.UVS.push_back(uv);
				model.Normals.push_back(normal);
        
        }

        return true;
}