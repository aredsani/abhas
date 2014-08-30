#include <GL/glew.h>
#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <glm/glm.hpp>
#include <vector>
#include <stdio.h>
#include <cstring>
#include <string>
#include <vector>
#include <iostream> 
using namespace std;
#include<objloader.hpp>
#include<shapes.hpp>
#include<texture.hpp>
#include<shader.hpp>

/* Global variables */
char title[] = "3D Shapes with animation";
GLfloat anglePyramid = 0.0f;  // Rotational angle for pyramid [NEW]
GLfloat angleCube = 0.0f;     // Rotational angle for cube [NEW]
int refreshMills = 15;        // refresh interval in milliseconds [NEW]


//GLuint programID= LoadShaders("TransformVertexShader.vertexshader","TexturefragmentShader.fragmentshader");
//GLuint Texture= loadBMP_custom("uvtemplate.bmp");
//GLuint TextureID= glGetUniformLocation(programID,"myTextureSampler");
 
#ifndef _TPass_
GLuint PprogramID;
GLuint PTexture;
GLuint PTextureID;
GLuint Puvbuffer;
GLuint PMatrixID ;
#define _TPass_
#endif

#ifndef _OBJfileRead_
vector<vertex> Eindex;
vector<vertex> UVindex;
vector<vertex> Nindex;
vector<glm::vec2> out_uvs;
#define _OBJfileRead_
#endif



/* Initialize OpenGL Graphics */
void initGL() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   glClearDepth(1.0f);                   // Set background depth to farthest
   glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
   glEnable(GL_TEXTURE_2D);
   glDepthFunc(GL_LESS);    // Set the type of depth-test
   glEnable(GL_CULL_FACE);
   glShadeModel(GL_SMOOTH);   // Enable smooth shading
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections




}
 

 
void obj_display(){

	//cout<<"fsjfa"<<endl;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
	glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix
	
	glLoadIdentity();                 // Reset the model-view matrix
	
	/*glUseProgram(PprogramID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, PTexture);
	glUniform1i(PTextureID,0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, Puvbuffer);
	glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,0,(void*)0);
	
	//glUniformMatrix4fv(PMatrixID, 1, GL_FALSE, &MVP[0][0]);
	*/
	
	glTranslatef(0.0f, 0.0f, -30.0f);  // Move right and into the screen
	glRotatef(angleCube, 1.0f, 1.0f, 1.0f);  // Rotate about (1,1,1)-axis
	/*glBegin(GL_TRIANGLES);
	for(unsigned int i=0;i<Eindex.size();i++){
		glColor3f(0.0f,1.0f,0.0f);
		glVertex3f(Eindex[i].position.x,Eindex[i].position.y, Eindex[i].position.z);
		
	}
	glEnd();*/
	/*glEnable( GL_TEXTURE_2D );
	glBindTexture( GL_TEXTURE_2D, PTexture);

	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

	glutSolidSphere(10,50,50);*/
	
	GLUquadric *qobj = gluNewQuadric(); 

	gluQuadricTexture(qobj,GL_TRUE); 

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,PTexture);

	gluSphere(qobj,10,50,50); 

	gluDeleteQuadric(qobj); 
	glDisable(GL_TEXTURE_2D);

	glDisable(GL_TEXTURE_2D);
	
	
	glutSwapBuffers();
	angleCube -= 0.15f;
	
	glDisableVertexAttribArray(1);
}
/* Called back when timer expired [NEW] */
void timer(int value) {
   glutPostRedisplay();      // Post re-paint request to activate display()
   glutTimerFunc(refreshMills, timer, 0); // next timer call milliseconds later
}
 
/* Handler for window re-size event. Called back when the window first appears and
   whenever the window is re-sized with its new width and height */
void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
   // Compute aspect ratio of the new window
   if (height == 0) height = 1;                // To prevent divide by 0
   GLfloat aspect = (GLfloat)width / (GLfloat)height;
 
   // Set the viewport to cover the new window
   glViewport(0, 0, width, height);
 
   // Set the aspect ratio of the clipping volume to match the viewport
   glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
   glLoadIdentity();             // Reset
   // Enable perspective projection with fovy, aspect, zNear and zFar
   gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}
 
/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv) {
	//vector<vertex> edges,ac,ad;
	
	bool a = loadOBJ("cube.obj",Eindex,UVindex,Nindex);
	for(unsigned int i=0;i<UVindex.size();i++){
		glm::vec2 temp1;
		temp1.x = UVindex[i].position.x;
		temp1.y = UVindex[i].position.y;
		out_uvs.push_back(temp1);
	}


	glutInit(&argc, argv);            // Initialize GLUT
	glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
	glutInitWindowSize(640, 480);   // Set the window's initial width & height
	glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
	glutCreateWindow(title);          // Create window with the given title
	//glClearColor(0.0f, 0.0f ,0.4f , 0.0f);
	glewInit();
	printf("c1\n");
	GLuint programID=LoadShaders("TransformVertexShader.vertexshader","TextureFragmentShader.fragmentshader");
	//GLuint Texture= loadBMP_custom("lol.bmp");
	GLuint Texture = loadDDS("uvmap.DDS");
	
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");

	GLuint TextureID= glGetUniformLocation(programID, "myTextureSampler");
	
	GLuint uvbuffer;
	PTexture = Texture;
	PTextureID = TextureID;
	PprogramID = programID;
	Puvbuffer = uvbuffer;
	PMatrixID= MatrixID;
	//l
	glutDisplayFunc(obj_display);       // Register callback handler for window re-paint event
	//glClearColor(0.0f, 0.0f ,0.4f , 0.0f);
	glutReshapeFunc(reshape);       // Register callback handler for window re-size event
	initGL();  // Our own OpenGL initialization                  
	
	glGenBuffers (1,&uvbuffer);
	glBindBuffer (GL_ARRAY_BUFFER, uvbuffer);
	glBufferData (GL_ARRAY_BUFFER, out_uvs.size()*sizeof(glm::vec2), &out_uvs[0], GL_STATIC_DRAW);
	glutTimerFunc(0, timer, 0);     // First timer call immediately
	

	glutMainLoop();                 // Enter the infinite event-processing loop
	
	glDeleteBuffers(1, &uvbuffer);
	glDeleteProgram(programID);
	glDeleteTextures(1, &TextureID);
	
	return 0;
}
