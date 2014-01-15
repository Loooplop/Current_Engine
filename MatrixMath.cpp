#include "MatrixMath.h"
#include "VectorMath.h"
#include <math.h>
inline float DotProduct(vec3 v1,vec3 v2)
{
  float x=(v1.GetX()*v2.GetX())+(v1.GetY()*v2.GetY())+(v1.GetZ()*v2.GetZ()); 
  return x; 
}       
inline float DotProduct(vec4 v1,vec4 v2)
{
  float x=(v1.GetX()*v2.GetX())+(v1.GetY()*v2.GetY())+(v1.GetZ()*v2.GetZ())+(v1.W*v2.W); 
  return x;        
};
inline vec3 normalize(vec3 v)
{
    float lenght=sqrt(v.GetX()*v.GetX()+v.GetY()*v.GetY()+v.GetZ()*v.GetZ());   
    float x=v.GetX()/lenght;
    float y=v.GetY()/lenght;
    float z=v.GetZ()/lenght;
    return vec3(x,y,z);
};
inline float Abs(float x)
{
  if(x<0)
  {
  return -1*x;       
  }
  else
  {
  return x;    
  };
}
mat2::mat2()
{
            
}
mat2::mat2(float UpperLeft,float UpperRight,float LowerLeft,float LowerRight)
{
    M[0]=UpperLeft;M[1]=UpperRight;
    M[2]=LowerLeft;M[3]=LowerRight;
            
}     
mat2::mat2(float *data)
{
   if(sizeof(data)==sizeof(float)*4)
   {
    M[0]=data[0];M[1]=data[1];
    M[2]=data[2];M[3]=data[3];                              
   }
   else {exit(0);};
                             
};  
mat2::~mat2()
{
             
};
mat2 mat2::GetInverse()
{
    mat2 V(M[3],M[1]*-1,
               M[2]*-1,M[0]);
    float determinant=1/((V.M[0]*V.M[3])-(V.M[1]*V.M[2]));
    return V*determinant;
};
mat2 mat2::operator+ (const mat2 &other)
{
    return mat2(M[0]+other.M[0],M[1]+other.M[1],M[2]+other.M[2],M[3]+other.M[3]);
};
mat2 mat2::operator- (const mat2 &other)
{
    return mat2(M[0]-other.M[0],M[1]-other.M[1],M[2]-other.M[2],M[3]-other.M[3]);
};
mat2 mat2::operator* (const mat2 &other)
{
    float UpperLeft=M[0]*other.M[0]+M[1]*other.M[2];
    float UpperRight=M[0]*other.M[1]+M[1]*other.M[3];
    float LowerLeft=M[2]*other.M[0]+M[3]*other.M[2];
    float LowerRight=M[2]*other.M[1]+M[3]*other.M[3];
    return mat2(UpperLeft,UpperRight,LowerLeft,LowerRight);
};
mat2 mat2::operator* (const float &other)
{
   return mat2(M[0]*other,M[1]*other,M[2]*other,M[3]*other);        
};
mat2 mat2::operator/ (const mat2 &other)
{      
    mat2 temp=other;   
    return mat2(M[0],M[1],M[2],M[3])*temp.GetInverse();
};
mat2 mat2::operator/ (const float &other)
{      
    return mat2(M[0]/other,M[1]/other,M[2]/other,M[3]/other);
};
float *mat2::GetValues()
{
    return M;      
};
std::ostream& operator<< (std::ostream &out, mat2 &Matrix)
{
    out<<"|"<<Matrix.M[0]<<" "<<Matrix.M[1]<<"|"<<std::endl<<"|"<<Matrix.M[2]<<" "<<Matrix.M[3]<<"|"<<std::endl;
    return out;
}
//----------------------------------------------------------------------------------------------------------------------------------------------
 mat3::mat3(float UpperLeft,float UpperCenter,float UpperRight,float MiddleLeft,float MiddleCenter,float MiddleRight,float LowerLeft,float LowerCenter,float LowerRight)
 {
     M[0]=UpperLeft;M[1]=UpperCenter;M[2]=UpperRight;
     M[3]=MiddleLeft;M[4]=MiddleCenter;M[5]=MiddleRight;
     M[6]=LowerLeft;M[7]=LowerCenter;M[8]=LowerRight;             
 };
 mat3::mat3(float *data)
{
   if(sizeof(data)==sizeof(float)*9)
   {
    M[0]=data[0];M[1]=data[1];M[2]=data[2];
    M[3]=data[3];M[4]=data[4];M[5]=data[5];
    M[6]=data[6];M[7]=data[7];M[8]=data[8];                              
   }
   else {exit(0);};
                             
};  
 mat3::mat3()
 {
             
 };     
mat3::~mat3()
{
             
};      
mat3 mat3::operator+ (const mat3 &other)
{
       return mat3(M[0]+other.M[0],M[1]+other.M[1],M[2]+other.M[2],
                         M[3]+other.M[3],M[4]+other.M[4],M[5]+other.M[5],
                         M[6]+other.M[6],M[7]+other.M[7],M[8]+other.M[8]);    
};
mat3 mat3::operator- (const mat3 &other)
{
       return mat3(M[0]-other.M[0],M[1]-other.M[1],M[2]-other.M[2],
                         M[3]-other.M[3],M[4]-other.M[4],M[5]-other.M[5],
                         M[6]-other.M[6],M[7]-other.M[7],M[8]-other.M[8]);   
};
mat3 mat3::operator* (const mat3 &other)
{
         vec3 FstRow(M[0],M[1],M[2]);
         vec3 SstRow(M[3],M[4],M[5]);
         vec3 TstRow(M[6],M[7],M[8]);
         
         vec3 FstColumn(other.M[0],
                            other.M[3],
                            other.M[6]);
         vec3 SstColumn(other.M[1],
                            other.M[4],
                            other.M[7]);
         vec3 TstColumn(other.M[2],
                            other.M[5],
                            other.M[8]);
         return mat3(DotProduct(FstRow,FstColumn),DotProduct(FstRow,SstColumn),DotProduct(FstRow,TstColumn),
                           DotProduct(SstRow,FstColumn),DotProduct(SstRow,SstColumn),DotProduct(SstRow,TstColumn),
                           DotProduct(TstRow,FstColumn),DotProduct(TstRow,SstColumn),DotProduct(TstRow,TstColumn));
         
};
mat3 mat3::operator* (const float &other)
{
       return mat3(M[0]*other,M[1]*other,M[2]*other,
                         M[3]*other,M[4]*other,M[5]*other,
                         M[6]*other,M[7]*other,M[8]*other);      
};
mat3 mat3::operator/ (mat3 &other)
{   
           mat3 F=mat3(M[0],M[1],M[2],M[3],M[4],M[5],M[6],M[7],M[8])*other.GetInverse();
           for(int x=0;x<9;x++)
           {
              if(Abs(F.M[x])>0.000000000009&&Abs(F.M[x])<0.00000009)
              {
                 F.M[x]=0;                   
              };
           };
           return F;
};
mat3 mat3::operator/ (const float &other)
{
       return mat3(M[0]/other,M[1]/other,M[2]/other,
                         M[3]/other,M[4]/other,M[5]/other,
                         M[6]/other,M[7]/other,M[8]/other);    
};
/*
  Values= 1 2 3 4 5 6 7 8 9
  [ Values[0] Values[1] Values[2] ] = [ 1 2 3 ]
  [ Values[3] Values[4] Values[5] ] = [ 4 5 6 ]
  [ Values[6] Values[7] Values[8] ] = [ 7 8 9 ]
  */ 
mat3 mat3::GetInverse()
{
  double det=M[0]*(M[8]*M[4]-M[7]*M[5])-M[3]*(M[8]*M[1]-M[7]*M[2])+M[6]*(M[5]*M[1]-M[4]*M[2]);
  if(det==0)
  {
  std::cout<<"Yeah well, you are fucked"<<std::endl;
  }
  mat3 Temp((M[8]*M[4])-(M[7]*M[5]),-((M[8]*M[1])-(M[7]*M[2])),(M[5]*M[1])-(M[4]*M[2]),
                  -((M[8]*M[3])-(M[6]*M[5])),   (M[8]*M[0])-(M[6]*M[2]),  -((M[5]*M[0])-(M[3]*M[2])),
                  (M[7]*M[3])-(M[6]*M[4]) , -((M[7]*M[0])-(M[6]*M[1])),   (M[4]*M[0])-(M[3]*M[1]));
  float F_det=1/det;
  return Temp*F_det;
};
mat3 mat3::GetTranspose()
{
	return mat3(M[0],M[3],M[6],
		        M[1],M[4],M[7],
				M[2],M[5],M[8]);
}
std::ostream& operator<< (std::ostream &out, mat3 &Matrix)
{
   out<<"_______"<<std::endl<<
        "|"<<Matrix.M[0]<<" "<<Matrix.M[1]<<" "<<Matrix.M[2]<< "|"<<std::endl<<
        "|"<<Matrix.M[3]<<" "<<Matrix.M[4]<<" "<<Matrix.M[5]<< "|"<<std::endl<<
        "|"<<Matrix.M[6]<<" "<<Matrix.M[7]<<" "<<Matrix.M[8]<< "|"<<std::endl;
      return out;           
};
//--------------------------------------------------------------------------------------------------------
 mat4::mat4(float UpperUpperLeftLeft,float UpperUpperLeft,float UpperUpperRight,float UpperUpperRightRight,
      float UpperLeftLeft,float UpperLeft,float UpperRight,float UpperRightRight,
      float LowerLeftLeft,float LowerLeft,float LowerRight,float LowerRightRight,
      float LowerLowerLeftLeft,float LowerLowerLeft,float LowerLowerRight,float LowerLowerRightRight)
{
      M[0] = UpperUpperLeftLeft;M[1] = UpperUpperLeft;M[2] = UpperUpperRight;M[3] = UpperUpperRightRight;
      M[4] = UpperLeftLeft;     M[5] = UpperLeft;     M[6] = UpperRight;     M[7] = UpperRightRight;
      M[8] = LowerLeftLeft;     M[9] = LowerLeft;     M[10] = LowerRight;     M[11] = LowerRightRight;
      M[12] = LowerLowerLeftLeft;M[13] = LowerLowerLeft;M[14] = LowerLowerRight;M[15] = LowerLowerRightRight;    
};
 mat4::mat4(float *data)
 {
      
      M[0]=data[0];M[1]=data[1];M[2]=data[2];M[3]=data[3];
      M[4]=data[4];M[5]=data[5];M[6]=data[6];M[7]=data[7];
      M[8]=data[8];M[9]=data[9];M[10]=data[10];M[11]=data[11]; 
      M[12]=data[12];M[13]=data[13];M[14]=data[14];M[15]=data[15];   
 };
 mat4::mat4()
 {
       
 };     
mat4::~mat4()
{
       
};      
mat4 mat4::operator+ (const mat4 &other)
{
     return mat4(M[0]+other.M[0],M[1]+other.M[1],M[2]+other.M[2],M[3]+other.M[3],
                 M[4]+other.M[4],M[5]+other.M[5],M[6]+other.M[6],M[7]+other.M[7],
                 M[8]+other.M[8],M[9]+other.M[9],M[10]+other.M[10],M[11]+other.M[11],
                 M[12]+other.M[12],M[13]+other.M[13],M[14]+other.M[14],M[15]+other.M[15]);
};
mat4 mat4::operator* (const mat4 &other)
{
    vec4 fr(M[0],M[1],M[2],M[3]);
    vec4 sr(M[4],M[5],M[6],M[7]);
    vec4 tr(M[8],M[9],M[10],M[11]);
    vec4 fur(M[12],M[13],M[14],M[15]);
    
    vec4 fc(other.M[0],other.M[4],other.M[8],other.M[12]);
    vec4 sc(other.M[1],other.M[5],other.M[9],other.M[13]);
    vec4 tc(other.M[2],other.M[6],other.M[10],other.M[14]);
    vec4 fuc(other.M[3],other.M[7],other.M[11],other.M[15]);
    return mat4(DotProduct(fr,fc),DotProduct(fr,sc),DotProduct(fr,tc),DotProduct(fr,fuc),
                DotProduct(sr,fc),DotProduct(sr,sc),DotProduct(sr,tc),DotProduct(sr,fuc),
                DotProduct(tr,fc),DotProduct(tr,sc),DotProduct(tr,tc),DotProduct(tr,fuc),
                DotProduct(fur,fc),DotProduct(fur,sc),DotProduct(fur,tc),DotProduct(fur,fuc));
};
mat4 mat4::operator* (const float &other)
{
     return mat4(M[0]*other,M[1]*other,M[2]*other,M[3]*other,
                 M[4]*other,M[5]*other,M[6]*other,M[7]*other,
                 M[8]*other,M[9]*other,M[10]*other,M[11]*other,
                 M[12]*other,M[13]*other,M[14]*other,M[15]*other); 
};
mat4 mat4::operator/ (mat4 &other)
{
     mat4 F=mat4(M[0],M[1],M[2],M[3],M[4],M[5],M[6],M[7],M[8],M[9],M[10],M[11],M[12],M[13],M[14],M[15])*other.GetInverse();
           return F;
};
mat4 mat4::operator/ (const float &other)
{
     return mat4(M[0]/other,M[1]/other,M[2]/other,M[3]/other,
                 M[4]/other,M[5]/other,M[6]/other,M[7]/other,
                 M[8]/other,M[9]/other,M[10]/other,M[11]/other,
                 M[12]/other,M[13]/other,M[14]/other,M[15]/other); 
};
mat4 mat4::operator- (const mat4 &other)
{
    return mat4(M[0]-other.M[0],M[1]-other.M[1],M[2]-other.M[2],M[3]-other.M[3],
                 M[4]-other.M[4],M[5]-other.M[5],M[6]-other.M[6],M[7]-other.M[7],
                 M[8]-other.M[8],M[9]-other.M[9],M[10]-other.M[10],M[11]-other.M[11],
                 M[12]-other.M[12],M[13]-other.M[13],M[14]-other.M[14],M[15]-other.M[15]);
};
mat4 mat4::GetInverse()
{
          float S0 = M[0] * M[5] - M[1] * M[4];
        float S1 = M[0] * M[6] - M[2] * M[4];
        float S2 = M[0] * M[7] - M[3] * M[4];
        float S3 = M[1] * M[6] - M[2] * M[5];
        float S4 = M[1] * M[7] - M[3] * M[5];
        float S5 = M[2] * M[7] - M[3] * M[6];
 
        float C5 = M[10] * M[15] - M[11] * M[14];
        float C4 = M[9] * M[15] - M[11] * M[13];
        float C3 = M[9] * M[14] - M[10] * M[13];
        float C2 = M[8] * M[15] - M[11] * M[12];
        float C1 = M[8] * M[14] - M[10] * M[12];
        float C0 = M[8] * M[13] - M[9] * M[12];
 
        // If deterMinant equals 0, there is no inverse
        float det = S0 * C5 - S1 * C4 + S2 * C3 + S3 * C2 - S4 * C1 + S5 * C0;
 
        // CoMpute adjugate Matrix
        mat4 inverse =mat4(
                 M[5] * C5  - M[6] * C4  + M[7] * C3,  -M[1] * C5 + M[2] * C4  - M[3] * C3,
                 M[13] * S5 - M[14] * S4 + M[15] * S3, -M[9] * S5 + M[10] * S4 - M[11] * S3,
 
                -M[4] * C5  + M[6] * C2  - M[7] * C1,   M[0] * C5 - M[2] * C2  + M[3] * C1,
                -M[12] * S5 + M[14] * S2 - M[15] * S1,  M[8] * S5 - M[10] * S2 + M[11] * S1,
 
                 M[4] * C4  - M[5] * C2  + M[7] * C0,  -M[0] * C4 + M[1] * C2  - M[3] * C0,
                 M[12] * S4 - M[13] * S2 + M[15] * S0, -M[8] * S4 + M[9] * S2  - M[11] * S0,
 
                -M[4] * C3  + M[5] * C1  - M[6] * C0,   M[0] * C3 - M[1] * C1  + M[2] * C0,
                -M[12] * S3 + M[13] * S1 - M[14] * S0,  M[8] * S3 - M[9] * S1  + M[10] * S0 )*(1 / det);
                return inverse;
};
mat4 mat4::GetTranspose()
{
   return mat4(M[0],M[4],M[8],M[12],
               M[1],M[5],M[9],M[13],
               M[2],M[6],M[10],M[14],
               M[3],M[7],M[11],M[15]);   
};
vec4 mat4::operator* (const vec4 &other)
{
     vec4 fr(M[0],M[1],M[2],M[3]);
    vec4 sr(M[4],M[5],M[6],M[7]);
    vec4 tr(M[8],M[9],M[10],M[11]);
    vec4 fur(M[12],M[13],M[14],M[15]);
    return  vec4(DotProduct(fr,other),DotProduct(sr,other),DotProduct(tr,other),DotProduct(fur,other));  
};
std::ostream& operator<< (std::ostream &out, mat4 &Matrix)
{
       out<<"_________"<<std::endl<<
        "|"<<Matrix.M[0]<<" "<<Matrix.M[1]<<" "<<Matrix.M[2]<<" "<<Matrix.M[3]<< "|"<<std::endl<<
        "|"<<Matrix.M[4]<<" "<<Matrix.M[5]<<" "<<Matrix.M[6]<<" "<<Matrix.M[7]<< "|"<<std::endl<<
        "|"<<Matrix.M[8]<<" "<<Matrix.M[9]<<" "<<Matrix.M[10]<<" "<<Matrix.M[11]<< "|"<<std::endl<<
        "|"<<Matrix.M[12]<<" "<<Matrix.M[13]<<" "<<Matrix.M[14]<<" "<<Matrix.M[15]<< "|"<<std::endl;
      return out;
};